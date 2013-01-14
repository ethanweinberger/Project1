/*
 * Suffix.h
 *
 *	This is the cpp file for the SUffix object. The Suffix object represents a
 *  particular suffix from a DNA sequence.  The main attributes of this suffix
 *  are: 
 *		dnaStrand - the sequence of DNA Bases that form the suffix
 *		fileName - the name of the fasta file the suffix came from
 *		location - the location the suffix begins from in the original DNA strand 
 *				   from the fasta file
 *		forward - true if the sufix is from the foward strand of the original DNA
 *				  strand from the fasta file
 *				- false if it is from the reverse complement
 *
 * Typical use for this object:
 *
 *	1. Suffix(aDnaStrand, aStrandName, aLocaiton, isForward) to create an instance
 *	2. toString(prefixSize) to get xml result for the suffix
 *
 *  Created on: 1-12-13
 *      Author: tomkolar
 */

#ifndef SUFFIX_H
#define SUFFIX_H

#include <string>
using namespace std;

class Suffix {

public:
	// Constuctors
	// ==============================================
	Suffix();
	Suffix(char* aDnaSequence, string aStrandName, int aLocation, bool isForward);

	// Destructor
	// =============================================
	virtual ~Suffix();

	// Public Methods
	// =============================================

	// string toString(int prefixSize)
	//  Purpose:
	//		Returns a formatted XML element representing the fileName,
	//		location and forwardness of this suffix
	//
	//		format:
	//			<result type='location' file='<<fileName>>' strand='<<forward|reverse>>' >
	//				<<location>>
	//			</result>
	//	Preconditions:
	//		Object has been fully populated
	string toString(int prefixSize);

	// Public Accessors
	// =============================================
	char*& getDnaSequence();
	string& getFileName();
	bool isForward();

private:
	// Attributes
	// =============================================
	char* dnaSequence;
    string fileName;
	int location;
    bool forward;

};

#endif /* SUFFIX_H */