#include "Run.h"


Run::Run()
{
	fr = new FramesReader();
	prs = new PrepareFaces();
	fd = new FaceDetector(string(CASCADE_PATH_FACE));

	training_set = new vector < Mat > ;
	faces = new vector < Rect > ;
	captureFrame = new Mat;
	
	
}


Run::~Run()
{
	delete fr;
	delete prs;
	delete fd;
	delete training_set;
	delete faces;
	delete captureFrame;
}

void Run::Face_Capture()
{
	
	int i = 0;
	unsigned int key;
	char *name_  = new char;
	cout << "Nhap ten: "; fflush(stdin); cin.getline(name_, 25);
	cout << "Nhap ma so cho anh: "; cin >> key;
	prs->Write_Listname(key, name_);
	namedWindow("OutputCapture", WINDOW_NORMAL);
	cout << "Trich xuat anh khuon mat!" << endl;
	while (i<60)
	{
		//Nhận hình qua mỗi khung hình camera
		*captureFrame = fr->getNext();
		//Tìm khuôn mặt
		fd->findFacesInImage(captureFrame, faces);
		// trích xuất khuôn mặt Size(150,150)
		for (vector<Rect>::const_iterator face = faces->begin(); face != faces->end(); face++)
		{
			Point pt1(face->x + face->width, face->y + face->height);
			Point pt2(face->x, face->y);

			rectangle(*captureFrame, pt1, pt2, MATCH_COLOR, 1, 8, 0); //Tạo khung hình vuônng 

			Mat face_img = (*captureFrame)(*face);

			prs->Write_frame(face_img, name_, key,i++);
		}
		//Shows màn hình khuôn mặt
		imshow("OutputCapture", *captureFrame);
		
		waitKey(1);	
	}
	cout << "Hoan thanh!" << endl;
}

void Run::Face_Recognition()
{
	
	pair<vector<int>, vector<string> > List_name;
	prs->~PrepareFaces();
	prs->Read_frame(string(TRAINING_LISTFRAME));//Cập nhật Images và labels
	prs->Read_Listname(string(TRAINING_LISTNAME));//Cập nhật listname
	pr = new PersonRecognizer(prs->Get_image(), LBPH_RADIUS, LBPH_NEIGHBORS, LBPH_GRID_X, LBPH_GRID_Y, LBPH_THRESHOLD, prs->Get_labels());
	List_name = prs->Get_Listname();
	string box_text;
	
	cout << "Nhan ESC de thoat" << endl;
	while (true)
		{
			
			//Nhận hình qua mỗi khung hình camera
			*captureFrame = fr->getNext();
			//Tìm khuôn mặt
			fd->findFacesInImage(captureFrame, faces);

			
			double match_conf =-1;
			int label = -1;
			// vẽ một hình chữ nhật cho tất cả các mặt trong các mảng vector trên ảnh gốc
			for (vector<Rect>::const_iterator face = faces->begin(); face != faces->end(); face++)
			{
				Scalar color = NO_MATCH_COLOR;
				Mat face_img = (*captureFrame)(*face);

				double confidence = 0;
				int labels=0;
				bool face_match = false;
				bool face_true = false;
				// cố gắng nhận ra các khuôn mặt:
				if (pr->recognize(face_img, confidence, labels))
				{
					//Trả về độ chính xác và ma so khuon mat
					color = MATCH_COLOR; //cập nhật màu green
					match_conf = confidence;//độ chính xác
					label = labels;			//Mã số khuôn mặt	
				}

				box_text = format("ID: ");

				if (label >= 0)
				{					
					for (int it  = 0; it < List_name.first.size(); it++)
					{
						if (List_name.first.at(it) == label)
						{
							face_true = true;
							box_text.append(List_name.second.at(it));
						}
					}
				}
				else box_text.append("Unknown");
				while (face_true)
				{
					cout << "Do chinh xac: " << match_conf << endl;
					cout << "Ma so: " << label << endl;
					Point pt1(face->x + face->width, face->y + face->height);
					Point pt2(face->x, face->y);

					rectangle(*captureFrame, pt1, pt2, color, 1, 8, 0); //Tạo khung hình vuông
					int pos_x = max(face->tl().x - 10, 0);
					int pos_y = max(face->tl().y - 10, 0);
					putText(*captureFrame, box_text, Point(pos_x, pos_y), FONT, 1.0, color, 1.5);//Chèn tên khi nhận dạng đúng
					break;
				}
				
			}
			//Shows màn hình khuôn mặt
			imshow("OutputCapture", *captureFrame);
			
			char key = (char)waitKey(1);
			// Thoát khỏi vòng lặp
			if (key == 27)
				break;
		}
}
