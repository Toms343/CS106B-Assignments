/*
 * File: WordLadder.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Word Ladder problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <time.h>
#include "console.h"
#include "lexicon.h"
#include "simpio.h"
#include "queue.h"
#include "hashset.h"
#include "stack.h"

using namespace std;

/* ***Constances*** */
const int NUMBER_OF_LETTERS = 26;
const string QUIT_WORD = "";

/* ***Prototypes*** */
void getLedder(string start,string dest,Lexicon englishWords, string &result);

int main() {

	//Opening Lexicon File
	Lexicon englishWords("EnglishWords.dat");

	while(true){

		string start = getLine("Enter Start Word (RETURN To Quit): ");

		if(start == QUIT_WORD){
			cout << "Goodbye" << endl;
			break;
		}

		string dest  = getLine("Enter Destination Word: ");
		
		//Code Bellow Calculates Ladder When Words Are Same Length And Bot Of Them Are In Lexicon
		if(start.length() == dest.length() && englishWords.contains(start) && englishWords.contains(dest)){
			
			cout << "Finding Ladder..." << endl;

			time_t beginTime = time(NULL);//I Use That (And 53 Line) To Calculate Working Time

			string result = "No Ladder Found";
			getLedder(start, dest, englishWords, result);

			time_t endTime = time(NULL);//53 Line

			cout << result << endl;
			cout << "Code Took " << endTime - beginTime << " Seconds To Finish" << endl;

		}else cout << "Words Are Not Same Size Or Are Not Found In Lexicon" << endl;
	}
    
    return 0;
}

//Method Bellow Finds Ladder From Start To Dest Arguments
void getLedder(string start,string dest,Lexicon englishWords,string &result){

	//HashSet Bellow Is For Save Used words
	HashSet<string> usedWords;
	//Code Starts Searching From Last Word To Get Correct Ladder Order, სტეკი რო ბოლო წევრს აბრუნებს ჯერ იმიტო ვამატებ dest-ს თავიდან :დ
	usedWords.add(dest);
	
	Stack<string> ladder;
	ladder.push(dest);

	//I Used Queue Bellow For BFS Algorithm
	Queue<Stack<string>> nextWords; 
	nextWords.enqueue(ladder);

	bool ladderFound = false;

	while(!nextWords.isEmpty()){
		
		ladder = nextWords.dequeue();
		string lastWord = ladder.peek();

		//If Code Reaches Destination Word While Loop Breaks
		if(lastWord == start){
			
			ladderFound = true;
			break;
		}

		//New Ladder To Add In Queue
		Stack<string> copy;

		//Double "For" Bellow Generates New Words For Ladder
		for(int i = 0; i < lastWord.length(); i++){

			string newWord = lastWord;

			for(int j = 0; j < NUMBER_OF_LETTERS; j++){

				newWord[i] = char(j + 'a');

				//I Add New Words In Ladder, If Lexicon Contains Them And They Are Not Used Already
				if(englishWords.contains(newWord) && !usedWords.contains(newWord)){
					
					copy = ladder;
					copy.push(newWord);

					nextWords.enqueue(copy);
					usedWords.add(newWord);
				}
			}
		}
	}

	//If State Bellow Is "False" We Don't Need To Change Result
	if(ladderFound == true){
		
		result = ladder.pop();

		while(!ladder.isEmpty()){
			
			result += string("--> ") + ladder.pop();
		}
	}
}