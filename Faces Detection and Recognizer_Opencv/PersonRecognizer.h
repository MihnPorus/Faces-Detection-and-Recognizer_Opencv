#pragma once


#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/contrib/contrib.hpp"

using namespace cv;


class PersonRecognizer 
{
private:
	Ptr<FaceRecognizer> *_model;
	Size _faceSize;
public:
	PersonRecognizer(const vector<Mat> &imgs, int radius, int neighbors,
		int grid_x, int grid_y, double threshold, vector<int> labels);
	virtual ~PersonRecognizer();
	bool recognize(const Mat &face, double &confidence, int & label) const;

};
