/*
 * LongestCommonPrefix.cpp
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
 *  Created on: 1-11-13
 *      Author: tomkolar
 */

#include "LongestCommonPrefix.h"
#include <sstream>
#include <vector>
#include <set>
using namespace std;

// Constuctors
// ==============================================
LongestCommonPrefix::LongestCommonPrefix() {
}

LongestCommonPrefix::LongestCommonPrefix(string aPrefix, int aSortIndex) {
	prefix = aPrefix;
	length = aPrefix.length();
	sortIndex = aSortIndex;
}

// Destructor
// =============================================
LongestCommonPrefix::~LongestCommonPrefix() {
}

// Public Methods
// =============================================

// addSuffix(Suffix*& aSuffix)
//  Purpose:
//		Adds aSuffix to the suffixes collection
//	Preconditions:
//	Postconditions:
//		aSuffixe added to suffixes vector
void LongestCommonPrefix::addSuffix(Suffix*& aSuffix) {
    suffixes.push_back(aSuffix);
}

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
string LongestCommonPrefix::toString() {
	stringstream ss;

	ss << "    <result type='DNA Sequence'>\n"; 
	for (Suffix* suffix : suffixes) {
		ss << suffix->toString(length); 
	}
	ss << "      "; 
	ss << prefix; 
	ss << "\n"; 
	ss << "    </result>\n"; 

	return ss.str();
}

// Public Accessors
// =============================================
string& LongestCommonPrefix::getPrefix() {
	return prefix;
}

int& LongestCommonPrefix::getSortIndex() {
	return sortIndex;
}

int& LongestCommonPrefix::getLength() {
	return length;
}
