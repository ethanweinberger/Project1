/*
 * LongestCommonPrefix.h
 *
 *  Created on: 1-11-13
 *      Author: tomkolar
 */

#ifndef LONGESTCOMMONPREFIX_H
#define LONGESTCOMMONPREFIX_H

#include "Suffix.h"
#include <string>
#include <vector>
using namespace std;

class LongestCommonPrefix {

public:

	LongestCommonPrefix(); 
	LongestCommonPrefix(string aPrefix, int aSortIndex); 
	~LongestCommonPrefix();

    string toString(); 
	void addSuffix(Suffix*& aSuffix); 
    string& getPrefix();
	int& getLength();
	int& getSortIndex();

private:
	vector<Suffix*> suffixes;
    string prefix;
	int length;
	int sortIndex;

};

#endif /* LONGESTCOMMONPREFIX_H */