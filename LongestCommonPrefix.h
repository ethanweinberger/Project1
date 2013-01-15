/*
 * LongestCommonPrefix.h
 *
 * 	This is the header file for the LongestCommonPrefix object. The Longest 
 *  CommonPrefix object holds all information pertaining to the longest common
 *  prefix shared by two or more suffixes. The main attributes are:
 *
 *		prefix - the prefix shared by the suffixes
 *		suffixes - a collection of Suffix objects that share the prefix
 *		length - the length of the prefix
 *		sortIndex - the index of the first suffix in the main sorted suffixes
 *					collection on the LongestCommonPrefixUtil object
 *
 *	Typical use:
 *		1. LongestCommonPrefix(aPrefix, aSortIndex) - instantiate object
 *		2. addSuffix(aSuffix) - add a suffix that shares the prefix (repeat
 *								until all suffixes that share the prefix have 
 *								been added
 *		3. toString() - returns a XML result string representing the object
 *
 * Created on: 1-11-13
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
	// Constuctors
	// ==============================================
	LongestCommonPrefix(); 
	LongestCommonPrefix(string aPrefix, int aSortIndex); 

	// Destructor
	// =============================================
	~LongestCommonPrefix();

	// Public Methods
	// =============================================

	// addSuffix(Suffix*& aSuffix)
	//  Purpose:
	//		Adds aSuffix to the suffixes collection
	//	Preconditions:
	//	Postconditions:
	//		aSuffixe added to suffixes vector
	void addSuffix(Suffix*& aSuffix); 

	// string toString()
	//  Purpose:
	//		Returns a formatted XML element representing the prefix and 
	//		the suffixes it contains
	//
	//		format:
	//			<result type='DNA Sequence'> >
	//				<<suffix1.toString(length)>>
	//				<<suffix2.toString(length)>>
	//				...
	//				<<suffixN.toString(length)>>
	//				<<prefix>>
	//			</result>
	//	Preconditions:
	//		Object has been fully populated
    string toString(); 

	// Public Accessors
	// =============================================
    string& getPrefix();
	int& getLength();
	int& getSortIndex();

private:
	// Attributes
	// =============================================
	vector<Suffix*> suffixes;
    string prefix;
	int length;
	int sortIndex;

};

#endif /* LONGESTCOMMONPREFIX_H */