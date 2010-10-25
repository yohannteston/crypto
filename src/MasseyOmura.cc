#include "MasseyOmura.h"

MasseyOmura::MasseyOmura(EllipticCurve* curve){
	this->curve = curve;
}
	

Point MasseyOmura::translateMessage(char message){
	mpz_class x_j, x_j_3, s_j;
	for(unsigned long int j=0;j<100;j++){
		x_j = 100*message + j;
		mpz_pow_ui(x_j_3.get_mpz_t(),x_j.get_mpz_t(),3);
		s_j = x_j_3 * (curve->getA4()*x_j) + curve->getA6();
		mpz_mod_ui(s_j.get_mpz_t(), s_j.get_mpz_t(),j);
	}
}

char MasseyOmura::translatePoint(Point p){
	mpz_class x;
	mpz_fdiv_q_ui(x.get_mpz_t(),p.getX().get_mpz_t(), 100);
	return (char)x.get_ui();
}

Point* MasseyOmura::doMasseyOmura(string message){
	Point* result = NULL;
	string cipher;

	//result = new Point[message.length()];
	for(unsigned int i =0; i < message.length(); i ++){
		result[i] = doMasseyOmura(message[i]);
	}
	return result;
}

Point MasseyOmura::doMasseyOmura(char message){
	//first, we get the point corresponding to the message
	Point p = this->translateMessage(message);

	gmp_randstate_t state;
	mpz_class a,b;
	
	// initializing the random number generator
	gmp_randinit_mt(state);
	
	//getting a
	mpz_urandomm(a.get_mpz_t(),state,p.getCurve()->getN().get_mpz_t());
	if(a == 0)
		a += 1;

	//getting b
	mpz_urandomm(b.get_mpz_t(), state, p.getCurve()->getN().get_mpz_t());
	if(b == 0)
		b += 1;
	
	Point m1 = p.multiple(a);
	Point m2 = p.multiple(b);

	// Alice inverts a
	mpz_invert(a.get_mpz_t(),a.get_mpz_t(),curve->getN().get_mpz_t());
	Point m3 = m2.multiple(a); //this is the cipher

	//deciphering, shouldn't stay here
	mpz_invert(b.get_mpz_t(),b.get_mpz_t(),curve->getN().get_mpz_t());
	Point m4 = m3.multiple(b);

	if(m4 == p)
		cout << "YaY" << endl;

	return m3;
}


