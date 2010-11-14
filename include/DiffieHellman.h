/**
 * \file DiffieHellman.h
 * \brief Class "DiffieHellman" which describes an elliptic curve (parameters a1 to a6, p and n) and its getters.
 * \author Yohann Teston & Christophe Carasco
 */

#ifndef __DIFFIEHELLMAN__
#define __DIFFIEHELLMAN__

#include <iostream>
#include <gmpxx.h>
#include <time.h>
#include <stdlib.h>

#include "Point.h"
#include "EllipticCurve.h"

using namespace std;

/* Each entity of the algorithm is an instance of this class */
class DiffieHellman {
	private:
		Point* p; /* p is the public point both sides agreed on */
		mpz_class secret; /* private (big) integer of the entity */

	public:
		/* Constructor / Destructor */
		DiffieHellman(Point* p);	/* Generates a random secret integer */
		~DiffieHellman(){}

		/* Computes the first computation A=aP where P is the agreed public point and a is the secret integer */
		Point* initialComputation();

		/* Computes the last computation K=aB where B is the received first computation from the other entity and a is the secret integer */
		Point* computeKey(Point* received);

		/* Getter */
		inline mpz_class getSecret() {return secret;}
		inline Point* getPoint() { return p;}

};

#endif
