#include "Player.h"
#include "Log.h"
#include <iostream>

Player::Player(int Health, int AttPower, int Defense, std::string Name) : Character(Health, AttPower, Defense, Name)
{
}

Actions Player::ChooseAction()
{
	int input;

	while (true) {
		Log::LogMessage(LOG_DEFAULT, "Choose your Action - 1: Attack 2 : Parry 3 : Defend");
		//std::cout << "Choose your Action - 1: Attack 2: Parry 3: Defend" << std::endl;
		std::cin >> input;

		if (std::cin.fail() || input < 0 || input >3) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			Log::LogMessage(LOG_ERROR, "Invalid Input. Should be 1, 2 or 3");
			//std::cout << "Invalid Input. Should be 1, 2 or 3" << std::endl;
		}
		else {
			break;
		}
	}

	switch (input) {
	case 1:
		return ATTACK;
	case 2:
		return PARRY;
	case 3:
		return DEFEND;
	}
}
