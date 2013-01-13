/*
 * SuffixTest.h
 *
 *  Created on: 1-10-13
 *      Author: tomkolar
 */

#ifndef FASTAFILE_H
#define FASTAFILE_H

#include <string>
using namespace std;

class FastaFile {

public:
	FastaFile();
	FastaFile(string filePath, string fileName);
	virtual ~FastaFile();

    string firstLineResultString();
    string baseCountsResultString();
    string getReverseComplement();
	const int getSequenceLength();
	string& getFileName();
	string& getDnaSequence();

private:
	string filePath;
    string fileName;
    string firstLine;
    string dnaSequence;

    void populate();
    char complement(char aChar);
    void countBases(int counts[]);

};

#endif /* FASTAFILE_H */