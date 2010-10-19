#include <iostream>
#include "EllipticCurve.h"
#include "Point.h"

using namespace std;

Point getAPoint(EllipticCurve* curve){
	cout << "Enter a point " << endl;
	string value;
	cout << "x: "; 
	cin >> value;
	mpz_class x(value);
	cout << endl << "y: ";
	cin >> value;
	cout << endl;
	mpz_class y(value);
	return Point(x,y,curve);
}

void opposite(EllipticCurve curve){
	Point p = getAPoint(&curve);
	cout << "The opposite of " << p << " is " << p.opposite() << endl;
}

void sum(EllipticCurve curve){
	Point p = getAPoint(&curve);
	Point q = getAPoint(&curve);
	cout << "The sum of " << p << " and " << q << " is " << p.sum(q) << endl;
}

void doubling(EllipticCurve curve){
	Point p = getAPoint(&curve);
	cout << "2*" << p << " is " << p.doubling() << endl;
}	

void multiple(EllipticCurve curve){
	Point p = getAPoint(&curve);
	string value;
	cout << "Enter the integer to multiply the point with: ";
	cin >> value;
	cout << endl;
	mpz_class n(value);
	cout << n << "*" << p << " is " << p.multiple(n) << endl;
}

void menu(EllipticCurve curve){
	bool done = false;
	do{
		int choice = 0;
		cout << "Choose your function :  " << endl;
		cout << "1: Opposite " << endl 
		<< "2: Sum " << endl
		<< "3: Doubling" << endl 
		<< "4: Multiple" << endl
		<< "5: exit" << endl;
		cin >> choice; 
		switch(choice){
			case 1:
				opposite(curve);
				break;
			case 2:
				sum(curve);
				break;
			case 3:
				doubling(curve);
				break;
			case 4: 
				multiple(curve);
				break;
			case 5:
				done = true; 
				break;
		}
	}while(!done);
}


