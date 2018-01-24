#include "GlobalInstances.h"


GlobalInstances::~GlobalInstances()
{
}

template<typename T>
T GlobalInstances::GetItem()
{
	//nothing here
}

template<>
Engine GlobalInstances::GetItem()
{
	return engine;
}
template<>
Renderer GlobalInstances::GetItem()
{
	return renderer;
}
template<>
PositionChecker GlobalInstances::GetItem()
{
	return posChecker;
}
template<>
Graphics GlobalInstances::GetItem()
{
	return graphics;
}
template<>
GameEffects GlobalInstances::GetItem()
{
	return gameEffects;
}
template<>
GameSupport GlobalInstances::GetItem()
{
	return support;
}
template<>
SdlUtils GlobalInstances::GetItem()
{
	return sdlUtils;
}

//template<>
//GameSupport GlobalInstances::GetItem()
//{
//	return engine;
//}


