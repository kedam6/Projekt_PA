#pragma once
#include "Cave.h"
#include "IFactory.h"
#include "GlobalInstances.h"


class CaveFactory : public IFactory<Cave>
{
public:
	CaveFactory();
	~CaveFactory();

	Cave Create() override;
};

