#pragma once
#include "GameSupport.h"
#include "Cave.h"
#include "GameInfo.h"

class NoiseMaker
{
private:
	GameSupport support;
public:
	NoiseMaker();
	NoiseMaker(GameSupport support);
	~NoiseMaker();

	void CreateNoiseInMap(Cave& cave, GameInfo& gameInfo, int difficulty);
};

