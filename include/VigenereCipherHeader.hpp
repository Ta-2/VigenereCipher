#ifndef VigH
#define VigH

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

class VigenereCipher{
private:
	int period = 0;
	vector<char> ItoC;
	vector<vector<char>> VigenereSquare;
	map<char, int>CtoI;	
public:
	VigenereCipher (string);
	string CheckString(string);
	void SetParameter(string);
	void MakeVigenereSquare();
	void PrintSquare();
	string E(string, string);
	string D(string, string);	
};

#endif
