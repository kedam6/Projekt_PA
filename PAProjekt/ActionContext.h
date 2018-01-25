#pragma once
class ActionContext
{
public:
	ActionContext();
	~ActionContext();
	int tick;
	int moveTick;
	int fallTick;
	int amoebaPossible;
	int validRockFord;
	int explTick;
	int fall;
	int currType;
	int x;
	int y;
};

