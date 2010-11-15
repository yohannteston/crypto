#ifndef __ELGAMAL__
#define __ELGAMAL__

#include <gmpxx.h>

#include "EllipticCurve.h"
#include "Point.h"
#include <stdlib.h>

class ElGamal{
	private:
		Point* p;
		Point* q;
		mpz_class secret;
		bool hasBeenInitialized;
	public:
		// this constructor is to be used by the receiver
		ElGamal(Point* p);
		// this constructor is to be used by the sender (does not initialize p to simulate she doesn't know the public key yet)
		ElGamal() { hasBeenInitialized = false;}
		~ElGamal() {}

		inline Point* getP() {return p;}
		inline Point* getQ() {return q;}
		inline mpz_class getSecret() {return secret;}

		inline void setP(Point* p) { this->p = p;}
		inline void setQ(Point* q) { this->q = q;}

		void initialize(Point* p);
		Point* getM1(mpz_class* k);
		Point* getM2(Point* message, mpz_class k);
		Point* decrypt(Point* m1, Point* m2);
		bool setPublicKey(Point* p, Point* q);

};

#endif
