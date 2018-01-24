#include "GameInitInfo.h"
#include "Cave.h"
#include "CaveInfo.h"

extern const int CaveData[];
extern const int CaveStartIdx[];


GameInitInfo::GameInitInfo()
{
	renderer = Renderer();
	positionChecker = PositionChecker();
	graphics = Graphics();
	gameEffects = GameEffects();
	support = GameSupport();
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

	int RandSeed1 = 0;
	int RandSeed2 = cave.caveData->RandSeed[difficulty];

	for (int y = 1; y < CAVE_HEIGHT - 1; y++) {
		for (int x = 0; x < CAVE_WIDTH; x++) {
			support.NextRandom(&RandSeed1, &RandSeed2);
			int store = DATA_DIRT;
			for (int caveDataaddIndex = 0; caveDataaddIndex < 4; caveDataaddIndex++) {
				if (RandSeed1 < cave.caveData->RandomFill[caveDataaddIndex * 2 + 1]) {
					store = cave.caveData->RandomFill[caveDataaddIndex * 2];
				}
			}
			if ((x>0) && (x<CAVE_WIDTH - 1))
				gameInfo.cavemap[x][y] = store;
		}
	}

	if (level == 4)
	{
		gameInfo.Intermission = 1;
		for (int y = 1; y < CAVE_HEIGHT - 1; y++) {
			for (int x = 0; x < CAVE_WIDTH; x++) {
				if ((x>19) || (y>10))
					gameInfo.cavemap[x][y] = DATA_STEELWALL;
			}
		}
	}

	int *drawidx = (&cave.caveData->DrawItems) + 1;
	int offset = 0;

	for (int item = 0; item < cave.caveData->DrawItems; item++)
	{
		int type = *(drawidx + offset);

		switch (type)
		{
		case DATA_DRAW_LINE:
		case DATA_DRAW_FILLRECT:
			graphics.DrawFillRect(*(drawidx + offset + 1), *(drawidx + offset + 2), *(drawidx + offset + 3), *(drawidx + offset + 4), *(drawidx + offset + 5), gameInfo.cavemap);
			offset += 6;
			break;
		case DATA_DRAW_FILLRECT2:
			graphics.DrawFillRect2(*(drawidx + offset + 1), *(drawidx + offset + 2), *(drawidx + offset + 3), *(drawidx + offset + 4), *(drawidx + offset + 5), *(drawidx + offset + 6), gameInfo.cavemap);
			offset += 7;
			break;
		case DATA_DRAW_RECTANGLE:
			graphics.DrawRect(*(drawidx + offset + 1), *(drawidx + offset + 2), *(drawidx + offset + 3), *(drawidx + offset + 4), *(drawidx + offset + 5), gameInfo.cavemap);
			offset += 6;
			break;
		case DATA_DRAW_POINT:
			graphics.DrawPoint(*(drawidx + offset + 1), *(drawidx + offset + 2), *(drawidx + offset + 3), gameInfo.cavemap);
			offset += 4;
			break;
		case DATA_DRAW_RASTER:
			graphics.DrawRaster(*(drawidx + offset + 1), *(drawidx + offset + 2), *(drawidx + offset + 3), *(drawidx + offset + 4), *(drawidx + offset + 5), *(drawidx + offset + 6), *(drawidx + offset + 7), gameInfo.cavemap);
			offset += 8;
			break;
		}

	}




	return gameInfo;
}
