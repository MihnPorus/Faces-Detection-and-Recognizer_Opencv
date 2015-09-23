#include "Run.h"
#include <iostream>
using namespace std;
int main(int argc, char** argv) {

	Run *run = new Run;
	int chon;
	bool key = true;
	do
	{
		cout << "1. Them khuon mat vao thu vien!\n2. Nhan dien khuon mat!\n3. Thoat!" << endl;
		cin >> chon;
		switch (chon)
		{
		case 1:
			run->Face_Capture();
			break;
		case 2:
			run->Face_Recognition();
			break;
		case 3:
			key = false;
			run->~Run();
			break;
		}
	} while (key);

	return 0;
}