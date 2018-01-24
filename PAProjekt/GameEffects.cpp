#include "GameEffects.h"
#include "GlobalValues.h"
#include "Objects.h"


GameEffects::GameEffects()
{
}


GameEffects::~GameEffects()
{
}

void GameEffects::Explode(int map[CAVE_WIDTH][CAVE_HEIGHT], int x, int y)
{
	for (int dy = -1; dy < 2; dy++)
		for (int dx = -1; dx < 2; dx++)
			if (map[x + dx][y + dy] != BD_STEELWALL)
				map[x + dx][y + dy] = BD_EXPLOSION1;
}

void GameEffects::Dexplode(int map[CAVE_WIDTH][CAVE_HEIGHT], int x, int y)
{
	for (int dy = -1; dy<2; dy++)
		for (int dx = -1; dx<2; dx++)
			if (map[x + dx][y + dy] != BD_STEELWALL)
				map[x + dx][y + dy] = BD_DEXPLOSION1;
}
