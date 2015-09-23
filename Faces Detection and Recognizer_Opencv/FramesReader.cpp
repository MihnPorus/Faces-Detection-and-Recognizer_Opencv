#include "FramesReader.h"

FramesReader::FramesReader( )
{
	_vid = new VideoCapture;
	_vid->open(0);
	
}

Mat FramesReader::getNext() {
	Mat *img =new Mat;
	*_vid >> *img;
	return *img;
}

FramesReader::~FramesReader() {
	_vid->release();
}


