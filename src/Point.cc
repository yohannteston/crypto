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
	mpz_class lambda = (x*x*2 + curve->getA2()*x*2 + curve->getA4() - curve->getA1()*x)/ (y*2 + curve->getA1()*x + curve->getA3());
	mpz_class x_r, y_r;
	x_r = lambda*lambda + curve->getA1()*lambda - curve->getA2() - x*2;
	mpz_mod(x_r.get_mpz_t(), x_r.get_mpz_t(), curve->getP().get_mpz_t());
	y_r = - (lambda + curve->getA1())*x_r + lambda * x - y - curve->getA3();
	mpz_mod(y_r.get_mpz_t(), y_r.get_mpz_t(), curve->getP().get_mpz_t());
	return Point(x_r, y_r, curve);
}

Point Point::sum(Point q){
	if(q == this->opposite()){
		//q is the opposite of p, the result is the point at infinity
	 	return Point(true);
	}else{
		if(x == q.getX()){
			return this->doubling();
		}else{
			mpz_class lambda = (q.getY() - y)/(q.getX() -x );
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
	Point q(false);
	if(n == 0){
		return Point(true);
	}else if(n < 0){
		n = n*-1;
		q = this->opposite();
	}else{
		q = *this;
	}
	vector<Point> values;
	values.push_back(q);
	return privateMultiple(q,n, values, true);	
}

Point Point::privateMultiple(Point p,mpz_class n, vector<Point> values, bool first){
	mpz_class i(0);
	unsigned long int pow = 0;
	mpz_class left(n), current(0), two(2);
	bool done = false;
	Point q = p;
	if(n == 1) {
		return q;
	}
	do{
		pow ++;	
		mpz_pow_ui(current.get_mpz_t(), two.get_mpz_t(), pow);
		if(current <= n && first){
			q = q.doubling();
			values.push_back(q);
		}
		if(current == n){
			done = true;
			left = n - current;
		}else if(current > n){
			done = true;
		}else{
			left = n - current;
		}
	}while(!done);
	if(current > n)
		pow --;
	q = values[pow];
	if(left != 0){
		return q.sum(privateMultiple(p,left,values, false));
	}else{
		return q;
	}
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
