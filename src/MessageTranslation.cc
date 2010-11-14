#include "MessageTranslation.h"


/* Translate the given message to a point of curve */
Point* MessageTranslation::translateMessage(mpz_class message, EllipticCurve* curve){
	mpz_class x_j, x_j_3, s_j, tmp;
	
	// first, we need to check if the message can fit in a point
	tmp = curve->getP()/100;
	if(message >= tmp){
		// the message is too big
		return NULL;
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
	return new Point(x_j,tmp, curve);
}

mpz_class MessageTranslation::translatePoint(Point* p){
	if(p == NULL)
		return mpz_class(0);
	mpz_class x;
	mpz_fdiv_q_ui(x.get_mpz_t(),p->getX().get_mpz_t(), 100);
	return x;
}


