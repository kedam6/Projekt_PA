#pragma once
#include <map>
#include <algorithm>
#include <functional>
#include <vector>
#include "Color.h"

using namespace std;

class ColorRepository
{
private:
	map<int, Color> colorLUT;
public:
	ColorRepository();
	~ColorRepository();
	void InitLUT();
	bool IsKeyPresentInLUT(int key);
	void GetColors(int type, int tick, int * colors);
};

