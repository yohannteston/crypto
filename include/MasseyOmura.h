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
	public:
		MasseyOmura(EllipticCurve* curve);
		~MasseyOmura(){}
	
		inline EllipticCurve* getCurve() { return curve;}

		Point translateMessage(char message);
		char translatePoint(Point p);
		Point* doMasseyOmura(string message);
		Point doMasseyOmura(char message);

};

#endif
