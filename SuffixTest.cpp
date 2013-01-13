
/*
 * SuffixTest.cpp
 *
 *  Created on: 1-8-13
 *      Author: tomkolar
 */

#include "SuffixTest.h"
#include "FastaFile.h"
#include "LongestCommonPrefixUtil.h"
#include "LongestCommonPrefix.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

SuffixTest::SuffixTest() {
}

SuffixTest::~SuffixTest() {
	// TODO Auto-generated destructor stub
}

/* run()
 *   Run the application
 */
void SuffixTest::run() {
	
//	string fileName1 = "NC_000912.fna";
//	string fileName2= "NC_004829.fna";
//	string fileName1 = "test_strand1.txt";
//	string fileName2 = "test_strand2.txt";
	string fileName1 = "NC_007205.fna";
	string fileName2= "NC_012920.fna";

	string fileDirectory = "C:/Users/kolart/Documents/Genome540/Assignment1/";

	FastaFile file1 = FastaFile(fileDirectory, fileName1);
	FastaFile file2 = FastaFile(fileDirectory, fileName2);

	cout
		<< file1.firstLineResultString()
		<< file2.firstLineResultString()
		<< file1.baseCountsResultString()
		<< file2.baseCountsResultString();

	LongestCommonPrefixUtil util = LongestCommonPrefixUtil(file1, file2);
	vector<LongestCommonPrefix*> lcps;
	util.findLongestCommonPrefix(lcps);
	for (LongestCommonPrefix* lcp : lcps) {
		cout << lcp->toString();
	}

}

