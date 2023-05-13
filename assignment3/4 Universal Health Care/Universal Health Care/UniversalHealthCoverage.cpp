/*
 * File: UniversalHealthCoverage.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the UniversalHealthCoverage problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */
#include <iostream>
#include <string>
#include "set.h"
#include "vector.h"
#include "console.h"

using namespace std;

/* Function: canOfferUniversalCoverage(Set<string>& cities,
 *                                     Vector< Set<string> >& locations,
 *                                     int numHospitals,
 *                                     Vector< Set<string> >& result);
 * Usage: if (canOfferUniversalCoverage(cities, locations, 4, result)
 * ==================================================================
 * Given a set of cities, a list of what cities various hospitals can
 * cover, and a number of hospitals, returns whether or not it's
 * possible to provide coverage to all cities with the given number of
 * hospitals.  If so, one specific way to do this is handed back in the
 * result parameter.
 */
bool canOfferUniversalCoverage(Set<string>& cities,
                               Vector< Set<string> >& locations,
                               int numHospitals,
                               Vector< Set<string> >& result);

/* ***Prototypes*** */
bool isCovered(Set<string> cities,Vector< Set<string> > result);

/* ***Constances*** */
const string NEGATIVE_ANSWER = "Coverage Can't Found.";
const string POSITIVE_ANSWER = "Coverage Found.";

int main() {
    
	//Test Case
	Set<string> cities;
	cities += "A", "B", "C", "D", "E", "F", "G", "K", "L", "M";

	Set<string> loc1;
	loc1 += "A";

	Set<string> loc2;
	loc2 += "A", "G", "C", "E", "B";

	Set<string> loc3;
	loc3 += "C", "D", "E", "F", "G";

	Set<string> loc4;
	loc4 += "K", "L", "M";

	Vector< Set<string> > locations;
	locations += loc1, loc2, loc3, loc4;

	int numHospitals = 3;

	Vector< Set<string> > result;
	//Test Case

	if(canOfferUniversalCoverage(cities, locations, numHospitals, result)){
		
		cout << POSITIVE_ANSWER << endl;
		cout << "-------------------" << endl;
		cout << result << endl;

	}else cout << NEGATIVE_ANSWER << endl;


    return 0;
}

bool canOfferUniversalCoverage(Set<string>& cities, Vector< Set<string> >& locations, int numHospitals, Vector< Set<string> >& result){

	//Base Case - Location Is Empty
	if(locations.isEmpty()){
		
		//If Cities Are Covered By Result And Result Size Is Less Than "NumHospitals" Method Returns True;
		if(isCovered(cities, result) && numHospitals >= result.size()){
			
			return true;

		}return false;
	}
	
	//Getting First Set Of Locations And Removing It From Locations
	Set<string> x = locations.get(0);
	locations.remove(0);

	//Generating Two Boolean, First Receives Result Without "X", Second With "X", In This Way Code Can Reach Every Subset Of Locations 
	bool withoutFirst = canOfferUniversalCoverage(cities, locations, numHospitals, result);
	//Adding "X" In Result;
	result.insert(0,x);
	bool withFirst = canOfferUniversalCoverage(cities, locations, numHospitals, result);

	//Adding Removed "X" In Locations Again.
	locations.insert(0,x);

	//If Second Boolean, Where "X" Is Add, Returns True, Code Don't Removes "X" From Result
	if(!withFirst) result.remove(0);

	return withFirst || withoutFirst;
}

//Method Bellow Recursively Returns True If Second Argument Covers First One 
bool isCovered(Set<string> cities,Vector< Set<string> > result){
	
	//Base Case - Second Argument Is Empty
	if(result.isEmpty()){
		
		//If First Argument Is Clear Code Returns True, Else False
		if(cities.isEmpty()) {
			
			return true;

		}else return false;
	}
	
	//Every Recursive Call, First Set Reduces By Second Sets First
	cities -= result[0];
	result.remove(0);

	return isCovered(cities, result);
}

