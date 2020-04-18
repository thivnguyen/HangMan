//
// Created by Thi Nguyen on 4/10/20.
//

#ifndef UNTITLED_HANGMAN_H
#define UNTITLED_HANGMAN_H

#include <stdbool.h>

#define MAXWORDS 100 //max words that array will store
#define MAXWORDLENGTH 20 //max length words can have
#define ALPHASIZE 26

void printInstructions();
char enterGuess(char *chosenWord, int rightGuesses, int wrongGuesses, int wordLength, int alphGuess[], 
		char guessesMade[], int top);
bool countGuess(const char alph[], int alphGuess[], char letter);

int readWords(FILE *filePtr, char storeWords [][MAXWORDLENGTH]);

void drawFigure(int i);
void drawHead(char figure[][8]);
void drawBody(char figure[][8]);
void drawLeftArm(char figure[][8]);
void drawRightArm(char figure[][8]);
void drawLeftLeg(char figure[][8]);
void drawRightLeg(char figure[][8]);
void printFigure(char figure[][8]);

void printCurrentStatus(char word[], char guesses[], int wordLength);
void printGuesses(char guessesMade[]);
void displayNumberOfLives(int wrongGuesses);
void printResults(char guesses[], int wordLength, int rightGuesses, int wrongGuesses, char *chosenWord);

bool anotherGame(char input);

#endif //UNTITLED_HANGMAN_H
