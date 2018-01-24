#pragma once
#include "Graphics.h"
#include "GameInfo.h"
#include "Cave.h"


class StageCreator
{
private:
	Graphics graphics;

public:
	StageCreator();
	StageCreator(Graphics g);
	~StageCreator();

	void CreateStage(GameInfo& gameInfo, Cave& cave);
};

