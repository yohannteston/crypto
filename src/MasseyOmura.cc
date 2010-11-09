/**
 * \file MasseyOmura.cc
 * \brief Definition of the methods declared in /include/MasseyOmura.h
 * \author Yohann Teston & Christophe Carasco
 */

#include "MasseyOmura.h"

/* Constructor: generates the secret integer */
MasseyOmura::MasseyOmura(EllipticCurve* curve){
	this->curve = curve;

	// generate the secret
	gmp_randstate_t state;
	
	// initializing the random number generator
	gmp_randinit_mt(state);	
	// set the seed using some "classical" randomness
	srand(clock());
	gmp_randseed_ui(state, (unsigned long int)rand());

	//getting a
	mpz_urandomm(secret.get_mpz_t(),state,curve->getN().get_mpz_t());
	if(secret == 0)
		// the secret can't be null
		secret = 1;
}
	

/* Translate the given message to a point of the curve */
Point MasseyOmura::translateMessage(mpz_class message){
	mpz_class x_j, x_j_3, s_j, tmp;
	
	// first, we need to check if the message can fit in a point
	tmp = curve->getP()/100;
	if(message >= tmp){
		// the message is too big
		// for now, return the point at infinity
		return Point(true);
	}
	mpz_class p = (curve->getP() - 1)/2;
	for(unsigned long int j=0;j<100;j++){
		x_j = 100*message + j;
		mpz_pow_ui(x_j_3.get_mpz_t(),x_j.get_mpz_t(),3);
		s_j = x_j_3 + (curve->getA4()*x_j) + curve->getA6();
		//computing s_j^((p-1)/2)
		mpz_powm(tmp.get_mpz_t(), s_j.get_mpz_t(),p.get_mpz_t(),curve->getP().get_mpz_t());
		if(tmp == 1){
			// we know that p = 3 mod 4 because we only use such curves
			p = (curve->getP() + 1)/4;
			mpz_powm(tmp.get_mpz_t(), s_j.get_mpz_t(), p.get_mpz_t(), curve->getP().get_mpz_t());
			break;
		}

	}
	return Point(x_j,tmp, curve);
}

mpz_class MasseyOmura::translatePoint(Point p){
	mpz_class x;
	mpz_fdiv_q_ui(x.get_mpz_t(),p.getX().get_mpz_t(), 100);
	return x;
}

/* Translates a message to a point of the curve and multiplies it with the private secret integer
 * To be done by entity A
 */
Point MasseyOmura::firstMessage(Point m){	
	return m.multiple(secret);
}

/* Multiplies the received point with the private secret integer
 * To be done by entity B after having received "first" from entity A
 */
Point MasseyOmura::answerToFirstMessage(Point first){
	return first.multiple(secret);
}

/* Inverts the secret integer and multiplies it with the received point to get the cipher
 * To be done by entity A after having received "answer" from entity B
 */
Point MasseyOmura::computeCipher(Point answer){
	// Invert the secret in order to encrypt the message
	mpz_class invertedSecret;
	mpz_invert(invertedSecret.get_mpz_t(),secret.get_mpz_t(),curve->getN().get_mpz_t());
	return answer.multiple(invertedSecret); //this is the cipher
}

/* Inverts the secret integer and multiplies it with the received cipher point to decipher it
 * To be done by entity B after having received "cipher" from entity A
 */
mpz_class MasseyOmura::decrypt(Point cipher){
	// In order to decrypt the message, we need to invert the secret
	
	mpz_class invertedSecret;
	mpz_invert(invertedSecret.get_mpz_t(),secret.get_mpz_t(),curve->getN().get_mpz_t());
	
	// now, decipher and translate this point into the original message
	Point result = cipher.multiple(invertedSecret);
	cout << "m4 (resulting point) is " << result << endl;
	return this->translatePoint(result);
}


