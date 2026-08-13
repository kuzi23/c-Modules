#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <cstddef>

// PmergeMe is not itself a template: only the container-adapting entry point
// (sort<Container>) is templated, so it can accept std::deque<int> or
// std::list<int>. The actual Ford-Johnson (merge-insertion) algorithm is plain,
// non-template code that always works on a std::vector<int> internally - only
// the initial copy-in and final copy-out are container-specific, which keeps the
// interesting algorithm in one place instead of duplicated per container.
class PmergeMe
{
	public:
		PmergeMe();
		PmergeMe(const PmergeMe& other);
		PmergeMe& operator=(const PmergeMe& other);
		~PmergeMe();

		template <typename Container>
		void sort(Container& container) const;

	private:
		static void fordJohnsonSort(std::vector<int>& values);
};

#include "PmergeMe.tpp"

#endif
