/*
 * File: InverseGenetics.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Inverse Genetics problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include <fstream>
#include "set.h"
#include "map.h"
#include "console.h"
using namespace std;

/* Function: listAllRNAStrandsFor(string protein,
 *                                Map<char, Set<string> >& codons);
 * Usage: listAllRNAStrandsFor("PARTY", codons);
 * ==================================================================
 * Given a protein and a map from amino acid codes to the codons for
 * that code, lists all possible RNA strands that could generate
 * that protein
 */
void listAllRNAStrandsFor(string protein, Map<char, Set<string> >& codons);

/* Function: loadCodonMap();
 * Usage: Map<char, Lexicon> codonMap = loadCodonMap();
 * ==================================================================
 * Loads the codon mapping table from a file.
 */
Map<char, Set<string> > loadCodonMap();

/* ***Constances*** */
const string WARNING_MESSAGE = "Not Enough Proteins To Generate Combination";

Set<string> listAllProteins(string protein,Map<char, Set<string> > &codons);



int main() {
    /* Load the codon map. */
    Map<char, Set<string> > codons = loadCodonMap();

	string protein = "LKW";

	listAllRNAStrandsFor(protein, codons);

    return 0;
}

void listAllRNAStrandsFor(string protein, Map<char, Set<string> >& codons){

	//If Protein Length Is Less Than 1 Code Just Returns Warning Message
	if(protein.length() >= 1){

		//Wrapping
		Set<string> result = listAllProteins(protein, codons);
		cout << result << endl;

	}else {
		cout << WARNING_MESSAGE << endl;
	}
}	

/* You do not need to change this function. */
Map<char, Set<string> > loadCodonMap() {
    ifstream input("codons.txt");
    Map<char, Set<string> > result;

    /* The current codon / protein combination. */
    string codon;
    char protein;

    /* Continuously pull data from the file until all data has been
     * read.
     */
    while (input >> codon >> protein) {
        result[protein] += codon;
    }

    return result;
}

//Function Bellow Recursively Attaches Sets Corresponding To The First Argument
Set<string> listAllProteins(string protein,Map<char, Set<string> > &codons){

	//If Protein Length == 1 Code Just Returns Relevant Set Of Codons
	if(protein.length() == 1) return codons.get(protein[0]);

	//Getting Set From Map, Key = First Letter Of Protein
	Set<string> firstCodon = codons.get(protein[0]);
	//Removing First Letter From Protein And Use Recursion To Get A Set
	Set<string> restOfCodons = listAllProteins(protein.substr(1), codons);

	//Creating New Result Set
	Set<string> result;

	//Generating New Combinations From Two Sets
	foreach(string s1 in firstCodon){

		foreach(string s2 in restOfCodons){
			
			//Adding New Combination In The "Result"
			result.add(s1 + s2);

		}
	}

	return result;
}



