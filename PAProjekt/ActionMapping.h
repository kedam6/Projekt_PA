#pragma once
#include <map>
#include "Action.h"
#include "PositionChecker.h"
#include "GameEffects.h"
#include "GameSupport.h"
#include "InputHandler.h"

using namespace std;

class ActionMapping
{
private:
	map<int, Action*> mapping;
	PositionChecker positionChecker;
	GameEffects gameEffects;
	GameSupport gameSupport;
	InputHandler inputHandler;

public:
	ActionMapping();
	ActionMapping(PositionChecker positionChecker, GameEffects gameEffects, GameSupport gameSupport, InputHandler inputHandler);
	void InitMapping();
	~ActionMapping();

	bool MappingHasKey(int type);

	Action* GetActionForType(int type);
};

