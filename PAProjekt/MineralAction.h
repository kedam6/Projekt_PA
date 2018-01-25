#pragma once
#include "Action.h"
#include "GameSupport.h"

class MineralAction :
	public Action
{
private:
	GameSupport support;
public:
	MineralAction();
	MineralAction(GameSupport support);
	~MineralAction();

	// Inherited via Action
	void PerformAction(GameInfo * game, int cave[CAVE_WIDTH][CAVE_HEIGHT], ActionContext & context) override;
};

