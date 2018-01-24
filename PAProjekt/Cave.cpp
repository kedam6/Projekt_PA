#include "Cave.h"



Cave::Cave()
{
}


Cave::~Cave()
{
}

void Cave::FillCaveWithData(const int* items)
{
	//struct Cave::CaveData* yes = (struct Cave::CaveData*)items;
	caveData = (struct Cave::CaveData*)items;
	//caveData = &Cave::CaveData();

	//caveData->DiamonValue = *(items);
	//caveData->DiamonValueBonus = *(items + 1);
	//caveData->DiamondsRequired[0] = *(items + 2);
	//caveData->DiamondsRequired[1] = *(items +3);
	//caveData->DiamondsRequired[2] = *(items +4);
	//caveData->DiamondsRequired[3] = *(items +5);
	//caveData->DiamondsRequired[4] = *(items +6);
	//caveData->CaveTime[0] = *(items +7);
	//caveData->CaveTime[1] = *(items +8);
	//caveData->CaveTime[2] = *(items +9);
	//caveData->CaveTime[3] = *(items +10);
	//caveData->CaveTime[4] = *(items +11);
	//caveData->Colors[0] = *(items +12);
	//caveData->Colors[1] = *(items +13);
	//caveData->Colors[2] = *(items +14);
	//caveData->RandSeed[0] = *(items +15);
	//caveData->RandSeed[1] = *(items +16);
	//caveData->RandSeed[2] = *(items +17);
	//caveData->RandSeed[3] = *(items +18);
	//caveData->RandSeed[4] = *(items +19);
	//caveData->RandomFill[0] = *(items +20);
	//caveData->RandomFill[1] = *(items +21);
	//caveData->RandomFill[2] = *(items +22);
	//caveData->RandomFill[3] = *(items +23);
	//caveData->RandomFill[4] = *(items +24);
	//caveData->RandomFill[5] = *(items +25);
	//caveData->RandomFill[6] = *(items +26);
	//caveData->RandomFill[7] = *(items +27);
	//caveData->MagicWallTime = *(items +28);
	//caveData->AmoebaTime = *(items +29);
	//caveData->DrawItems = *(items +30);
}
