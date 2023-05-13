/*************************************************************
 * File: pqueue-vector.cpp
 *
 * Implementation file for the VectorPriorityQueue
 * class.
 */
 
#include "pqueue-vector.h"
#include "error.h"
#include "vector.h"


const string ERR_MESSAGE = "VectorQueue Is Empty, Fill Firstly And Try Again.";

VectorPriorityQueue::VectorPriorityQueue() {
	//Vector Is Already Created In "pqueue-vector.h"
}

VectorPriorityQueue::~VectorPriorityQueue() {
	//PriorityQueue Is Based On Vector, So We Don't Need To Deconstructe It
}

//Method Returns "Data" Vector Size
int VectorPriorityQueue::size() {
	
	return data.size();
}

//If Size Returns 0, Function Bellow Returns True;
bool VectorPriorityQueue::isEmpty() {
	
	return size() == 0;
}

//Method Bellow Adds New Element In Vector
void VectorPriorityQueue::enqueue(string value) {
	
	data.add(value);
}

//If Vector Is Empty Method Returns Error Message, Else Finds Minimal Element Of Data And Moves It To End Of Vector
string VectorPriorityQueue::peek() {
	
	if(isEmpty()){

		error(ERR_MESSAGE);
	
	}
	
	int minimalIndex = 0;

	for(int i = 1; i < data.size(); i++){
		
		if(data[minimalIndex] > data[i]) minimalIndex = i;
	}

	string result = data[minimalIndex];
	data[minimalIndex] = data[data.size() - 1];
	data[data.size() - 1] = result;

	return result;

}

//If Vector Is Empty Method Returns Error Message, Else Method Removes And Returns Minimal Element Of Vector
string VectorPriorityQueue::dequeueMin() {

	if(isEmpty()){
	
		error(ERR_MESSAGE);

	}

	string result = peek();
	data.remove(data.size() - 1);

	return result;
}

