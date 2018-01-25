#pragma once
#include "GameInfo.h"
#include "GlobalValues.h"
#include "ActionMapping.h"
#include "GameObjects.h"
#include "Action.h"
#include "ActionContext.h"

class ActionHandler
{
private:
	ActionMapping actionMapping;

public:
	ActionHandler();
	ActionHandler(ActionMapping actionMapping);
	~ActionHandler();

	void HandleAllMapChanges(GameInfo* game, int cave[CAVE_WIDTH][CAVE_HEIGHT], int move, int fall);
};

