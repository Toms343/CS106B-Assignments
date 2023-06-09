/*
 * File: Sierpinski.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Sierpinski problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <math.h>
#include "simpio.h"
#include "gwindow.h"

using namespace std;

/* ***Constances*** */

/* ***G Window Sizes*** */
const double WINDOW_WIDTH = 750;
const double WINDOW_HEIGHT = 750;

/* ***Triangle Starting Positions*** */
const double START_X = WINDOW_WIDTH / 2;
const double TOP_MARGIN = 25;

/* ***Minimal Triangle Side Length In SierPinski*** */
const double MINIMAL_TRIANGLE_SIZE = 5;

/* ***THETAS*** */
const double STARTING_ANGLE = -60;
const double ANGLE_CHANGER = -120;
const double SECOND_STARTING_ANGLE = 0;

/* ***Prototypes*** */
void getUserInput(double &side, int &fractalNum);
void drawSierpinski(GWindow &gw,double startX,double startY,double side,int fractalNum);
void drawRecursively(GWindow &gw, GPoint top, GPoint left, GPoint right, double side, int fractalNum);

int main() {

	//Creating New GWindow
	GWindow gw(WINDOW_WIDTH,WINDOW_HEIGHT);

	double side = 0;
	int fractalNum = -1;
	
	//REceiving User Input
	getUserInput(side, fractalNum);

	//Drawing Triangle
	drawSierpinski(gw,START_X,TOP_MARGIN,side, fractalNum);

	return 0;
}

//Method Bellow Draws Sierpinski Triangle Recursively
void drawSierpinski(GWindow &gw,double startX,double startY,double side,int fractalNum){
	
	//62-64 Lines Draws Sierpinski's Zero Triangle On Window
	GPoint p1 = gw.drawPolarLine(startX, startY, side, STARTING_ANGLE);
	GPoint p2 = gw.drawPolarLine(p1.getX(), p1.getY(), side, STARTING_ANGLE + ANGLE_CHANGER);
	GPoint p3 = gw.drawPolarLine(p2.getX(), p2.getY(), side, STARTING_ANGLE + 2 * ANGLE_CHANGER);

	//I Used Function Bellow To Draw Triangle Recursively
	drawRecursively(gw, p3, p2, p1, side / 2, fractalNum);

}

//Method Receives Corner Points Of Triangle And Draws Middle Triangle
void drawRecursively(GWindow &gw, GPoint top, GPoint left, GPoint right, double side, int fractalNum){

	//Recursion Stops When Received fractalNum == 0
	if(fractalNum == 0) return;
	
	//Triangles Left Sides MidPoint
	GPoint leftMid((top.getX() + left.getX()) / 2 , (top.getY() + left.getY()) / 2);

	//This Codes Bellow Draws Lines And Also Generates MidPoints Of Right And Bottom Side
	GPoint rightMid = gw.drawPolarLine(leftMid.getX(), leftMid.getY(), side, SECOND_STARTING_ANGLE);
	GPoint bottomMid = gw.drawPolarLine(rightMid.getX(), rightMid.getY(), side, SECOND_STARTING_ANGLE + ANGLE_CHANGER);

	//Draws Last Line Of Triangle 
	gw.drawLine(leftMid.getX(), leftMid.getY(), bottomMid.getX(), bottomMid.getY());

	//I Call The Same Method For The Obtained Three Triangle
	drawRecursively(gw, top, leftMid, rightMid, side / 2, fractalNum - 1);
	drawRecursively(gw, leftMid, left, bottomMid, side / 2, fractalNum - 1);
	drawRecursively(gw, rightMid, bottomMid, right, side / 2, fractalNum - 1);

}

//Method Bellow Receives User Input
void getUserInput(double &side, int &fractalNum){

	//While Loops Bellow Break When User Enters Number More Than 0
	while(side <= 0) {
			
		side = getReal("Enter Triangle Side Length, Side Must Be More Than 0: ");
	}

	int safeMode = -1;

	//While Loop Bellow Breaks When User Enters 0 or 1
	while(!(safeMode == 0 || safeMode == 1)){
		
		safeMode = getInteger("Do You Want To Draw In Safe Mode? (Code Helps To Choose Right FractalNumber, 1 - True, 0 -False): ");

	}

	//While Loop Bellow Breaks When User Enters Correct Fractal Number
	while(true){
		fractalNum = getInteger("Enter Fractal Number, It Must Be 0 Or More: ");

		//If Fractal Num Is 0 Or More Than 0 And SafeMode Is Turned Off Loop Breaks
		if(fractalNum >= 0){
			
			//If Safe Mode Is Turned On Code Checks Minimal Side Length, And If Its In Range Loop Breaks Again
			if(safeMode == 1){
				
				if(side / pow(2.0,fractalNum) < MINIMAL_TRIANGLE_SIZE){

					cout << "Minimal Triangle Side Size Will Be Less Than " << MINIMAL_TRIANGLE_SIZE << " Try Lower Number." << endl;
					
				}else break;

			}else break;
		}
	}
}
