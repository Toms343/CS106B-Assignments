/*
 * File: ConsecutiveHeads.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Consecutive Heads problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "simpio.h"
#include "random.h"

using namespace std;

/* ***Prototype*** */
int countFlips();

int main() {
	
	int result = countFlips();

	cout << "It took " << result << " flips to get 3 consecutive heads." << endl; 

    return 0;
}

//Function returns number of flips to get 3 consecutive heads
int countFlips() {
	
	int counter = 0;
	int headCounter = 0;

	while(true){

		counter ++;
		
		//True == Tails; False == Heads;
		if(randomChance(0.5)){

			headCounter = 0;
			cout << "Tail" << endl;
		
		}else{

			headCounter ++;
			cout<< "Head" << endl;
		
		}

		if(headCounter == 3) return counter;
	}
}
