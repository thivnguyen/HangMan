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

    //point to file
    FILE *filePtr = fopen("Words.txt", "r");

    if (filePtr == NULL){
        puts ("Error opening file");
    }
    else {
        char allWords[MAXWORDS][MAXWORDLENGTH]; //every row makes 1 string
        int numWords = readWords(filePtr, allWords); //read words from the file
        fclose(filePtr);

        bool done = false; //done with game

        // Game starts here
        while (done == false) {
            //choose random word
            srand(time(NULL));
            int wordChosenI = rand() % (numWords + 1); //choose a word at random

            //copy word into a separate array
            char *wordChosen = allWords[wordChosenI];
            int lengthOfWord = strlen(wordChosen);
            char word[lengthOfWord + 1]; //word will be stored with a '\0' @ the end
            strcpy(word, wordChosen);
            //int guesses[lengthOfWord] = {0};

            printInstructions();
		
            int incorrectGuesses = 0;
	    int correctGuesses = 0;
	    char lettersGuessed[ALPHASIZE]; // array to keep track of guesses user already made
	    int start = -1; // beginning of letters guessed array;

            // User starts guessing
            while (incorrectGuesses < 6) // Add || (smth to indicate all letters guessed)
            {
                int alphabetGuesses[ALPHASIZE] = {0};
                char guess;

                // Ask for user input

                // Save user input into guess

                countGuess(alphabet, alphabetGuesses, guess);

                // enterGuess()

                // drawFigure()
                drawFigure (incorrectGuesses);

                // printCurrentStatus(word, guesses, lengthOfWord);
		
		//printGuesses(lettersGuessed);

                // displayNumberOfLives()
		displayNumberOfLives(incorrectGuesses);
            }

            // printResults()
	    printResults(alphabetGuesses, int wordLength, int correctGuesses, int incorrectGuesses, char *chosenWord)

            puts("Enter 'Y' if you would like to play again");
            char play;
            scanf("%c", play);
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
char enterGuess(char *chosenWord, int rightGuesses, int wrongGuesses, int wordLength, int alphGuess[], 
		char guessesMade[], int top)
{
	char characterGuess;
	bool found = false;
 
  	printf("Enter a letter from the alphabet: \n"); // prompt
  	scanf(" %c", &characterGuess); // read character

  	//loop through the word to search for character guessed
   	for(int i = 0; i < wordLength; ++i)
   	{
	   if (chosenWord[i] == characterGuess)
	   {
		   found = true;
		   alphGuess[i] = 1; /*Place a 1 in the index of the alphGuess[]
		   				based on where char is located in word*/
	   }
   	}

	if (found == true)// if guess is correct increment rightGuesses
  	{
		rightGuesses++;
  	}
  	else // else increment wrongGuesses
  	{
		wrongGuesses++;
  	}

  	top++; // increment to next position for guesses made array
  	for (int k = 0; k < ALPHASIZE; k++)
  	{
		guessesMade[top] == characterGuess; // copy guess into guessedMade array 
  	}
 
   	if (wrongGuesses == 6)
   	{
     		printf("You're out of guesses. \n");
   	}
 
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

    //initially, when numWrongGuesses = 0, only draw stick
    char figure [8][8]= {  {" _____"},{" |   |"},{" |     "}, {" |     "}, {" |     "},{" |     "},{" |     "},{"---"}};
    switch (numWrongGuesses){
        //0 = print without figure
        case 0:
            break;

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

        default:
            puts ("Incorrect argument");
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

void printCurrentStatus(char word[], char guesses[], int wordLength)
{
    int j = 0; // count correctly guessed letters
    for (int i = 0; i < wordLength; i++)
    {
        if (guesses[i] == 1)
        {
            printf("%c", word[i]);
        }
        else
        {
            printf("%s", "_");
        }
        
    }
    
}

// Print letters user guessed using letters guessed array
void printGuesses(char guessesMade[])
{
	size_t n = sizeof(guessesMade)/sizeof(guessesMade[0]);
	printf(“The guesses you’ve made: \n“)
	
	for (size_t i = 0; i < n && i != ‘\0’; ++i)
	{
		printf(“%c ”, guessesMade[i];
	}
}


// Print how many guesses user has left
void displayNumberOfLives(int wrongGuesses)
{
	int maxNumberOfLives = 6;
	int currentNumberOfLives = maxNumberOfLives - wrongGuesses;
	printf("\nYou have %d guesses left\n", currentNumberOfLives);
}

// Print “You win/lose” statements with number of correct and incorrect guesses
void printResults(char guesses[], int wordLength, int rightGuesses, int wrongGuesses, char *chosenWord)
{
	int countOnes = 0;
    	for(int i = 0; i < wordLength; ++i)
  	{
       		if (guesses[i] == 1)
		{
			countOnes++; // counts number of elements with the value 1
      		}
    	}
    	if(countOnes == wordLength ) // checks if the number of 1’s is equal to length of the word
    	{
        	printf("You win!\n"
        	"Number of correct guesses: %d\n"
        	"Number of incorrect guesses: %d\n",
        	rightGuesses, wrongGuesses); 
    	}

 	else 
    	{ 
        	printf("You lose! The word was %s\n"
 	    	"Number of correct guesses: %d\n" 
        	"Number of incorrect guesses: %d\n",
        	chosenWord, rightGuesses, wrongGuesses);
    	}
}

// Returns true if wants to play again
bool anotherGame(char input)
{
    if (input == 'y' || input == 'Y') // User enters 'y' or 'Y'
    {
        return true;
    }
    else // User enters any other character
    {
        return false;
    }   
}
