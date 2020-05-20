// Hangman.h
// By Thi Nguyen, Lynn Tran, Cathy Vu
// Functions to read from File, for user to etner guesses, and for printing results


#ifndef HANGMAN_H
#define HANGMAN_H

#include <stdbool.h>
#include <stdio.h>

#define MAXWORDS 100 //max words that array will store
#define MAXWORDLENGTH 20 //max length words can have including '\0'
#define ALPHASIZE 26 //size of alphabet

//Prints game instructions
void printInstructions();

//Reads file of words and stores words into 2d array
int readWords(FILE *filePtr, char storeWords [][MAXWORDLENGTH]);

//Asks the user to enter their guess
char enterGuess(int alphabetGuesses[]);

//Keeps track of guesses by checking if a letter has been guessed
bool guessedAlr(const char alph[], int alphGuess[], char letter);

//Keeps track of guesses by managing variables for correct and incorrect guesses, arrays for word, and arrays for letters guessed
bool checkGuesses(const char chosenWord[], unsigned int *rightGuesses, unsigned int *wrongGuesses, unsigned int wordLength, int wordGuesses[],
                  char guessesMade[], int *top, char characterGuess);

//Prints current status of word based on correctly guessed letters
bool printCurrentStatus(const char word[], const int guesses[], unsigned int wordLength);

//Prints letters guessed by player
void printGuesses(const char guessesMade[]);

//Prints number of lives left based on number of incorrect guesses
void displayNumberOfLives(unsigned int wrongGuesses);

//Prints game results after player has won/lost
void printResults(const int guesses[],unsigned int wordLength, unsigned int rightGuesses, unsigned int wrongGuesses, char *chosenWord);

//Continues or ends program based on whether or not user wants to play another game
bool anotherGame(char input);

//Determines whether the word chosen from the list of words has already been used in the game before
bool allWordsUsed (const unsigned int wordsAlrChosen[], int length);

#endif
