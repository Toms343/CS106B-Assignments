/*
 * File: NumericConversions.cpp
 * ---------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Numeric Conversions problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"

using namespace std;

/* ***prototypes*** */
string intToString(int n);
int stringToInt(string str);

/* Main program */

int main() {

	string str = getLine("Enter String To Convert In Number: ");
	int result1 = stringToInt(str);
	cout << result1 << endl;

	int num = getInteger("Enter Integer To Convert In String: ");
	string result2 = intToString(num);
	cout << result2 << endl;

    return 0;
}

//Function bellow recursively transforms string to int
int stringToInt(string str){
	
	//If bellow is used to avoid some bugs (when string is "negative") 
	if(str[0] == '-') {
		
		return -1 * stringToInt(str.substr(1));

	}

	if(str.length() == 1)	{

		return str[0] - '0';

	}	
	
	return stringToInt(str.substr(0,str.length() - 1)) * 10 + str[str.length() - 1] - '0';

}

//Function bellow recursively transfors int to string
string intToString(int n){
	
	//If bellow is used to avoid some bugs(when int is negative)
	if( n < 0 ) {
		
		//With this return bellow i avoid bug when user enters INT_MIN 
		return "-" + intToString(-(n / 10)) + char(-(n%10) +'0');

	}

	if( n >= 0 && n < 10 ) return string() + char(n + '0');

	return intToString( n / 10 ) + char( n % 10 + '0'); 

}
