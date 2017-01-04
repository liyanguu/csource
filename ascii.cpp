//*********************************************************************
// TITLE: ascii.cpp - printout an ASCII code table
// 
// CHANGE LOG:
//	2014-4-13 created by liyang.
//	2015-9-17 modified lineFd, itemNbr should start at 1.
//*********************************************************************


#include<iostream>
using namespace std;

char lineFd(const int&, const int&);
   
int main() {
	const int COL = 16;
	char c;

	cout << "************ACSII code table**************" << endl;
	for (int i = 32; i < 128; ++i)
		cout << (c = char(i)) << lineFd(i + 1, COL);
	cout << endl;
	return 0;
}

char lineFd(const int& itemNbr, const int& columnNbr) {
	return itemNbr % columnNbr ? ' ' : '\n'; 
}
