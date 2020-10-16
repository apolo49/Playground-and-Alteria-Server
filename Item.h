#pragma once

#include <string>
#include <iostream>

using namespace std;

class Item {
protected:
	string name;
public:

	Item(string Name = "") : name(Name) {}

	void UseItem() {
		use();
	}

	void getType() {
		cout << "Item" << endl;
	}

	void use() {
	}

	string getName() {
		return name;
	}
};
