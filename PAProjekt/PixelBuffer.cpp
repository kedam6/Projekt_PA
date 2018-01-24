#include "PixelBuffer.h"



PixelBuffer::PixelBuffer(unsigned int* pixelBuffer)
{
	this->pixelBuffer = pixelBuffer;
}

PixelBuffer::~PixelBuffer()
{
	//delete pixelBuffer;
}

unsigned int * PixelBuffer::GetBuffer()
{
	return pixelBuffer;
}
