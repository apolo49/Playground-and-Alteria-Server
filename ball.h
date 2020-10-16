#pragma once
#include "Item.h"

class ball : public Item
{
public:
	ball() {
		name = "ball";
	}

	void getType() {
		cout << "ball" << endl;
	}

	void use() {
		cout << "boing\n" << endl;
	}
};
