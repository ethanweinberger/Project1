/*
 * SuffixLocation.cpp
 *
 *  Created on: 1-11-13
 *      Author: tomkolar
 */

#include "SuffixLocation.h"
#include <string>
#include <sstream>
using namespace std;

SuffixLocation::SuffixLocation() {
}

SuffixLocation::~SuffixLocation() {
}

SuffixLocation::SuffixLocation(string file, int loc, bool isForward) {
	fileName = file;
	location = loc;
	forward = isForward;
}

string SuffixLocation::toString() {
	stringstream ss;

	ss << "\t\t\t<location file='";
	ss << fileName;
	ss << "' strand='";
	ss << (forward?"forward":"reverse");
	ss << "'>\n";
	ss << "\t\t\t\t";
	ss << location;
	ss << "\n";
	ss << "\t\t\t</location>\n";

	return ss.str();
}

string SuffixLocation::getFileName() {
	return fileName;
}