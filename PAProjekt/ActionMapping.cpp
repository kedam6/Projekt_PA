#include "ActionMapping.h"


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
	amoeba = AmoebaAction(positionChecker);
	dexplosion = DexplosionAction();
	enemy = EnemyAction(gameEffects, positionChecker);
	explosion = ExplosionAction();
	mineral = MineralAction(gameSupport);
	falling = FallingAction(gameEffects, mineral);
	inbox = InboxAction();
	magicwall = MagicWallAction();

	outbox = OutboxAction();
	player = PlayerAction(gameEffects, positionChecker);
	rockford = RockfordAction(gameEffects, positionChecker, inputHandler);

	mapping[DATA_AMOEBA] = &amoeba;
	mapping[DATA_OUTBOX] = &outbox;
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
