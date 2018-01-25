#include "MagicWallAction.h"



MagicWallAction::MagicWallAction()
{
}



void MagicWallAction::PerformAction(GameInfo * game, int cave[CAVE_WIDTH][CAVE_HEIGHT], ActionContext & context)
{
	if (game->MagicWallActive == 1)
	{
		cave[context.x][context.y] = DATA_MAGICWALL_ACTIVE;
	}
}
