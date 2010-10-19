#include "EllipticCurve.h"

EllipticCurve::EllipticCurve(mpz_class a1, mpz_class a2, mpz_class a3, mpz_class a4, mpz_class a6, mpz_class p){
	this->a1 = a1;
	this->a2 = a2;
	this->a3 = a3;
	this->a4 = a4;
	this->a6 = a6;
	this->p = p;
}

EllipticCurve::EllipticCurve(ifstream& f){
	size_t delim;
	string line, name, value;
	char buf[256];
	while(f.getline(buf,256)){
		line = buf;
		delim = line.find("=");
		if(delim != string::npos){
			name = line.substr(0,delim);
			value = line.substr(delim+1, line.length()-delim-1);
			cout << name << " = " << value << endl;
			if(name == "p")
				p = mpz_class(value);
			else if(name == "a1")
				a1 = mpz_class(value);
			else if(name == "a2")
				a2 = mpz_class(value);
			else if(name == "a3")
				a3 = mpz_class(value);
			else if(name == "a4")
				a4 = mpz_class(value);
			else if(name == "a6")
				a6 = mpz_class(value);
			else
				cout << "huhu" << endl;
		}
	}
}


ostream & operator <<(ostream & cout, EllipticCurve c) {
	cout << "Elliptic curve : " << endl << "p: " << c.p << endl
	<< "a1: " << c.a1 << endl << "a2: " << c.a2 << endl <<
	"a3: " << c.a3 << endl << "a4: " << c.a4 << endl  
	<< "a6: " << c.a6 << endl;
	return cout;
}
