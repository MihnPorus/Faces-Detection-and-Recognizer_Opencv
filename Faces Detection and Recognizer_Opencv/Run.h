#pragma once
#include "defs.h"
#include "FramesReader.h"
#include "FaceDetector.h"
#include "PersonRecognizer.h"
#include "PrepareFaces.h"
#include <fstream>
#include <iostream>

using namespace std;
using namespace cv;
class Run
{
private:
	PersonRecognizer *pr;
	FramesReader *fr ;
	PrepareFaces *prs ;
	FaceDetector *fd ;
	vector<Mat>  *training_set ;
	vector<Rect> *faces ;
	Mat *captureFrame ;


public:
	void Face_Capture();
	void Face_Recognition();
	Run();
	~Run();
};

