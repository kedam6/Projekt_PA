#include "Cave.h"



Cave::Cave()
{
}


Cave::~Cave()
{
}

void Cave::FillCaveWithData(const int* items)
{
	caveData = (struct Cave::CaveData*)items;
}
