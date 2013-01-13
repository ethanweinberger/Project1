/*
 * LongestCommonPrefixUtil.cpp
 *
 *  Created on: 1-10-13
 *      Author: tomkolar
 */

#include "LongestCommonPrefixUtil.h"
#include "LongestCommonPrefix.h"
#include "FastaFile.h"
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

LongestCommonPrefixUtil::LongestCommonPrefixUtil() {
}

LongestCommonPrefixUtil::LongestCommonPrefixUtil(FastaFile& file1, FastaFile& file2) {
	fastaFile1 = file1;
	fastaFile2 = file2;
	strand1Length = file1.getSequenceLength();
	strand2Length = file2.getSequenceLength();
	populateSuffixes();
}

LongestCommonPrefixUtil::~LongestCommonPrefixUtil() {
}

void LongestCommonPrefixUtil::findLongestCommonPrefix(vector<LongestCommonPrefix*>& lcps) {

	// Find the longest common prefix(es)
	int longestSoFar = 0;

	// Iterate the sufix list and compare adjacent suffixes
	for (unsigned i = 0; i < suffixes.size() - 1  ; i++) {


		// Only check for lcp if from different strands
		if (suffixes[i]->getFileName().compare(suffixes[i+1]->getFileName()) != 0) {
			// Get strands to compare
			char* suffix1 = suffixes[i]->getDnaStrand();
			char* suffix2 = suffixes[i+1]->getDnaStrand();

			string lcpString = findLongestCommonPrefix(suffix1, suffix2);
			int lcpLength = lcpString.length();

			// Is this the longest lcp?
			if (lcpLength >= longestSoFar) {
				// If new longest length then clear lcps and reset longestSoFar
				if (lcpLength > longestSoFar) {
					lcps.clear();
					longestSoFar = lcpLength;
				}

				// Check if we already have this lcp
				bool alreadyExists = false;
				for (LongestCommonPrefix* lcp : lcps) {
					if (lcpString.compare(lcp->getPrefix()) == 0) {
						alreadyExists = true;
						break;
					}
				}

				// Add to collection of lcps (if not already there)
				if (!alreadyExists) {
					LongestCommonPrefix* lcp = new LongestCommonPrefix(lcpString, i);
					lcp->addSuffix(suffixes[i]);
					lcp->addSuffix(suffixes[i+1]);
					lcps.push_back(lcp);
				}
			}
		}
	}

	// Go back and look for matches that are adjacent to the longest common prefix(es) that
	// were found
	for (LongestCommonPrefix* lcp : lcps) {
		int lcpIndex = lcp->getSortIndex();
		string lcpPrefix = lcp->getPrefix();

		// Search backwards
		for (int i = lcpIndex - 1; i >= 0; i--) {
			char* backwardsSuffix = suffixes[i]->getDnaStrand();
			char* lcpSuffix = suffixes[lcpIndex]->getDnaStrand();
			string lcpString = findLongestCommonPrefix(lcpSuffix, backwardsSuffix);

			// Add to lcp if backwards suffix has same prefix as the lcp
			if ((int)lcpString.length() >= lcp->getLength())
				lcp->addSuffix(suffixes[i]);
			else
				break;
		}

		// Search forwards
		for (int i = lcpIndex + 2; i < (int)suffixes.size() - 1 ; i++) {
			char* forwardsSuffix = suffixes[i]->getDnaStrand();
			char* lcpSuffix = suffixes[lcpIndex]->getDnaStrand();
			string lcpString = findLongestCommonPrefix(lcpSuffix, forwardsSuffix);

			// Add to lcp if forwards suffix has same prefix as the lcp
			if ((int)lcpString.length() >= lcp->getLength())
				lcp->addSuffix(suffixes[i]);
			else
				break;
		}
	}

}

void LongestCommonPrefixUtil::populateSuffixes() {

	suffixes.reserve((fastaFile1.getSequenceLength() * 2) + fastaFile2.getSequenceLength() * 2);
	fastaFile1.populateSuffixes(suffixes);
	fastaFile2.populateSuffixes(suffixes);

	sort(suffixes.begin(), suffixes.end(), comparisonFunc);
}

bool LongestCommonPrefixUtil::comparisonFunc(Suffix* suffix1, Suffix* suffix2) {
	return strcmp(suffix1->getDnaStrand(), suffix2->getDnaStrand()) < 0;
}

string LongestCommonPrefixUtil::findLongestCommonPrefix (char*& string1, char*& string2) {

	int maxLength = min(strlen(string1), strlen(string2));
	stringstream prefixStream;

	for (int i = 0; i < maxLength; i++) {
		if (string1[i] == '~' || string2[i] == '~')
			break;

		if (string1[i] == string2[i])
			prefixStream << string1[i];
		else
			break;
	}
		
	return prefixStream.str();
}


