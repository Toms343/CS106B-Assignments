/*
 * File: Combinations.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Combinations problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "simpio.h"

using namespace std;

/* ***Strucutre*** */
struct numsT{
	int n;
	int k;
};

/* ***Prototypes*** */
int combinations(int n, int k);
numsT readNums();

int main() {
    
	numsT nums = readNums();

	int result = combinations(nums.n,nums.k);

	cout << "Result: " << result << endl;

    return 0;
}

//Function bellow returns numsT struct
numsT readNums(){

	int n = 1;
	int k = 2;

	//Program asks user to enter numbers before n < k or n is negative
	while(n < k || k < 0){
		
		cout << "Positive Numbers Only, N Must Be Greater Than K" << endl;

		n = getInteger("Enter N: ");
		k = getInteger("Enter K: ");

	}

	numsT result;

	result.n = n;
	result.k = k;

	return result;
	
}


//Function bellow recursively calculates combination of 2 number when n >= k
int combinations(int n, int k){

	if( n == k || k == 0){

		return 1;
	}

	return combinations(n - 1, k - 1) + combinations (n - 1, k);
}
