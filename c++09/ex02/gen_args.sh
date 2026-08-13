#!/bin/bash
# Prints N random positive integers separated by spaces (default 3000), e.g.:
#   ./PmergeMe $(./gen_args.sh 3000)
count=${1:-3000}
for ((i = 0; i < count; i++)); do
	echo -n "$((RANDOM % 100000 + 1)) "
done
echo
