#include "PositionChecker.h"
#include "GameObjects.h"


PositionChecker::PositionChecker()
{
}


PositionChecker::~PositionChecker()
{
}

int PositionChecker::ButterflyLeft(int butterfly)
{
	if (butterfly == DATA_BUTTERFLY_RIGHT) return DATA_BUTTERFLY_DOWN;
	if (butterfly == DATA_BUTTERFLY_UP) return DATA_BUTTERFLY_RIGHT;
	if (butterfly == DATA_BUTTERFLY_LEFT) return DATA_BUTTERFLY_UP;
	return DATA_BUTTERFLY_LEFT;
}

int PositionChecker::ButterflyRight(int butterfly)
{
	if (butterfly == DATA_BUTTERFLY_RIGHT) return DATA_BUTTERFLY_UP;
	if (butterfly == DATA_BUTTERFLY_DOWN) return DATA_BUTTERFLY_RIGHT;
	if (butterfly == DATA_BUTTERFLY_LEFT) return DATA_BUTTERFLY_DOWN;
	return DATA_BUTTERFLY_LEFT;
}

int PositionChecker::ButterflyX(int butterfly)
{
	if (butterfly == DATA_BUTTERFLY_RIGHT) return 1;
	if (butterfly == DATA_BUTTERFLY_DOWN) return 0;
	if (butterfly == DATA_BUTTERFLY_LEFT) return -1;
	return 0;
}

int PositionChecker::ButterflyY(int butterfly)
{
	if (butterfly == DATA_BUTTERFLY_RIGHT) return 0;
	if (butterfly == DATA_BUTTERFLY_DOWN) return 1;
	if (butterfly == DATA_BUTTERFLY_LEFT) return 0;
	return -1;
}

int PositionChecker::FireflyLeft(int firefly)
{
	if (firefly == DATA_FIREFLY_RIGHT) return DATA_FIREFLY_TOP;
	if (firefly == DATA_FIREFLY_TOP) return DATA_FIREFLY_LEFT;
	if (firefly == DATA_FIREFLY_LEFT) return DATA_FIREFLY_DOWN;
	return DATA_FIREFLY_RIGHT;
}

int PositionChecker::FireflyRight(int firefly)
{
	if (firefly == DATA_FIREFLY_RIGHT) return DATA_FIREFLY_DOWN;
	if (firefly == DATA_FIREFLY_DOWN) return DATA_FIREFLY_LEFT;
	if (firefly == DATA_FIREFLY_LEFT) return DATA_FIREFLY_TOP;
	return DATA_FIREFLY_RIGHT;
}

int PositionChecker::FireflyX(int firefly)
{
	if (firefly == DATA_FIREFLY_RIGHT) return 1;
	if (firefly == DATA_FIREFLY_DOWN) return 0;
	if (firefly == DATA_FIREFLY_LEFT) return -1;
	return 0;
}

int PositionChecker::FireflyY(int firefly)
{
	if (firefly == DATA_FIREFLY_RIGHT) return 0;
	if (firefly == DATA_FIREFLY_DOWN) return 1;
	if (firefly == DATA_FIREFLY_LEFT) return 0;
	return -1;
}

int PositionChecker::MoveX(int direction)
{
	if (direction == 1) return 0;
	if (direction == 2) return 1;
	if (direction == 3) return 0;
	if (direction == 4) return -1;
	return 0;
}

int PositionChecker::MoveY(int direction)
{
	if (direction == 1) return -1;
	if (direction == 2) return 0;
	if (direction == 3) return 1;
	if (direction == 4) return 0;
	return 0;
}
