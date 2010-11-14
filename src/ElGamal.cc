#include "ElGamal.h"

ElGamal::ElGamal(Point* p){
	this->p = p;
	hasBeenInitialized = true;
	gmp_randstate_t state;
	// initializing the random number generator
	gmp_randinit_mt(state);	
	// set the seed using some "classical" randomness
	srand(clock());
	gmp_randseed_ui(state, (unsigned long int)rand());

	//getting the secret
	mpz_urandomm(secret.get_mpz_t(),state,p->getCurve()->getN().get_mpz_t());

	// compute q = s*p
	q = p->multiple(secret);
}

// compute the first part of the ciphertext using the ElGamal protocol
Point* ElGamal::getM1(mpz_class* k){
	if(!hasBeenInitialized)
		//if the ElGamal object hasn't been initialized, we return NULL to signify the error
		return NULL;

	// generate k randomly
	gmp_randstate_t state;
	// initializing the random number generator
	gmp_randinit_mt(state);	
	// set the seed using some "classical" randomness
	srand(clock());
	gmp_randseed_ui(state, (unsigned long int)rand());
	// make sure k isn't null or if is it initialize it
	if(k == NULL)
		k = new mpz_class(0);
	// generate k and store it at the corresponding location
	mpz_urandomm(k->get_mpz_t(),state,p->getCurve()->getN().get_mpz_t());
	
	// now, compute m1 = kP
	return p->multiple(*k);
}

// compute the second part of the ciphertext
Point* ElGamal::getM2(Point* message, mpz_class k){
	if(!hasBeenInitialized)
		return NULL; // same as above
	
	// compute m2 = message + k*q
	Point* kQ = q->multiple(k);
	return kQ->sum(message);
}

// decrypt a message encrypted using the ElGamal protocol
Point* ElGamal::decrypt(Point* m1, Point* m2){
	// to decrypt, do m2 - secret*m1, that is m2 + (-secret*m1)	
	Point* tmp = m1->multiple(-secret);
	return m2->sum(tmp);
}

// this function simulates the download of the public key by the sender. Must be called before any exchange of data
bool ElGamal::setPublicKey(Point* p, Point* q){
	if(p == NULL || q == NULL)
		return false; // those points can't be null
	this->p = p;
	this->q = q;
	hasBeenInitialized = true;
	return true;
}
