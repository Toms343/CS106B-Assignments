/*************************************************************
 * File: pqueue-doublylinkedlist.cpp
 *
 * Implementation file for the DoublyLinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-doublylinkedlist.h"
#include "error.h"

const string ERR_MESSAGE = "DoubleLinkedListQueue Is Empty, Fill Firstly And Try Again. ";

DoublyLinkedListPriorityQueue::DoublyLinkedListPriorityQueue() {
	// TODO: Fill this in!
	head = NULL;
	length = 0;
}

DoublyLinkedListPriorityQueue::~DoublyLinkedListPriorityQueue() {
	
	//Deleting All Elements From Heap
	while(head != NULL){
		
		Cell* next = head->next;
		delete head;
		head = next;
	}
}

//Method Bellow Returns "length" Variable
int DoublyLinkedListPriorityQueue::size() {
	
	return length;
}

//If Size == 0, Method Returns True
bool DoublyLinkedListPriorityQueue::isEmpty() {
	
	return size() == 0;
}

void DoublyLinkedListPriorityQueue::enqueue(string value) {
	
	//Increasing Length
	length ++;

	//Declaring New "Cell" And Add It To The Top Of The List
	Cell* newHead = new Cell;

	newHead->value = value;
	newHead->next = head;
	newHead->prev = NULL;
	
	//Using If Statment Bellow To Avoid Bug, When Adding First Element
	if(head != NULL) head->prev = newHead;

	head = newHead;
}

string DoublyLinkedListPriorityQueue::peek() {
	
	//If Linked List Is Empty, Method Returns Error Message
	if(isEmpty()){
		
		error(ERR_MESSAGE);
	}
	
	//"Minimal" Saves Addres Of Smallest Element In LinkedList, After Peek Function Called;
	minimal = head;
	Cell* checker = head->next;

	while(true){
		
		if(checker == NULL) break;

		//If Checkers Value Is Less Than "Minimal-s" Value, Just Changing Minimal With Checker
		if(minimal->value  >  checker->value) minimal = checker;

		checker = checker->next;
	}

	//Method Returns "Minimal" Cells Elements Value
	return minimal->value;
}

string DoublyLinkedListPriorityQueue::dequeueMin() {
	
	//Using Peek Function To Get Smallest String
	string result = peek();
	length --;


	//If Smallest Cell Is Head, Code Just Changes Head Value And Removes It, After If Statment
	if(minimal == head){
	
		head = head->next;
		if(head != NULL) head->prev = NULL;

	//If Not, Code Just Changes Adresses Of Previous And Next Elements
	}else{

		if(minimal->prev != NULL) minimal->prev->next = minimal->next;
		if(minimal->next != NULL) minimal->next->prev = minimal->prev;

	}

	//Deleting Minimal From Heap
	delete minimal;

	return result;
}