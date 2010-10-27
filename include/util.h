#ifndef __UTIL__
#define __UTIL__

#include <string>
#include <iostream>
#include <math.h>

using namespace std;

string char2Bin(unsigned char c);

string fillWithZeroes(string s);

string string2Bin(string message);

string addZeroes(string bin, unsigned int nbZeroes);

string bin2String(string bin);

char bin2Char(string s);
#endif
