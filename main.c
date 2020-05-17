#include "hangman.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

const char alphabet[ALPHASIZE] = {'A', 'B', 'C', 'D', 'E', 'F', 'G',
                                  'H', 'I', 'J', 'K', 'L', 'M', 'N',
                                  'O', 'P', 'Q', 'R', 'S', 'T', 'U',
                                  'V', 'W', 'X', 'Y', 'Z'};

int main(void) {

    //point to file
    FILE *filePtr = fopen("Words.txt", "r");

    if (filePtr == NULL) {
        puts("Error opening file");
    } else {
        char allWords[MAXWORDS][MAXWORDLENGTH]; //every row makes 1 string
        int lastWordInd = readWords(filePtr, allWords); //read words from the file
        fclose(filePtr);

        bool done = false; //done with game

        // Game starts here
        while (done == false) {
            //choose random word
            srand(time(NULL));
            unsigned int wordChosenI = rand() % (lastWordInd + 1); //choose a word at random

            //copy word into a separate array
            char *wordChosen = allWords[wordChosenI];
            unsigned int lengthOfWord = strlen(wordChosen);
            char word[lengthOfWord + 1]; //word will be stored with a '\0' @ the end
            strcpy(word, wordChosen);
            int guesses[lengthOfWord]; //keeps tracks of which characters has been guessed correctly

            //initialize guesses array to 0
            for (int i = 0; i < lengthOfWord; i++) {
                guesses[i] = 0;
            }

            printInstructions();

            unsigned int incorrectGuesses = 0;
            unsigned int correctGuesses = 0;
            char lettersGuessed[ALPHASIZE] = {0}; // array to keep track of guesses user already made
            int lettersGuessedInd = -1; // beginning of letters guessed array;

            //print word with empty spaces so user knows how many letters are in word before guessing
            drawFigure(incorrectGuesses);
            printCurrentStatus(word, guesses, lengthOfWord);

            int alphabetGuesses[ALPHASIZE] = {0};
            bool winner = false; //indicates whether winner has won

            // User starts guessing
            while (incorrectGuesses < 6 && !winner) {

                // Ask for user input
                char userGuess = enterGuess(alphabetGuesses);

                //check whether character exist or not and increment correct/incorrect guesses accordingly
                bool correctGuess = checkGuesses(word, &correctGuesses, &incorrectGuesses, lengthOfWord, guesses,
                                                 lettersGuessed, &lettersGuessedInd, userGuess);

                if (correctGuess) {
                    puts("Yay! Your guess is correct!");
                } else {
                    puts("Incorrect guess. You lost 1 life :(");
                }

                drawFigure(incorrectGuesses);

                //print _ for letters that are not guessed yet and the char for characters guessed correctly
                winner = printCurrentStatus(word, guesses, lengthOfWord);

                //print characters user have already guessed
                printGuesses(lettersGuessed);

                //display number of lives left
                displayNumberOfLives(incorrectGuesses);
            }



            // print results
            printResults(guesses, lengthOfWord, correctGuesses, incorrectGuesses, word);

            char play;
            unsigned int input = 0;
            bool legitResponse = false;
            while (input != 1 || !legitResponse) {
                puts("Enter 'Y' if you would like to play again. 'N' if you don't.");
                input = scanf(" %c", &play);

                if (play == 78 || play == 89 || play == 110 || play == 121) {
                    legitResponse = true;
                }
            }
            if (anotherGame(play) == true) {
                puts("You have chosen to play another game.");
            } else {
                done = true;
                puts("Bye!");
            }
        }
    }
    return 0;
}

// Prints game instructions
void printInstructions() {
    char welcome[] = "Welcome to Hangman!";
    char howToPlay[] = "How To Play:";
    char instr1[] = "1. A word as been randomly chosen, and you must guess the word to win the game!";
    char instr2[] = "2. Enter one character at a time to guess the word.";
    char instr3[] = "3. For each incorrect guess, a part of the hangman will appear. You get a maximum of 6 incorrect gueses";
    char instr4[] = "4. For each correct guess, the chosen letter will appear in its designated place(s) in the word.";
    char instr5[] = "5. Each character in the word has been indicated by a \"_\" ";
    char instr6[] = "6. The game has begun. Start guessing and good luck!";

    printf("%25s\n\n%15s\n%s\n%s\n%s\n%s\n%s\n%s\n", welcome, howToPlay, instr1, instr2, instr3, instr4, instr5,
           instr6);

}

// Ask user to enter a letter and loop through the word to search for character guessed
//return true if guess is correct
char enterGuess(int alphabetGuesses[]) {
    char characterGuess;

    unsigned int input = 0;
    bool inRange = false;
    while (input != 1 || !inRange) {
        printf("Enter a letter from the alphabet: \n"); // prompt
        input = scanf(" %c", &characterGuess); // read character

        //check if character is in range
        if (characterGuess >= 65 && characterGuess <= 90 || characterGuess >= 97 && characterGuess <= 122) {
            inRange = true;
        }
    }

    bool charAlrGuessed = guessedAlr(alphabet, alphabetGuesses, characterGuess);
    while (charAlrGuessed) {
        puts("You already guessed this. Please guess again.");

        input = 0;
        inRange = false;

        while (input != 1 || !inRange) {
            printf("Enter a letter from the alphabet: \n"); // prompt
            input = scanf(" %c", &characterGuess); // read character

            //check if character is in range
            if (characterGuess >= 65 && characterGuess <= 90 || characterGuess >= 97 && characterGuess <= 122) {
                inRange = true;
            }
        }

        charAlrGuessed = guessedAlr(alphabet, alphabetGuesses, characterGuess);
    }

    return toupper(characterGuess);
}

