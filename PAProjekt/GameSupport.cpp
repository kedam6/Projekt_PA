#include "GameSupport.h"
#include <functional>

using namespace std;

GameSupport::GameSupport()
{
}


GameSupport::~GameSupport()
{
}

void GameSupport::NextRandom(int * seed1, int * seed2)
{
	short TempRand1;
	short TempRand2;
	short carry;
	short result;

	TempRand1 = (*seed1 & 0x0001) * 0x0080;
	TempRand2 = (*seed2 >> 1) & 0x007F;
	result = (*seed2) + (*seed2 & 0x0001) * 0x0080;
	carry = (result > 0x00FF);
	result = result & 0x00FF;
	result = result + carry + 0x13;
	carry = (result > 0x00FF);
	*seed2 = result & 0x00FF;
	result = *seed1 + carry + TempRand1;
	carry = (result > 0x00FF);
	result = result & 0x00FF;
	result = result + carry + TempRand2;
	*seed1 = result & 0x00FF;
}
