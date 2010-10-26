#ifndef __MASSEYOMURA__
#define __MASSEYOMURA__

#include "EllipticCurve.h"
#include "Point.h"

#include <string>
#include <iostream>


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

		Point translateMessage(char message);
		char translatePoint(Point p);

		Point firstMessage(char message);
		Point answerToFirstMessage(Point first);
		Point computeCipher(Point answer);
		char decrypt(Point cipher);

};

#endif
