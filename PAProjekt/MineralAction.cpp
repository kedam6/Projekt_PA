#include "MineralAction.h"



MineralAction::MineralAction()
{
}

MineralAction::MineralAction(GameSupport support)
{
	this->support = support;
}


MineralAction::~MineralAction()
{
}

void MineralAction::PerformAction(GameInfo * game, int cave[CAVE_WIDTH][CAVE_HEIGHT], ActionContext & context)
{
	int x = context.x;
	int y = context.y;

	if (context.fallTick == 0)
	{
		if (
			((cave[x][y] == DATA_BOULDER) || (cave[x][y] == DATA_DIAMOND)) &&
			(cave[x][y + 1] == DATA_SPACE)
			)
		{
			cave[x][y + 1] = context.currType + context.fall;
			cave[x][y] = DATA_SPACE;
		}
		else if (
			cave[x][y + 1] == DATA_SPACE
			)
		{
			cave[x][y] = DATA_SPACE;
			cave[x][y + 1] = context.currType + context.fall;
		}
		else if (
			((cave[x][y + 1] == DATA_BOULDER) || (cave[x][y + 1] == DATA_DIAMOND)) &&
			(cave[x - 1][y + 1] == DATA_SPACE) &&
			(cave[x - 1][y] == DATA_SPACE)

			)
		{
			cave[x - 1][y] = context.currType + context.fall;
			cave[x][y] = DATA_SPACE;
		}
		else if (
			((cave[x][y + 1] == DATA_BOULDER) || (cave[x][y + 1] == DATA_DIAMOND)) &&
			(cave[x + 1][y + 1] == DATA_SPACE) &&
			(cave[x + 1][y] == DATA_SPACE)

			)
		{
			cave[x + 1][y] = context.currType + context.fall;
			cave[x][y] = DATA_SPACE;
		}
		else if (
			(cave[x][y + 1] == DATA_MAGICWALL) &&
			(cave[x][y] == DATA_BOULDER_FALL)
			)
		{
			game->MagicWallActive = 1;
		}
		else if (
			(cave[x][y + 1] == DATA_MAGICWALL_ACTIVE) &&
			((cave[x][y] == DATA_DIAMOND_FALL) ||
			(cave[x][y] == DATA_BOULDER_FALL)) &&
				(cave[x][y + 2] == DATA_SPACE)
			)
		{
			cave[x][y + 2] = DATA_DIAMOND_FALL;
			cave[x][y] = DATA_SPACE;
		}
		else if (
			(cave[x][y + 1] == DATA_MAGICWALL_ACTIVE) &&
			((cave[x][y] == DATA_DIAMOND_FALL) ||
			(cave[x][y] == DATA_BOULDER_FALL)) &&
				(cave[x][y + 2] != DATA_SPACE)
			)
		{
			cave[x][y] = DATA_SPACE;
		}
		else if (
			(cave[x][y + 1] == DATA_SLIME) &&
			(cave[x][y] == DATA_DIAMOND) &&
			(cave[x][y + 2] == DATA_SPACE)
			)
		{
			support.NextRandom(&game->SlimeSeed1, &game->SlimeSeed2);
			if (game->SlimeSeed1 < 10)
			{
				cave[x][y + 2] = DATA_DIAMOND_FALL;
				cave[x][y] = DATA_SPACE;
			}
		}
		else if (
			(cave[x][y + 1] == DATA_SLIME) &&
			(cave[x][y] == DATA_BOULDER) &&
			(cave[x][y + 2] == DATA_SPACE)
			)
		{
			support.NextRandom(&game->SlimeSeed1, &game->SlimeSeed2);
			if (game->SlimeSeed1 < 10)
			{
				cave[x][y + 2] = DATA_BOULDER_FALL;
				cave[x][y] = DATA_SPACE;
			}
		}
	}
}
