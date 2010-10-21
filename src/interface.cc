#include "interface.h"

using namespace std;

EllipticCurve getACurve(){
	string filename;
	cout << "Enter the name of the file where the new curve is stored : ";
	cin >> filename;
	cout << endl;
	ifstream f(filename.c_str(), ios::in);
	return EllipticCurve(f);
}

Point getAPoint(EllipticCurve* curve){
	cout << "Enter a point " << endl;
	string value;
	cout << "x: "; 
	cin >> value;
	if(value == "infinity"){
		cout << "Returning the point at infinity" << endl;
		return Point(true);
	}
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

void diffieHellman(EllipticCurve curve){
	Point p = getAPoint(&curve);
	DiffieHellman dh(p);
	if(*(dh.getKeyA()) == *(dh.getKeyB()))
		cout << "YaY" << endl;
	cout << "DH (chosen point: " << *(dh.getP()) << ")" << endl
	<< "Alice's key is " << *(dh.getKeyA()) << endl 
	<< "Bob's key is " << *(dh.getKeyB()) << endl;


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
		<< "5: Print the current curve" << endl
		<< "6: Change the curve" << endl
		<< "7: Do a DH protocol run" << endl
		<< "Other: exit" << endl;
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
				cout << curve << endl;
				break;
			case 6: 
				curve = getACurve();
				cout << curve << endl;
				break;
			case 7:
				diffieHellman(curve);
				break;
			default:
				done = true; 
				break;
		}
	}while(!done);
}


