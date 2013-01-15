/*
 * LongestCommonPrefixUtil.h
 *
 * 	This is the header file for the LongestCommonPrefixUtil object. This is
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
	// Constuctors
	// ==============================================
	LongestCommonPrefixUtil();
	LongestCommonPrefixUtil(FastaFile& file1, FastaFile& file2);

	// Destructor
	// =============================================
	virtual ~LongestCommonPrefixUtil();

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
	void findLongestCommonPrefix(vector<LongestCommonPrefix*>& lcps);

private:
	// Attributes
	// =============================================
	FastaFile fastaFile1, fastaFile2;
	vector<Suffix*> suffixes;

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
	void populateSuffixes();

	// string findLongestCommonPrefix (char*& string1, char*& string2)
	//  Purpose:
	//		returns the longest common prefix between the two strings
	string findLongestCommonPrefix (char*& string1, char*& string2);

	// bool comparisonFunc(Suffix* suffix1, Suffix* suffix2)
	//  Purpose:
	//		comparsion function for sorting Suffix objects
	static bool comparisonFunc(Suffix* suffix1, Suffix* suffix2);


};

#endif /* LONGESTCOMMONPREFIXUTIL_H */