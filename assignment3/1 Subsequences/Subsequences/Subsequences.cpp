/*
 * File: Subsequences.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Subsequences problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"

using namespace std;

/* Given two strings, returns whether the second string is a
 * subsequence of the first string.
 */
bool isSubsequence(string text, string subsequence);

int main() {

	string text = getLine("Enter Text: ");
	string subsequence = getLine("Enter Subsequence: ");

	cout << endl;

	if(isSubsequence(text, subsequence)){
		
		cout << "Second String Is Subsequence" << endl;

	}else cout << "Second String Is Not Subsequence" << endl;
    
    return 0;
}

bool isSubsequence(string text, string subsequence){
	
	//If Second String Is Empty Code Returns True
	if(subsequence.length() == 0 ) return true;

	//If First String Doesn't Contain Second Strings First Letter, Code Returns False
	if(text.find(subsequence[0]) != ::string.npos){

		//Second Strings First Letters Index In First String
		int index = text.find(subsequence[0]);
		
		//Call Recursive, Method Receives First Strings Substring From Index And Second Strings Substring From 1
		return isSubsequence(text.substr(index), subsequence.substr(1));

	}else return false;
}