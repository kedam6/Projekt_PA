#include "PlayerAction.h"



PlayerAction::PlayerAction()
{
}

PlayerAction::PlayerAction(GameEffects gameEffects, PositionChecker positionChecker)
{
	this->gameEffects = gameEffects;
	this->positionChecker = positionChecker;
}



void PlayerAction::PerformAction(GameInfo * game, int cave[CAVE_WIDTH][CAVE_HEIGHT], ActionContext & context)
{
	int x = context.x;
	int y = context.y;

	if (context.moveTick == 0)
	{
		int dir = positionChecker.ButterflyLeft(context.currType);

		for (int di = 0; di<4; di++)
		{
			if (
				(cave[x + positionChecker.MoveX(di)][y + positionChecker.MoveY(di)] == DATA_ROCKFORD) ||
				(cave[x + positionChecker.MoveX(di)][y + positionChecker.MoveY(di)] == DATA_ROCKFORD_GRAB)
				)
			{
				gameEffects.Dexplode(cave, x, y);
				game->Lost = 1;
			}
			if (cave[x + positionChecker.MoveX(di)][y + positionChecker.MoveY(di)] == DATA_AMOEBA)
			{
				gameEffects.Dexplode(cave, x, y);
			}
		}

		if (cave[x][y] != DATA_DEXPLOSION1)
		{
			if (cave[x + positionChecker.ButterflyX(dir)][y + positionChecker.ButterflyY(dir)] == DATA_SPACE)
			{
				cave[x + positionChecker.ButterflyX(dir)][y + positionChecker.ButterflyY(dir)] = dir;
				cave[x][y] = DATA_SPACE;
			}
			else if (cave[x + positionChecker.ButterflyX(context.currType)][y + positionChecker.ButterflyY(context.currType)] == DATA_SPACE)
			{
				cave[x + positionChecker.ButterflyX(context.currType)][y + positionChecker.ButterflyY(context.currType)] = context.currType;
				cave[x][y] = DATA_SPACE;
			}
			else
			{
				cave[x][y] = positionChecker.ButterflyRight(context.currType);
			}
		}
	}
}
