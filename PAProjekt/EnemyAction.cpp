#include "EnemyAction.h"



EnemyAction::EnemyAction()
{
}

EnemyAction::EnemyAction(GameEffects gameEffects, PositionChecker positionChecker)
{
	this->gameEffects = gameEffects;
	this->positionChecker = positionChecker;
}



void EnemyAction::PerformAction(GameInfo * game, int cave[CAVE_WIDTH][CAVE_HEIGHT], ActionContext & context)
{
	int x = context.x;
	int y = context.y;

	if (context.moveTick == 0)
	{
		int dir = positionChecker.FireflyLeft(context.currType);

		for (int di = 0; di<4; di++)
		{
			if (
				(cave[x + positionChecker.MoveX(di)][y + positionChecker.MoveY(di)] == DATA_ROCKFORD) ||
				(cave[x + positionChecker.MoveX(di)][y + positionChecker.MoveY(di)] == DATA_ROCKFORD_GRAB)
				)
			{
				gameEffects.Explode(cave, x, y);
				game->Lost = 1;
			}
			if (cave[x + positionChecker.MoveX(di)][y + positionChecker.MoveY(di)] == DATA_AMOEBA)
			{
				gameEffects.Explode(cave, x, y);
			}
		}

		if (cave[x][y] != DATA_EXPLOSION1)
		{
			if (cave[x + positionChecker.FireflyX(dir)][y + positionChecker.FireflyY(dir)] == DATA_SPACE)
			{
				cave[x + positionChecker.FireflyX(dir)][y + positionChecker.FireflyY(dir)] = dir;
				cave[x][y] = DATA_SPACE;
			}
			else if (cave[x + positionChecker.FireflyX(context.currType)][y + positionChecker.FireflyY(context.currType)] == DATA_SPACE)
			{
				cave[x + positionChecker.FireflyX(context.currType)][y + positionChecker.FireflyY(context.currType)] = context.currType;
				cave[x][y] = DATA_SPACE;
			}
			else
			{
				cave[x][y] = positionChecker.FireflyRight(context.currType);
			}
		}
	}
}
