#include "Inventory.h"

bool Inventory::addItem(Stack Item) {
	std::vector<Stack>::iterator it = std::find(Contents.begin(), Contents.end(), Item);
	if (it != Contents.end()) {
		int index = std::distance(Contents.begin(), it);
		bool remove = Contents.at(index).addToQuantity(Item.getQuantity());
		if (remove) {
			if (index >= 1) {
				Contents.erase(Contents.begin() - (index - 1));
			}
			else {
				Contents.erase(Contents.begin());
			}
			return true;
		}
		else {
			return true;
		}
	}
	else {
		if (Contents.size() < 32) {
			Contents.insert(Contents.end(), Item);
			return true;
		}
		else {
			return false;
		}
	}
}

bool Inventory::removeItem(int Index) {
	Stack stack;
	try {
		Contents.at(Index) = stack;
		if (stack.getItemName() != "NULL") {
			return true;
		}
		else {
			return false;
		}
	}
	catch (const out_of_range& oor) {
		return false;
	}
}

Item Inventory::getItem(string itemName) {
	std::vector<Stack>::iterator it = std::find(Contents.begin(), Contents.end(), itemName);
	if (it != Contents.end()) {
		long index = std::distance(Contents.begin(), it);
		return Contents.at(index).getItem();
	}
	else {
		try {
			throw ItemNotFoundException();
		}
		catch (exception& e) {
			cout << e.what() << endl;
		}
	}
	return Item();
}