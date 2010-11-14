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

	//getting the secret
	mpz_urandomm(secret.get_mpz_t(),state,curve->getN().get_mpz_t());
	if(secret == 0)
		// the secret can't be null
		secret = 1;
}
	
/* Translates a message to a point of the curve and multiplies it with the private secret integer
 * To be done by entity A
 */
Point* MasseyOmura::firstMessage(Point* m){
	if(m == NULL)
		return NULL;
	return m->multiple(secret);
}

/* Multiplies the received point with the private secret integer
 * To be done by entity B after having received "first" from entity A
 */
Point* MasseyOmura::answerToFirstMessage(Point* first){
	if(first == NULL)
		return NULL;
	return first->multiple(secret);
}

/* Inverts the secret integer and multiplies it with the received point to get the cipher
 * To be done by entity A after having received "answer" from entity B
 */
Point* MasseyOmura::computeCipher(Point* answer){
	if(answer == NULL)
		return NULL;
	// Invert the secret in order to encrypt the message
	mpz_class invertedSecret;
	mpz_invert(invertedSecret.get_mpz_t(),secret.get_mpz_t(),curve->getN().get_mpz_t());
	return answer->multiple(invertedSecret); //this is the cipher
}

/* Inverts the secret integer and multiplies it with the received cipher point to decipher it
 * To be done by entity B after having received "cipher" from entity A
 */
Point* MasseyOmura::decrypt(Point* cipher){
	if(cipher == NULL)
		return NULL;
	// In order to decrypt the message, we need to invert the secret
	mpz_class invertedSecret;
	mpz_invert(invertedSecret.get_mpz_t(),secret.get_mpz_t(),curve->getN().get_mpz_t());
	
	// now, decipher and translate this point into the original message
	return cipher->multiple(invertedSecret);
}


