#pragma once
#include "Action.h"
#include "MineralAction.h"
#include "GameEffects.h"

class FallingAction :
	public Action
{
private:
	MineralAction mineralAction;
	GameEffects gameEffects;
public:
	FallingAction();
	FallingAction(GameEffects gameEffects, MineralAction mineralAction);
	~FallingAction();

	// Inherited via Action
	virtual void PerformAction(GameInfo * game, int cave[CAVE_WIDTH][CAVE_HEIGHT], ActionContext & context) override;
};

