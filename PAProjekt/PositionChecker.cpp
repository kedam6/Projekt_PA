#include "PositionChecker.h"
#include "Objects.h"


PositionChecker::PositionChecker()
{
}


PositionChecker::~PositionChecker()
{
}

int PositionChecker::ButterflyLeft(int butterfly)
{
	if (butterfly == BD_BUTTERFLYr) return BD_BUTTERFLYd;
	if (butterfly == BD_BUTTERFLYu) return BD_BUTTERFLYr;
	if (butterfly == BD_BUTTERFLYl) return BD_BUTTERFLYu;
	return BD_BUTTERFLYl;
}

int PositionChecker::ButterflyRight(int butterfly)
{
	if (butterfly == BD_BUTTERFLYr) return BD_BUTTERFLYu;
	if (butterfly == BD_BUTTERFLYd) return BD_BUTTERFLYr;
	if (butterfly == BD_BUTTERFLYl) return BD_BUTTERFLYd;
	return BD_BUTTERFLYl;
}

int PositionChecker::ButterflyX(int butterfly)
{
	if (butterfly == BD_BUTTERFLYr) return 1;
	if (butterfly == BD_BUTTERFLYd) return 0;
	if (butterfly == BD_BUTTERFLYl) return -1;
	return 0;
}

int PositionChecker::ButterflyY(int butterfly)
{
	if (butterfly == BD_BUTTERFLYr) return 0;
	if (butterfly == BD_BUTTERFLYd) return 1;
	if (butterfly == BD_BUTTERFLYl) return 0;
	return -1;
}

int PositionChecker::FireflyLeft(int firefly)
{
	if (firefly == BD_FIREFLYr) return BD_FIREFLYt;
	if (firefly == BD_FIREFLYt) return BD_FIREFLYl;
	if (firefly == BD_FIREFLYl) return BD_FIREFLYd;
	return BD_FIREFLYr;
}

int PositionChecker::FireflyRight(int firefly)
{
	if (firefly == BD_FIREFLYr) return BD_FIREFLYd;
	if (firefly == BD_FIREFLYd) return BD_FIREFLYl;
	if (firefly == BD_FIREFLYl) return BD_FIREFLYt;
	return BD_FIREFLYr;
}

int PositionChecker::FireflyX(int firefly)
{
	if (firefly == BD_FIREFLYr) return 1;
	if (firefly == BD_FIREFLYd) return 0;
	if (firefly == BD_FIREFLYl) return -1;
	return 0;
}

int PositionChecker::FireflyY(int firefly)
{
	if (firefly == BD_FIREFLYr) return 0;
	if (firefly == BD_FIREFLYd) return 1;
	if (firefly == BD_FIREFLYl) return 0;
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
