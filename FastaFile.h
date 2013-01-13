/*
 * SuffixTest.h
 *
 *  Created on: 1-10-13
 *      Author: tomkolar
 */

#ifndef FASTAFILE_H
#define FASTAFILE_H

#include "Suffix.h"
#include <string>
#include <vector>

using namespace std;

class FastaFile {

public:
	FastaFile();
	FastaFile(string filePath, string fileName);
	virtual ~FastaFile();

    string firstLineResultString();
    string baseCountsResultString();
	const int getSequenceLength();
	string& getFileName();
	string& getDnaSequence();
	void populateSuffixes(vector<Suffix*>& suffixes);

private:
	string filePath;
    string fileName;
    string firstLine;
    string dnaSequence;
	string reverseComplement;

    void populate();
    void createReverseComplement();
    char complement(char aChar);
    void countBases(int counts[]);

};

#endif /* FASTAFILE_H */