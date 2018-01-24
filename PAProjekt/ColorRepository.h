#pragma once
#include <map>
#include <algorithm>
#include <functional>

using namespace std;

class ColorRepository
{
private:
	map<int, void(int*, int) const, greater_equal<int>> colorLUT;
public:
	ColorRepository();
	~ColorRepository();
	void InitLUT();
	void GetColors(int type, int tick, int * colors);
};

