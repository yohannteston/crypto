#ifndef __ELLIPTICCURVE_H__
#define __ELLIPTICCURVE_H__

#include <gmpxx.h>
#include<fstream>
#include<string>
#include <iostream>

using namespace std;

class EllipticCurve {
	private: 
		mpz_class a1;
		mpz_class a2;
		mpz_class a3;
		mpz_class a4;
		mpz_class a6;
		
		mpz_class p;

	public:
		EllipticCurve(mpz_class a1, mpz_class a2, mpz_class a3, mpz_class a4, mpz_class a6, mpz_class p);
		EllipticCurve(ifstream& f);
		inline mpz_class getA1() { return this->a1;}
		inline mpz_class getA2() { return this->a2;}
		inline mpz_class getA3() { return this->a3;}
		inline mpz_class getA4() { return this->a4;}
		inline mpz_class getA6() { return this->a6;}
		inline mpz_class getP() { return this->p;}

		friend ostream & operator <<(ostream & cout, EllipticCurve c);  
};

#endif
