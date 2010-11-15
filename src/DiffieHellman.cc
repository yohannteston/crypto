/**
 * \file DiffieHellman.cc
 * \brief Definition of the methods declared in /include/DiffieHellman.h
 * \author Yohann Teston & Christophe Carasco
 */

#include "DiffieHellman.h"

DiffieHellman::DiffieHellman(Point* p){
	this->p = p;
	// generate the random numbers
	gmp_randstate_t state;

	// initialize the random number generator
	gmp_randinit_mt(state);
	// set the seed using some "classical" randomness
	gmp_randseed_ui(state, (unsigned long int)rand());
	
	// generate the secret 
	mpz_urandomm(secret.get_mpz_t(),state,p->getCurve()->getN().get_mpz_t());
}

// this function computes aP
Point* DiffieHellman::initialComputation(){
	if(p == NULL)
		return NULL;
	//compute secret*P, first step of the exchange for this end
	return p->multiple(secret);

}

// this function computes the shared key
Point* DiffieHellman::computeKey(Point* received){
	if(received == NULL)
		return NULL;
	return received->multiple(secret);
}


