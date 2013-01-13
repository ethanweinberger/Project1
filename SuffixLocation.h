/*
 * SuffixLocation.h
 *
 *  Created on: 1-11-13
 *      Author: tomkolar
 */

#ifndef SUFFIXLOCATION_H
#define SUFFIXLOCATION_H

#include <string>
#include <sstream>
using namespace std;

class SuffixLocation {

public:
   
	SuffixLocation();
	SuffixLocation(string file, int loc, bool isForward);
	~SuffixLocation();

    string toString();
	string getFileName();

private:
    int location;
	string fileName;
    bool forward;

};

#endif /* SUFFIXLOCATION_H */