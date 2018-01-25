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

bool GameManager::MoveToNextLevel(GameInfo* game)
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
		return true;
	}
	return false;
}

bool GameManager::RestartLevel(GameInfo* game)
{
	if (game->Lost == RESULT_CYCLES)
	{
		int old_cave = game->Cave;
		int old_difficulty = game->Difficulty;

		StartNewGame(game, old_cave, old_difficulty);
		return true;
	}

	return false;
}

void GameManager::Process(GameInfo* game)
{
	game->Tick++;

	int moveTick = 0;
	int fallTick = 0;


	CheckForSecretDevKey(game);

	if (PlayerWon(game))
	{
		moveTick = 1;
		fallTick = 1;

		//25 cykli gry aby pokazac graczowi jego zwyciestwo
		game->Won++;

		bool isSafeToReturn = MoveToNextLevel(game);
		
		if(isSafeToReturn)
			return;
	}


	if (PlayerLost(game))
	{
		//25 cykli gry aby pokazac graczowi jego porazke
		game->Lost++;

		bool isSafeToReturn = RestartLevel(game);
		
		if (isSafeToReturn)
			return;
	}

	int newMap[CAVE_WIDTH][CAVE_HEIGHT];
	mapHandler.SaveNewMap(game->cavemap, newMap);



	actionHandler.HandleAllMapChanges(game, newMap, moveTick, fallTick);



	//for (int y = 1; y < CAVE_HEIGHT - 1; y++)
	//{
	//	for (int x = 0; x < CAVE_WIDTH; x++)
	//	{
	//		game->cavemap[x][y] = newMap[x][y];
	//	}
	//}
	mapHandler.SaveNewMap(newMap, game->cavemap);

	sdlUtils.SdlReleaseKeys();
}
