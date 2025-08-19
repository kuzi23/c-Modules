#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

// Main to test ScavTrap too
int main() {
	ScavTrap scavTrap("ScavTrap");
	ScavTrap scavTrap2(scavTrap);
	ScavTrap scavTrap3 = scavTrap;

	// ClapTrap clapTrap("ClapTrap");
	// ClapTrap clapTrap2(clapTrap);
	// ClapTrap clapTrap3 = clapTrap;

	// clapTrap.attack("Face McShooty");
	// clapTrap.takeDamage(5);
	// clapTrap.beRepaired(5);

	scavTrap.attack("Face McShooty");
	for (int i = 0; i < 10; i++)
		scavTrap.attack("Face McShooty");
	for (int i = 0; i < 10; i++)
		scavTrap.takeDamage(25);
	scavTrap.beRepaired(5);

	scavTrap.guardGate();

	return 0;
}
