#include "AmoebaAction.h"
#include <random>
#include "GameObjects.h"


AmoebaAction::AmoebaAction()
{
}

AmoebaAction::AmoebaAction(PositionChecker posChecker)
{
	this->posChecker = posChecker;
}


AmoebaAction::~AmoebaAction()
{
}

void AmoebaAction::PerformAction(GameInfo * game, int cave[CAVE_WIDTH][CAVE_HEIGHT], ActionContext & context)
{
	int x = context.x;
	int y = context.y;

	if (game->AmoebaSpace == 0)
	{
		cave[x][y] = DATA_DIAMOND;
	}
	else
	{
		for (int dir = 1; dir<5; dir++)
		{
			if (
				(cave[x + posChecker.MoveX(dir)][y + posChecker.MoveY(dir)] == DATA_SPACE) ||
				(cave[x + posChecker.MoveX(dir)][y + posChecker.MoveY(dir)] == DATA_DIRT)
				)
			{
				context.amoebaPossible++;
				if (((game->AmoebaTime * 8) < context.tick) && (rand() % 15 == 0))
				{
					cave[x + posChecker.MoveX(dir)][y + posChecker.MoveY(dir)] = DATA_AMOEBA;
				}
				else if ((game->Tick > START_DELAY) && (rand() % 100 == 0))
				{
					cave[x + posChecker.MoveX(dir)][y + posChecker.MoveY(dir)] = DATA_AMOEBA;
				}
			}
		}
	}

}
