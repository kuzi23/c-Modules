#include "ClapTrap.hpp"

int main() {
	ClapTrap clapTrap("ClapTrap");
	ClapTrap clapTrap2(clapTrap);
	ClapTrap clapTrap3 = clapTrap;

	clapTrap.attack("Face McShooty");
	clapTrap.takeDamage(5);
	clapTrap.beRepaired(5);

	return 0;
}
