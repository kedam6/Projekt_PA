#include "NoiseMaker.h"
#include "GlobalValues.h"
#include "GameObjects.h"
#include "GlobalInstances.h"


NoiseMaker::NoiseMaker()
{
}

NoiseMaker::NoiseMaker(GameSupport gameSupport)
{
	this->support = gameSupport;
}


NoiseMaker::~NoiseMaker()
{
}

void NoiseMaker::CreateNoiseInMap(Cave& cave, GameInfo& gameInfo, int difficulty)
{
	int RandSeed1 = 120;
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
}
