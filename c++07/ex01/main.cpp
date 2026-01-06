#include "iter.hpp"

void printInt(int n) {
    std::cout << n << " ";
}

int main(int argc, char **argv) 
{
    (void) argc;
    (void) argv;
    int arr[] = {1, 2, 3, 4, 5};
    iter(arr, 5, printInt);
    std::cout << std::endl;
    return 0;
}
