#include "Game.h"
#include <iostream>

using namespace std;

int main()
{
	HumanPlayer hp("Player");
	BadPlayer daniel("daniel");
	BadPlayer bp("bart");

	SmartPlayer ai("Computer");


	Board b(6, 4);

//	for (int i = 1; i <= b.holes(); i++)
//		b.setBeans(NORTH, i, 0);

	Game minigame(b, &ai, &hp);

	minigame.play();

}