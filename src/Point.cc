#include "Point.h"

Point::Point(mpz_class x, mpz_class y, EllipticCurve* curve){	
	this->x = x;
	this->y = y;
	this->curve= curve;
	this->pointAtInfinity = false;
}

Point::Point(bool pointAtInfinity){
	this->pointAtInfinity = pointAtInfinity;
}

Point Point::opposite(){
	mpz_class y_q = -y -curve->getA1()*x - curve->getA3();
	mpz_mod(y_q.get_mpz_t(), y_q.get_mpz_t(), curve->getP().get_mpz_t());
	return Point(x, y_q, curve);
}

Point Point::doubling(){
	// we compute the denominator
	mpz_class lambda = (x*x*3 + curve->getA2()*x*2 + curve->getA4() - curve->getA1()*y);
	// same thing for the numerator 
	mpz_class lambda2 = (y*2 + curve->getA1()*x + curve->getA3());
	mpz_invert(lambda2.get_mpz_t(),lambda2.get_mpz_t(),curve->getP().get_mpz_t());
	lambda *= lambda2;
	mpz_class x_r, y_r;
	// computing the resulting point's x coordinate
	x_r = lambda*lambda + curve->getA1()*lambda - curve->getA2() - x*2;
	mpz_mod(x_r.get_mpz_t(), x_r.get_mpz_t(), curve->getP().get_mpz_t());
	// same work for the y coordinate
	y_r = - (lambda + curve->getA1())*x_r + lambda * x - y - curve->getA3();
	mpz_mod(y_r.get_mpz_t(), y_r.get_mpz_t(), curve->getP().get_mpz_t());
	return Point(x_r, y_r, curve);
}

Point Point::sum(Point q){
	if(q.isPointAtInfinity() &&  this->pointAtInfinity){
		//both terms are the point at infinity 
		return Point(true);
	}
	if(q.isPointAtInfinity())
		return *this;
	if(this->pointAtInfinity)
		return q;
	if(q == this->opposite()){
		//q is the opposite of p, the result is the point at infinity
	 	return Point(true);
	}else{
		if(*this == q){
			return this->doubling();
		}else{
			mpz_class lambda = q.getY() - y;
			mpz_class lambda2 = q.getX() -x;
			mpz_invert(lambda2.get_mpz_t(), lambda2.get_mpz_t(), curve->getP().get_mpz_t());
			lambda *= lambda2;
			mpz_class x_r, y_r;
			x_r = lambda*lambda + curve->getA1()*lambda - curve->getA2() - x - q.getX();
			mpz_mod(x_r.get_mpz_t(),x_r.get_mpz_t(),curve->getP().get_mpz_t());
			y_r = - (lambda + curve->getA1())*x_r + lambda * x - y - curve->getA3();
			mpz_mod(y_r.get_mpz_t(),y_r.get_mpz_t(),curve->getP().get_mpz_t());
			return Point(x_r, y_r, curve);
		}
	}	
}

Point Point::multiple(mpz_class n){
	Point q = *this;
	char* s = NULL;
	s = mpz_get_str(s,2,n.get_mpz_t());
	// we have to skip the first character
	s ++; 
	while(*s != '\0'){
		q = q.doubling();
		if(*s == '1')
			q = q.sum(*this);
		s ++;
	}
	return q;
}

mpz_class Point::order(){

}

bool Point::operator==(Point q){
	return x == q.getX() && y == q.getY();
}

ostream & operator <<(ostream & cout, Point p) {
	if(p.pointAtInfinity)
		cout << "point at infinity";
	else
		cout << "("<< p.x << "," << p.y << ")";
	return cout;
}
