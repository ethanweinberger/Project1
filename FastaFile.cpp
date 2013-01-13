/*
 * FastaFile.cpp
 *
 *  Created on: 1-8-13
 *      Author: tomkolar
 */

#include "FastaFile.h"
#include <sstream>
#include <iostream>
#include <fstream>
using namespace std;

FastaFile::FastaFile() {
}

FastaFile::~FastaFile() {
}

FastaFile::FastaFile(string path, string name) {
        filePath = path;
        fileName = name;
        populate();
    }

string FastaFile::firstLineResultString() {
        stringstream ss;

        ss << "\t\t<result type='first line' file='" << fileName << "'>\n";
        ss << "\t\t\t" << firstLine << "\n";
        ss << "\t\t</result>\n";

        return ss.str();
    }

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

string FastaFile::getReverseComplement() {
        stringstream ss;

        // Append the complements in order
        for (string::size_type i = 0; i < dnaSequence.length(); i++) {
                ss << complement(dnaSequence[i]);
        }

        // Reverse the string
		string complement = ss.str();
		return string(complement.rbegin(), complement.rend());
    }

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
}

const int FastaFile::getSequenceLength() {
	return dnaSequence.length();
}

string& FastaFile::getFileName() {
    return fileName;
}

string& FastaFile::getDnaSequence() {
	return dnaSequence;
}
