/*
 * Driver.cpp
 *
 *	This is the driver for the Longest Common Prefix program.  The program
 *  is designed to find the longest common prefix shared by two DNA sequences.
 *  The sequences are extracted from fasta files that are passed in as 
 *  arguments to the program.  The output from the program is an XML formated
 *  results set with the longest common shared DNA sequence between the two
 *  fasta files which includes the actual DNA sequence as well as its location
 *  in each of the sequences from the fasta files.
 *
 *  Typical use:  (assumes program compiled with name lcp)
 *
 *		lcp fastaFileName1 fastaFileName2 <directory>		
 *
 *	Output:
 *
 *		<result type='first line' file='filename'>
 *			  first line of one FASTA file
 *		</result>
 *		<result type='first line' file='filename'>
 *			first line of the other FASTA file
 *		</result>
 *		<result type='nucleotide histogram' file='filename'>
 *			Nucleotide histograms for each base or 'ambiguity code' 
 *			For instance, A=50,C=50,G=50,T=50,N=2
 *		</result>
 *		<result type='nucleotide histogram' file='filename'>
 *			A nucleotide histogram for the other fasta file
 *		</result>
 *		<result type='DNA sequence'>
 *			<location file='filename' strand='forward' or 'reverse'>
 *			   The location of the matching subsequence within the input sequence.
 *			</location>
 *			<location file='filename' strand='forward' or 'reverse'>
 *			   The location of the matching subsequence in the other input sequence.
 *			</location>
 *			longest shared DNA subsequence
 *		</result>
 *		<result type='DNA sequence'>
 *		  (additional matches of same length, if any... )
 *		</result>
 *
 *  Created on: 1-9-13
 *      Author: Tom Kolar
 */
#include "FastaFile.h"
#include "LongestCommonPrefixUtil.h"
#include "LongestCommonPrefix.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main( int argc, char *argv[] ) {

	// Check that file names were entered as arguments
	if (argc < 3) {
		cout << "Invalid # of arguments\n";
		cout << "usage:  lcp fastaFile1 fastaFile2 <directory>\n";
		return -3;
	}
	
	// Set the fasta file Names
	string fileName1 = argv[1];
	string fileName2 = argv[2];

	// Check for directory name argument (default to current)
	string fileDirectory = "./";
	if (argc >= 4) {
			fileDirectory = argv[3];
	}

	vector<LongestCommonPrefix*> lcps;
	try {
		FastaFile file1 = FastaFile(fileDirectory, fileName1);
		FastaFile file2 = FastaFile(fileDirectory, fileName2);

		cout
			<< file1.firstLineResultString()
			<< file2.firstLineResultString()
			<< file1.baseCountsResultString()
			<< file2.baseCountsResultString();

		LongestCommonPrefixUtil util = LongestCommonPrefixUtil(file1, file2);
		util.findLongestCommonPrefix(lcps);
		for (LongestCommonPrefix* lcp : lcps) {
			cout << lcp->toString();
		}
	}
   catch (const char* msg) {
     cerr << msg << endl;
	 return -1;
   }

   // Free up memory allocated to lcps vector
	for (std::vector<LongestCommonPrefix *>::iterator it = lcps.begin(); it != lcps.end(); ++it) {
		delete *it;
	}

	return 0;
}
