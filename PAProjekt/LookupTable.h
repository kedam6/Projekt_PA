#pragma once
#include <vector>

using namespace std;

template<typename T, typename U>
class LookupTable
{
private:
	vector<T> coll;
public:
	LookupTable() = 0;
	~LookupTable() = 0;
	
	T Get(U index) = 0;
};

