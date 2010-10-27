#include "MasseyOmura.h"

MasseyOmura::MasseyOmura(EllipticCurve* curve){
	this->curve = curve;

	// generate the secret
	gmp_randstate_t state;
	
	// initializing the random number generator
	gmp_randinit_mt(state);
	
	//getting a
	mpz_urandomm(secret.get_mpz_t(),state,curve->getN().get_mpz_t());
	if(secret == 0)
		// the secret can't be null
		secret = 1;
}
	

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
			//mpz_mod_ui(tmp.get_mpz_t(), curve->getP().get_mpz_t(), 4);
			//if(tmp == 3){
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

/*
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
	//mpz_class f("12947113607748953445651312347416028163670822454875668089001242231837310041886");
	//mpz_class o(1);
	//Point p(o,f,curve);
	cout << "p is " << p << endl;

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

	cout << a << endl << b << endl;
	
	Point m1 = p.multiple(a);
	Point m2 = m1.multiple(b);

	// Alice inverts a
	cout << a << endl;
	mpz_invert(a.get_mpz_t(),a.get_mpz_t(),curve->getN().get_mpz_t());
	cout << a << endl;
	Point m3 = m2.multiple(a); //this is the cipher

	//deciphering, shouldn't stay here
	mpz_invert(b.get_mpz_t(),b.get_mpz_t(),curve->getN().get_mpz_t());
	Point m4 = m3.multiple(b);

	cout << "m4 " << m4 <<  endl;

	if(m4 == p) {
		cout << "YaY" << endl;
		cout << "trying to retrieve the original message" << this->translatePoint(m4) << endl;
	}

	return m3;
}

*/

Point MasseyOmura::firstMessage(mpz_class message){
	Point p = this->translateMessage(message);
	if(p.isPointAtInfinity()){
		return p;
	}
	return p.multiple(secret);
}

Point MasseyOmura::answerToFirstMessage(Point first){
	return first.multiple(secret);
}

Point MasseyOmura::computeCipher(Point answer){
	// Invert the secret in order to encrypt the message
	mpz_class invertedSecret;
	mpz_invert(invertedSecret.get_mpz_t(),secret.get_mpz_t(),curve->getN().get_mpz_t());
	return answer.multiple(invertedSecret); //this is the cipher
}

mpz_class MasseyOmura::decrypt(Point cipher){
	// In order to decrypt the message, we need to invert the secret
	
	mpz_class invertedSecret;
	mpz_invert(invertedSecret.get_mpz_t(),secret.get_mpz_t(),curve->getN().get_mpz_t());
	
	// now, decipher and translate this point into the original message
	return this->translatePoint(cipher.multiple(invertedSecret));


}


