#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hangman.h"
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

int main(void) {

    const char alphabet[ALPHASIZE] = {'A', 'B', 'C', 'D', 'E', 'F', 'G',
                                'H', 'I', 'J', 'K', 'L', 'M', 'N',
                                'O', 'P', 'Q', 'R', 'S', 'T', 'U',
                                'V', 'W', 'X', 'Y', 'Z'};
    int alphabetGuesses[ALPHASIZE] = {0};
    char guess;
    printInstructions();
    countGuess(alphabet, alphabetGuesses, guess);

    //point to file
    FILE *filePtr = fopen("Words.txt", "r");
    char allWords[MAXWORDS][MAXWORDLENGTH]; //every row makes 1 string
    int numWords = readWords (filePtr, allWords); //read words from the file
    fclose(filePtr);

    //choose random word
    srand (time(NULL));
    int wordChosenI = rand() % (numWords + 1); //choose a word at random

    //copy word into a separate array
    char *wordChosen = allWords[wordChosenI];
    int lengthOfWord = strlen(wordChosen);
    char word [lengthOfWord+1]; //word will be stored with a '\0' @ the end
    strcpy(word, wordChosen);

    return 0;
}

// Prints game instructions
void printInstructions()
{
    char welcome[] = "Welcome to Hangman!";
    char howToPlay[] = "How To Play:";
    char instr1[] = "1. A word as been randomly chosen, and you must guess the word to win the game!";
    char instr2[] = "2. Enter one character at a time to guess the word.";
    char instr3[] = "3. For each incorrect guess, a part of the hangman will appear. You get a maximum of 6 incorrect gueses";
    char instr4[] = "4. For each correct guess, the chosen letter will appear in its designated place(s) in the word.";
    char instr5[] = "5. Each character in the word has been indicated by a \"_\" ";
    char instr6[] = "6. The game has begun. Start guessing and good luck!";

    printf("%25s\n\n%15s\n%s\n%s\n%s\n%s\n%s\n%s\n", welcome, howToPlay, instr1, instr2, instr3, instr4, instr5, instr6);

}

// Ask user to enter a letter and loop through the word to search for character guessed 
char enterGuess(char *chosenWord)
 {  
    char characterGuess;
    int lengthOfWord = strlen(chosenWord);
    int count = 0; // initialize number of guesses made

    while(count < 6) // change 6 to a constant later
    {
      printf("Enter a letter from the alphabet: \n");
      scanf(" %c", &characterGuess);
      count++;
    }
    if (count == 6)
    {
      printf("You're out of guesses. \n");
    }
    //loop through the word to search for character guessed
    /*  for(int i =0; i < lengthOfWord; ++i)
      {
        if (chosenWord[i] == characterGuess)
        {
	        guesses[i] = 1; place a 1 in the index of the guesses[] based on where the character is located in the word
        }
      }*/
 }

// Keep track of guesses
bool countGuess(const char alph[], int alphGuess[], char letter)
{
    letter = toupper(letter);   // Change letter to uppercase
    int i = 0;                  // Initialize counter
    bool guessed = false;
    while (i < ALPHASIZE) // Check if letter matches
    {
        if (alph[i] == letter) // Letter is found
        {
            if (alphGuess[i] == 0) // Letter has not been guessed
            {
                alphGuess[i] = 1;
            }
            else
            {
                guessed = true;
            }
            break;
        }
        i++;
    }
    return guessed;
}


int readWords(FILE *filePtr, char storeWords [][MAXWORDLENGTH]) {

    char singleWord[46]; //stores single word read from file
    int counter = 0; //will indicate row word will be stored

    while (fgets(singleWord, 45, filePtr)) {
        sscanf(singleWord, "%s", storeWords[counter]); //store word into 2D char array
        counter++;
    }

    fclose(filePtr);
    return counter + 1; //index of last word
}

/*
 _____
 |   |
 |   O
 |  \|/
 |   |
 |  / \
 |
---
 //figure[0] = {' ','_','_','_','_','_','\0'}
 //figure[1] = {' ','|',' ',' ',' ,'|','\0'}
 //figure[2] = {' ','|',' ',' ',' ',' ','\0'}
 //figure[3] = {' ','|',' ',' ',' ',' ','\0'}
 //figure[4] = {' ','|',' ',' ',' ',' ','\0'}
 //figure[5] = {' ','|',' ',' ',' ',' ','\0'}
 //figure[6] = {' ','|',' ',' ',' ',' ','\0'}
 //figure[6] = {'-','-','-',' ',' ',' ','\0'}
 */

void drawFigure(int numWrongGuesses){
    char figure [8][8]= {  {" _____"},{" |   |"},{" |     "}, {" |     "}, {" |     "},{" |     "},{" |     "},{"---"}};
    switch (numWrongGuesses){
        //1 = head
        case 1:
            drawHead(figure);
            break;

            //2 = body
        case 2:
            drawBody(figure);
            break;

            //3 = left arm
        case 3:
            drawHead(figure);
            drawBody(figure);
            drawLeftArm(figure);
            break;

            //4 = right arm
        case 4:
            drawHead(figure);
            drawBody(figure);
            drawLeftArm(figure);
            drawRightArm(figure);
            break;

            //5 = left leg
        case 5:
            drawHead(figure);
            drawBody(figure);
            drawLeftArm(figure);
            drawRightArm(figure);
            drawLeftLeg(figure);
            break;

            //6 = right leg
        case 6:
            drawHead(figure);
            drawBody(figure);
            drawLeftArm(figure);
            drawRightArm(figure);
            drawLeftLeg(figure);
            drawRightLeg(figure);
            break;
    }

    printFigure(figure);
}

void drawHead(char figure[][8]){
    figure[2][5] = 'O';
}

void drawBody(char figure[][8]){
    figure[3][5] = '|';
    figure[4][5] = '|';
}

void drawLeftArm(char figure[][8]){
    figure[3][4] = '\\';
}

void drawRightArm(char figure[][8]){
    figure[3][6] = '/';
}

void drawLeftLeg(char figure[][8]){
    figure[5][4] = '/';
}

void drawRightLeg(char figure[][8]){
    figure[5][6] = '\\';
}

void printFigure(char figure[][8]){
    for (int i = 0; i < 8; i++){
        printf ("%s\n",(figure[i]));
    }
}

