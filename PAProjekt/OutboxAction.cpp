#include "OutboxAction.h"
#include "GameObjects.h"


OutboxAction::OutboxAction()
{
}


OutboxAction::~OutboxAction()
{
}

void OutboxAction::PerformAction(GameInfo * game, int cave[CAVE_WIDTH][CAVE_HEIGHT], ActionContext & context)
{
	int x = context.x;
	int y = context.y;

	if (game->DiamondsCollected >= game->DiamondsRequired)
	{
		cave[x][y] = DATA_OUTBOX_ACTIVE;
	}
}
