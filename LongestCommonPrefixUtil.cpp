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
		char* suffix1 = suffixes[i];
		char* suffix2 = suffixes[i+1];

		// Only check for lcp if from different strands
		if (!fromSameStrand(suffix1, suffix2)) {
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
					lcp->addSuffixLocation(getSuffixLocationFor(suffix1));
					lcp->addSuffixLocation(getSuffixLocationFor(suffix2));
					lcps.push_back(lcp);
				}
			}
		}
	}

	// Go back and look for matches that are adjacentn to the longest common prefix(es) that
	// were found
	for (LongestCommonPrefix* lcp : lcps) {
		int lcpIndex = lcp->getSortIndex();
		string lcpPrefix = lcp->getPrefix();

		// Search backwards
		for (int i = lcpIndex - 1; i >= 0; i--) {
			char* backwardsSuffix = suffixes[i];
			char* lcpSuffix = suffixes[lcpIndex];
			string lcpString = findLongestCommonPrefix(lcpSuffix, backwardsSuffix);

			// Add to lcp if backwards suffix has same prefix as the lcp
			if (lcpString.length() >= lcp->getLength())
				lcp->addSuffixLocation(getSuffixLocationFor(backwardsSuffix));
			else
				break;
		}

		// Search forwards
		for (int i = lcpIndex + 2; i < suffixes.size() - 1 ; i++) {
			char* forwardsSuffix = suffixes[i];
			char* lcpSuffix = suffixes[lcpIndex];
			string lcpString = findLongestCommonPrefix(lcpSuffix, forwardsSuffix);

			// Add to lcp if forwards suffix has same prefix as the lcp
			if (lcpString.length() >= lcp->getLength())
				lcp->addSuffixLocation(getSuffixLocationFor(forwardsSuffix));
			else
				break;
		}
	}

}

bool LongestCommonPrefixUtil::isSingleStrand(LongestCommonPrefix lcp) {
	return lcp.isSingleStrand();
}

void LongestCommonPrefixUtil::populateSuffixes() {
	stringstream ss;
	ss
		<< fastaFile1.getDnaSequence() << '~'
		<< fastaFile1.getReverseComplement() << '~'
		<< fastaFile2.getDnaSequence() << '~'
		<< fastaFile2.getReverseComplement() << '~';

	suffixString = ss.str();

	suffixes.reserve(suffixString.length());
	for (string::size_type i = 0; i < suffixString.length(); i++) {
		suffixes.push_back(&suffixString[i]);
	}
	sort(suffixes.begin(), suffixes.end(), comparisonFunc);
}

bool LongestCommonPrefixUtil::comparisonFunc(const char *c1, const char *c2)
{
    return strcmp(c1, c2) < 0;
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

SuffixLocation LongestCommonPrefixUtil::getSuffixLocationFor(char*& suffix) {
	// Determine the minimum suffix size for each strand type
	//    The suffix search strand is constructed as:
	//       strand1forwared~strand1reverse~strand2forward~strand2reverse~
	int strand1ForwardMin = strand1Length + 2 * strand2Length + 4;
	int strand1ReverseMin = 2 * strand2Length + 3;
	int strand2ForwardMin = strand2Length + 2;
	int strand2ReverseMin = 0;

	// Determine the file name and direction
	string fileName;
	bool isForward = true;
	int location;
	int suffixLength = strlen(suffix);

	// If the suffix size is greater or equal to the minimum size for the strand1 reverse
	// complement than it is from the first fasta file.
	if (suffixLength >= strand1ReverseMin) {
		fileName = fastaFile1.getFileName();
		// Check for strand direction
		if (suffixLength >= strand1ForwardMin) {
			location = strand1ForwardMin + strand1Length + 1 - suffixLength;
		}
		else {
			isForward = false;
			location = strand1ForwardMin - suffixLength;
		}
	}
	else {
		fileName = fastaFile2.getFileName();
		// Check for strand direction
		if (suffixLength >= strand2ForwardMin) {
			location = strand1ReverseMin - suffixLength;
		}
		else {
			isForward = false;
			location = strand2ForwardMin - suffixLength;
		}
	}

	return SuffixLocation(fileName, location, isForward);
}

bool LongestCommonPrefixUtil::fromSameStrand(char*& suffix1, char*& suffix2) {
	int strand1ReverseMin = 2 * strand2Length + 3;
	int suffix1Length = strlen(suffix1);
	int suffix2Length = strlen(suffix2);
	if ((suffix1Length >= strand1ReverseMin && suffix2Length >= strand1ReverseMin)
		  || (suffix1Length < strand1ReverseMin && suffix2Length < strand1ReverseMin))
		return true;

	return false;
}