/*************************************************************
 * File: pqueue-linkedlist.cpp
 *
 * Implementation file for the LinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-linkedlist.h"
#include "error.h"

#include <iostream>

const string ERR_MESSAGE = "LinkedListQueue Is Empty, Fill Firstly And Try Again."; 

//Constructing New LinkedListPriorityQueue
LinkedListPriorityQueue::LinkedListPriorityQueue() {

	head = NULL;
	length = 0;
}

//Deconstructing LinkedListPriorityQueue
LinkedListPriorityQueue::~LinkedListPriorityQueue() {
	
	while(head != NULL){
		
		Cell* next = head->next;
		delete head;
		head = next;
	}
}

//Function Bellow Returns "Length"
int LinkedListPriorityQueue::size() {
	
	return length;
}

//If Length == 0, Function Returns True
bool LinkedListPriorityQueue::isEmpty() {
	
	return size() == 0;
}

//Function Bellow Enquees New Elements In Linked List And Increases Length By One
void LinkedListPriorityQueue::enqueue(string value) {	
	
	length ++;

	//If We Are Adding First Element, We Use That Code Bellow
	if(head == NULL){
		
		Cell* newHead = new Cell;
		newHead->value = value;
		newHead->next = head;
		head = newHead;
		return;
	}
	
	Cell* checker = head;

	//Searching For Minimal Element Bellow
	while(true){
		
		//If Received Value Is Less Than "Checkers" Value, I Add New Cell Before It
		if(value < checker->value){
			
			Cell* next = new Cell;
			next->value = checker->value;
			next->next = checker->next;

			checker->value = value;
			checker->next = next;
				
			return;
		}

		//If Next Pointer Is NULL, Code Will Stops On Next Itterations First "If Statment", To Avoid That I Use If Statment Bellow
		if(checker->next == NULL){
			
			Cell* next = new Cell;
			next->value = value;
			next->next = checker->next;

			checker->next = next;

			return;
		}

		checker = checker->next;
	}
}

string LinkedListPriorityQueue::peek() {

	//If Queue Is Empty Method Returns Error Message
	if(isEmpty()){
		
		error(ERR_MESSAGE);
	}

	//If It's Not Empty Just Returning Value Of Head Cell
	return head->value;
}

string LinkedListPriorityQueue::dequeueMin() {

	//I Don't Check Queue Size There, Because I Used Peek Function.(სადაც ისედაც გათვალისწინებულია)
	string result = peek();
	length --;

	//Deleting Old "Head" Cell From Heap And Give It New Value
	Cell *next = head->next;
	delete head;
	head = next;

	return result;
}

