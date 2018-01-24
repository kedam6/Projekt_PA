#include "Engine.h"
#include "GlobalValues.h"
#include "Objects.h"
#include "GameInitInfo.h"
#include "PositionChecker.h"
#include <stdlib.h>


Engine::Engine(SdlUtils utils, GameInitInfo initializer, Renderer renderer, PositionChecker positionChecker, Graphics graphics, GameEffects gameEff, GameSupport gameSupport)
{
	initializer = GameInitInfo();
	renderer = Renderer();
	positionChecker = PositionChecker();
	graphics = Graphics();
	gameEffects = GameEffects();
	support = GameSupport();
	sdlUtils = utils;
}
Engine::Engine()
{
}


Engine::~Engine()
{
}

void Engine::Process(GameInfo * game)
{


	game->Tick++;
	int tick = game->Tick;



	int move_tick = 0;
	int fall_tick = 0;
	int expl_tick = 0;

	if (sdlUtils.SdlGetKey(6))
	{
		game->Won = 1;
	}

	if (game->Won > 0)
	{
		move_tick = 1;
		fall_tick = 1;

		game->Won++;


		if (game->Won == 25)
		{
			int old_cave = game->Cave;
			int old_difficulty = game->Difficulty;

			old_cave++;
			if (old_cave == CAVE_COUNT)
			{
				old_cave = 0;
				old_difficulty++;
			}
			if (old_difficulty == 5)
			{
				old_cave = 0;
				old_difficulty = 0;
			}

			//free(game);
			auto newGame = initializer.InitGame(old_cave, old_difficulty);
			*game = newGame;
			return;
		}
	}

	if (game->Lost > 0)
	{
		game->Lost++;

		if (game->Lost == 25)
		{
			int old_cave = game->Cave;
			int old_difficulty = game->Difficulty;

			//free(game);
			auto newGame = initializer.InitGame(old_cave, old_difficulty);
			*game = newGame;
			return;
		}
	}



	int new_cavemap[CAVE_WIDTH][CAVE_HEIGHT];
	for (int y = 0; y < CAVE_HEIGHT; y++)
	{
		for (int x = 0; x < CAVE_WIDTH; x++)
		{
			new_cavemap[x][y] = game->cavemap[x][y];
		}
	}

	int amoeba_possible = 0;
	int valid_rockford = 0;

	for (int y = 0; y < CAVE_HEIGHT; y++)
	{
		for (int x = 0; x < CAVE_WIDTH; x++)
		{
			int curr_type = game->cavemap[x][y];
			if (game->cavemap[x][y] != new_cavemap[x][y])
			{
				continue;
			};
			int fall = 1;
			switch (curr_type)
			{
			case BD_AMOEBA:
				if (game->AmoebaSpace == 0)
				{
					new_cavemap[x][y] = BD_DIAMOND;
				}
				else
					for (int dir = 1; dir<5; dir++)
					{
						if (
							(new_cavemap[x + positionChecker.MoveX(dir)][y + positionChecker.MoveY(dir)] == BD_SPACE) ||
							(new_cavemap[x + positionChecker.MoveX(dir)][y + positionChecker.MoveY(dir)] == BD_DIRT)
							)
						{
							amoeba_possible++;
							if (((game->AmoebaTime * 8) < tick) && (rand() % 15 == 0))
							{
								new_cavemap[x + positionChecker.MoveX(dir)][y + positionChecker.MoveY(dir)] = BD_AMOEBA;
							}
							else if ((game->Tick>START_DELAY) && (rand() % 100 == 0))
							{
								new_cavemap[x + positionChecker.MoveX(dir)][y + positionChecker.MoveY(dir)] = BD_AMOEBA;
							}
						}
					}
				break;
			case BD_OUTBOX:
				if (game->DiamondsCollected >= game->DiamondsRequired)
				{
					new_cavemap[x][y] = BD_OUTBOXactive;
				}
				break;
			case BD_EXPLOSION1:
			case BD_EXPLOSION2:
			case BD_EXPLOSION3:
			case BD_EXPLOSION4:
				if (expl_tick == 0)
				{
					new_cavemap[x][y] = curr_type + 1;
				}
				break;
			case BD_EXPLOSION5:
				if (expl_tick == 0)
				{
					new_cavemap[x][y] = BD_SPACE;
				}
				break;
			case BD_DEXPLOSION1:
			case BD_DEXPLOSION2:
			case BD_DEXPLOSION3:
			case BD_DEXPLOSION4:
				if (expl_tick == 0)
				{
					new_cavemap[x][y] = curr_type + 1;
				}
				break;
			case BD_DEXPLOSION5:
				if (expl_tick == 0)
				{
					new_cavemap[x][y] = BD_DIAMOND;
				}
				break;
			case BD_INBOX:
				valid_rockford = 1;
				game->Player_X = x;
				if (game->Tick == START_DELAY)
					new_cavemap[x][y] = BD_ROCKFORD;

				break;
			case BD_ROCKFORDgrab:
			case BD_ROCKFORD:
				valid_rockford = 1;
				if (move_tick == 0)
				{

					int direction = 0;

					if (sdlUtils.SdlGetKey(5))
					{
						game->Lost = 1;
						gameEffects.Explode(new_cavemap, x, y);
						break;
					}
					if ((game->Won == 0) && ((game->CaveTime - (game->Tick / 8)) < 1))
					{
						game->Lost = 1;
						gameEffects.Explode(new_cavemap, x, y);
						break;
					}

					if (sdlUtils.SdlGetKey(1))
					{
						direction = 2;
					}
					else if (sdlUtils.SdlGetKey(2))
					{
						direction = 3;
					}
					else if (sdlUtils.SdlGetKey(3))
					{
						direction = 4;
					}
					else if (sdlUtils.SdlGetKey(0))
					{
						direction = 1;
					};

					if (direction != 0)
					{
						if (
							(new_cavemap[x + positionChecker.MoveX(direction)][y + positionChecker.MoveY(direction)] == BD_SPACE) ||
							(new_cavemap[x + positionChecker.MoveX(direction)][y + positionChecker.MoveY(direction)] == BD_DIRT)
							)
						{
							new_cavemap[x + positionChecker.MoveX(direction)][y + positionChecker.MoveY(direction)] = BD_ROCKFORD;
							new_cavemap[x][y] = BD_SPACE;
							game->Player_X = x + positionChecker.MoveX(direction);
						}
						if (
							new_cavemap[x + positionChecker.MoveX(direction)][y + positionChecker.MoveY(direction)] == BD_OUTBOXactive
							)
						{
							new_cavemap[x + positionChecker.MoveX(direction)][y + positionChecker.MoveY(direction)] = BD_ROCKFORD;
							new_cavemap[x][y] = BD_SPACE;
							game->Player_X = x + positionChecker.MoveX(direction);
							game->Won = 1;
						}
						else if (
							(new_cavemap[x + positionChecker.MoveX(direction)][y + positionChecker.MoveY(direction)] == BD_DIAMOND) ||
							(new_cavemap[x + positionChecker.MoveX(direction)][y + positionChecker.MoveY(direction)] == BD_DIAMONDfall)
							)
						{
							new_cavemap[x + positionChecker.MoveX(direction)][y + positionChecker.MoveY(direction)] = BD_ROCKFORD;
							new_cavemap[x][y] = BD_SPACE;
							game->Player_X = x + positionChecker.MoveX(direction);
							game->DiamondsCollected++;
						}
						else if (
							(new_cavemap[x + positionChecker.MoveX(direction)][y] == BD_BOULDER) &&
							(positionChecker.MoveY(direction) == 0)
							)
						{
							if (curr_type == BD_ROCKFORDgrab)
							{
								if (new_cavemap[x + positionChecker.MoveX(direction) * 2][y] == BD_SPACE)
								{
									new_cavemap[x + positionChecker.MoveX(direction) * 2][y] = BD_BOULDER;
									new_cavemap[x + positionChecker.MoveX(direction)][y] = BD_ROCKFORD;
									game->Player_X = x + positionChecker.MoveX(direction);
									new_cavemap[x][y] = BD_SPACE;
								}
							}
							else
							{
								new_cavemap[x][y] = BD_ROCKFORDgrab;
							}
						}

					}
				}
				break;
			case BD_BOULDERfall:
			case BD_DIAMONDfall:
				if (fall_tick == 0)
				{
					if (
						(new_cavemap[x][y + 1] == BD_FIREFLYt) ||
						(new_cavemap[x][y + 1] == BD_FIREFLYl) ||
						(new_cavemap[x][y + 1] == BD_FIREFLYr) ||
						(new_cavemap[x][y + 1] == BD_FIREFLYd) ||
						(new_cavemap[x][y + 1] == BD_ROCKFORD)
						)
					{
						if (new_cavemap[x][y + 1] == BD_ROCKFORD)
							game->Lost = 1;
						gameEffects.Explode(new_cavemap, x, y + 1);

					}
					else if (
						(curr_type == BD_BOULDERfall) &&
						(new_cavemap[x][y + 1] == BD_MAGICWALL)
						)
					{
					}
					else if (
						(new_cavemap[x][y + 1] != BD_SPACE) &&
						(new_cavemap[x][y + 1] != BD_MAGICWALLactive)
						)
					{
						new_cavemap[x][y] -= 1;
					}
					fall = 0;
				}
			case BD_BOULDER:
			case BD_DIAMOND:
				if (fall_tick == 0)
				{
					if (
						((new_cavemap[x][y] == BD_BOULDER) || (new_cavemap[x][y] == BD_DIAMOND)) &&
						(new_cavemap[x][y + 1] == BD_SPACE)
						)
					{
						new_cavemap[x][y + 1] = curr_type + fall;
						new_cavemap[x][y] = BD_SPACE;
					}
					else if (
						new_cavemap[x][y + 1] == BD_SPACE
						)
					{
						new_cavemap[x][y] = BD_SPACE;
						new_cavemap[x][y + 1] = curr_type + fall;
					}
					else if (
						((new_cavemap[x][y + 1] == BD_BOULDER) || (new_cavemap[x][y + 1] == BD_DIAMOND)) &&
						(new_cavemap[x - 1][y + 1] == BD_SPACE) &&
						(new_cavemap[x - 1][y] == BD_SPACE)

						)
					{
						new_cavemap[x - 1][y] = curr_type + fall;
						new_cavemap[x][y] = BD_SPACE;
					}
					else if (
						((new_cavemap[x][y + 1] == BD_BOULDER) || (new_cavemap[x][y + 1] == BD_DIAMOND)) &&
						(new_cavemap[x + 1][y + 1] == BD_SPACE) &&
						(new_cavemap[x + 1][y] == BD_SPACE)

						)
					{
						new_cavemap[x + 1][y] = curr_type + fall;
						new_cavemap[x][y] = BD_SPACE;
					}
					else if (
						(new_cavemap[x][y + 1] == BD_MAGICWALL) &&
						(new_cavemap[x][y] == BD_BOULDERfall)
						)
					{
						game->MagicWallActive = 1;
					}
					else if (
						(new_cavemap[x][y + 1] == BD_MAGICWALLactive) &&
						((new_cavemap[x][y] == BD_DIAMONDfall) ||
						(new_cavemap[x][y] == BD_BOULDERfall)) &&
							(new_cavemap[x][y + 2] == BD_SPACE)
						)
					{
						new_cavemap[x][y + 2] = BD_DIAMONDfall;
						new_cavemap[x][y] = BD_SPACE;
					}
					else if (
						(new_cavemap[x][y + 1] == BD_MAGICWALLactive) &&
						((new_cavemap[x][y] == BD_DIAMONDfall) ||
						(new_cavemap[x][y] == BD_BOULDERfall)) &&
							(new_cavemap[x][y + 2] != BD_SPACE)
						)
					{
						new_cavemap[x][y] = BD_SPACE;
					}
					else if (
						(new_cavemap[x][y + 1] == BD_SLIME) &&
						(new_cavemap[x][y] == BD_DIAMOND) &&
						(new_cavemap[x][y + 2] == BD_SPACE)
						)
					{
						support.NextRandom(&game->SlimeSeed1, &game->SlimeSeed2);
						if (game->SlimeSeed1 < 10)
						{
							new_cavemap[x][y + 2] = BD_DIAMONDfall;
							new_cavemap[x][y] = BD_SPACE;
						}
					}
					else if (
						(new_cavemap[x][y + 1] == BD_SLIME) &&
						(new_cavemap[x][y] == BD_BOULDER) &&
						(new_cavemap[x][y + 2] == BD_SPACE)
						)
					{
						support.NextRandom(&game->SlimeSeed1, &game->SlimeSeed2);
						if (game->SlimeSeed1 < 10)
						{
							new_cavemap[x][y + 2] = BD_BOULDERfall;
							new_cavemap[x][y] = BD_SPACE;
						}
					}
				}
				break;
			case BD_MAGICWALL:
				if (game->MagicWallActive == 1)
				{
					new_cavemap[x][y] = BD_MAGICWALLactive;
				}
				break;
			case BD_FIREFLYr:
			case BD_FIREFLYl:
			case BD_FIREFLYt:
			case BD_FIREFLYd:
				if (move_tick == 0)
				{
					int dir = positionChecker.FireflyLeft(curr_type);

					for (int di = 0; di<4; di++)
					{
						if (
							(new_cavemap[x + positionChecker.MoveX(di)][y + positionChecker.MoveY(di)] == BD_ROCKFORD) ||
							(new_cavemap[x + positionChecker.MoveX(di)][y + positionChecker.MoveY(di)] == BD_ROCKFORDgrab)
							)
						{
							gameEffects.Explode(new_cavemap, x, y);
							game->Lost = 1;
						}
						if (new_cavemap[x + positionChecker.MoveX(di)][y + positionChecker.MoveY(di)] == BD_AMOEBA)
						{
							gameEffects.Explode(new_cavemap, x, y);
						}
					}

					if (new_cavemap[x][y] != BD_EXPLOSION1)
					{
						if (new_cavemap[x + positionChecker.FireflyX(dir)][y + positionChecker.FireflyY(dir)] == BD_SPACE)
						{
							new_cavemap[x + positionChecker.FireflyX(dir)][y + positionChecker.FireflyY(dir)] = dir;
							new_cavemap[x][y] = BD_SPACE;
						}
						else if (new_cavemap[x + positionChecker.FireflyX(curr_type)][y + positionChecker.FireflyY(curr_type)] == BD_SPACE)
						{
							new_cavemap[x + positionChecker.FireflyX(curr_type)][y + positionChecker.FireflyY(curr_type)] = curr_type;
							new_cavemap[x][y] = BD_SPACE;
						}
						else
						{
							new_cavemap[x][y] = positionChecker.FireflyRight(curr_type);
						}
					}
				}
				break;
				//there must still be a bug, oberserved a resting diamond on top a freestanding boulder
			case BD_BUTTERFLYr:
			case BD_BUTTERFLYl:
			case BD_BUTTERFLYu:
			case BD_BUTTERFLYd:
				if (move_tick == 0)
				{
					int dir = positionChecker.ButterflyLeft(curr_type);

					for (int di = 0; di<4; di++)
					{
						if (
							(new_cavemap[x + positionChecker.MoveX(di)][y + positionChecker.MoveY(di)] == BD_ROCKFORD) ||
							(new_cavemap[x + positionChecker.MoveX(di)][y + positionChecker.MoveY(di)] == BD_ROCKFORDgrab)
							)
						{
							gameEffects.Dexplode(new_cavemap, x, y);
							game->Lost = 1;
						}
						if (new_cavemap[x + positionChecker.MoveX(di)][y + positionChecker.MoveY(di)] == BD_AMOEBA)
						{
							gameEffects.Dexplode(new_cavemap, x, y);
						}
					}

					if (new_cavemap[x][y] != BD_DEXPLOSION1)
					{
						if (new_cavemap[x + positionChecker.ButterflyX(dir)][y + positionChecker.ButterflyY(dir)] == BD_SPACE)
						{
							new_cavemap[x + positionChecker.ButterflyX(dir)][y + positionChecker.ButterflyY(dir)] = dir;
							new_cavemap[x][y] = BD_SPACE;
						}
						else if (new_cavemap[x + positionChecker.ButterflyX(curr_type)][y + positionChecker.ButterflyY(curr_type)] == BD_SPACE)
						{
							new_cavemap[x + positionChecker.ButterflyX(curr_type)][y + positionChecker.ButterflyY(curr_type)] = curr_type;
							new_cavemap[x][y] = BD_SPACE;
						}
						else
						{
							new_cavemap[x][y] = positionChecker.ButterflyRight(curr_type);
						}
					}
				}
				break;
			}
		}
	}
	if ((valid_rockford == 0) && (game->Lost == 0))
		game->Lost = 1;


	game->AmoebaSpace = amoeba_possible;




	for (int y = 1; y < CAVE_HEIGHT - 1; y++)
	{
		for (int x = 0; x < CAVE_WIDTH; x++)
		{
			game->cavemap[x][y] = new_cavemap[x][y];
		}
	}

	sdlUtils.SdlReleaseKeys();
}
