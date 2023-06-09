/*
 * File: FleschKincaid.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Flesch-Kincaid problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <fstream>
#include <string>
#include "simpio.h"
#include "console.h"
#include "filelib.h"
#include "tokenscanner.h"

using namespace std;

struct statsT{

	int sentences;
	int words;
	int syllabels;

};


/* ***Constances*** */
const double C0 = -15.59;
const double C1 = 0.39;
const double C2 = 11.8;

/* ***Checker Words*** */ 
const string SENTENCE_CHECKERS = "?!.";
const string SYLLABELS_CHECKERS = "aeiouy";

/* ***Prototypes*** */
string getFileName();
statsT readFile(string fileName);
void modifyLine(string line, statsT& res);
int countSyllabels(string token);

int main() {

	string fileName = getFileName();
	statsT results = readFile(fileName);
	cout << "-------------------------" << endl;
	double result = C0 + C1 * ((double)results.words / results.sentences) + C2 * ((double)results.syllabels / results.words);

	cout << "Book Score Is: " << result << endl;


    return 0;
}

//Function bellow reads file and process every line of text
statsT readFile(string fileName){

	statsT result;//Declare new structure to save stats

	result.sentences = 0;
	result.syllabels = 0;
	result.words = 0;

	ifstream input;
	input.open(fileName.c_str());
	string line;

	while(getline(input, line)){
		
		modifyLine(line, result);
	}

	input.close();
	
	//To avoid some bugs i use ifstate bellow
	if(result.sentences == 0) result.sentences = 1;
	if(result.words     == 0) result.words     = 1;

	return result;

}

//Function bellow calculates number of sentences, words and syllabels in received string
void modifyLine(string line, statsT& res){
	
	TokenScanner scanner(line);
	scanner.ignoreWhitespace();
	//I used function bellow to avoid bug when code perceives "isn't" in two words
	scanner.addWordCharacters("'");


	while(scanner.hasMoreTokens()){

		string token = scanner.nextToken();
			
			//If token is punctuation mark, number of sentences increases by 1
			if(SENTENCE_CHECKERS.find(token) != string::npos){
				
				res.sentences += 1;
			
			//else if token is word, number of words increases by 1
			}else if(isalpha(token[0])){ 
				
				res.words += 1;
				int sylls = countSyllabels(token);
				res.syllabels += sylls;
			}

			
	}
}

//Method returns number of syllabels in received word
int countSyllabels(string token){

	int counter = 0;

	int size = token.length();
	token = toLowerCase(token); //lowercasing word to avoid some bugs
	
	for(int i = 0; i < size; i++){
		
		//Firstly check if char is vowel
		if(SYLLABELS_CHECKERS.find(token[i]) != string::npos){
			
			//code checks if char on [i-1] position is vowel, if it's not number of syllabels increases by one
			if(i == 0 ){
				counter += 1;

			}else if(SYLLABELS_CHECKERS.find(token[i - 1]) == string::npos){
				
				//If char is "last word" and its 'e' code do nothing
				if( !(i == (token.length() - 1) && token[i] == 'e')){
					counter += 1;	
				}
			}
		}
	}
	if(counter == 0) return 1;

	return counter;
}

//Method bellow stops working, when user enters existing file name
string getFileName(){

	string result = "";
	
	while(true){
		
		cout << "'.txt' is not necesarry" << endl;
		result = getLine("Enter File Name:  ");
		result = string(result) + ".txt";

		if(fileExists(result)) return result;
		
		cout << "File Not Found, Try Again" << endl;
		cout << "-------------------------" << endl;
	}
}