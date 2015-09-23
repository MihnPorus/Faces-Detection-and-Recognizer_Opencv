#include "FaceDetector.h"

FaceDetector::FaceDetector(const string &cascadePath) {
	_cascade = new CascadeClassifier;
	_cascade->load(cascadePath);//Load thư viện haarcascades
}

FaceDetector::~FaceDetector() {
	_cascade->~CascadeClassifier();
}

void FaceDetector::findFacesInImage(const Mat *img, vector<Rect> *res) {
	Mat tmp;
	// chuyển đổi hình ảnh sang màu xám và bình thường hóa biểu đồ:
	cvtColor(*img, tmp, CV_BGR2GRAY);

	//Cân bằng lại
	equalizeHist(tmp, tmp);

	// làm sạch vector
	res->clear();

	// phát hiện khuôn mặt:
	_cascade->detectMultiScale(tmp, *res, DET_SCALE_FACTOR, DET_MIN_NEIGHBORS, CV_HAAR_FIND_BIGGEST_OBJECT | CV_HAAR_SCALE_IMAGE, Size(30, 30));
}