#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#define ALPHASIZE 26

void printInstructions();
bool countGuess(const char alph[], int alphGuess[], char letter);

int main(void) {
    
    const char alphabet[ALPHASIZE] = {'A', 'B', 'C', 'D', 'E', 'F', 'G',
                                'H', 'I', 'J', 'K', 'L', 'M', 'N',
                                'O', 'P', 'Q', 'R', 'S', 'T', 'U',
                                'V', 'W', 'X', 'Y', 'Z'};
    int alphabetGuesses[ALPHASIZE] = {0};

    printInstructions();
    countGuess(alphabet, alphabetGuesses, 'c');

}

// Prints game instructions
void printInstructions()
{
    char welcome[] = "Welcome to Hangman!";
    char howToPlay[] = "How To Play:";
    char instr1[] = "1. A word as been randomly chosen, and you must guess the word to win the game!";
    char instr2[] = "2. Enter one character at a time to guess the word.";
    char instr3[] = "3. For each incorrect guess, a part of the hangman will appear. You get a maximum of n incorrect gueses";
    char instr4[] = "4. For each correct guess, the chosen letter will appear in its designated place(s) in the word.";
    char instr5[] = "5. Each character in the word has been indicated by a \"_\" ";
    char instr6[] = "6. The game has begun. Start guessing and good luck!";

    printf("%25s\n\n%15s\n%s\n%s\n%s\n%s\n%s\n%s\n", welcome, howToPlay, instr1, instr2, instr3, instr4, instr5, instr6);

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
