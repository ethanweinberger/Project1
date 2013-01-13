/*
 * LongestCommonPrefix.cpp
 *
 *  Created on: 1-11-13
 *      Author: tomkolar
 */

#include "LongestCommonPrefix.h"
#include <sstream>
#include <vector>
#include <set>
using namespace std;

LongestCommonPrefix::LongestCommonPrefix() {
}

LongestCommonPrefix::LongestCommonPrefix(string aPrefix, int aSortIndex) {
	prefix = aPrefix;
	length = aPrefix.length();
	sortIndex = aSortIndex;
}

LongestCommonPrefix::~LongestCommonPrefix() {
}

string LongestCommonPrefix::toString() {
	stringstream ss;

	ss << "\t\t<result type='DNA Sequence'>\n"; 
	for (Suffix* suffix : suffixes) {
		ss << suffix->toString(length); 
	}
	ss << "\t\t\t"; 
	ss << prefix; 
	ss << "\n"; 
	ss << "\t\t</result>\n"; 

	return ss.str();
}

void LongestCommonPrefix::addSuffix(Suffix*& aSuffix) {
    suffixes.push_back(aSuffix);
}

string& LongestCommonPrefix::getPrefix() {
	return prefix;
}

int& LongestCommonPrefix::getSortIndex() {
	return sortIndex;
}

int& LongestCommonPrefix::getLength() {
	return length;
}
