#pragma once

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <fstream>
#include "defs.h"
#include <iostream>

using namespace std;
using namespace cv;
class PrepareFaces
{
private:
	vector<Mat> *Images;
	vector<int> *labels;
	pair< vector<int>, vector<string> > *List_name;
	
public:
	PrepareFaces();
	void Read_frame( const string &list_path);
	void Write_frame(Mat &frame, char* name, int label,int i);
	void Read_Listname(const string &list_path);
	void Write_Listname(int key, char *name);
	vector<Mat> Get_image();	
	vector<int> Get_labels();	
	void Set_Listname(int key,char *name);
	pair<vector<int>, vector<string>  > Get_Listname();
	~PrepareFaces();
};

