#pragma once
class Cave
{
public:
	Cave();
	~Cave();

	struct CaveData
	{
		int DiamonValue;
		int DiamonValueBonus;
		int DiamondsRequired[5];
		int CaveTime[5];
		int Colors[3];
		int RandSeed[5];
		int RandomFill[8];
		int MagicWallTime;
		int AmoebaTime;
		int DrawItems;
	};

	struct CaveData* caveData;

	void FillCaveWithData(const int* items);

};

