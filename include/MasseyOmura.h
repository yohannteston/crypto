#ifndef __MASSEYOMURA__
#define __MASSEYOMURA__

#include "EllipticCurve.h"
#include "Point.h"

#include <string>
#include <iostream>
#include <gmpxx.h>

using namespace std;

class MasseyOmura{
	private:
		EllipticCurve* curve; //the curve used by the algorithm
		mpz_class secret;
	
	public:
		MasseyOmura(EllipticCurve* curve);
		~MasseyOmura(){}
	
		inline EllipticCurve* getCurve() { return curve;}
		inline mpz_class getSecret() { return secret;}

		Point translateMessage(mpz_class message);
		mpz_class translatePoint(Point p);

		Point firstMessage(mpz_class message);
		Point answerToFirstMessage(Point first);
		Point computeCipher(Point answer);
		mpz_class decrypt(Point cipher);

};

#endif
