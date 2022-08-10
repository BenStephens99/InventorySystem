#ifndef __TEST_GAME_H__
#define __TEST_GAME_H__

#include "../engine/AbstractGame.h"
#include <iostream>
#include <windows.h>

struct Circle {
	Point2 pos;
	bool isAlive;
};

class MyGame : public AbstractGame {
	private:
		Rect box;
		int cir;
		Vector2i velocity;
		Item collidingWith;
		bool hasPickedUpFirst;
		std::string collidingWithName = "a";
		

		std::vector<std::shared_ptr<Circle>> circles;
		std::vector<Item> InGameItems;

		/* GAMEPLAY */
		int score, numCircles, lives;
		bool gameWon;

		void handleKeyEvents();
		void update();
		void render();
		void renderUI();
		

	public:
        MyGame();
		~MyGame();
};

#endif