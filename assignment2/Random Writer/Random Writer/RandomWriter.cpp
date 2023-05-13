/*
 * File: RandomWriter.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Random Writer problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <fstream>
#include <time.h>
#include "map.h"
#include "vector.h"
#include "simpio.h"
#include "filelib.h"
#include "console.h"
#include "random.h"

using namespace std;

/* ***Constances*** */
const int MAX_MARKOV_NUM = 10;
const int SIZE_OF_TEXT = 2000;

/* ***Prototypes*** */
void getUserInput(string &fileName,int &markovNum);
void readFile(Map<string, Vector<char>> &probability,string fileName,int markovNum);
void generateText(Map<string, Vector<char>> &probability, string mostUsedWord);
void findMostUsedWord(string &mostUsedWord, Map<string, Vector<char>> &probability);

int main() {
		
	string fileName;
	int markovNum = 0;
	
	//Method Bellow Receives User Input
	getUserInput(fileName, markovNum);
	cout << "Processing Text..." << endl;

	Map<string,Vector<char>> probability;

	time_t start = time(NULL);//I Used That Function (And Line 56) Fot Calculating Working Time

	//Reading File
	readFile(probability, fileName, markovNum);

	string mostUsedWord;

	//Finding Most Used Word
	findMostUsedWord(mostUsedWord, probability);

	//Generating Text
	generateText(probability, mostUsedWord);

	time_t end = time(NULL);//Line 56

	cout << "Code Took " << end - start << " Seconds To Finish Working." <<endl;

    return 0;
}

//Function Bellow Finds Longest Vector In Map And Returns Key Of It
void findMostUsedWord(string &mostUsedWord, Map<string, Vector<char>> &probability){
	
	int longestVect = 0;
	int newVectSize = 0;

	foreach(string key in probability){
		
		newVectSize = probability.get(key).size();

		//If New Vector Size Is More Than Last Saved Vector Size, Code Changes Most Used Word And Longest Vector Size
		if(newVectSize > longestVect){
			
			mostUsedWord = key;
			longestVect = newVectSize;
		}
	}
}

//Method Bellow Generates Random Text
void generateText(Map<string, Vector<char>> &probability, string mostUsedWord){

	//If Map Is Clear, It Means That Text Size Is Not Enough For Generating Text, So Code Returns.
	if(probability.isEmpty()){
	
		cout << "Received Text Is Not Enough For Generating."  << endl;
		return;
	}

	int wordCounter = mostUsedWord.size();
	string result = mostUsedWord;

	Vector<char> last;
	int index = 0;

	//While Loop Breaks When wordCounter reaches Constance
	while(wordCounter < SIZE_OF_TEXT){
			
		last = probability.get(mostUsedWord);
		
		//If "MostUSedWords" Value In Map Is Clear While Loop Breaks
		if(!last.isEmpty()){
			
			index = randomInteger(0,last.size() - 1); 
			mostUsedWord = mostUsedWord.substr(1) + last[index];
			result += last[index]; 
			wordCounter ++;

		}else break;
	}
	
	cout << result << endl;
}

void getUserInput(string &fileName,int &markovNum){
	
	//Whilie Loop Break When User Enters Corret File Name
	while(true){
	
		fileName = getLine("Enter File Name (.txt Is Not Necesarry): ");
		fileName = string(fileName) + ".txt";

		if(fileExists(fileName)) break;
		cout << "File Name Is Not Correct, Try Again." << endl;
	}

	//While Loop Bellow Breaks When User Enter Number Form 1 To MAX_MARKOV_NUM
	while(markovNum < 1 || markovNum > MAX_MARKOV_NUM){
		
		markovNum = getInteger("Enter Markov Number Beteween 0 And 10: ");
	}	
}

void readFile(Map<string, Vector<char>> &probability,string fileName,int markovNum){
		
	ifstream input;
	input.open(fileName.c_str());

	char symbol;
	string key;

	//For Loop Bellow Generates First Key 
	for(int i = 0; i < markovNum; i ++){
		
		//If We Can No Longer Read From The File, It Means That Markovnumber Is More Than Text Size,So Code Just Returns
		if(input.get(symbol)) {

			key += symbol;

		}else  return;
	}

	//Every Time, I Add Received Value In "Key's" Vector And Then Generating New Key
	while(input.get(symbol)){

		probability[key] +=symbol;
		key = key.substr(1) + symbol;
	}

	input.close();
}
