#pragma once
class PixelBuffer
{
private:
	unsigned int* pixelBuffer;
public:
	PixelBuffer(unsigned int* pixelBuffer);
	PixelBuffer() {}
	~PixelBuffer();

	unsigned int* GetBuffer();
};

