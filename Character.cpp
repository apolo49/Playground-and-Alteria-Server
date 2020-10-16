#include "character.h"

bool Character::addStackToInv(Stack stack) {
	if (inventory.addItem(stack)) {
		return true;
	}
	else {
		return false;
	}
}

bool Character::addItemToInv(Item item) {
	if (inventory.addItem(Stack(item, 1))) {
		return true;
	}
	else {
		return false;
	}
}

void Character::GenStats() {
	string indices[6] = { "Strength","Lore","Magika","Learning","Speed", "Agility" };
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(0, 5);
	for (int i = 0; i < 5; i++) {
		Stats.at(indices[distr(gen)]) += 1;
	}
}

int Character::getStat(string stat) {
	if ((stat.compare("ATK") == 0) || (stat.compare("DEF") == 0) || (stat.compare("SPD") == 0) || (stat.compare("SP_ATK") == 0) || (stat.compare("SP_DEF") == 0)) {
		return Stats.at(stat);
	}
	else {
		if ((stat.compare("Attack") == 0) || (stat.compare("attack") == 0)) {
			return Stats.at("ATK");
		}
		else if ((stat.compare("Defense") == 0) || (stat.compare("defense") == 0)) {
			return Stats.at("DEF");
		}
		else if ((stat.compare("Speed") == 0) || (stat.compare("speed") == 0)) {
			return Stats.at("SPD");
		}
		else if ((stat.compare("Special Attack") == 0) || (stat.compare("Special attack") == 0) || (stat.compare("special Attack") == 0) || (stat.compare("special attack") == 0)) {
			return Stats.at("SP_ATK");
		}
		else if ((stat.compare("Special Defense") == 0) || (stat.compare("Special defense") == 0) || (stat.compare("special Defense") == 0) || (stat.compare("special defense") == 0)) {
			return Stats.at("SP_DEF");
		}
		else {
			try {
				throw StatNotFoundException();
			}
			catch (exception& e)
			{
				cout << e.what() << endl;
			}
			return 1;
		}
	}
}