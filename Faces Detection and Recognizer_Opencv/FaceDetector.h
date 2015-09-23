#pragma once
#include <string>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "defs.h"
#include <iostream>

using namespace cv;

class FaceDetector {
public:
	FaceDetector( const string &cascadePath);
	~FaceDetector();
	void findFacesInImage(const Mat *img, vector<Rect> *res);
private:
	CascadeClassifier *_cascade;
};
