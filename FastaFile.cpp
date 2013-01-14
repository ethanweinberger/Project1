/*
 * FastaFile.cpp
 *
 *	This is the cpp file for the FastaFile object. The FastaFile object
 *  is a utility object designed to read in a Fasta File and keep the 
 *  information for the file in memory.
 *
 *  ************* WARNING ***********************************
 *  *  There is no error handling in place for this object! *
 *  *  This means that if the file does not exist or is     *
 *  *  formatted incorrectly, you will get an error and     *
 *  *  will not be able to use this object.                 *
 *  *                                                       *
 *  *  If this code gets moved to a production setting      *
 *  *  appropriate error handling should be implemented!    *
 *  *********************************************************
 *
 * Typical use for the file would be to use the FastaFile(pathName, fileName)
 * constructor to create the object.  This will automatically open the
 * Fasta File specified by the pathName and fileName, and read its contents
 * storing them in the firstLine, and dnaSequence attributes.
 *
 * populateSuffixes(vector<Suffix*>) is a convenience method that will
 * populate the passed in vector with the forward and reverse complement
 * suffixes for the dnaSequence read in from the Fasta file.
 *
 *  Created on: 1-10-13
 *      Author: tomkolar
 */

#include "FastaFile.h"
#include "Suffix.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// Constuctors
// ==============================================
FastaFile::FastaFile() {
}


FastaFile::FastaFile(string path, string name) {
        filePath = path;
        fileName = name;
        populate();
    }

// Destructor
// ==============================================
FastaFile::~FastaFile() {
}

// Public Methods
// =============================================

// populateSuffixes(vector<Suffix*>& suffixes)
//  Purpose: 
//		Populate the suffixes vector with the suffixes from the dnaSequence and
//		its reverse complment.
//  Preconditions:
//		Fasta File has been read and dnaSequence has been populated
//  Postconditions:
//		suffixes vector contains Suffix objects for each suffix of the dnaSequence
//      and its reverse complement
void FastaFile::populateSuffixes(vector<Suffix*>& suffixes) {

	// Create forward suffixes
	int sequenceLength = dnaSequence.length();
	for (int i = 0; i < sequenceLength; i++) {
		suffixes.push_back(new Suffix(&dnaSequence[i], fileName, i+1, true));
	}

	// Create reverse suffixes
	for (int i = 0; i < sequenceLength; i++) {
		suffixes.push_back(new Suffix(&reverseComplement[i], fileName, sequenceLength -i + 1, false));
	}

}

// string firstLineResultString()
//  Purpose:
//		Returns the string value of an XML element representing the first line of 
//		the Fasta file.
//  Preconditions:
//		Fasta File has been read and firstLine has been populated
string FastaFile::firstLineResultString() {
	stringstream ss;

	ss << "\t\t<result type='first line' file='" << fileName << "'>\n";
	ss << "\t\t\t" << firstLine << "\n";
	ss << "\t\t</result>\n";

	return ss.str();
}

// string baseCountsResultString()
//  Purpose:
//		Returns the string value of an XML element representing the base counts 
//		of the dnaSequence.
//  Preconditions:
//		Fasta File has been read and dnaSequence has been populated
string FastaFile::baseCountsResultString() {
	stringstream ss;

	// Header
	ss <<  "\t\t<result type='nucleotide histogram' file='" << fileName << "'>\n";

	// Base Counts
	int baseCounts[5] = {0};
	countBases(baseCounts);

	ss << "\t\t\t";
	ss << "A=" << baseCounts[0];
	ss << ",C=" << baseCounts[1];
	ss << ",G=" << baseCounts[2];
	ss << ",T=" << baseCounts[3];
	if (baseCounts[4] > 0)
		ss << ",N=" << baseCounts[4];

	ss << "\n";

	// Footer
	ss << "\t\t</result>\n";

	return ss.str();
}

// Public Accessors
// =============================================
const int FastaFile::getSequenceLength() {
	return dnaSequence.length();
}

string& FastaFile::getFileName() {
    return fileName;
}

string& FastaFile::getDnaSequence() {
	return dnaSequence;
}

// Private Methods
// =============================================

// populate()
//  Purpose:
//		Reads in the Fasta File specified by filePath and fileName and populates
//		the object with its contents
//	Preconditions:
//		fileName and filePath have been set
//  Postconditions:
//		firstLine - populated with first line from file
//		dnaSequence - populated with dnaSequence from file
//		reverseComplement - populated with reverse complement of dnaSequence
void FastaFile::populate() {

    ifstream inputFile(filePath + fileName);
	stringstream ss;
	string line;

	getline(inputFile, firstLine);
		
	while(getline(inputFile, line)) {
		ss << line;
	}

	dnaSequence = ss.str();

	inputFile.close();

	createReverseComplement();
}

// createReverseComplment()
//  Purpose:
//		populates the reverseComplement attribute with the reverse comlpement
//		of the dnaSequence
//	Preconditions:
//		dnaSequence has been set
//  Postconditions:
//		reverseComplement - populated with reverse complement of dnaSequence
void FastaFile::createReverseComplement() {
    stringstream ss;

    // Append the complements in order
    for (string::size_type i = 0; i < dnaSequence.length(); i++) {
            ss << complement(dnaSequence[i]);
    }

    // Reverse the string and set it to the reverseComplement attribute
	string complement = ss.str();
	reverseComplement = string(complement.rbegin(), complement.rend());
}

// char complement(char aChar)
//  Purpose:  returns the dna complement of aChar
char FastaFile::complement(char aChar) {
    if (aChar == 'A')
        return 'T';

    if (aChar == 'T')
        return 'A';

    if (aChar == 'G')
        return 'C';

    if (aChar == 'C')
        return 'G';

    return aChar;
}

// countBases(int counts[])
//  Purpose:
//		populates the counts array with the counts for base occurrences
//		in dnaSequence.  The array is populated with the folllowing 
//		scheme:
//			counts[0] = counts for A
//			counts[1] = counts for C
//			counts[2] = counts for G
//			counts[3] = counts for T
//			counts[4] = counts for other characters encountered
void FastaFile::countBases(int counts[]) {
	for (string::size_type i=0; i < dnaSequence.length(); i++) {
		char currentChar = dnaSequence[i];
		if (currentChar == 'A')
			counts[0]++;
		else if (currentChar == 'C')
			counts[1]++;
		else if (currentChar == 'G')
			counts[2]++;
		else if (currentChar == 'T')
			counts[3]++;
		else
			counts[4]++;
	}

}







