// Hangman Game
// By Thi Nguyen, Lynn Tran, Cathy Vu

#include "hangman.h"
#include "drawfigure.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

//array containing alphabet
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
        int totalWords = lastWordInd + 1; //total Wwords read
        fclose(filePtr);

        bool done = false; //done with game

        unsigned int wordsAlrChosen [totalWords];

        //initialize wordsAlrChosen array to 0
        for (int i = 0; i < totalWords; i++) {
            wordsAlrChosen[i] = 0;
        }

        // Game starts here
        while (done == false && !allWordsUsed(wordsAlrChosen, totalWords)) {
            //choose random word
            srand(time(NULL));
            unsigned int wordChosenI = rand() % (totalWords); //choose a word at random

            //make sure that word chosen has not be used in game yet
            while ( wordsAlrChosen [wordChosenI] == 1){
                wordChosenI = rand() % (totalWords);
            }

            wordsAlrChosen[wordChosenI] = 1; //set slot to 1 to indicate that word at slot has been chosen

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

            unsigned int incorrectGuesses = 0;  // initialize number of incorrect guesses
            unsigned int correctGuesses = 0; // initialize number of correct guesses
            char lettersGuessed[ALPHASIZE] = {0}; // array to keep track of guesses user already made
            int lettersGuessedInd = -1; // beginning of letters guessed array;

            //print word with empty spaces so user knows how many letters are in word before guessing
            drawFigure(incorrectGuesses);
            printCurrentStatus(word, guesses, lengthOfWord);

            int alphabetGuesses[ALPHASIZE] = {0};
            bool winner = false; //indicates whether winner has won

            // User starts guessing
            while (incorrectGuesses < 6 && !winner) /* runs as long as number of incorrect guesses is less than 6 and user
	    						hasn't won yet*/
            {

                // Ask for user input
                char userGuess = enterGuess(alphabetGuesses);

                //check whether character exist or not and increment correct/incorrect guesses accordingly
                bool correctGuess = checkGuesses(word, &correctGuesses, &incorrectGuesses, lengthOfWord, guesses,
                                                 lettersGuessed, &lettersGuessedInd, userGuess);

                if (correctGuess) // if guess is correct
                {
                    puts("Yay! Your guess is correct!");
                } else // guess is incorrect
                {
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

            if (!allWordsUsed(wordsAlrChosen, totalWords)) {
                char play;  // decision on whether or not to play again
                unsigned int input = 0;
                char userInput [50] = {0}; //store entire user input, used for error checking
                bool legitResponse = false;

                while (input != 1 || !legitResponse) {
                    puts("Enter 'Y' if you would like to play again. 'N' if you don't."); // prompt
                    input = scanf("%s", userInput); // read user's response

                    if (strlen(userInput) == 1){
                        play = userInput[0];
                        //Makes sure Y, y, N, or n is entered
                        if (play == 78 || play == 89 || play == 110 || play == 121) {
                            legitResponse = true;
                        }
                    }
                }

                if (anotherGame(play) == true) // user wants to play another game
                {
                    puts("You have chosen to play another game.");
                } else // user does not want to play again
                {
                    done = true;
                    puts("Bye!");
                }
            }
            else{
                puts ("You have guessed all the words and have beat the game! Congratulations!");
            }
        }
    }
    return 0;
}

//read words from text file
int readWords(FILE *filePtr, char storeWords[][MAXWORDLENGTH]) {

    char singleWord[46]; //stores single word read from file
    int counter = 0; //will indicate row word will be stored

    while (fgets(singleWord, 45, filePtr)) {
        sscanf(singleWord, "%19s", storeWords[counter]); //store word into 2D char array
        counter++;
    }

    fclose(filePtr); // closes file
    return counter - 1; //index of last word
}

// Prints game instructions
void printInstructions() {
    char welcome[] = "Welcome to Hangman!";
    char howToPlay[] = "How To Play:";
    char instr1[] = "1. A word as been randomly chosen, and you must guess the word to win the game!";
    char instr2[] = "2. Enter one character at a time to guess the word.";
    char instr3[] = "3. For each incorrect guess, a part of the hangman will appear. You get a maximum of 6 incorrect guesses";
    char instr4[] = "4. For each correct guess, the chosen letter will appear in its designated place(s) in the word.";
    char instr5[] = "5. Each character in the word has been indicated by a \"_\" ";
    char instr6[] = "6. The game has begun. Start guessing and good luck!";

    printf("%25s\n\n%15s\n%s\n%s\n%s\n%s\n%s\n%s\n", welcome, howToPlay, instr1, instr2, instr3, instr4, instr5,
           instr6);

}

