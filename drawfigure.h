// drawfigure.h
// By Thi Nguyen, Lynn Tran, Cathy Vu
// functions to manipulate hangman


#ifndef DRAWFIGURE_H
#define DRAWFIGURE_H

//Calls functions to change 2d array for figure based on number of incorrect guesses
void drawFigure(unsigned int numWrongGuesses);

//Changes corresponding slot in 2d array for head drawing
void drawHead(char figure[][8]);

//Changes corresponding slot in 2d array for body drawing
void drawBody(char figure[][8]);

//Changes corresponding slot in 2d for left arm drawing
void drawLeftArm(char figure[][8]);

//Changes corresponding slot in 2d for right arm drawing
void drawRightArm(char figure[][8]);

//Changes corresponding slot in 2d for left leg drawing
void drawLeftLeg(char figure[][8]);

//Changes corresponding slot in 2d for right leg drawing
void drawRightLeg(char figure[][8]);

//Prints figure
void printFigure(char figure[][8]);

#endif
