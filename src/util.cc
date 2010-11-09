/**
 * \file util.cc
 * \brief Definition of the helper methods declared in /include/util.h
 * \author Yohann Teston & Christophe Carasco
 */

#include "util.h"

string char2Bin(unsigned char c){
	if(c == 1)
		return string("1"); 
	if(c == 0)
		return string("0");

	char n = '0' + c%2;
	string s = char2Bin(c >> 1);
   s.push_back(n);
	return s;
}

string fillWithZeroes(string s){
	int l = s.length();
	string res = "";
	if(l < 8){
		for(int i=l; i<8; i++)
			res +='0';
	}
	res += s;
	return res;
}

string string2Bin(string message){
	string res = "";
	for(unsigned int i=0; i < message.length(); i++){
		res += fillWithZeroes(char2Bin(message[i]));
	}
	return res;
}

string addZeroes(string bin, unsigned int nbZeroes){
	string res = "";
	for (unsigned int i= 0; i < nbZeroes;i++){
		res += "0";
	}
	return res + bin;
}

string bin2String(string bin){
	string res;
	unsigned int length = bin.length();
	if(length%8){
		bin = addZeroes(bin,8 - length%8);
	}
	for(unsigned int i=0; i < length; i+=8){
		res += bin2Char(bin.substr(i,i+8));
	}
	return res;
}

char bin2Char(string s){
	// s is 8-characters long
	int exp = 0;
	char res = 0;
	for(int i = 7; i >= 0; i --){
		if(s[i] - '0')
			res += pow(2,exp);
		exp++;
	}
	return res;
}


