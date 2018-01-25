#include "ExplosionAction.h"



ExplosionAction::ExplosionAction()
{
}



void ExplosionAction::PerformAction(GameInfo * game, int cave[CAVE_WIDTH][CAVE_HEIGHT], ActionContext & context)
{
	int x = context.x;
	int y = context.y;

	if (context.currType == DATA_EXPLOSION5)
	{
		if (context.explTick == 0)
		{
			cave[x][y] = DATA_SPACE;
		}
	}
	else
	{
		if (context.explTick == 0)
		{
			cave[x][y] = context.currType + 1;
		}
	}
}
