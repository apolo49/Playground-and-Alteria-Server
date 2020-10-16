#pragma once
#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>
#include "stack.h"

using namespace std;

class Inventory
{
	vector<Stack> Contents;
public:
	vector<Stack> getContents() {
		return Contents;
	}

	Item getItem(int index) {
		return Contents.at(index).getItem();
	}

	Item getItem(string itemName);

	bool addItem(Stack Item);

	bool removeItem(int Index);
};