bool checkGuesses(const char chosenWord[], unsigned int *rightGuesses, unsigned int *wrongGuesses, unsigned int wordLength,
             int wordGuesses[],
             char guessesMade[], int *top, char characterGuess) {

    bool found = false;

    //loop through the word to search for character guessed
    for (int i = 0; i < wordLength; ++i) {
        if (chosenWord[i] == characterGuess) {
            found = true;
            wordGuesses[i] = 1; /*Place a 1 in the index of the wordGuesses[]
		   				based on where char is located in word*/
        }
    }

    if (found)// if guess is correct increment rightGuesses
    {
        *rightGuesses = *rightGuesses + 1;
    } else // else increment wrongGuesses
    {
        *wrongGuesses = *wrongGuesses + 1;
    }

    *top = *top + 1; // increment to next position for guesses made array

    guessesMade[*top] = characterGuess; // copy guess into guessedMade array

    if (*wrongGuesses == 6) {
        printf("You're out of guesses. \n");
    }

    return found;

}


// Keep track of guesses
// return true if letter has been guessed before
bool guessedAlr(const char alph[], int alphGuess[],  char letter) {
    letter = toupper(letter);   //make character uppercase before comparing
    int i = 0;                  // Initialize counter
    bool guessed = false;
    while (i < ALPHASIZE) // Check if letter matches
    {
        if (alph[i] == letter) // Letter is found
        {
            if (alphGuess[i] == 0) // Letter has not been guessed
            {
                alphGuess[i] = 1;
            } else {
                guessed = true;
            }
            break;
        }
        i++;
    }
    return guessed;
}


int readWords(FILE *filePtr, char storeWords[][MAXWORDLENGTH]) {

    char singleWord[46]; //stores single word read from file
    int counter = 0; //will indicate row word will be stored

    while (fgets(singleWord, 45, filePtr)) {
        sscanf(singleWord, "%21s", storeWords[counter]); //store word into 2D char array
        counter++;
    }

    fclose(filePtr);
    return counter - 1; //index of last word
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

void drawFigure(unsigned int numWrongGuesses) {

    //initially, when numWrongGuesses = 0, only draw stick
    char figure[8][8] = {{" _____"},
                         {" |   |"},
                         {" |     "},
                         {" |     "},
                         {" |     "},
                         {" |     "},
                         {" |     "},
                         {"---"}};
    switch (numWrongGuesses) {
        //0 = print without figure
        case 0:
            break;

            //1 = head
        case 1:
            drawHead(figure);
            break;

            //2 = body
        case 2:
            drawHead(figure);
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

        default:
            puts("Incorrect argument");
    }

    printFigure(figure);
}

void drawHead(char figure[][8]) {
    figure[2][5] = 'O';
}

void drawBody(char figure[][8]) {
    figure[3][5] = '|';
    figure[4][5] = '|';
}

void drawLeftArm(char figure[][8]) {
    figure[3][4] = '\\';
}

void drawRightArm(char figure[][8]) {
    figure[3][6] = '/';
}

void drawLeftLeg(char figure[][8]) {
    figure[5][4] = '/';
}

void drawRightLeg(char figure[][8]) {
    figure[5][6] = '\\';
}

void printFigure(char figure[][8]) {
    for (int i = 0; i < 8; i++) {
        printf("%s\n", (figure[i]));
    }
}

bool printCurrentStatus(const char word[], const int guesses[], unsigned int wordLength) {
    int counter = 0;

    //int j = 0; // count correctly guessed letters
    for (int i = 0; i < wordLength; i++) {
        if (guesses[i] == 1) {
            counter++;
            printf("%c", word[i]);
            printf(" ");
        } else {
            printf("%s", "_ ");
        }

    }
    puts(" ");

    if (counter == wordLength) {
        return true;
    }
    return false;

}

// Print letters user guessed using letters guessed array
void printGuesses(const char guessesMade[]) {
    size_t n = sizeof(guessesMade) / sizeof(guessesMade[0]);
    printf("The guesses you’ve made: \n");

    for (size_t i = 0; i < n && guessesMade[i] != '\0'; ++i) {
        printf("%c ", guessesMade[i]);
    }
}

// Print how many guesses user has left
void displayNumberOfLives(unsigned int wrongGuesses) {
    unsigned int maxNumberOfLives = 6;
    unsigned int currentNumberOfLives = maxNumberOfLives - wrongGuesses;
    printf("\nYou still have %u lives\n", currentNumberOfLives);
}

// Print “You win/lose” statements with number of correct and incorrect guesses
void printResults(const int guesses[], unsigned int wordLength, unsigned int rightGuesses, unsigned int wrongGuesses,
                  char *chosenWord) {
    int countOnes = 0;
    for (int i = 0; i < wordLength; ++i) {
        if (guesses[i] == 1) {
            countOnes++; // counts number of elements with the value 1
        }
    }
    if (countOnes == wordLength) // checks if the number of 1’s is equal to length of the word
    {
        printf("\nYou win!\n"
               "Number of correct guesses: %d\n"
               "Number of incorrect guesses: %d\n",
               rightGuesses, wrongGuesses);
    } else {
        printf("You lose! The word was %s\n"
               "Number of correct guesses: %d\n"
               "Number of incorrect guesses: %d\n",
               chosenWord, rightGuesses, wrongGuesses);
    }
}

// Returns true if wants to play again
bool anotherGame(char input) {
    if (input == 'y' || input == 'Y') // User enters 'y' or 'Y'
    {
        return true;
    } else // User enters 'n' or 'N'
    {
        return false;
    }
}
