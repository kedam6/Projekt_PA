#include "GameInitInfo.h"
#include "Cave.h"
#include "CaveInfo.h"

extern const int CaveData[];
extern const int CaveStartIdx[];


GameInitInfo::GameInitInfo()
{

}

GameInitInfo::GameInitInfo(Graphics g, Renderer r, PositionChecker p, GameEffects ge, GameSupport s, NoiseMaker n, StageCreator sc)
{
	this->graphics = g;
	this->renderer = r;
	this->positionChecker = p;
	this->gameEffects = ge;
	this->support = s;
	this->noiseMaker = n;
	this->stageCreator = sc;
}


GameInitInfo::~GameInitInfo()
{
}

GameInfo GameInitInfo::InitGame(int level, int difficulty)
{
	GameInfo gameInfo = GameInfo();
	Cave cave = Cave();

	cave.FillCaveWithData(&CaveData[CaveStartIdx[level]]);

	for (int x = 0; x < CAVE_WIDTH; x++) {
		for (int y = 0; y < CAVE_HEIGHT; y++) {
			gameInfo.covered[x][y] = 1;
			gameInfo.cavemap[x][y] = DATA_STEELWALL;
		}
	}

	gameInfo.Won = 0;
	gameInfo.Lost = 0;
	gameInfo.Tick = 0;
	gameInfo.SlimeSeed1 = 0;
	gameInfo.SlimeSeed2 = 0;
	gameInfo.DiamondsCollected = 0;
	gameInfo.Player_X = 0;
	gameInfo.Cave = level;
	gameInfo.Difficulty = difficulty;
	gameInfo.DiamonValue = cave.caveData->DiamonValue;
	gameInfo.DiamonValueBonus = cave.caveData->DiamonValueBonus;
	gameInfo.DiamondsRequired = cave.caveData->DiamondsRequired[difficulty];
	gameInfo.CaveTime = cave.caveData->CaveTime[difficulty];
	gameInfo.Colors = cave.caveData->Colors;
	gameInfo.MagicWallTime = cave.caveData->MagicWallTime;
	gameInfo.MagicWallActive = 0;
	gameInfo.AmoebaTime = cave.caveData->AmoebaTime;
	gameInfo.AmoebaSpace = 1;
	gameInfo.Intermission = 0;

	noiseMaker.CreateNoiseInMap(cave, gameInfo, difficulty);

	stageCreator.CreateStage(gameInfo, cave);
	

	return gameInfo;
}
