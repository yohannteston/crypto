/**
 * \file interface.cc
 * \brief Define functions to get the inputs from the user and react consequently
 * \author Yohann Teston & Christophe Carasco
 */

#include "interface.h"

using namespace std;

/* Asks for a filename corresponding to the definition of a curve */
EllipticCurve getACurve(){
	string filename;
	cout << "Enter the name of the file where the new curve is stored : ";
	cin >> filename;
	cout << endl;
	ifstream f(filename.c_str(), ios::in);
	return EllipticCurve(f);
}

/* Asks for x and y coordinates to create a point (on the curve) */
Point getAPoint(EllipticCurve* curve){
	cout << "Enter a point " << endl;
	string value;
	cout << "x: "; 
	cin >> value;
	if(value == "infinity"){
		cout << "Returning the point at infinity" << endl;
		return Point(true);
	}
	mpz_class x(value);
	cout << endl << "y: ";
	cin >> value;
	cout << endl;
	mpz_class y(value);
	return Point(x,y,curve);
}

/* Computes and displays the opposite of a specified point (of a curve) */
void opposite(EllipticCurve curve){
	Point p = getAPoint(&curve);
	cout << "The opposite of " << p << " is " << p.opposite() << endl;
}

/* Computes and displays the sum of two specified points (of the same curve) */
void sum(EllipticCurve curve){
	Point p = getAPoint(&curve);
	Point q = getAPoint(&curve);
	cout << "The sum of " << p << " and " << q << " is " << p.sum(q) << endl;
}

/* Computes and displays the doubling of a specified point (of a curve) */
void doubling(EllipticCurve curve){
	Point p = getAPoint(&curve);
	cout << "2*" << p << " is " << p.doubling() << endl;
}	

/* Computes and displays the multiple of a specified point (of a curve) with a given (big) integer */
void multiple(EllipticCurve curve){
	Point p = getAPoint(&curve);
	string value;
	cout << "Enter the integer to multiply the point with: ";
	cin >> value;
	cout << endl;
	mpz_class n(value);
	cout << n << "*" << p << " is " << p.multiple(n) << endl;
}

/* Simulates the Diffie-Hellman algorithm for exchanging keys */
void diffieHellman(EllipticCurve curve){
	// use the generator given with the curve as the starting point
	Point p = Point(curve.getGx(), curve.getGy(), &curve);

	// create the actors for the exchange
	DiffieHellman alice(&p), bob(&p);
	cout << "Alice's secret is " << alice.getSecret() << endl
	<< "Bob's secret is " << bob.getSecret() << endl;

	// compute the intermediate results
	Point aP = alice.initialComputation();
	Point bP = bob.initialComputation();

	/* NETWORK COMMUNICATION. Let's consider Alice sent aP to Bob and Bob sent bP to Alice */

	// use the previous calculated values to get the shared key
	Point keyAlice = alice.computeKey(bP);
	Point keyBob = bob.computeKey(aP);

	// check the result
	if(keyAlice == keyBob)
		cout << "The keys are the same" << endl;
	else
		cout << "Error, the keys differ" << endl;
	cout << "DH (chosen point: " << p << ")" << endl
	<< "Alice's key is " << keyAlice << endl 
	<< "Bob's key is " << keyBob << endl;
}

/* Simulates the Massey-Omura algorithm for exchanging messages */
void masseyOmura(EllipticCurve curve){
	string message;
	cout << "Enter a message: ";
	cin >> message;
	cout << endl;

	string mBin = string2Bin(message);	
	mpz_class value(mBin, 2);
	
	// Scenario, Alice wants to securely send message to Bob
	MasseyOmura alice(&curve), bob(&curve);
	cout << "Alice's secret is " << alice.getSecret() << endl  
	<< "Bob's secret is " << bob.getSecret() << endl;

	//first, translate the message in a point 
	Point m = alice.translateMessage(value);
	cout << "m is " << m << endl;
	
	if(m.isPointAtInfinity()){
		cout << "The message is too big to fit in a point" << endl;
		return;
	}

	Point m1 = alice.firstMessage(m);

	cout << "m's decimal value is " << value << endl;

	/* NETWORK COMMUNICATION: Alice sent m1 to Bob */

	/* "Bob" displays the received message m1 and computes its answer based on m1 */
	cout << "m1 is " << m1 << endl;
	Point m2 = bob.answerToFirstMessage(m1);

	/* NETWORK COMMUNICATION: Bob sent m2 to Alice */

	/* "Alice" displays the received message m2 and computes its final answer based on m2 */
	cout << "m2 is " << m2 << endl;
	Point m3 = alice.computeCipher(m2);

	/* NETWORK COMMUNICATION: Alice sent m3 to Bob */

	/* "Bob" displays the received message m3 and decrypts it */
	cout << "m3 is " << m3 << endl;
	mpz_class result = bob.decrypt(m3);

	/* "Bob" displays the resulting message */
	cout << "The decimal result is " << result << endl;

	char* s = NULL;
	mBin = mpz_get_str(s,2,result.get_mpz_t());

	/* checks the result */
	if(value == result)
		cout << "The result matches the original message" << endl;
	else
		cout << "Error, the result differs from the original message" << endl;
	cout << "Original message: " << message << endl << "MO result: " << bin2String(mBin) << endl;
}

/* displays a menu allowing the user to make some basic operations: sum, doubling, multiple, print the curve, change the curve, do a Diffie-Hellman protocol run or a Massey-Omura run. */
void menu(EllipticCurve curve){
	bool done = false;
	do{
		int choice = 0;
		cout << "Choose your function :  " << endl;
		cout << "1: Opposite " << endl 
		<< "2: Sum " << endl
		<< "3: Doubling" << endl 
		<< "4: Multiple" << endl
		<< "5: Print the current curve" << endl
		<< "6: Change the curve" << endl
		<< "7: Do a Diffie-Hellman protocol run" << endl 
		<< "8: Do a Massey-Omura protocol run" << endl
		<< "Other: exit" << endl;
		cin >> choice; 
		switch(choice){
			case 1:
				opposite(curve);
				break;
			case 2:
				sum(curve);
				break;
			case 3:
				doubling(curve);
				break;
			case 4: 
				multiple(curve);
				break;
			case 5: 
				cout << curve << endl;
				break;
			case 6: 
				curve = getACurve();
				cout << curve << endl;
				break;
			case 7:
				diffieHellman(curve);
				break;
			case 8:
				masseyOmura(curve);
				break;
			default:
				done = true; 
				break;
		}
	}while(!done);
}


