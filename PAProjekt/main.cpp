#include "Game.h"
#include "GameFactory.h"


//z jakiegos powodu trzeba oddefiniowac main przez SDL
#undef main

int main(int argv, char* args)
{
	GameFactory gf = GameFactory();
	Game game = gf.Create();

	game.Run();

	return 0;
}