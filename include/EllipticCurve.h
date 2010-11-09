/**
 * \file EllipticCurve.h
 * \brief Class "EllipticCurve" which describes an elliptic curve (parameters a1 to a6, p and n) and its getters.
 * \author Yohann Teston & Christophe Carasco
 */

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
		
		mpz_class p; //the curve is defined on F_p (p prime)
		mpz_class n; //order of the curve

		mpz_class gx;
		mpz_class gy;
		
	public:
		/* Constructors */
		EllipticCurve(mpz_class a1, mpz_class a2, mpz_class a3, mpz_class a4, mpz_class a6, mpz_class p, mpz_class n,mpz_class gx, mpz_class gy);	/* with explicit values */
		EllipticCurve(ifstream& f);	/* read a curve from a well-formated file */

		/* Getters */
		inline mpz_class getA1() { return this->a1;}
		inline mpz_class getA2() { return this->a2;}
		inline mpz_class getA3() { return this->a3;}
		inline mpz_class getA4() { return this->a4;}
		inline mpz_class getA6() { return this->a6;}
		inline mpz_class getP() { return this->p;}
		inline mpz_class getN() { return this->n;}
		inline mpz_class getGx() {return gx;}
		inline mpz_class getGy() {return gy;}

		friend ostream & operator <<(ostream & cout, EllipticCurve c);  
};

#endif
