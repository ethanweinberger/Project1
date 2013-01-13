/*
 * SuffixTest.h
 *
 *  Created on: 1-8-13
 *      Author: tomkolar
 */

#ifndef LONGESTCOMMONPREFIXUTIL_H
#define LONGESTCOMMONPREFIXUTIL_H

#include "FastaFile.h"
#include "LongestCommonPrefix.h"
#include "Suffix.h"
#include <string>
#include <vector>
using namespace std;

class LongestCommonPrefixUtil {
public:
	LongestCommonPrefixUtil();
	LongestCommonPrefixUtil(FastaFile& file1, FastaFile& file2);
	virtual ~LongestCommonPrefixUtil();
	void findLongestCommonPrefix(vector<LongestCommonPrefix*>& lcps);

private:

	FastaFile fastaFile1, fastaFile2;
	string suffixString;
	int strand1Length, strand2Length;
	vector<Suffix*> suffixes;

	void populateSuffixes();
	string findLongestCommonPrefix (char*& string1, char*& string2);
	static bool comparisonFunc(Suffix* suffix1, Suffix* suffix2);


};

#endif /* LONGESTCOMMONPREFIXUTIL_H */