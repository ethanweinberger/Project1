/*
 * Suffix.h
 *
 *  Created on: 1-12-13
 *      Author: tomkolar
 */

#ifndef SUFFIX_H
#define SUFFIX_H

#include <string>
using namespace std;

class Suffix {

public:
	Suffix();
	Suffix(char* aDnaStrand, string aStrandName, int aLocation, bool isForward);
	virtual ~Suffix();

	char*& getDnaStrand();
	string& getFileName();
	bool isForward();
	string toString(int prefixSize);

private:
	char* dnaStrand;
    string fileName;
	int location;
    bool forward;

};

#endif /* SUFFIX_H */