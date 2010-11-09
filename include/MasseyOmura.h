/**
 * \file interface.h
 * \brief Class "EllipticCurve" which describes an elliptic curve (parameters a1 to a6, p and n) and its getters.
 * \author Yohann Teston & Christophe Carasco
 */

#ifndef __MASSEYOMURA__
#define __MASSEYOMURA__

#include "EllipticCurve.h"
#include "Point.h"

#include <string>
#include <iostream>
#include <gmpxx.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

/* Each entity of the algorithm is an instance of this class */
class MasseyOmura{
	private:
		EllipticCurve* curve; /* the curve used by the algorithm */
		mpz_class secret;
	
	public:
		/* Constructor / Destructor */
		MasseyOmura(EllipticCurve* curve);	/* Generates a random secret integer */
		~MasseyOmura(){}
	
		/* Getters */
		inline EllipticCurve* getCurve() { return curve;}
		inline mpz_class getSecret() { return secret;}

		/* Translates a message to a point of the curve */
		Point translateMessage(mpz_class message);
		mpz_class translatePoint(Point p);

		/* Translates a message to a point of the curve and multiplies it with the private secret integer
		 * To be done by entity A
		 */
		Point firstMessage(Point m);

		/* Multiplies the received point with the private secret integer
		 * To be done by entity B after having received "first" from entity A
		 */
		Point answerToFirstMessage(Point first);

		/* Inverts the secret integer and multiplies it with the received point to get the cipher
		 * To be done by entity A after having received "answer" from entity B
		 */
		Point computeCipher(Point answer);

		/* Inverts the secret integer and multiplies it with the received cipher point to decipher it
		 * To be done by entity B after having received "cipher" from entity A
		 */
		mpz_class decrypt(Point cipher);

};

#endif
