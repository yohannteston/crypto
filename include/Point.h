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
		inline bool isPointAtInfinity() { return pointAtInfinity;}
		inline void setPointAtInfinity(bool value) { pointAtInfinity = value; }

		Point(mpz_class x, mpz_class y, EllipticCurve* curve);
		Point(bool pointAtInfinity);
		~Point(){}
		Point opposite();
		Point sum(Point q);
		Point doubling();
		Point multiple(mpz_class n);

		//overloaded operators
		bool operator==(Point q);
		friend ostream & operator <<(ostream & cout, Point p);  
};
#endif
