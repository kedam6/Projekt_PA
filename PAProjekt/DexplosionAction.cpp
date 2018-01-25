#include "DexplosionAction.h"


DexplosionAction::DexplosionAction()
{
}


DexplosionAction::~DexplosionAction()
{
}

void DexplosionAction::PerformAction(GameInfo * game, int cave[CAVE_WIDTH][CAVE_HEIGHT], ActionContext & context)
{
	int x = context.x;
	int y = context.y;

	if (context.currType == DATA_DEXPLOSION5)
	{
		if (context.explTick == 0)
		{
			cave[x][y] = DATA_DIAMOND;
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
