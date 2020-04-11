//
// Created by Thi Nguyen on 4/10/20.
//

#ifndef UNTITLED_HANGMAN_H
#define UNTITLED_HANGMAN_H

#define MAXWORDS 100 //max words that array will store
#define MAXWORDLENGTH 20 //max length words can have


int readWords(FILE *filePtr, char storeWords [][MAXWORDLENGTH]);
void drawFigure(int i);
void drawHead(char figure[][8]);
void drawBody(char figure[][8]);
void drawLeftArm(char figure[][8]);
void drawRightArm(char figure[][8]);
void drawLeftLeg(char figure[][8]);
void drawRightLeg(char figure[][8]);
void printFigure(char figure[][8]);

#endif //UNTITLED_HANGMAN_H
