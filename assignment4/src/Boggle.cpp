/*
 * File: Boggle.cpp
 * ----------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the main starter file for Assignment #4, Boggle.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "gboggle.h"
#include "grid.h"
#include "gwindow.h"
#include "lexicon.h"
#include "random.h"
#include "simpio.h"
#include "hashmap.h"

using namespace std;

/* Constants */

const int BOGGLE_WINDOW_WIDTH = 650;
const int BOGGLE_WINDOW_HEIGHT = 350;

const string STANDARD_CUBES[16]  = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};
 
const string BIG_BOGGLE_CUBES[25]  = {
    "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
    "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
    "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
    "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
    "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

/* Function prototypes */

void welcome();
void giveInstructions();


/* ***Constances*** */
const int DIMMENSION_ONE = 4;
const int DIMMENSION_TWO = 5;

//Cube Length
const int CUBES_INDEX = 5;

//Minimal Word Size
const int MIN_WORD_SIZE = 4;

//Pause Time
const int PAUSE_TIME = 150;

/* ***Prototypes*** */
void playGame();
void askGridSize(int &dimmension);

/* ***SetUp Fuctions*** */
void generateBoard(Grid<char> &board, int dimmension);
void computerConfig(Grid<char> &board,int dimmension, string &grid);
void userConfig(Grid<char> &board,int dimmension, string &grid);
void fillWithLetters(Grid<char> &board,int dimmension,string &grid);

/* ***Word Finders*** */
void getAllWords(Grid<char> &board, HashMap<string, Vector<int> > &words);
void getWords(Grid<char> &board, int x, int y, HashMap<string, Vector<int> >  &words, Lexicon &lex, Vector<int> &value, string key);

/* ***Playing Functions*** */ 
void startGuessing(HashMap<string, Vector<int> > &words);
void userPlay(HashMap<string, Vector<int> > &words, Set<string> &usedWords);
void computerPlay(HashMap<string, Vector<int> > &words, Set<string> &usedWords);

/* ***I Don't Know xD*** */
bool contains(Vector<int> &vect, int num);

/* Main program */

int main() {

    GWindow gw(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);
    initGBoggle(gw);
    welcome();
    giveInstructions();

	cout << "-------------------------" << endl;

	while(true){

		string ans = "?";

		while(!(ans == "yes" || ans == "no")){
			
			ans = getLine("Do You Want To Play Game? ");
			ans = toLowerCase(ans);
		}

		if(ans == "no"){
			
			cout << "Bye, Bye!!! "<< endl;
			break;
		}

		//Starting Game Here
		playGame();
	}

    return 0;
}

/*
 * Function: welcome
 * Usage: welcome();
 * -----------------
 * Print out a cheery welcome message.
 */

void welcome() {
    cout << "Welcome!  You're about to play an intense game ";
    cout << "of mind-numbing Boggle.  The good news is that ";
    cout << "you might improve your vocabulary a bit.  The ";
    cout << "bad news is that you're probably going to lose ";
    cout << "miserably to this little dictionary-toting hunk ";
    cout << "of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

/*
 * Function: giveInstructions
 * Usage: giveInstructions();
 * --------------------------
 * Print out the instructions for the user.
 */

void giveInstructions() {
    cout << endl;
    cout << "The boggle board is a grid onto which I ";
    cout << "I will randomly distribute cubes. These ";
    cout << "6-sided cubes have letters rather than ";
    cout << "numbers on the faces, creating a grid of ";
    cout << "letters on which you try to form words. ";
    cout << "You go first, entering all the words you can ";
    cout << "find that are formed by tracing adjoining ";
    cout << "letters. Two letters adjoin if they are next ";
    cout << "to each other horizontally, vertically, or ";
    cout << "diagonally. A letter can only be used once ";
    cout << "in each word. Words must be at least four ";
    cout << "letters long and can be counted only once. ";
    cout << "You score points based on word length: a ";
    cout << "4-letter word is worth 1 point, 5-letters ";
    cout << "earn 2 points, and so on. After your puny ";
    cout << "brain is exhausted, I, the supercomputer, ";
    cout << "will find all the remaining words and double ";
    cout << "or triple your paltry score." << endl << endl;
    cout << "Hit return when you're ready...";
    getLine();
}

//Method Asks User About Grid Size
void askGridSize(int &dimmension){

	string ans = "";
	
	//While Loop Breaks When USer Wrties "No" Or "Yes"
	while(!(ans == "yes" || ans == "no")){
			
		cout << "Write Yes Or No Only." << endl;
		ans = getLine("Do You Want 5x5 Boggle Board? ");
		ans = toLowerCase(ans);
	}

	//If Answer == Yes I Just Change Received Dimmension
	if(ans == "yes"){
		
		dimmension = DIMMENSION_TWO;
	}
}

void playGame(){
	
	cout << "-----------------------" << endl;
	cout << "Wellcome To Boggle Game" << endl;
	cout << "-------------------------" << endl;

	int dimmension =  DIMMENSION_ONE;
	askGridSize(dimmension);
	drawBoard(dimmension,dimmension);

	cout << "-----------------------" << endl;
	cout << "Dimmension Choosed" << endl;
	cout << "-------------------------" << endl;
	
	//Creating And Filling Grid
	Grid<char> board(dimmension, dimmension);
	generateBoard(board, dimmension);

	cout << "-----------------------" << endl;
	cout << "Board Filled" << endl;
	cout << "-------------------------" << endl;

	//Getting All Possible Words For Generated Grid
	HashMap<string, Vector<int> > words;
	getAllWords(board, words);

	cout << "You Can Start Playing Now" << endl;
	cout << "-------------------------" << endl;

	//User Starts Playing There
	startGuessing(words);

	cout << "Thanks For Playing" << endl;
	cout << "-----------------------" << endl;
}

//Function Generates Board
void generateBoard(Grid<char> &board, int dimmension){

	string userConf = getLine("Do You Want To Configurate Box? " );
	userConf = toLowerCase(userConf);

	//Asking User About Configuration Of Board
	while(!(userConf == "yes" || userConf == "no")){

		userConf = getLine("Enter Yes Or No Only: ");
		userConf = toLowerCase(userConf);
	}
	
	//Declaring New String To Fill With Grid Letters
	string grid = "";

	//Functions Bellow Are Filling "grid"
	if(userConf == "yes"){
		
		userConfig(board, dimmension, grid);
	
	}else{
		
		computerConfig(board, dimmension, grid);
	}
	
	//Moving Letters In Grid
	fillWithLetters(board, dimmension, grid);
}

//Function Bellow Fills "grid" Automaticaly, Without User Input
void computerConfig(Grid<char> &board,int dimmension, string &grid){

	int index = 0;

	for(int i = 0; i < dimmension*dimmension; i++){
		
		//Generating Random Integer "index", And Add Character On "grid"
		index = randomInteger(0, CUBES_INDEX);

		//If Dimmension == 4, Adding Grid Cubes From Standard Cubes, Else From Big Boggle Cubes
		if(dimmension == DIMMENSION_ONE){

			grid += STANDARD_CUBES[i][index];
		
		}else{
			
			grid += BIG_BOGGLE_CUBES[i][index];
		}
	}

	for(int i = 0; i < grid.size(); i++){
		
		//Generating Random "grid"
		index = randomInteger(i, grid.size() - 1);
		char temp = grid[index];
		grid[index] = grid[i];
		grid[i] = temp;

	}	
}

//Function Bellow Fills "grid" With User Configuration
void userConfig(Grid<char> &board,int dimmension, string &grid){

	//While Loop Breaks when User Enters String With Correct Size
	while(grid.size() != dimmension * dimmension){
		
		cout << "String Length Must Be " << dimmension * dimmension << endl;
		grid = getLine("Enter Your Combination: ");
		grid = toUpperCase(grid);

	}		
}

//Filling Grid With Received String
void fillWithLetters(Grid<char> &board,int dimmension,string &grid){
	
	int index = 0;

	for(int i = 0; i < dimmension; i++){
		
		for(int j = 0; j < dimmension; j++){

			board[i][j] = grid[index];
			labelCube(i, j, grid[index]);
			index ++;
		}
	}
}

//Function Bellow Calls Method, Which Finds All Possible Words For Every Grid Point
void getAllWords(Grid<char> &board, HashMap<string, Vector<int> > &words){
	
	//Declaring Lexicon
	Lexicon lex("EnglishWords.dat");

	for(int i = 0; i < board.numRows(); i++){
			
		for(int j = 0; j < board.numCols(); j++){

			Vector<int> value;
			
			//Recursive Function
			getWords(board, i, j, words, lex, value, "");
		}
	}
}

//Function Bellow Returns True If First Argument Contains Second Argument
bool contains(Vector<int> &vect, int num){
		
	for(int i = 0; i < vect.size(); i++){
		
		if(vect[i] == num) return true;
	}

	return false;
}

//Method Recursively Finds All Possible Words
void getWords(Grid<char> &board, int x, int y, HashMap<string, Vector<int> >  &words, Lexicon &lex, Vector<int> &value, string key){

	//Recursion Doesn't Have Base Case, Because Code Always Reaches Edges Of Grid And Stops Working
	if(key.size() >= MIN_WORD_SIZE && lex.contains(key) && !words.containsKey(key)){
		//If The "key" Meets All The Conditions, I Just Add It On Map With Relevant Vector
		words[key] = value;
	}
			
	for(int i = x - 1; i <= x + 1; i++){
		
		for(int j = y - 1; j <= y + 1; j++){
			
			//If "i" or "j" Is Out Of Bound, Function Does Nothing
			if(i >= 0 && i < board.numRows() && j >= 0 && j < board.numCols()){
				
				//If We Already Used Received "Box" Position Or Lexicon Doesn't Contains Received Prefix Code Does Notehing
				if(!contains(value, 10 * i + j) && lex.containsPrefix(key + board[i][j])){
					
					//Adding New Points Position On Vector And Call Recursion
					value.add(10 * i + j);
					getWords(board, i, j, words, lex, value, key + board[i][j]);
					value.remove(value.size() - 1);
				}	
			}
		}	
	}
}

//User Starts Playing Bellow
void startGuessing(HashMap<string, Vector<int> > &words){

	Set<string> usedWords;
	
	userPlay(words, usedWords);

	cout << "-----------------------" << endl;
	cout << "Computers Turn" << endl;
	cout << "-----------------------" << endl;

	computerPlay(words, usedWords);
}

//Getting Words From User
void userPlay(HashMap<string, Vector<int> > &words, Set<string> &usedWords){
	
	string userInput;

	//While Loop Breaks When User Hits RETURN
	while(true){
		
		userInput = getLine("Enter Word (Hit RETURN To Finish Attempt): ");
		userInput = toUpperCase(userInput);

		if(userInput == "") break;
		
		//If Word Is Used Or Word Can't Be Found On HashMap, Code Just Return ERROR Message
		if(!usedWords.contains(userInput)){

			if(words.containsKey(userInput)){

				Vector<int> cubes = words[userInput];

				recordWordForPlayer(userInput, HUMAN);
				usedWords.add(userInput);

				for(int i = 0; i < cubes.size(); i++){

					int index = cubes[i];
					//Using Methods Bellow To Show Box's On Board
					highlightCube(index / 10, index % 10, true);
					pause(PAUSE_TIME);
					highlightCube(index / 10, index % 10, false);
				}
	
			}else{

				cout << "That Word Can't Drawn On Board" << endl;
			}

		}else{
			
			cout << "You Already Entered That Word" << endl;
		}
	}
}

//Printing Rest Of Words
void computerPlay(HashMap<string, Vector<int> > &words, Set<string> &usedWords){

	Set<string> result;

	//Arvici Rato Mara, Foreachsi Roca Mewera Sityvis Daprintva Interfeisze Nela Shveboda, Am Gadakopirebis Mere Ufro Swrafad Shveba
	//Sityva-Sityva Werda Manamde Axla Egreve Shlis Sityvebs :D 
	foreach(string word in words){
			
		if(!usedWords.contains(word)){
			
			result.add(word);
		}	
	}

	while(!result.isEmpty()){
		
		recordWordForPlayer(result.first(), COMPUTER);
		result.remove(result.first());
	}
}