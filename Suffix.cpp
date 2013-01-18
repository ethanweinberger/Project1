
/*
 * Suffix.cpp
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

#include "Suffix.h"
#include <string>
#include <sstream>
using namespace std;

// Constuctors
// ==============================================
Suffix::Suffix() {
}

Suffix::Suffix(char* aDnaSequence, string aFileName, int aLocation, bool isForward) {
	dnaSequence = aDnaSequence;
	fileName = aFileName;
	location = aLocation;
	forward = isForward;
}

// Destructor
// =============================================
Suffix::~Suffix() {
}

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
string Suffix::toString(int prefixSize) {
	stringstream ss;

	ss << "      <location file='";
	ss << fileName;
	ss << "' strand='";
	ss << (forward?"forward":"reverse");
	ss << "'>\n";
	ss << "        ";
	ss << (forward?location:location-prefixSize);
	ss << "\n";
	ss << "      </location>\n";

	return ss.str();
}

// Public Accessors
// =============================================
char*& Suffix::getDnaSequence() {
	return dnaSequence;
}

string& Suffix::getFileName() {
	return fileName;
}

bool Suffix::isForward(){
	return forward;
}
