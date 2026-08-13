#ifndef PMERGEME_TPP
#define PMERGEME_TPP

// Works for any container of int offering begin()/end()/assign() (vector, deque,
// list, ...): copy its elements into a plain vector, run the real algorithm once
// there, then write the sorted values back. This is why std::list can be sorted
// with the very same Ford-Johnson code as std::deque despite not having random
// access iterators - the algorithm never sees the caller's container directly.
template <typename Container>
void PmergeMe::sort(Container& container) const
{
	std::vector<int> working(container.begin(), container.end());
	fordJohnsonSort(working);
	container.assign(working.begin(), working.end());
}

#endif
