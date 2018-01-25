#pragma once
#include "GameInfo.h"
#include "GlobalValues.h"
#include "ActionMapping.h"

class ActionHandler
{
private:
	ActionMapping actionMapping;

public:
	ActionHandler();
	ActionHandler(ActionMapping actionMapping);
	~ActionHandler();

	void HandleAllMapChanges(GameInfo* game, int cave[CAVE_WIDTH][CAVE_HEIGHT]);
};

