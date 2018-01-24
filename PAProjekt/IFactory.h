#pragma once

template<typename T>
class IFactory
{
public:
	virtual T Create() = 0;
};