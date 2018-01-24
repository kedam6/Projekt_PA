#pragma once
class PositionChecker
{
public:
	PositionChecker();
	~PositionChecker();
	int ButterflyLeft(int butterfly);
	int ButterflyRight(int butterfly);
	int ButterflyX(int butterfly);
	int ButterflyY(int butterfly);
	int FireflyLeft(int firefly);
	int FireflyRight(int firefly);
	int FireflyX(int firefly);
	int FireflyY(int firefly);
	int MoveX(int direction);
	int MoveY(int direction);
};

