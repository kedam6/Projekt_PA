#include "Engine.h"
#include "GlobalValues.h"
#include "GameObjects.h"
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
			case DATA_AMOEBA:
				if (game->AmoebaSpace == 0)
				{
					new_cavemap[x][y] = DATA_DIAMOND;
				}
				else
					for (int dir = 1; dir<5; dir++)
					{
						if (
							(new_cavemap[x + positionChecker.MoveX(dir)][y + positionChecker.MoveY(dir)] == DATA_SPACE) ||
							(new_cavemap[x + positionChecker.MoveX(dir)][y + positionChecker.MoveY(dir)] == DATA_DIRT)
							)
						{
							amoeba_possible++;
							if (((game->AmoebaTime * 8) < tick) && (rand() % 15 == 0))
							{
								new_cavemap[x + positionChecker.MoveX(dir)][y + positionChecker.MoveY(dir)] = DATA_AMOEBA;
							}
							else if ((game->Tick>START_DELAY) && (rand() % 100 == 0))
							{
								new_cavemap[x + positionChecker.MoveX(dir)][y + positionChecker.MoveY(dir)] = DATA_AMOEBA;
							}
						}
					}
				break;
			case DATA_OUTBOX:
				if (game->DiamondsCollected >= game->DiamondsRequired)
				{
					new_cavemap[x][y] = DATA_OUTBOX_ACTIVE;
				}
				break;
			case DATA_EXPLOSION1:
			case DATA_EXPLOSION2:
			case DATA_EXPLOSION3:
			case DATA_EXPLOSION4:
				if (expl_tick == 0)
				{
					new_cavemap[x][y] = curr_type + 1;
				}
				break;
			case DATA_EXPLOSION5:
				if (expl_tick == 0)
				{
					new_cavemap[x][y] = DATA_SPACE;
				}
				break;
			case DATA_DEXPLOSION1:
			case DATA_DEXPLOSION2:
			case DATA_DEXPLOSION3:
			case DATA_DEXPLOSION4:
				if (expl_tick == 0)
				{
					new_cavemap[x][y] = curr_type + 1;
				}
				break;
			case DATA_DEXPLOSION5:
				if (expl_tick == 0)
				{
					new_cavemap[x][y] = DATA_DIAMOND;
				}
				break;
			case DATA_INBOX:
				valid_rockford = 1;
				game->Player_X = x;
				if (game->Tick == START_DELAY)
					new_cavemap[x][y] = DATA_ROCKFORD;

				break;
			case DATA_ROCKFORD_GRAB:
			case DATA_ROCKFORD:
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
							(new_cavemap[x + positionChecker.MoveX(direction)][y + positionChecker.MoveY(direction)] == DATA_SPACE) ||
							(new_cavemap[x + positionChecker.MoveX(direction)][y + positionChecker.MoveY(direction)] == DATA_DIRT)
							)
						{
							new_cavemap[x + positionChecker.MoveX(direction)][y + positionChecker.MoveY(direction)] = DATA_ROCKFORD;
							new_cavemap[x][y] = DATA_SPACE;
							game->Player_X = x + positionChecker.MoveX(direction);
						}
						if (
							new_cavemap[x + positionChecker.MoveX(direction)][y + positionChecker.MoveY(direction)] == DATA_OUTBOX_ACTIVE
							)
						{
							new_cavemap[x + positionChecker.MoveX(direction)][y + positionChecker.MoveY(direction)] = DATA_ROCKFORD;
							new_cavemap[x][y] = DATA_SPACE;
							game->Player_X = x + positionChecker.MoveX(direction);
							game->Won = 1;
						}
						else if (
							(new_cavemap[x + positionChecker.MoveX(direction)][y + positionChecker.MoveY(direction)] == DATA_DIAMOND) ||
							(new_cavemap[x + positionChecker.MoveX(direction)][y + positionChecker.MoveY(direction)] == DATA_DIAMOND_FALL)
							)
						{
							new_cavemap[x + positionChecker.MoveX(direction)][y + positionChecker.MoveY(direction)] = DATA_ROCKFORD;
							new_cavemap[x][y] = DATA_SPACE;
							game->Player_X = x + positionChecker.MoveX(direction);
							game->DiamondsCollected++;
						}
						else if (
							(new_cavemap[x + positionChecker.MoveX(direction)][y] == DATA_BOULDER) &&
							(positionChecker.MoveY(direction) == 0)
							)
						{
							if (curr_type == DATA_ROCKFORD_GRAB)
							{
								if (new_cavemap[x + positionChecker.MoveX(direction) * 2][y] == DATA_SPACE)
								{
									new_cavemap[x + positionChecker.MoveX(direction) * 2][y] = DATA_BOULDER;
									new_cavemap[x + positionChecker.MoveX(direction)][y] = DATA_ROCKFORD;
									game->Player_X = x + positionChecker.MoveX(direction);
									new_cavemap[x][y] = DATA_SPACE;
								}
							}
							else
							{
								new_cavemap[x][y] = DATA_ROCKFORD_GRAB;
							}
						}

					}
				}
				break;
			case DATA_DIAMOND_FALL:
			case DATA_BOULDER_FALL:
				if (fall_tick == 0)
				{
					if (
						(new_cavemap[x][y + 1] == DATA_FIREFLY_TOP) ||
						(new_cavemap[x][y + 1] == DATA_FIREFLY_LEFT) ||
						(new_cavemap[x][y + 1] == DATA_FIREFLY_RIGHT) ||
						(new_cavemap[x][y + 1] == DATA_FIREFLY_DOWN) ||
						(new_cavemap[x][y + 1] == DATA_ROCKFORD)
						)
					{
						if (new_cavemap[x][y + 1] == DATA_ROCKFORD)
							game->Lost = 1;
						gameEffects.Explode(new_cavemap, x, y + 1);

					}
					else if (
						(curr_type == DATA_BOULDER_FALL) &&
						(new_cavemap[x][y + 1] == DATA_MAGICWALL)
						)
					{
					}
					else if (
						(new_cavemap[x][y + 1] != DATA_SPACE) &&
						(new_cavemap[x][y + 1] != DATA_MAGICWALL_ACTIVE)
						)
					{
						new_cavemap[x][y] -= 1;
					}
					fall = 0;
				}
			case DATA_BOULDER:
			case DATA_DIAMOND:
				if (fall_tick == 0)
				{
					if (
						((new_cavemap[x][y] == DATA_BOULDER) || (new_cavemap[x][y] == DATA_DIAMOND)) &&
						(new_cavemap[x][y + 1] == DATA_SPACE)
						)
					{
						new_cavemap[x][y + 1] = curr_type + fall;
						new_cavemap[x][y] = DATA_SPACE;
					}
					else if (
						new_cavemap[x][y + 1] == DATA_SPACE
						)
					{
						new_cavemap[x][y] = DATA_SPACE;
						new_cavemap[x][y + 1] = curr_type + fall;
					}
					else if (
						((new_cavemap[x][y + 1] == DATA_BOULDER) || (new_cavemap[x][y + 1] == DATA_DIAMOND)) &&
						(new_cavemap[x - 1][y + 1] == DATA_SPACE) &&
						(new_cavemap[x - 1][y] == DATA_SPACE)

						)
					{
						new_cavemap[x - 1][y] = curr_type + fall;
						new_cavemap[x][y] = DATA_SPACE;
					}
					else if (
						((new_cavemap[x][y + 1] == DATA_BOULDER) || (new_cavemap[x][y + 1] == DATA_DIAMOND)) &&
						(new_cavemap[x + 1][y + 1] == DATA_SPACE) &&
						(new_cavemap[x + 1][y] == DATA_SPACE)

						)
					{
						new_cavemap[x + 1][y] = curr_type + fall;
						new_cavemap[x][y] = DATA_SPACE;
					}
					else if (
						(new_cavemap[x][y + 1] == DATA_MAGICWALL) &&
						(new_cavemap[x][y] == DATA_BOULDER_FALL)
						)
					{
						game->MagicWallActive = 1;
					}
					else if (
						(new_cavemap[x][y + 1] == DATA_MAGICWALL_ACTIVE) &&
						((new_cavemap[x][y] == DATA_DIAMOND_FALL) ||
						(new_cavemap[x][y] == DATA_BOULDER_FALL)) &&
							(new_cavemap[x][y + 2] == DATA_SPACE)
						)
					{
						new_cavemap[x][y + 2] = DATA_DIAMOND_FALL;
						new_cavemap[x][y] = DATA_SPACE;
					}
					else if (
						(new_cavemap[x][y + 1] == DATA_MAGICWALL_ACTIVE) &&
						((new_cavemap[x][y] == DATA_DIAMOND_FALL) ||
						(new_cavemap[x][y] == DATA_BOULDER_FALL)) &&
							(new_cavemap[x][y + 2] != DATA_SPACE)
						)
					{
						new_cavemap[x][y] = DATA_SPACE;
					}
					else if (
						(new_cavemap[x][y + 1] == DATA_SLIME) &&
						(new_cavemap[x][y] == DATA_DIAMOND) &&
						(new_cavemap[x][y + 2] == DATA_SPACE)
						)
					{
						support.NextRandom(&game->SlimeSeed1, &game->SlimeSeed2);
						if (game->SlimeSeed1 < 10)
						{
							new_cavemap[x][y + 2] = DATA_DIAMOND_FALL;
							new_cavemap[x][y] = DATA_SPACE;
						}
					}
					else if (
						(new_cavemap[x][y + 1] == DATA_SLIME) &&
						(new_cavemap[x][y] == DATA_BOULDER) &&
						(new_cavemap[x][y + 2] == DATA_SPACE)
						)
					{
						support.NextRandom(&game->SlimeSeed1, &game->SlimeSeed2);
						if (game->SlimeSeed1 < 10)
						{
							new_cavemap[x][y + 2] = DATA_BOULDER_FALL;
							new_cavemap[x][y] = DATA_SPACE;
						}
					}
				}
				break;
			case DATA_MAGICWALL:
				if (game->MagicWallActive == 1)
				{
					new_cavemap[x][y] = DATA_MAGICWALL_ACTIVE;
				}
				break;
			case DATA_FIREFLY_RIGHT:
			case DATA_FIREFLY_LEFT:
			case DATA_FIREFLY_TOP:
			case DATA_FIREFLY_DOWN:
				if (move_tick == 0)
				{
					int dir = positionChecker.FireflyLeft(curr_type);

					for (int di = 0; di<4; di++)
					{
						if (
							(new_cavemap[x + positionChecker.MoveX(di)][y + positionChecker.MoveY(di)] == DATA_ROCKFORD) ||
							(new_cavemap[x + positionChecker.MoveX(di)][y + positionChecker.MoveY(di)] == DATA_ROCKFORD_GRAB)
							)
						{
							gameEffects.Explode(new_cavemap, x, y);
							game->Lost = 1;
						}
						if (new_cavemap[x + positionChecker.MoveX(di)][y + positionChecker.MoveY(di)] == DATA_AMOEBA)
						{
							gameEffects.Explode(new_cavemap, x, y);
						}
					}

					if (new_cavemap[x][y] != DATA_EXPLOSION1)
					{
						if (new_cavemap[x + positionChecker.FireflyX(dir)][y + positionChecker.FireflyY(dir)] == DATA_SPACE)
						{
							new_cavemap[x + positionChecker.FireflyX(dir)][y + positionChecker.FireflyY(dir)] = dir;
							new_cavemap[x][y] = DATA_SPACE;
						}
						else if (new_cavemap[x + positionChecker.FireflyX(curr_type)][y + positionChecker.FireflyY(curr_type)] == DATA_SPACE)
						{
							new_cavemap[x + positionChecker.FireflyX(curr_type)][y + positionChecker.FireflyY(curr_type)] = curr_type;
							new_cavemap[x][y] = DATA_SPACE;
						}
						else
						{
							new_cavemap[x][y] = positionChecker.FireflyRight(curr_type);
						}
					}
				}
				break;
				//there must still be a bug, oberserved a resting diamond on top a freestanding boulder
			case DATA_BUTTERFLY_RIGHT:
			case DATA_BUTTERFLY_LEFT:
			case DATA_BUTTERFLY_UP:
			case DATA_BUTTERFLY_DOWN:
				if (move_tick == 0)
				{
					int dir = positionChecker.ButterflyLeft(curr_type);

					for (int di = 0; di<4; di++)
					{
						if (
							(new_cavemap[x + positionChecker.MoveX(di)][y + positionChecker.MoveY(di)] == DATA_ROCKFORD) ||
							(new_cavemap[x + positionChecker.MoveX(di)][y + positionChecker.MoveY(di)] == DATA_ROCKFORD_GRAB)
							)
						{
							gameEffects.Dexplode(new_cavemap, x, y);
							game->Lost = 1;
						}
						if (new_cavemap[x + positionChecker.MoveX(di)][y + positionChecker.MoveY(di)] == DATA_AMOEBA)
						{
							gameEffects.Dexplode(new_cavemap, x, y);
						}
					}

					if (new_cavemap[x][y] != DATA_DEXPLOSION1)
					{
						if (new_cavemap[x + positionChecker.ButterflyX(dir)][y + positionChecker.ButterflyY(dir)] == DATA_SPACE)
						{
							new_cavemap[x + positionChecker.ButterflyX(dir)][y + positionChecker.ButterflyY(dir)] = dir;
							new_cavemap[x][y] = DATA_SPACE;
						}
						else if (new_cavemap[x + positionChecker.ButterflyX(curr_type)][y + positionChecker.ButterflyY(curr_type)] == DATA_SPACE)
						{
							new_cavemap[x + positionChecker.ButterflyX(curr_type)][y + positionChecker.ButterflyY(curr_type)] = curr_type;
							new_cavemap[x][y] = DATA_SPACE;
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

void Engine::Close()
{
	sdlUtils.SdlClose();
}

GameInfo Engine::InitGame()
{
	//create buffer
	PixelBuffer pixelBuffer = sdlUtils.SdlInit(CAVE_WIDTH * ZOOM, (INFO_HEIGHT + CAVE_HEIGHT) * ZOOM, "BD (based on Boulder Dash 2 from Commodore 64)", 60);
	this->buffer = pixelBuffer;
	//init game
	GameInfo ret = GameInitInfo().InitGame(0, 0);

	return ret;
}

bool Engine::HandleEvents()
{
	return sdlUtils.SdlHandleEvents((void*)buffer.GetBuffer());
}

bool Engine::LimitFps(int * limiter)
{
	return sdlUtils.SdlLimitFps(limiter);
}

PixelBuffer Engine::GetPixelBuffer()
{
	return buffer;
}
