#include "MyGame.h"

MyGame::MyGame() : AbstractGame(), score(0), lives(3), numCircles(5), gameWon(false), box(5, 5, 30, 30) {
	TTF_Font * font = ResourceManager::loadFont("res/fonts/arial.ttf", 72);
	gfx->useFont(font);
	gfx->setVerticalSync(true);

    for (int i = 0; i < numCircles; i++) {
        std::shared_ptr<Circle> circle = std::make_shared<Circle>();
        circle->isAlive = true;
        circle->pos = Point2(getRandom(0, 750), getRandom(0, 550));
        circles.push_back(circle);
    }
;
	mySystem->showInventory("Player", mySystem->Inventory);
	
	Item Sword;
	Sword.Name = "Sword";
	Sword.Weight = 10;
	Sword.position = Point2(getRandom(0, 750), getRandom(0, 550));
	Sword.isActive = true;
	InGameItems.push_back(Sword);

	Item Hat;
	Hat.Name = "Hat";
	Hat.Weight = 15;
	Hat.position = Point2(getRandom(0, 750), getRandom(0, 550));
	Hat.isActive = true;
	InGameItems.push_back(Hat);

	Item Shirt;
	Shirt.Name = "Shirt";
	Shirt.Weight = 15;
	Shirt.position = Point2(getRandom(0, 750), getRandom(0, 550));
	Shirt.isActive = true;
	InGameItems.push_back(Shirt);

	Item Trousers;
	Trousers.Name = "Trousers";
	Trousers.Weight = 15;
	Trousers.position = Point2(getRandom(0, 750), getRandom(0, 550));
	Trousers.isActive = true;
	InGameItems.push_back(Trousers);

	Item Boots;
	Boots.Name = "Boots";
	Boots.Weight = 15;
	Boots.position = Point2(getRandom(0, 750), getRandom(0, 550));
	Boots.isActive = true;
	InGameItems.push_back(Boots);

	mySystem->showInventory("Game", InGameItems);
}

MyGame::~MyGame() {

}

void MyGame::handleKeyEvents() {
	int speed = 3;
	cir = 1;

	if (eventSystem->isPressed(Key::W)) {
		velocity.y = -speed;
	}

	if (eventSystem->isPressed(Key::S)) {
		velocity.y = speed;
	}

	if (eventSystem->isPressed(Key::A)) {
		velocity.x = -speed;
	}

	if (eventSystem->isPressed(Key::D)) {
		velocity.x = speed;
		
	}

	if (eventSystem->isPressed(Key::I)) {
		mySystem->dropItem(InGameItems, mySystem->Inventory.back(), Point2(box.x, box.y));
		Sleep(500);
	}

	if (eventSystem->isPressed(Key::E)) {
		for (auto key : InGameItems) {
			if (key.isActive && box.contains(key.position)) {

				if (mySystem->pickupItem(key)) {

					std::cout << key.Name << std::endl;

					mySystem->removeFromInventory(InGameItems, key);

					key.isActive = false;

					mySystem->showInventory("Game", InGameItems);
					mySystem->showInventory("Player", mySystem->Inventory);


				}  
				
			}
		}
	}
}

void MyGame::update() {
	box.x += velocity.x;
	box.y += velocity.y;

	for (auto key : circles) {
		if (key->isAlive && box.contains(key->pos)) {
			score += 200;
			key->isAlive = false;
			numCircles--;
		}
	}

	for (auto key : InGameItems) {
		if (key.isActive && box.contains(key.position)) {
			collidingWith.Name = mySystem->getCollidingWith(key).Name;
			}
		}

	velocity.x = 0;
    velocity.y = 0;

	if (numCircles == 0) {
		gameWon = true;
	}
}

void MyGame::render() {
	gfx->setDrawColor(SDL_COLOR_RED);
	gfx->drawRect(box);
	

	gfx->setDrawColor(SDL_COLOR_YELLOW);
	for (auto key : circles)
		if (key->isAlive) {
			gfx->drawCircle(key->pos, 10);
		}

	gfx->setDrawColor(SDL_COLOR_BLUE);
	for (auto key : InGameItems)
		if (key.isActive) {
			gfx->drawCircle(key.position, 10);
		}
}

void MyGame::renderUI() {
	gfx->setDrawColor(SDL_COLOR_AQUA);
	std::string scoreStr = std::to_string(score);
	gfx->drawText(scoreStr, 780 - scoreStr.length() * 50, 25);
	
	
	collidingWithName = collidingWith.Name;
	gfx->drawText("Name: " + collidingWithName, 20, 500);


	gfx->drawText(mySystem->getWeightForUI(), 20, 20);

	if (gameWon) {
		gfx->drawText("YOU WON", 250, 500);
	}

}

