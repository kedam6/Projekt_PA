#pragma once
#include <map>
#include <algorithm>
#include <vector>

using namespace std;

template<typename T, typename U>
class LookupTable
{
public:
	template<typename T, typename U>
	class InternalStorage {
	public:
		map<T, U> coll;
		InternalStorage() { coll = map<T, U>(); }

		int count;
		void Add(T key, U value) { coll[key] = value; }
		U Get(T key) { return coll[key]; }
		bool ContainsKey(T key) { return coll.find(key) != coll.end(); }
	};
private:


	bool initialized = false;
	InternalStorage<T, U> storage;
public:
	LookupTable() { storage = InternalStorage<T, U>(); }
	~LookupTable() {}
	
	inline void Init(vector<T> keys, vector<U> values)
	{
		for (int i = 0; i < keys.size(); i++)
		{
			storage.Add(keys[i], values[i]);
		}

		initialized = true;
	}

	U Get(T key)
	{
		if (initialized && storage.ContainsKey(key))
			return storage.Get(key);
	}
};

