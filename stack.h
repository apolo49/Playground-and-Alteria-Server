#pragma once

#include "Item.h"
#include <ostream>

class Stack {
	Item item;
	int Quantity;
public:

	/*
	--------------------------------OP OVERLOADS----------------------------------
	*/

	friend ostream& operator<<(ostream& os, Stack& stack) {
		string Amount = to_string(stack.Quantity);
		return os << "Amount: " + Amount + ", Item = " + stack.getItemName();
	}

	friend bool operator== (Item item, Stack stack) {
		if (item.getName() == stack.getItemName()) {
			return 1;
		}
		else if (stack.getItemName() == item.getName()) {
			return 1;
		}
		else {
			return 0;
		}
	}

	friend bool operator== (Stack stack, string item) {
		if (item == stack.getItemName()) {
			return 1;
		}
		else if (stack.getItemName() == item) {
			return 1;
		}
		else {
			return 0;
		}
	}

	friend bool operator== (string item, Stack stack) {
		if (item == stack.getItemName()) {
			return 1;
		}
		else if (stack.getItemName() == item) {
			return 1;
		}
		else {
			return 0;
		}
	}

	friend bool operator== (Stack stack1, Stack stack2) {
		if (stack1.getItemName() == stack2.getItemName()) {
			return 1;
		}
		else {
			return 0;
		}
	}

	/*
	----------------------------END OF OP OVERLOADS------------------------------
	*/

	bool setQuantity(int size) {
		Quantity = size;
		if (Quantity <= 0) {
			item = Item("");
			return true;
		}
		else {
			return false;
		}
	}

	bool addToQuantity(int modifier) {
		Quantity += modifier;
		if (Quantity <= 0) {
			item = Item("");
			return true;
		}
		else {
			return false;
		}
	}

	string getItemName() {
		return item.getName();
	}

	Item getItem() {
		return item;
	}

	int getQuantity() {
		return Quantity;
	}

	Stack() {
		Quantity = 0;
		item = Item("");
	}

	Stack(Item stackType, int Amount) {
		Quantity = Amount;
		item = stackType;
	}
};
