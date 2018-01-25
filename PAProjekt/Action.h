#pragma once
#include "BaseAction.h"
#include "GameObjects.h"

class Action : public BaseAction
{
private:
	int id;

public:
	Action();
	Action(int id);
	~Action();
	int GetId() { return id; }
};

