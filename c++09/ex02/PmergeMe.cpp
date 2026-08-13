#include "PmergeMe.hpp"
#include <algorithm>

// Everything in this anonymous namespace is a private implementation detail of
// the Ford-Johnson sort: none of it is visible outside this translation unit.
namespace
{
	// Returns, for a chain of `pairCount` pending elements, the order in which they
	// should be binary-inserted (as 0-based indices into the pend[] array, excluding
	// index 0 which is always inserted for free - see mergeInsertionSort below).
	// Ford-Johnson uses Jacobsthal numbers (1, 3, 5, 11, 21, 43, ...) to group the
	// insertions: within each group the indices are visited from largest to
	// smallest. This ordering is what gives the algorithm its near-optimal
	// comparison count; correctness does NOT depend on this exact order (the bound
	// tracking below stays valid for any order) - only the comparison count does.
	std::vector<size_t> jacobsthalInsertionOrder(size_t pairCount)
	{
		std::vector<size_t> order;
		if (pairCount <= 1)
			return order;

		// Build Jacobsthal numbers J(n) = J(n-1) + 2*J(n-2) until every rank up to
		// pairCount is covered. boundaries[0] = 1 represents rank 1 (pend[0]),
		// which is handled specially by the caller and never appears in `order`.
		std::vector<size_t> boundaries;
		boundaries.push_back(1);
		size_t prev2 = 0;
		size_t prev1 = 1;
		while (boundaries.back() < pairCount)
		{
			size_t next = prev1 + 2 * prev2;
			prev2 = prev1;
			prev1 = next;
			boundaries.push_back(next);
		}

		size_t lastUpper = 1;
		for (size_t b = 1; b < boundaries.size(); ++b)
		{
			size_t upper = boundaries[b];
			if (upper > pairCount)
				upper = pairCount;
			for (size_t rank = upper; rank > lastUpper; --rank)
				order.push_back(rank - 1); // 1-based rank -> 0-based pend index
			lastUpper = upper;
			if (lastUpper >= pairCount)
				break;
		}
		return order;
	}

