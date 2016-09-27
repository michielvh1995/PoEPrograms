// ChesterCalculator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <algorithm>



float EnduReduc(int charges);
float Delem(float res, int damage);
float PReduc(int armour, float dmg, float base);
void Jurgen();
void physReduc();

int _tmain(int argc, _TCHAR* argv[])
{
	int option;
	std::cout << "Choose your option: \n";
	std::cout << "(1) Jurgen's phys to elem dmg calculator\n";
	std::cout << "(2) Physical dmg reduction calculator\n";
	std::cin >> option;

	if (option == 1)
		Jurgen();
	else if (option == 2)
		physReduc();

	return 0;
}


void Jurgen()
{
	int armour, charges, dmg;
	float res, perOf, perAs, deter;
	float fperOf, fperAs, fres, fdeter;

	std::cout << "Armour \n";
	std::cin >> armour;
	std::cout << "Endurance Charge Count? \n";
	std::cin >> charges;
	std::cout << "Elemental Resistance? \n";
	std::cin >> res;
	std::cout << "Elemental damage taken? \n";
	std::cin >> dmg;
	std::cout << "x% of elemental damage taken, for y% of its value. \n";
	std::cin >> perOf >> perAs;
	std::cout << "How much % more armour from determination? \n";
	std::cin >> deter;

	fdeter = 1 + deter / 100;
	fperAs = perAs / 100;
	fperOf = perOf / 100;
	fres = 1 - res / 100;

	float elemDmg = Delem(fres, dmg*fperOf);
	float physDmg = dmg*fperOf*fperAs * PReduc(armour *fdeter, dmg*fperOf*fperAs, EnduReduc(charges));

	std::cout << "\n \nElemental:" << elemDmg << " physical: " << physDmg << "\n";
	std::cout << "Total dmg reduction: " << dmg - elemDmg - physDmg << "\n \n";

	std::cout << "Continue (y/y)? \n";
	std::cin >> fres;
}

void physReduc()
{
	int armour, charges, dmg;
	float deter, fdeter;

	std::cout << "Armour \n";
	std::cin >> armour;
	std::cout << "Endurance Charge Count? \n";
	std::cin >> charges;
	std::cout << "Physical damage taken? \n";
	std::cin >> dmg;
	std::cout << "How much % more armour from determination? \n";
	std::cin >> deter;

	fdeter = 1 + deter / 100;

	float physDmg = dmg * PReduc(armour *fdeter, dmg, EnduReduc(charges));

	std::cout << "Physical damage taken: " << physDmg << "\n";
	std::cout << "Total dmg reduction: " << dmg - physDmg << "\n \n";

	std::cout << "Continue (y/y)? \n";
	std::cin >> deter;
}

// Calculate the effectiveness of endurance charges
float EnduReduc(int charges)
{
	return charges * 0.04;
}

// Calculate elemental damage taken
float Delem(float res, int damage)
{
	return res*damage;
}

// Calculate how much armour reduces phys dmg
float ArmourReduc(float armour, float dmg)
{
	return armour / (armour + 10 * dmg);
}

float PReduc(int armour, float dmg, float base)
{
	float max = 0.90;
	float total = base + ArmourReduc(armour, dmg);
	return 1 - std::min(max, total);
}

