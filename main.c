#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hangman.h"


int main(void) {

    //point to file
    FILE *filePtr = fopen("Words.txt", "r");
    char allWords[MAXWORDS][MAXWORDLENGTH]; //every row makes 1 string
    int numWords = readWords (filePtr, allWords); //read words from the file
    fclose(filePtr);

    srand (time(NULL));
    int wordChosen = rand() % (numWords + 1); //choose a word at random

    char *word = allWords[wordChosen];
    drawFigure(6);
    return 0;
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