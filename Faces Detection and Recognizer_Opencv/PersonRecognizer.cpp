#include "PersonRecognizer.h"


PersonRecognizer::PersonRecognizer(const vector<Mat> &imgs, int radius, int neighbors,
	int grid_x, int grid_y, double threshold, vector<int> labels) {
	_model = new Ptr < FaceRecognizer > ;
	// tất cả hình ảnh là khuôn mặt của cùng một người, vì vậy khởi tạo các nhãn tương tự cho tất cả.
	_faceSize = Size(imgs[0].size().width, imgs[0].size().height);

	//  xây dựng mô hình nhận diện:
	*_model = createLBPHFaceRecognizer(radius, neighbors, grid_x, grid_y, threshold);
	(*_model)->train(imgs, labels);
}

PersonRecognizer::~PersonRecognizer() {
	_model->release();
}

bool PersonRecognizer::recognize(const Mat &face, double &confidence,int &label) const {
	Mat gray;
	cvtColor(face, gray, CV_BGR2GRAY);//chuyển màu ảnh thành xám
	resize(gray, gray, _faceSize); // chỉnh lại kích thước ảnh
	(*_model)->predict(gray, label, confidence); // nhận dạng mặt, trả về label va confidence
	return label!=-1;
}
