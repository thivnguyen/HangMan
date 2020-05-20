//
// Functions to manipulate hangman
// By Thi Nguyen, Lynn Tran, Cathy Vu
//

#ifndef HANGMAN_DRAWFIGURE_H
#define HANGMAN_DRAWFIGURE_H


void drawFigure(unsigned int numWrongGuesses);
void drawHead(char figure[][8]);
void drawBody(char figure[][8]);
void drawLeftArm(char figure[][8]);
void drawRightArm(char figure[][8]);
void drawLeftLeg(char figure[][8]);
void drawRightLeg(char figure[][8]);
void printFigure(char figure[][8]);

#endif //HANGMAN_DRAWFIGURE_H
