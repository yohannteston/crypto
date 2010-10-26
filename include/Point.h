#ifndef __POINT_H__
#define __POINT_H__

#include <iostream>
#include <gmpxx.h>
#include <vector>
#include "EllipticCurve.h"

using namespace std;


class Point {
	private:
		mpz_class x;
		mpz_class y;
		EllipticCurve* curve;
		bool pointAtInfinity; 

		Point privateMultiple(Point p, mpz_class n, vector<Point> values, bool first);

	public:
		// getters/setters
		inline mpz_class getX() { return x;}
		inline mpz_class getY() { return y;}
		inline EllipticCurve* getCurve() { return curve;}

		inline bool isPointAtInfinity() { return pointAtInfinity;}
		inline void setPointAtInfinity(bool value) { pointAtInfinity = value; }

		Point(mpz_class x, mpz_class y, EllipticCurve* curve);
		Point();
		Point(bool pointAtInfinity);
		~Point(){}
		// computes the opposite of this point
		Point opposite(); 
		// computes the sum of this point and q
		Point sum(Point q);
		// doubles this point
		Point doubling();
		// computes the multiplication of this point by n
		Point multiple(mpz_class n);

		//overloaded operators
		bool operator==(Point q);
		friend ostream & operator <<(ostream & cout, Point p);  
};
#endif
