/**
 * \file Point.cc
 * \brief Defines the methods declared in /include/Point.h
 * \author Yohann Teston & Christophe Carasco
 */


#include "Point.h"

/* Constructors */
Point::Point():x(0),y(0) {
	curve = NULL;
	pointAtInfinity = false;
}

Point::Point(mpz_class x, mpz_class y, EllipticCurve* curve){	
	this->x = x;
	this->y = y;
	this->curve= curve;
	this->pointAtInfinity = false;
}

Point::Point(bool pointAtInfinity){
	this->pointAtInfinity = pointAtInfinity;
	this->curve = NULL;
}

/* computes the opposite of this point according to the formulas given in class and return it */
Point Point::opposite(){
	if(pointAtInfinity){
		//this point is the point at infinity
		return Point(true);
	}
	mpz_class y_q = -y -curve->getA1()*x - curve->getA3();
	mpz_mod(y_q.get_mpz_t(), y_q.get_mpz_t(), curve->getP().get_mpz_t());	/* Don't forget to apply the modulus because the curve is defined on F_p */
	return Point(x, y_q, curve);
}

/* doubles the point according to the formulas given in class and return it */
Point Point::doubling(){
	if(pointAtInfinity){
		//twice the point at infinity is the point at infinity
		return Point(true);
	}
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

/* computes the sum of this point and q according to the formulas given in class and return it */
Point Point::sum(Point q){
	/* particular case 1: both terms are the point at infinity, then return the point at infinity */
	if(q.isPointAtInfinity() &&  this->pointAtInfinity){
		return Point(true);
	}

	/* particular cases 2 & 3: if one of the points is the point at infinity, then return the other point */
	if(q.isPointAtInfinity())
		return *this;
	if(this->pointAtInfinity)
		return q;

	/* particular case 4: q is the opposite of p, the result is the point at infinity */
	if(q == this->opposite()){
	 	return Point(true);
	} 

	/* particular case 5: q equals p, the result is the double of the point */
	if(*this == q){
		return this->doubling();
	}

	/* general case */
	mpz_class lambda = q.getY() - y;	/* computes the numerator of lambda */
	mpz_class lambda2 = q.getX() -x;	/* computes the denominator of lambda */
	mpz_invert(lambda2.get_mpz_t(), lambda2.get_mpz_t(), curve->getP().get_mpz_t());	/* computes the inverse of the denominator modulo p (of the curve) */
	lambda *= lambda2;			/* Eventually, computes lambda */

	/* computes the resulting point's x & y coordinates  and return it */
	mpz_class x_r, y_r;
	x_r = lambda*lambda + curve->getA1()*lambda - curve->getA2() - x - q.getX();
	mpz_mod(x_r.get_mpz_t(),x_r.get_mpz_t(),curve->getP().get_mpz_t());
	y_r = - (lambda + curve->getA1())*x_r + lambda * x - y - curve->getA3();
	mpz_mod(y_r.get_mpz_t(),y_r.get_mpz_t(),curve->getP().get_mpz_t());
	return Point(x_r, y_r, curve);
}

/* computes the multiplication of this point by n */
Point Point::multiple(mpz_class n){
	/* particular case 1: n=0, the result is the point at infinity */
	if(n == 0){
		return Point(true);
	}

	Point q;
	/* particular case 2: n<0, Q = (-n)*P = n*(-P), let's then consider -n instead and the opposite of P */
	if(n < 0){
		// -n becomes n
		n = n * -1;
		q = this->opposite();
	}else
		q = *this;

	Point first = q;
	char* s = NULL;
	s = mpz_get_str(s,2,n.get_mpz_t());	/* get the binary value of n as a string */
	/* Applies the square-and-multiply algorithm */
	s ++; 	/* we have to skip the first character */
	while(*s != '\0'){
		q = q.doubling();
		if(*s == '1')
			q = q.sum(first);
		s ++;
	}
	return q;
}

/* overloaded operators */
bool Point::operator==(Point q){
	return x == q.getX() && y == q.getY();	/* two points are considered equals if x1 = x2 and y1 = y2 */
}

// friendly operator to print a point
ostream & operator <<(ostream & cout, Point p) {
	if(p.pointAtInfinity)
		cout << "point at infinity";
	else
		cout << "("<< p.x << "," << p.y << ")";
	return cout;
}
