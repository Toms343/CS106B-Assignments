/*************************************************************
 * File: pqueue-heap.cpp
 *
 * Implementation file for the HeapPriorityQueue
 * class.
 */
 
#include "pqueue-heap.h"
#include "error.h"

#include <iostream>

const string ERR_MESSAGE = "HeapPriorityQueue Is Empty, Fill Firstly";

HeapPriorityQueue::HeapPriorityQueue() {
	
	//Declaring New Array And Fill Other Private Variables
	allocatedLength = 1;
	realSize = 0;
	increaser = 1;

	data = new string[allocatedLength]();

}

//Function Deletes Array From Heap
HeapPriorityQueue::~HeapPriorityQueue() {
	
	delete[] data;
}

//Fucntion Returns realSize Of Array
int HeapPriorityQueue::size() {
	
	return realSize;
}

//If realSize == 0 Method Bellow Returns True
bool HeapPriorityQueue::isEmpty() {
	
	return size() == 0;
}

//I Use Method Bellow To Increase Arrays Size
void HeapPriorityQueue::increaseArray(){
		
	//Declaring New Array With Longer Length
	increaser *= 2;
	string* tmp = new string[increaser + allocatedLength]();

	//Moving All Elements From Data To New Array
	for(int i = 0; i < allocatedLength; i++){
		
		tmp[i] = data[i];
	}

	//Increasing Allocated Length Of Array
	allocatedLength = increaser + allocatedLength;

	//Deleting Old Data From Heap
	delete[] data;
	data = tmp;
}

//Method Bellow Moves Last Element Of Array To Correct Position
void HeapPriorityQueue::bubbleUp(){

	int index = realSize - 1; //Index Of Last Element
	string tmp = "";

	while(true){
		
		//If "Parent" Element Is Less Than "Child" Element, It Means Everythin Is Correct And While Loop Breaks;
		if(data[index] >= data[(index - 1) / 2]) break;

		//If Loop Doesn't Break I Just Change Place For "Parent" And "Child"
		tmp = data[(index - 1) / 2];
		data[(index - 1)/ 2] = data[index];
		data[index] = tmp;
		
		//After Place Change, "Childs" Index Will Be "Parents" Index, So I Just Decrease Index
		index = (index - 1) / 2;
	}
}

void HeapPriorityQueue::enqueue(string value) {
	
	//If Array Is Already Full, I Increase Array Size And After It Add New Element
	if(realSize == allocatedLength){

		increaseArray();
	}

	//Increasing Size And Add New Element
	data[realSize] = value;
	realSize ++;
	
	//Bubble Up Array's Last Element
	bubbleUp();
}

void HeapPriorityQueue::bubbleDown(){
	
	//Moving Last Element Of Array To Zero Position
	data[0] = data[realSize - 1];
	//We Dont Need Last Element, So I Just Clear It
	data[realSize - 1] = "";

	//We Have To Move First Element To Coorect Position, So First "Index" Will Be 0
	int index = 0;
	string tmp = "";
	
	while(true){
		
		//If First "Childrens" Index Is Out Of Bound, It Means Everything Is Correct
		if(2 * index + 1 < realSize - 1){
			
			//If Second "Childs" Index Is In Bound And It's Value Is Less Than First "Childs" Value, მეორე შვილს გაუცვლის ადგილს, თუ მისი მნიშვნელობა მეტია
			if(2 * index + 2 < realSize - 1 && data[2 * index + 1] > data[2 * index + 2]){
				
				//If "Parent" Is Less Than "Child" While Loop Breaks
				if(data[index] <= data[2 * index + 2]) return;

				//If Not Changing Positions And Index
				tmp = data[index];
				data[index] = data[2 * index + 2];
				data[2 * index + 2] = tmp;

				index = 2 * index + 2;

			}else{
					
				//If "Parents" IS Lestt Than "Child" While Loop Breaks;
				if(data[index] <= data[2 * index + 1]) return;

				//If Not Changing Position And Index
				tmp = data[index];
				data[index] = data[2 * index + 1];
				data[2 * index + 1] = tmp;

				index = 2 * index + 1;
			}

		}else return;
	}
	
}

string HeapPriorityQueue::peek() {
	
	//If Queue Is Empty Method Returns Error Message
	if(isEmpty()){
			
		error(ERR_MESSAGE);
	}

	//Queue Is Already Sorted So, I Just Return First Element Of Array
	return data[0];
}

string HeapPriorityQueue::dequeueMin() {
	
	//Using Peek Fucntion To Get Result String
	string result = peek();

	//Decreasing Size And Use BubbleDown Function
	bubbleDown();
	realSize --;
		
	return result;
}

