#include "PrepareFaces.h"


PrepareFaces::PrepareFaces()
{
	Images = new vector < Mat > ;
	labels = new vector < int > ;
	List_name = new pair < vector<int>, vector<string> > ;
}


PrepareFaces::~PrepareFaces()
{
	Images->clear();
	labels->clear();
	List_name->first.clear();
	List_name->second.clear();
}

void PrepareFaces::Read_frame(const string &list_path)
{
	char separator = ';';
	std::ifstream file(list_path.c_str(), ifstream::in);
	if (!file) {
		string error_message = "Đầu vào tệp tin không hợp lệ, vui lòng kiểm tra lại!";
		CV_Error(CV_StsBadArg, error_message);
	}
	string line, path, classlabel;
	while (getline(file, line)) {
		stringstream liness(line);
		getline(liness, path, separator);
		getline(liness, classlabel);
		if (!path.empty() && !classlabel.empty()) {
			Images->push_back(imread(path, CV_LOAD_IMAGE_GRAYSCALE));
			labels->push_back(atoi(classlabel.c_str()));
		}
	}
}

void PrepareFaces::Write_frame(Mat &frame, char* name,int label,int i)
{	
	ofstream out_list(format("%s/%s", OUTPUT_DIR, OUTPUT_LISTFRAME).c_str(),ios::app);
	//resize:
	resize(frame, frame, FACE_SIZE);
	//write to disk:
	string face_path = format("%s/%s%d.jpg", OUTPUT_DIR, name,i);
	cout << face_path << endl;
	imwrite(face_path, frame);
	out_list << face_path << ";"<< label<<endl;
}

void PrepareFaces::Set_Listname(int key,char *name)
{
	List_name->second.push_back(name);
	List_name->first.push_back(key);
}

pair<vector<int>, vector<string> > PrepareFaces::Get_Listname()
{
	return *List_name;
}

vector<Mat> PrepareFaces::Get_image()
{
	
	return *Images;
}

vector<int> PrepareFaces::Get_labels()
{
	return *labels;
}

void PrepareFaces::Read_Listname(const string &list_path)
{
	char separator = ';';
	std::ifstream file(list_path.c_str(), ifstream::in);
	if (!file) {
		string error_message = "Đầu vào tệp tin không hợp lệ, vui lòng kiểm tra lại!";
		CV_Error(CV_StsBadArg, error_message);
	}
	string line, key,name;
	while (getline(file, line)) {
		stringstream liness(line);
		getline(liness, name, separator);
		getline(liness, key);
		if (!name.empty() && !key.empty()) {
			List_name->second.push_back(name);
			List_name->first.push_back(atoi(key.c_str()));
		}
	}
}

void PrepareFaces::Write_Listname(int key, char *name)
{
	ofstream out_list(format("%s/%s", OUTPUT_DIR, OUTPUT_LISTNAME).c_str(), ios::app);
	//write to disk:
	out_list << name << ";" << key << endl;
}

