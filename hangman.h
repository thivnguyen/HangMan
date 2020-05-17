//
// Created by Thi Nguyen on 4/10/20.
//

#ifndef UNTITLED_HANGMAN_H
#define UNTITLED_HANGMAN_H

#include <stdbool.h>
#include <stdio.h>

#define MAXWORDS 100 //max words that array will store
#define MAXWORDLENGTH 20 //max length words can have
#define ALPHASIZE 26

void printInstructions();
int readWords(FILE *filePtr, char storeWords [][MAXWORDLENGTH]);

//functions for user to enter a guess and to check a user guess
char enterGuess(int alphabetGuesses[]);
bool guessedAlr(const char alph[], int alphGuess[], char letter);
bool checkGuesses(const char chosenWord[], unsigned int *rightGuesses, unsigned int *wrongGuesses, unsigned int wordLength, int wordGuesses[],
                  char guessesMade[], int *top, char characterGuess);

//functions to manipulate hangman
void drawFigure(unsigned int numWrongGuesses);
void drawHead(char figure[][8]);
void drawBody(char figure[][8]);
void drawLeftArm(char figure[][8]);
void drawRightArm(char figure[][8]);
void drawLeftLeg(char figure[][8]);
void drawRightLeg(char figure[][8]);
void printFigure(char figure[][8]);

//functions to print game status
bool printCurrentStatus(const char word[], const int guesses[], unsigned int wordLength);
void printGuesses(const char guessesMade[]);
void displayNumberOfLives(unsigned int wrongGuesses);
void printResults(const int guesses[],unsigned int wordLength, unsigned int rightGuesses, unsigned int wrongGuesses, char *chosenWord);

bool anotherGame(char input);


#endif //UNTITLED_HANGMAN_H
