#pragma once
#include <map>
#include "Action.h"
#include "PositionChecker.h"
#include "GameEffects.h"
#include "GameSupport.h"
#include "InputHandler.h"
#include "BlankAction.h"
#include "AmoebaAction.h"
#include "DexplosionAction.h"
#include "EnemyAction.h"
#include "ExplosionAction.h"
#include "FallingAction.h"
#include "InboxAction.h"
#include "MagicWallAction.h"
#include "MineralAction.h"
#include "OutboxAction.h"
#include "PlayerAction.h"
#include "RockfordAction.h"
#include "GameObjects.h"

using namespace std;

static AmoebaAction amoeba;
static DexplosionAction dexplosion;
static EnemyAction enemy;
static ExplosionAction explosion;
static MineralAction mineral;
static FallingAction falling;
static InboxAction inbox;
static MagicWallAction magicwall;
static OutboxAction outbox;
static PlayerAction player;
static RockfordAction rockford;


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

