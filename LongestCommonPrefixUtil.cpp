/*
 * LongestCommonPrefixUtil.cpp
 *
 * 	This is the cpp file for the LongestCommonPrefixUtil object. This is
 *  a utility object that will find the longest common prefix from two 
 *  two fasta files.
 *
 *  Typical use:
 *		1. LongestCommonPrefixUtil(fastFile1, fastaFile2)
 *		2. findLongestCommonPrefix(vector<LongestCommonPrefix> lcps)
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

// Constuctors
// ==============================================
LongestCommonPrefixUtil::LongestCommonPrefixUtil() {
}

LongestCommonPrefixUtil::LongestCommonPrefixUtil(FastaFile& file1, FastaFile& file2) {
	fastaFile1 = file1;
	fastaFile2 = file2;
	populateSuffixes();
}

// Destructor
// =============================================
LongestCommonPrefixUtil::~LongestCommonPrefixUtil() {
}

// Public Methods
// =============================================

// findLongestCommonPrefix(vector<LongestCommonPrefix*>& lcps)
//  Purpose:
//		Find the longest common prefix for the two fasta files associated
//		with this utility object.  Populates the passed in lcps vector
//		with the longest common prefixes found.  Note that there may be
//		more than one longest common prefix if the prefixes have the same
//		length.
//	Preconditions:
//		fastaFile1 and fastFile2 have been populated
//	Postconditions:
//		The passed in lcps vector will be populated with LongestCommonPrefix objects
//		representing the longest commmon prefix(es) between the two fasta files.
void LongestCommonPrefixUtil::findLongestCommonPrefix(vector<LongestCommonPrefix*>& lcps) {

	// Find the longest common prefix(es)
	int longestSoFar = 0;

	// Iterate the sufix list and compare adjacent suffixes
	for (unsigned i = 0; i < suffixes.size() - 1  ; i++) {


		// Only check for lcp if from different strands
		if (suffixes[i]->getFileName().compare(suffixes[i+1]->getFileName()) != 0) {
			// Get strands to compare
			char* suffix1 = suffixes[i]->getDnaSequence();
			char* suffix2 = suffixes[i+1]->getDnaSequence();

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
			char* backwardsSuffix = suffixes[i]->getDnaSequence();
			char* lcpSuffix = suffixes[lcpIndex]->getDnaSequence();
			string lcpString = findLongestCommonPrefix(lcpSuffix, backwardsSuffix);

			// Add to lcp if backwards suffix has same prefix as the lcp
			if ((int)lcpString.length() >= lcp->getLength())
				lcp->addSuffix(suffixes[i]);
			else
				break;
		}

		// Search forwards
		for (int i = lcpIndex + 2; i < (int)suffixes.size() - 1 ; i++) {
			char* forwardsSuffix = suffixes[i]->getDnaSequence();
			char* lcpSuffix = suffixes[lcpIndex]->getDnaSequence();
			string lcpString = findLongestCommonPrefix(lcpSuffix, forwardsSuffix);

			// Add to lcp if forwards suffix has same prefix as the lcp
			if ((int)lcpString.length() >= lcp->getLength())
				lcp->addSuffix(suffixes[i]);
			else
				break;
		}
	}

}

// Private Methods
// =============================================

// populateSuffixes()
//  Purpose:
//		populate the suffixes vector with the the suffixes from
//		the two fasta files, then sort them in lexicographical order
//	Preconditions:
//		fastaFile1 and fastFile2 have been populated
//	Postconditions:
//		suffixes vector containes a sorted list of all suffixes from 
//		the two fasta files
void LongestCommonPrefixUtil::populateSuffixes() {

	suffixes.reserve((fastaFile1.getSequenceLength() * 2) + fastaFile2.getSequenceLength() * 2);
	fastaFile1.populateSuffixes(suffixes);
	fastaFile2.populateSuffixes(suffixes);

	sort(suffixes.begin(), suffixes.end(), comparisonFunc);
}

// string findLongestCommonPrefix (char*& string1, char*& string2)
//  Purpose:
//		returns the longest common prefix between the two strings
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

// bool comparisonFunc(Suffix* suffix1, Suffix* suffix2)
//  Purpose:
//		comparsion function for sorting Suffix objects
bool LongestCommonPrefixUtil::comparisonFunc(Suffix* suffix1, Suffix* suffix2) {
	return strcmp(suffix1->getDnaSequence(), suffix2->getDnaSequence()) < 0;
}

