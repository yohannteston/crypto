#ifndef __MESSAGETRANSLATION__
#define __MESSAGETRANSLATION__

#include <gmpxx.h>

#include "Point.h"
#include "EllipticCurve.h"

class MessageTranslation {
	public:
		MessageTranslation() {}
		~MessageTranslation() {}

		/* Translates a message to a point of the curve */
		static Point* translateMessage(mpz_class message, EllipticCurve* curve);
		
		/* Translates a point in a message */
		static mpz_class translatePoint(Point* p);
};

#endif
