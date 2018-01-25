#include "ActionMapping.h"
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


ActionMapping::ActionMapping()
{
}

ActionMapping::ActionMapping(PositionChecker positionChecker, GameEffects gameEffects, GameSupport gameSupport, InputHandler inputHandler)
{
	this->positionChecker = positionChecker;
	this->gameEffects = gameEffects;
	this->gameSupport = gameSupport;
	this->inputHandler = inputHandler;
	InitMapping();
}

void ActionMapping::InitMapping()
{
	AmoebaAction amoeba = AmoebaAction(positionChecker);
	DexplosionAction dexplosion = DexplosionAction();
	EnemyAction enemy = EnemyAction(gameEffects, positionChecker);
	ExplosionAction explosion = ExplosionAction();
	MineralAction mineral = MineralAction(gameSupport);
	FallingAction falling = FallingAction(gameEffects, mineral);
	InboxAction inbox = InboxAction();
	MagicWallAction magicwall = MagicWallAction();

	OutboxAction outbox = OutboxAction();
	PlayerAction player = PlayerAction(gameEffects, positionChecker);
	RockfordAction rockford = RockfordAction(gameEffects, positionChecker, inputHandler);

	mapping[DATA_AMOEBA] = &amoeba;
	mapping[DATA_OUTBOX] = &amoeba;
	mapping[DATA_EXPLOSION1] = &explosion;
	mapping[DATA_EXPLOSION2] = &explosion;
	mapping[DATA_EXPLOSION3] = &explosion;
	mapping[DATA_EXPLOSION4] = &explosion;
	mapping[DATA_EXPLOSION5] = &explosion;
	mapping[DATA_DEXPLOSION1] = &dexplosion;
	mapping[DATA_DEXPLOSION2] = &dexplosion;
	mapping[DATA_DEXPLOSION3] = &dexplosion;
	mapping[DATA_DEXPLOSION4] = &dexplosion;
	mapping[DATA_DEXPLOSION5] = &dexplosion;
	mapping[DATA_INBOX] = &inbox;
	mapping[DATA_ROCKFORD_GRAB] = &rockford;
	mapping[DATA_ROCKFORD] = &rockford;
	mapping[DATA_DIAMOND_FALL] = &falling;
	mapping[DATA_BOULDER_FALL] = &falling;
	mapping[DATA_BOULDER] = &mineral;
	mapping[DATA_DIAMOND] = &mineral;
	mapping[DATA_MAGICWALL] = &magicwall;
	mapping[DATA_FIREFLY_RIGHT] = &enemy;
	mapping[DATA_FIREFLY_LEFT] = &enemy;
	mapping[DATA_FIREFLY_TOP] = &enemy;
	mapping[DATA_FIREFLY_DOWN] = &enemy;
	mapping[DATA_BUTTERFLY_RIGHT] = &player;
	mapping[DATA_BUTTERFLY_LEFT] = &player;
	mapping[DATA_BUTTERFLY_UP] = &player;
	mapping[DATA_BUTTERFLY_DOWN] = &player;
}

ActionMapping::~ActionMapping()
{
}

bool ActionMapping::MappingHasKey(int key)
{
	map<int, Action*>::iterator it = mapping.find(key);

	return it != mapping.end();
}

Action* ActionMapping::GetActionForType(int type)
{
	if (MappingHasKey(type))
	{
		return mapping[type];
	}

	return NULL;
}
