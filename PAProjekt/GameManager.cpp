#include "GameManager.h"



GameManager::GameManager()
{
}

GameManager::GameManager(SdlUtils utils, GameInitInfo initializer, Renderer renderer, PositionChecker positionChecker, Graphics graphics, GameEffects gameEff, GameSupport gameSupport, ActionHandler actionHandler)
{
	this->initializer = initializer;
	this->renderer = renderer;
	this->positionChecker = positionChecker;
	this->graphics = graphics;
	this->gameEffects = gameEff;
	this->support = gameSupport;
	this->sdlUtils = utils;
	this->mapHandler = MapHandler();
	this->actionHandler = actionHandler;
}


GameManager::~GameManager()
{
}

void GameManager::CheckForSecretDevKey(GameInfo* game)
{
	if (sdlUtils.SdlGetKey(6))
	{
		game->Won = 1;
	}
}

void GameManager::StartNewGame(GameInfo* game, int cave, int difficulty)
{
	auto newGame = initializer.InitGame(cave, difficulty);
	*game = newGame;
}

bool GameManager::PlayerWon(GameInfo* game)
{
	return game->Won > 0;
}

bool GameManager::PlayerLost(GameInfo* game)
{
	return game->Lost > 0;
}

void GameManager::MoveToNextLevel(GameInfo* game)
{
	if (game->Won == RESULT_CYCLES)
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

		StartNewGame(game, old_cave, old_difficulty);
		return;
	}
}

void GameManager::RestartLevel(GameInfo* game)
{
	if (game->Lost == RESULT_CYCLES)
	{
		int old_cave = game->Cave;
		int old_difficulty = game->Difficulty;

		StartNewGame(game, old_cave, old_difficulty);
		return;
	}
}

void GameManager::Process(GameInfo* game)
{
	game->Tick++;
	int tick = game->Tick;

	int move_tick = 0;
	int fall_tick = 0;
	int expl_tick = 0;

	CheckForSecretDevKey(game);

	if (PlayerWon(game))
	{
		move_tick = 1;
		fall_tick = 1;

		game->Won++;

		MoveToNextLevel(game);
	}


	if (PlayerLost(game))
	{
		//25 cykli gry aby pokazac graczowi jego porazke
		game->Lost++;

		RestartLevel(game);
	}

	int new_cavemap[CAVE_WIDTH][CAVE_HEIGHT];
	mapHandler.SaveNewMap(game->cavemap, new_cavemap);

	int amoeba_possible = 0;
	int valid_rockford = 0;

	actionHandler.HandleAllMapChanges(game, new_cavemap);

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
	mapHandler.SaveNewMap(new_cavemap, game->cavemap);

	sdlUtils.SdlReleaseKeys();
}
