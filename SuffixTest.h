
/*
 * SuffixTest.h
 *
 *  Created on: 1-8-13
 *      Author: tomkolar
 */

#ifndef SUFFIXTEST_H_
#define SUFFIXTEST_H_


#include <string>
#include <vector>
using namespace std;

class SuffixTest {
public:
	SuffixTest();
	virtual ~SuffixTest();

	/* run()
	 *   Run the application
	 */
	void run();

	/* string readFile(const string &fileName)
	 *   Read a file into a string and return the string
	 */
	string readFile(const string &fileName);

	/* string reverseComplement(const string &aString)
	 *   Returns the reverse complement of a string
	 */
	string reverseComplement(const string &dnaStrand);

	/* string complement (const char &aChar)
	 *   Returns the dna complement of aChar
	 */
	string complement(const char &aChar);

	/* 	getSuffixes(vector<char *> &suffixes, string aString);
	 *   Returns a vector of pointers to the suffixes for aString
	 */
	void getSuffixes(vector<char *> &suffixes, string aString);

	static bool comparisonFunc(const char *c1, const char *c2);


};

#endif /* SUFFIXTEST_H_ */
