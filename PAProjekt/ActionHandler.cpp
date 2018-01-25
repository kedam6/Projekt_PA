#include "ActionHandler.h"



ActionHandler::ActionHandler()
{
}

ActionHandler::ActionHandler(ActionMapping actionMapping)
{
	this->actionMapping = actionMapping;
}


ActionHandler::~ActionHandler()
{
}

void ActionHandler::HandleAllMapChanges(GameInfo * game, int cave[CAVE_WIDTH][CAVE_HEIGHT], int moveTick, int fallTick)
{
	ActionContext context = ActionContext();
	context.tick = game->Tick;
	context.moveTick = moveTick;
	context.fallTick = fallTick;
	context.amoebaPossible = 0;
	context.validRockFord = 0;
	context.explTick = 0;

	for (int y = 0; y < CAVE_HEIGHT; y++)
	{
		for (int x = 0; x < CAVE_WIDTH; x++)
		{
			int currType = game->cavemap[x][y];

			if (game->cavemap[x][y] != cave[x][y])
			{
				//brak zmiany - nic nie robimy
				continue;
			}
			context.fall = 1;
			context.currType = currType;
			context.x = x;
			context.y = y;

			Action* action = actionMapping.GetActionForType(currType);

			if(action != NULL)
				action->PerformAction(game, cave, context);
		}
	}

	if ((context.validRockFord == 0) && (game->Lost == 0))
		game->Lost = 1;

	game->AmoebaSpace = context.amoebaPossible;
}
