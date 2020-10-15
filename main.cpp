// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdlib.h>
#include <iostream>

#include "cardgen.h"
#include "gamesystem.h"


int main(void)
{
	game_system::Game my_game;
	my_game.set_game(3);
	my_game.NewGame();

	return 0;
}

