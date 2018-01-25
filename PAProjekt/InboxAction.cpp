#include "InboxAction.h"



InboxAction::InboxAction()
{
}



void InboxAction::PerformAction(GameInfo * game, int cave[CAVE_WIDTH][CAVE_HEIGHT], ActionContext & context)
{
	context.validRockFord = 1;
	game->Player_X = context.x;

	if (game->Tick == START_DELAY)
		cave[context.x][context.y] = DATA_ROCKFORD;

}
