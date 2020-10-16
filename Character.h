#pragma once
#include "Inventory.h"
#include <iostream>
#include <map>
#include <random>
#include <time.h>

class Character
{
private:
	Inventory inventory;
	map<string, uint64_t> Stats = { {"Strength",0},{"Lore",0 }, {"Magika",0}, {"Learning",0}, {"Speed",0}, {"Agility", 0} };
	string Name;
	void GenStats();
public:

	Character(string name = "") : Name(name) {
		GenStats();
	}

	void ResetStats() {
		Stats = { {"Strength",0},{"Lore",0 }, {"Magika",0}, {"Learning",0}, {"Speed",0}, {"Agility", 0} };
		GenStats();
	}

	Inventory getInventory() {
		return inventory;
	}

	map<string, uint64_t> getStats() {
		return Stats;
	}

	Item getItemFromInv(int index) {
		return inventory.getItem(index);
	}

	Item getItemFromInv(string itemName) {
		return inventory.getItem(itemName);
	}

	std::string getName() {
		return this->Name;
	}

	bool addItemToInv(Item item);

	bool addStackToInv(Stack stack);

	int getStat(string stat);
};
