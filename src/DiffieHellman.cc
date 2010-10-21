#include "DiffieHellman.h"

DiffieHellman::DiffieHellman(Point p){
	this->p = new Point(p.getX(), p.getY(), false);
	
	// generating the random numbers
	gmp_randstate_t state;
	mpz_class a,b;
	
	// initializing the random number generator
	gmp_randinit_mt(state);
	
	//getting a
	mpz_urandomm(a.get_mpz_t(),state,p.getCurve()->getN().get_mpz_t());
	
	//getting b
	mpz_urandomm(b.get_mpz_t(),state,p.getCurve()->getN().get_mpz_t());

	//computing the shared key
	// "Alice" computes a*p
	Point pA = p.multiple(a);

	// "Bob" computes b*p
	Point pB = p.multiple(b);

	// let's imagine they exchange pA and pB
	// "Alice" computes a*pB, that's her key
	pB = pB.multiple(a);
	keyA = new Point(pB.getX(), pB.getY(), false);
	// "Bob" computes b*pA, that's his key
	pA = pA.multiple(b);
	keyB = new Point(pA.getX(), pA.getY(), false);

}
