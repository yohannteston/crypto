#include <iostream>
#include "EllipticCurve.h"
#include "Point.h"
#include "DiffieHellman.h"
#include "MasseyOmura.h"
#include "util.h"

using namespace std;

EllipticCurve getACurve();

Point getAPoint(EllipticCurve* curve);
	
void menu(EllipticCurve curve);

