#ifndef __MY_ENGINE_H__
#define __MY_ENGINE_H__

#include <string>
#include <iostream>
#include <vector>

#include "../EngineCommon.h"
#include "../GraphicsEngine.h"

struct Item {
	std::string Name;
	int Weight;
	Point2 position;
	bool isActive;
};



class MyEngineSystem {
	friend class XCube2Engine;
	private:

		int InventoryMaxWeight;
		int InventoryWeight;
		Item lastPickedUp;

	public:

		std::vector<Item> Inventory;

		MyEngineSystem();

		bool pickupItem(Item &);

		void showInventory(std::string, std::vector<Item> &);
		void removeFromInventory(std::vector<Item> &, Item);
		int findInVector(std::vector<Item> &, std::string);
		void dropItem(std::vector<Item>&, Item &, Point2 &);
		std::string MyEngineSystem::getWeightForUI();
	
		Item getLastPickedUp();

		Item getCollidingWith(Item);
};

#endif