#include "ClapTrap.hpp"
#include "FragTrap.hpp"

// Main to test FragTrap too
int main() {

	FragTrap fragTrap("FragTrap");
	FragTrap fragTrap2(fragTrap);
	FragTrap fragTrap3 = fragTrap;

	fragTrap.attack("Face McShooty");
	// for (int i = 0; i < 10; i++)
		fragTrap.attack("Face McShooty");
	// for (int i = 0; i < 10; i++)
		fragTrap.takeDamage(25);
	fragTrap.beRepaired(5);
	fragTrap.highFivesGuys();

	return 0;
}
