#include "MyEngineSystem.h"


MyEngineSystem::MyEngineSystem()
{
	InventoryMaxWeight = 50;
	InventoryWeight = 0;


	Item lastPickedUp; 
	lastPickedUp.Name = "Null";
	lastPickedUp.Weight = 0;
	lastPickedUp.position = Point2(0, 0);
	lastPickedUp.isActive = false;
}


bool MyEngineSystem::pickupItem(Item & i) {
	
	if (InventoryWeight + i.Weight > InventoryMaxWeight) {
		std::cout << "Inventory full" << std::endl;
		return false;
	}
	else {
		
		InventoryWeight += i.Weight;
		Inventory.push_back(i);
		lastPickedUp = i;
		std::cout << "Picked up item: " << lastPickedUp.Name << std::endl;
		return true;
	} 
}

Item MyEngineSystem::getCollidingWith(Item i) {
	return i;
}

Item MyEngineSystem::getLastPickedUp() {
	return lastPickedUp;
}

std::string MyEngineSystem::getWeightForUI() {

	std::string weight = std::to_string(InventoryWeight);
	std::string maxWeight = std::to_string(InventoryMaxWeight);

	return weight + "/" + maxWeight;
}

void MyEngineSystem::showInventory(std::string s, std::vector<Item> & v) {
	std::cout << std::endl;
	std::cout << "_________ " << s <<" Inventory _________" << std::endl;
	std::cout << std::endl;
	for (auto key : v) {
		std::cout << "Name: " << key.Name << " ||  " << "Weight: " << std::to_string(key.Weight)<< std::endl;
	}
	std::cout << std::endl;
	if (s == "Player") 
	std::cout << "Weight: " << InventoryWeight << std::endl;
	std::cout << "___________________________________" << std::endl;
}

void MyEngineSystem::removeFromInventory (std::vector<Item> & inventory , Item i) {
	
	int pos = 0;
	pos = findInVector(inventory, i.Name);
	inventory.erase(inventory.begin() + pos - 1);
}

int MyEngineSystem::findInVector(std::vector<Item> & vector , std::string name) {
	
	int position = 0;
	for (auto j : vector) {
		position++;
		if (j.Name == name) 
		{
			return position;
		} 
	}
}

void MyEngineSystem::dropItem(std::vector<Item>& v, Item & i, Point2 & pos) {
	std::cout << "Dropped item: " << i.Name << std::endl;
	i.position = pos;
	v.push_back(i);
	removeFromInventory(Inventory, i);
	InventoryWeight -= i.Weight;
}