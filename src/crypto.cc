#include <gmpxx.h>
#include <iostream>
#include <fstream>
#include <string>
#include "EllipticCurve.h"
#include "interface.h"


using namespace std;

int main(int argc,char** argv){
	string filename;
	if(argc != 2){
		cout << "In order to work, I need an elliptic curve ... Please, give me the file name of such a curve." << endl;
		cin >> filename;
	}else{
		filename = argv[1];
	}
	ifstream f(filename.c_str(), ios::in);
	EllipticCurve curve(f);	
	cout << curve << endl;
	menu(curve);
}
