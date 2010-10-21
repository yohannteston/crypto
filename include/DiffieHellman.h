#ifndef __DIFFIEHELLMAN__
#define __DIFFIEHELLMAN__

#include <iostream>
#include <gmpxx.h>

#include "Point.h"
#include "EllipticCurve.h"

using namespace std;

class DiffieHellman {
	private:
		Point* keyA;
		Point* keyB;
		Point* p;

	public:
		DiffieHellman(Point p);
		~DiffieHellman(){}

		inline Point* getKeyA() { return keyA;}
		inline Point* getKeyB() { return keyB;}
		inline Point* getP() { return p;}

};

#endif