	// Sorts `values` and additionally reports, via `outPermutation`, where each
	// original index ended up: outPermutation[i] is the position of values[i] in
	// the returned vector. This local, per-call permutation is what lets a level
	// of recursion find its own "big" elements again after they come back sorted,
	// without needing to smuggle bookkeeping data through several nested calls.
	std::vector<int> mergeInsertionSort(const std::vector<int>& values,
		std::vector<size_t>& outPermutation)
	{
		size_t n = values.size();
		outPermutation.assign(n, 0);
		if (n < 2)
			return values; // 0 or 1 elements: already sorted, permutation is trivial

		// If there's an odd one out, set it aside; it gets inserted last, after
		// everything else has already been merged into one sorted chain.
		bool hasStraggler = (n % 2 == 1);
		size_t pairCount = hasStraggler ? (n - 1) / 2 : n / 2;
		int straggler = hasStraggler ? values[n - 1] : 0;
		size_t stragglerOriginalIdx = n - 1;

		// Step 1 - pairing: compare elements two at a time. The smaller of each
		// pair ("pend") is set aside for later insertion; the larger ("big")
		// continues into the recursive sort below. We remember each element's
		// original index so we can report the final permutation at the end.
		std::vector<int> pend(pairCount), bigs(pairCount);
		std::vector<size_t> pendOriginalIdx(pairCount), bigsOriginalIdx(pairCount);
		for (size_t i = 0; i < pairCount; ++i)
		{
			int a = values[2 * i];
			int b = values[2 * i + 1];
			if (a < b)
			{
				pend[i] = a;
				pendOriginalIdx[i] = 2 * i;
				bigs[i] = b;
				bigsOriginalIdx[i] = 2 * i + 1;
			}
			else
			{
				pend[i] = b;
				pendOriginalIdx[i] = 2 * i + 1;
				bigs[i] = a;
				bigsOriginalIdx[i] = 2 * i;
			}
		}

		// Step 2 - recursion: sort the larger halves the same way. This is the
		// "merge" half of merge-insertion: it recursively builds a fully sorted
		// main chain out of just the bigs, ignoring the pends entirely for now.
		std::vector<size_t> bigsPermutation;
		std::vector<int> chain = mergeInsertionSort(bigs, bigsPermutation);

		// finalPos[k] tracks, for each ORIGINAL index k of `values`, its current
		// position inside `chain` once that element has been placed. Bigs are
		// already placed (chain starts out as the sorted bigs); pends and the
		// straggler become "resolved" one at a time as we insert them below.
		std::vector<size_t> finalPos(n, 0);
		std::vector<bool> resolved(n, false);
		for (size_t i = 0; i < pairCount; ++i)
		{
			finalPos[bigsOriginalIdx[i]] = bigsPermutation[i];
			resolved[bigsOriginalIdx[i]] = true;
		}

		// Ford-Johnson's insertion order (pend[0] first, then Jacobsthal order) is
		// defined in terms of RANK within the sorted chain - i.e. rank 0 is the
		// pend[] element whose partner ended up smallest - not the original pairing
		// order, since the recursive sort can reorder the bigs arbitrarily.
		// rankToIndex[r] converts a rank back to the pairing index i that owns it.
		std::vector<size_t> rankToIndex(pairCount);
		for (size_t i = 0; i < pairCount; ++i)
			rankToIndex[bigsPermutation[i]] = i;

		// Step 3 - free insertion: the pend paired with the smallest big (rank 0)
		// is guaranteed smaller than every element in the chain, so it can be
		// placed at the very front with zero comparisons.
		size_t firstIndex = rankToIndex[0];
		chain.insert(chain.begin(), pend[firstIndex]);
		for (size_t k = 0; k < n; ++k)
			if (resolved[k])
				finalPos[k] += 1; // every already-placed element shifted right by one
		finalPos[pendOriginalIdx[firstIndex]] = 0;
		resolved[pendOriginalIdx[firstIndex]] = true;

		// Step 4 - bounded binary insertion of the rest, in Jacobsthal order.
		// pend[i] is always smaller than its own big, and that big's current
		// position is finalPos[bigsOriginalIdx[i]], so pend[i] can only belong
		// somewhere strictly before that index - this bound is what keeps every
		// binary search from having to scan the whole (growing) chain.
		std::vector<size_t> order = jacobsthalInsertionOrder(pairCount);
		for (size_t idx = 0; idx < order.size(); ++idx)
		{
			size_t i = rankToIndex[order[idx]];
			size_t bound = finalPos[bigsOriginalIdx[i]];
			std::vector<int>::iterator rangeEnd = chain.begin() + bound;
			std::vector<int>::iterator pos = std::upper_bound(chain.begin(), rangeEnd, pend[i]);
			size_t insertedAt = static_cast<size_t>(pos - chain.begin());
			chain.insert(pos, pend[i]);

			for (size_t k = 0; k < n; ++k)
				if (resolved[k] && finalPos[k] >= insertedAt)
					finalPos[k] += 1; // anything at/after the insertion point shifted right
			finalPos[pendOriginalIdx[i]] = insertedAt;
			resolved[pendOriginalIdx[i]] = true;
		}

		// Step 5 - the leftover odd element (if any) has no computed bound, so it
		// is binary-inserted last against the now fully-merged chain.
		if (hasStraggler)
		{
			std::vector<int>::iterator pos = std::upper_bound(chain.begin(), chain.end(), straggler);
			size_t insertedAt = static_cast<size_t>(pos - chain.begin());
			chain.insert(pos, straggler);

			for (size_t k = 0; k < n; ++k)
				if (resolved[k] && finalPos[k] >= insertedAt)
					finalPos[k] += 1;
			finalPos[stragglerOriginalIdx] = insertedAt;
			resolved[stragglerOriginalIdx] = true;
		}

		outPermutation = finalPos;
		return chain;
	}
}

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe&) {}

PmergeMe& PmergeMe::operator=(const PmergeMe&)
{
	return *this;
}

PmergeMe::~PmergeMe() {}

void PmergeMe::fordJohnsonSort(std::vector<int>& values)
{
	std::vector<size_t> permutation; // discarded: the top-level caller only wants the values
	values = mergeInsertionSort(values, permutation);
}
