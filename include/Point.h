/**
 * \file Point.h
 * \brief class "Point" in which are declared all the required operations on the point : opposite, sum, doubling and multiple
 * \author Yohann Teston & Christophe Carasco
 */


#ifndef __POINT_H__
#define __POINT_H__

#include <iostream>
#include <gmpxx.h>
#include <vector>
#include "EllipticCurve.h"

using namespace std;


class Point {
	private:
		mpz_class x;			/*!< Coordinate x */
		mpz_class y;			/*!< Coordinate y */
		EllipticCurve* curve;		/*!< pointer to the curve on which the point is */
		bool pointAtInfinity; 		/*!< boolean value that tells us if the point is the "point at infinity". In that case, the coordinates are no longer useful */

	public:
		// getters/setters
		inline mpz_class getX() { return x;}
		inline mpz_class getY() { return y;}
		inline EllipticCurve* getCurve() { return curve;}

		inline bool isPointAtInfinity() { return pointAtInfinity;}
		inline void setPointAtInfinity(bool value) { pointAtInfinity = value; }

		/* Constructors */
		Point(mpz_class x, mpz_class y, EllipticCurve* curve);		/* links a point with coordinates (x, y) to the given curve */
		Point();							/* Creates a point with cooordinates (0, 0) */
		Point(bool pointAtInfinity, EllipticCurve* curve);	/* Creates the Point at infinity */

		/* Destructor */
		~Point(){}

		/* check that this point is on curve */
		bool check();
		/* computes the opposite of this point */
		Point* opposite(); 
		/* computes the sum of this point and q */
		Point* sum(Point* q);
		/* doubles this point */
		Point* doubling();
		/* computes the multiplication of this point by n */
		Point* multiple(mpz_class n);

		/* overloaded operators */
		bool operator==(Point q);
		friend ostream & operator <<(ostream & cout, Point p); 
};
#endif
