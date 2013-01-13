
/*
 * Suffix.cpp
 *
 *  Created on: 1-12-13
 *      Author: tomkolar
 */

#include "Suffix.h"
#include <string>
#include <sstream>
using namespace std;

Suffix::Suffix() {
}

Suffix::Suffix(char* aDnaStrand, string aFileName, int aLocation, bool isForward) {
	dnaStrand = aDnaStrand;
	fileName = aFileName;
	location = aLocation;
	forward = isForward;
}

Suffix::~Suffix() {
}

char*& Suffix::getDnaStrand() {
	return dnaStrand;
}

string& Suffix::getFileName() {
	return fileName;
}

bool Suffix::isForward(){
	return forward;
}

string Suffix::toString(int prefixSize) {
	stringstream ss;

	ss << "\t\t\t<location file='";
	ss << fileName;
	ss << "' strand='";
	ss << (forward?"forward":"reverse");
	ss << "'>\n";
	ss << "\t\t\t\t";
	ss << (forward?location:location-prefixSize);
	ss << "\n";
	ss << "\t\t\t</location>\n";

	return ss.str();
}


