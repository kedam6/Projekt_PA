#pragma once
class FpsLimitter
{
private:
	int fpsMill;
	int initTick;

public:
	FpsLimitter();
	~FpsLimitter();
	void SetFpsMill(int mill);
	void LimitFps();
	int SdlLimitFps(int* limiter);
};

