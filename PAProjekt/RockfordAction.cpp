#include "RockfordAction.h"



RockfordAction::RockfordAction(GameEffects gameEffects, PositionChecker positionChecker, InputHandler input)
{
	this->gameEffects = gameEffects;
	this->positionChecker = positionChecker;
	this->input = input;
}

RockfordAction::RockfordAction()
{
}


RockfordAction::~RockfordAction()
{
}

void RockfordAction::PerformAction(GameInfo * game, int cave[CAVE_WIDTH][CAVE_HEIGHT], ActionContext & context)
{
	int x = context.x;
	int y = context.y;

	context.validRockFord = 1;

	if (context.moveTick == 0)
	{

		int direction = 0;

		if (input.GetKey(5))
		{
			game->Lost = 1;
			gameEffects.Explode(cave, x, y);
			return;
		}
		if ((game->Won == 0) && ((game->CaveTime - (game->Tick / 8)) < 1))
		{
			game->Lost = 1;
			gameEffects.Explode(cave, x, y);
			return;
		}

		if (input.GetKey(1))
		{
			direction = 2;
		}
		else if (input.GetKey(2))
		{
			direction = 3;
		}
		else if (input.GetKey(3))
		{
			direction = 4;
		}
		else if (input.GetKey(0))
		{
			direction = 1;
		};

		if (direction != 0)
		{
			if (
				(cave[x + positionChecker.MoveX(direction)][y + positionChecker.MoveY(direction)] == DATA_SPACE) ||
				(cave[x + positionChecker.MoveX(direction)][y + positionChecker.MoveY(direction)] == DATA_DIRT)
				)
			{
				cave[x + positionChecker.MoveX(direction)][y + positionChecker.MoveY(direction)] = DATA_ROCKFORD;
				cave[x][y] = DATA_SPACE;
				game->Player_X = x + positionChecker.MoveX(direction);
			}
			if (
				cave[x + positionChecker.MoveX(direction)][y + positionChecker.MoveY(direction)] == DATA_OUTBOX_ACTIVE
				)
			{
				cave[x + positionChecker.MoveX(direction)][y + positionChecker.MoveY(direction)] = DATA_ROCKFORD;
				cave[x][y] = DATA_SPACE;
				game->Player_X = x + positionChecker.MoveX(direction);
				game->Won = 1;
			}
			else if (
				(cave[x + positionChecker.MoveX(direction)][y + positionChecker.MoveY(direction)] == DATA_DIAMOND) ||
				(cave[x + positionChecker.MoveX(direction)][y + positionChecker.MoveY(direction)] == DATA_DIAMOND_FALL)
				)
			{
				cave[x + positionChecker.MoveX(direction)][y + positionChecker.MoveY(direction)] = DATA_ROCKFORD;
				cave[x][y] = DATA_SPACE;
				game->Player_X = x + positionChecker.MoveX(direction);
				game->DiamondsCollected++;
			}
			else if (
				(cave[x + positionChecker.MoveX(direction)][y] == DATA_BOULDER) &&
				(positionChecker.MoveY(direction) == 0)
				)
			{
				if (context.currType == DATA_ROCKFORD_GRAB)
				{
					if (cave[x + positionChecker.MoveX(direction) * 2][y] == DATA_SPACE)
					{
						cave[x + positionChecker.MoveX(direction) * 2][y] = DATA_BOULDER;
						cave[x + positionChecker.MoveX(direction)][y] = DATA_ROCKFORD;
						game->Player_X = x + positionChecker.MoveX(direction);
						cave[x][y] = DATA_SPACE;
					}
				}
				else
				{
					cave[x][y] = DATA_ROCKFORD_GRAB;
				}
			}

		}
	}
}
