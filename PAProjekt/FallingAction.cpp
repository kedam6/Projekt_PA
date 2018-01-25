#include "FallingAction.h"



FallingAction::FallingAction()
{
}

FallingAction::FallingAction(GameEffects gameEffects, MineralAction mineralAction)
{
	this->gameEffects = gameEffects;
	this->mineralAction = mineralAction;
}



void FallingAction::PerformAction(GameInfo * game, int cave[CAVE_WIDTH][CAVE_HEIGHT], ActionContext & context)
{
	int x = context.x;
	int y = context.y;

	if (context.fallTick == 0)
	{
		if (
			(cave[x][y + 1] == DATA_FIREFLY_TOP) ||
			(cave[x][y + 1] == DATA_FIREFLY_LEFT) ||
			(cave[x][y + 1] == DATA_FIREFLY_RIGHT) ||
			(cave[x][y + 1] == DATA_FIREFLY_DOWN) ||
			(cave[x][y + 1] == DATA_ROCKFORD)
			)
		{
			if (cave[x][y + 1] == DATA_ROCKFORD)
				game->Lost = 1;
			gameEffects.Explode(cave, x, y + 1);

		}
		else if (
			(context.currType == DATA_BOULDER_FALL) &&
			(cave[x][y + 1] == DATA_MAGICWALL)
			)
		{
		}
		else if (
			(cave[x][y + 1] != DATA_SPACE) &&
			(cave[x][y + 1] != DATA_MAGICWALL_ACTIVE)
			)
		{
			cave[x][y] -= 1;
		}
		context.fall = 0;
	}

	mineralAction.PerformAction(game, cave, context);
}
