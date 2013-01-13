/*
 * LongestCommonPrefix.h
 *
 *  Created on: 1-11-13
 *      Author: tomkolar
 */

#ifndef LONGESTCOMMONPREFIX_H
#define LONGESTCOMMONPREFIX_H

#include "SuffixLocation.h"
#include <string>
#include <vector>
using namespace std;

class LongestCommonPrefix {

public:

	LongestCommonPrefix(); 
	LongestCommonPrefix(string aPrefix, int aSortIndex); 
	~LongestCommonPrefix();

    string toString(); 
	void addSuffixLocation(SuffixLocation aLocation); 
    string& getPrefix();
	int& getLength();
	bool isSingleStrand();
	int& getSortIndex();

private:
	vector<SuffixLocation> suffixLocations;
    string prefix;
	int length;
	int sortIndex;

};

#endif /* LONGESTCOMMONPREFIX_H */