// page.cpp - output file to display


#include<iostream>
#include<fstream>
using namespace std;

int main(int argc, char* argv[]) {
	ifstream fin;
	int file_cnt = 0;
	char* good_files[argc];

	for (int i = 1; i < argc; ++i) {
		if (fin.open(argv[i])) {
			++file_cnt;
			good_files[i] = argv[i];
			char c;
			while(fin.get(c)) {
				cout << c;
			}
		} else
			cout << argv[i] << " ----is not a proper file." << endl;
		fin.close();
	}
	if (file_cnt > 0) {
		cout << endl << "----" << file_cnt << "file(s) processed: ";
		for (int i = 1; i <= file_cnt; ++i)
			cout << good_files[i];
		cout << endl;
	}
	return 0;
}	
