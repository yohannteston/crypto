#ifndef __DIFFIEHELLMAN__
#define __DIFFIEHELLMAN__

#include <iostream>
#include <gmpxx.h>

#include "Point.h"
#include "EllipticCurve.h"

using namespace std;

class DiffieHellman {
	private:
		Point* p; // p is the public point both sides agreed on
		mpz_class secret;

	public:
		DiffieHellman(Point* p);
		~DiffieHellman(){}

		Point initialComputation();
		Point computeKey(Point received);

		inline mpz_class getSecret() {return secret;}

};

#endif
