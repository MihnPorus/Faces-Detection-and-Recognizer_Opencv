#pragma once

#include <string>
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

class FramesReader
{
public:
	FramesReader();
	~FramesReader();
	Mat getNext();
private:
	VideoCapture *_vid;
};