// Ask user to enter a letter and loop through the word to search for character guessed
//return character that users guessed
char enterGuess(int alphabetGuesses[]) {
    char userInput [50] = {0};
    char characterGuess;

    unsigned int input = 0;
    bool isLetter = false;
    bool oneChar = false; //indicates that only one character is entered
    while (input != 1 || !isLetter || !oneChar) {
        printf("Enter a letter from the alphabet: \n"); // prompt

        input = scanf ("%50s", userInput); //use %s to make that that entire user input is taken in

        //if user entered a character
        oneChar = strlen(userInput) == 1;
        if (oneChar){
            characterGuess = userInput[0];
            //check if character is a letter of alphabet
            if (isalpha(characterGuess)) {
                isLetter = true;
            }
        }
    }

    bool charAlrGuessed = guessedAlr(alphabet, alphabetGuesses, characterGuess);
    while (charAlrGuessed) {
        printf("You already guessed %c. Please guess again. ", toupper(characterGuess));

        input = 0;
        isLetter = false;
        oneChar = false;
        while (input != 1 || !isLetter || !oneChar) {
            printf("Enter a letter from the alphabet: \n"); // prompt

            input = scanf ("%50s", userInput); //use %s to make that that entire user input is taken in

            //if user entered a character
            oneChar = strlen(userInput) == 1;
            if (oneChar){
                characterGuess = userInput[0];
                //check if character is a letter of alphabet
                if (isalpha(characterGuess)) {
                    isLetter = true;
                }
            }
        }

        charAlrGuessed = guessedAlr(alphabet, alphabetGuesses, characterGuess);
    }

    return toupper(characterGuess);
}

//Keeps track of guesses by managing variables for correct and incorrect guesses, arrays for word, and arrays for letters guessed
bool
checkGuesses(const char chosenWord[], unsigned int *rightGuesses, unsigned int *wrongGuesses, unsigned int wordLength,
             int wordGuesses[],
             char guessesMade[], int *top, char characterGuess) {

    bool found = false;

    //loop through the word to search for character guessed
    for (int i = 0; i < wordLength; ++i) {
        if (chosenWord[i] == characterGuess)// if guess is in the word
        {
            found = true;
            //Place a 1 in the index of the wordGuesses[]
		   	//based on where char is located in word
            wordGuesses[i] = 1;
        }
    }

    if (found)// if guess is correct increment rightGuesses
    {
        *rightGuesses = *rightGuesses + 1; // increment rightGuesses
    } else // else increment wrongGuesses
    {
        *wrongGuesses = *wrongGuesses + 1; // increment wrongGuesses
    }

    *top = *top + 1; // increment to next position for guesses made array

    guessesMade[*top] = characterGuess; // copy guess into guessedMade array


    if (*wrongGuesses == 6) // user used up all guesses
    {
        printf("You're out of guesses. \n");
    }

    return found;

}


// Keep track of guesses
// return true if letter has been guessed before
bool guessedAlr(const char alph[], int alphGuess[], char letter) {
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
        i++; // increment
    }
    return guessed;
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

//Calls functions to change 2d array for figure based on number of incorrect guesses
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

//Changes corresponding slot in 2d array for head drawing
void drawHead(char figure[][8]) {
    figure[2][5] = 'O';
}

//Changes corresponding slot in 2d array for body drawing
void drawBody(char figure[][8]) {
    figure[3][5] = '|';
    figure[4][5] = '|';
}

//Changes corresponding slot in 2d for left arm drawing
void drawLeftArm(char figure[][8]) {
    figure[3][4] = '\\';
}

//Changes corresponding slot in 2d for right arm drawing
void drawRightArm(char figure[][8]) {
    figure[3][6] = '/';
}

//Changes corresponding slot in 2d for left leg drawing
void drawLeftLeg(char figure[][8]) {
    figure[5][4] = '/';
}

//Changes corresponding slot in 2d for right leg drawing
void drawRightLeg(char figure[][8]) {
    figure[5][6] = '\\';
}

//Prints figure
void printFigure(char figure[][8]) {
    for (int i = 0; i < 8; i++) {
        printf("%s\n", (figure[i]));
    }
}

//Prints current status of word based on correctly guessed letters
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

    printf("The guesses you’ve made: \n");

    for (int i = 0; guessesMade[i] != 0; ++i) //iterates until the \0 null character is reached
    {
        printf("%c ", guessesMade[i]); // print each letter in guessesMade[]
    }
}


// Print how many guesses user has left
void displayNumberOfLives(unsigned int wrongGuesses) {
    unsigned int maxNumberOfLives = 6; // maximum number of lives (guesses) user has
    unsigned int currentNumberOfLives = maxNumberOfLives - wrongGuesses; // update current number of lives
    printf("\nYou still have %u lives\n", currentNumberOfLives);
}

// Print “You win/lose” statements with number of correct and incorrect guesses
void printResults(const int guesses[], unsigned int wordLength, unsigned int rightGuesses, unsigned int wrongGuesses,
                  char *chosenWord) {
    int countOnes = 0; // counts number of elements with the value 1 in guesses[] array

    for (int i = 0; i < wordLength; ++i) {
        if (guesses[i] == 1) // if element is 1
        {
            countOnes++; // increment
        }
    }
    if (countOnes == wordLength) // checks if the number of 1’s is equal to length of the word --> user won
    {
        printf("\nYou win!\n"
               "Number of correct guesses: %u\n"
               "Number of incorrect guesses: %u\n",
               rightGuesses, wrongGuesses);
    } else // number of 1's does not equal to the length of the word --> user lost
    {
        printf("You lose! The word was %s\n"
               "Number of correct guesses: %u\n"
               "Number of incorrect guesses: %u\n",
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

//Determines whether the word chosen from the list of words has already been used in the game before
bool allWordsUsed (const unsigned int wordsAlrChosen[], int length){
    for (int i = 0; i < length; i ++){
        if (wordsAlrChosen[i] == 0){
            return false;
        }
    }
    return true;
}
