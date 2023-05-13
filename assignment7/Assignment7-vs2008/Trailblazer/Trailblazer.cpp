/******************************************************************************
 * File: Trailblazer.cpp
 *
 * Implementation of the graph algorithms that comprise the Trailblazer
 * assignment.
 */

#include "Trailblazer.h"
#include "TrailblazerGraphics.h"
#include "TrailblazerTypes.h"
#include "TrailblazerPQueue.h"
using namespace std;

const double PROBABILITY = 1;

/* Function: shortestPath
 * 
 * Finds the shortest path between the locations given by start and end in the
 * specified world.	 The cost of moving from one edge to the next is specified
 * by the given cost function.	The resulting path is then returned as a
 * Vector<Loc> containing the locations to visit in the order in which they
 * would be visited.	If no path is found, this function should report an
 * error.
 *
 * In Part Two of this assignment, you will need to add an additional parameter
 * to this function that represents the heuristic to use while performing the
 * search.  Make sure to update both this implementation prototype and the
 * function prototype in Trailblazer.h.
 */

//Method Bellow Receives Grid With Nodes And Initializes It
void initializeGrid(Grid<Node>& grid){
	
	for(int i = 0; i < grid.numRows(); i++){
		
		for(int j = 0; j < grid.numCols(); j++){

			//Setting All Node Color To Gray And Weight To 0
			grid[i][j].color = GRAY;
			grid[i][j].weight = 0;
		}
	}
}

void transferToVector(Vector<Loc>& result, Loc start, Loc end, Grid<Node>& grid){
		
	Loc tmp = end;

	//While Loop Breaks When Code Reaches Start Location
	while(true){
		
		if(tmp == start){
			result.insert(0,start);
			return;
		}

		result.insert(0, tmp);
		tmp = grid[tmp.row][tmp.col].parent;
	}
}

//Function Returns Shortest Path From First To Second Argument
Vector<Loc>shortestPath(Loc start, Loc end, Grid<double>& world, double costFn(Loc from, Loc to, Grid<double>& world),double heuristic(Loc start, Loc end, Grid<double>& world)){
	
	Grid<Node> grid(world.numRows(), world.numCols());
	initializeGrid(grid);
	
	//Declaring Priority Queue And Adding Start Location
	TrailblazerPQueue<Loc> queue;
	queue.enqueue(start, 0.0);

	//Declaring Some Variables To Use Them In While Loop
	Loc child, active;
	double posWeight;
	double heuristicWeight;

	//While Loop Breaks When Active Location Reaches Destination
	while(!queue.isEmpty()){
		
		//Dequeue Minimal Element From Queue On Evry Iteration
		active = queue.dequeueMin();

		//Set Minimal Elements Color To Green
		colorCell(world, active, GREEN);
		grid[active.row][active.col].color = GREEN;

		if(active == end) break;
		
		//Iterating On "Active" Locations Childrens
		for(int i = active.row - 1; i <= active.row + 1; i++){
			
			for(int j = active.col - 1; j <= active.col + 1; j++){

				if(!(i == active.row && j == active.col) && grid.inBounds(i, j)){
					
					child.row = i;
					child.col = j;
					
					//Calculation Possible Weight From "Active" To "Childs" Location, Also Calculating Heuristic Height From Child To End
					posWeight = grid[active.row][active.col].weight + costFn(active, child, world);
					heuristicWeight = heuristic(child, end, world);

					//If Child Location Color Is "YELLOW" And Possible Weight Is Less Than Current Weight
					//"If Statment" Bellow Will Decreases Childs Priority, Sets It New Parent And New Possible Weight
					if(grid[i][j].color == YELLOW && grid[i][j].weight > posWeight){
						
						grid[i][j].weight = posWeight;
						grid[i][j].parent = active;
						
						queue.decreaseKey(child, posWeight + heuristicWeight);

					//If Color Is "GRAY", Code Will Set Childs Color To "YELLOW", Weight To Possible Weight And Parent To Active
					}else if(grid[i][j].color == GRAY) {
							
						grid[i][j].color = YELLOW;
						grid[i][j].weight = posWeight;
						grid[i][j].parent = active;

						queue.enqueue(child, posWeight + heuristicWeight);
						colorCell(world, child, YELLOW);
					}
				}
			}
		}	
	}
	
	//After Finding Path, Code Transfers Information From Grid<Node> To Vector<Loc>
	Vector<Loc> result;
	transferToVector(result, start, end, grid);

    return result;
}

//Method Bellow Initializes Edges And Clusters For "CreateMaze" Function
void mazeInitialization(TrailblazerPQueue<Edge>& queue, int numRows, int numCols, Grid<int>& clusters){
		
	//Declaring some Variables To Use Them In For Statment Bellow
	Loc pointOne;
	Loc pointTwo;
	Loc pointThree;

	Edge tmp;

	//Double For Statment Bellow Creates 2 Edge From Each Point.
	for(int i = 0; i < numRows; i++){
		
		for(int j = 0; j < numCols; j++){

			//"Active" Point
			pointOne.row = i;
			pointOne.col = j;

			//Initializing Clusters Grid
			clusters[i][j] = i * numRows + j;

			//If Point Right To The "Active" Point Is In Bounds, Code Creates One Edge Between Them
			if(j + 1 < numCols){
				
				pointTwo.row = i;
				pointTwo.col = j + 1;

				tmp = makeEdge(pointOne, pointTwo);
				queue.enqueue(tmp, randomReal(0, PROBABILITY));

			}

			//If Point Down To The "Active" Point Is In Bounds, Code Creates One Edge Between Them
			if(i + 1 < numRows){

				pointThree.row = i + 1;
				pointThree.col = j;

				tmp = makeEdge(pointOne, pointThree);
				queue.enqueue(tmp, randomReal(0, PROBABILITY));
			}
		}
	}
}

//Method Bellow Merges Received Two Cluster In Grid
void mergeClusters(int cluster1, int cluster2, Grid<int>& cluster){
	
	for(int i = 0; i < cluster.numRows(); i++){
		
		for(int j = 0; j < cluster.numCols(); j++){

			if(cluster[i][j] == cluster2) cluster[i][j] = cluster1;
		}
	}
}
		
Set<Edge> createMaze(int numRows, int numCols) {
	
	//Declaring Some Variables To Save Some Information In Progress Of Algorithm
	TrailblazerPQueue<Edge> queue;
	Grid<int> clusters(numRows, numCols);
	mazeInitialization(queue, numRows, numCols, clusters);

	//More Variables To Use Them In While Loop
	int numOfClusters = numRows * numCols;
	Set<Edge> result;
	Edge tmp;

	int cluster1;
	int cluster2;

	//While Loop Breaks When Number Of Clusters Reaches 1
	while(numOfClusters > 1){
		
		tmp = queue.dequeueMin();

		cluster1 = clusters[tmp.start.row][tmp.start.col];
		cluster2 = clusters[tmp.end.row][tmp.end.col];
		
		//If Clusters Are Not The Same Code Bellow Merges Them And Decreases Number Of Clusters By One
		if(cluster1 != cluster2){
			

			result.add(tmp);
			numOfClusters--;
			mergeClusters(cluster1, cluster2, clusters);
		}

	}

    return result;
}
