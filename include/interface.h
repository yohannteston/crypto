/**
 * \file interface.h
 * \brief Declare functions to get the inputs from the user and react consequently
 * \author Yohann Teston & Christophe Carasco
 */

#include <iostream>
#include "EllipticCurve.h"
#include "Point.h"
#include "DiffieHellman.h"
#include "MasseyOmura.h"
#include "util.h"
#include "MessageTranslation.h"
#include "ElGamal.h"

using namespace std;

EllipticCurve* getACurve();

Point* getAPoint(EllipticCurve* curve);
	
void menu(EllipticCurve* curve);

