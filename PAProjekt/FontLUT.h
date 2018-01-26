#pragma once
#include "LookupTable.h"


class FontLUT : public LookupTable<int, unsigned int>
{
public:
	FontLUT()
	{
		this->Init(vector<int> {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, vector<unsigned int> { 32319, 17393, 24253, 32437, 31879, 30391, 29343, 31905, 32447, 31911 });
	}
	~FontLUT();

	unsigned int operator[] (int x) {
		return Get(x);
	}
};

