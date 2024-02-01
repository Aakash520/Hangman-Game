#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
using namespace std;

// Function to display the hangman figure based on the number of incorrect attempts
void displayHangman(int incorrectAttempts)
{
    // Displaying the hangman figure using ASCII art
	cout << " ___________________________ \n"
		 << "|                           |\n"
		 << "|========| HANGMEN |========|\n"
		 << "|                           |\n"
		 << "|          +-----+          |\n"
         << "|          |     |          |\n";
//===================================================
    cout << "|          ";  
    // Displaying the head of the hangman if there is at least one incorrect attempt
    if(incorrectAttempts >= 1)
		cout << "o";
	else
		cout << " "; 
	cout << "     |          |\n";
//===================================================
	cout << "|         "; 
	// Displaying the upper body based on the number of incorrect attempts
	if(incorrectAttempts >= 4)
		cout << "/|\\";
	else if(incorrectAttempts >= 3)
		cout << "/| ";
	else if(incorrectAttempts >= 2)
		cout << "/  "; 
    else if(incorrectAttempts >= 0)
		cout << "   ";
	cout << "    |          |\n";
//===================================================
	cout << "|         "; 
	// Displaying the lower body based on the number of incorrect attempts
	if(incorrectAttempts >= 6)
		cout << "/ \\";
	else if(incorrectAttempts >= 5)
		cout << "/  "; 
    else if(incorrectAttempts >= 0)
		cout << "   ";
	cout << "    |          |\n";
//===================================================

	cout << "|                |          |\n"
         << "|                |          |\n"
		 << "|       ============        |\n"
		 << "|___________________________|\n";
}

// Function to fill an array with underscores
void fillArray(char secretWord[], int length)
{
    for (int i = 0; i < length; i++)
        secretWord[i] = '_';
}

// Function to display the guessed word
void displayWord(char secretWord[], int length)
{
    for (int i = 0; i < length; i++)
        cout << secretWord[i] << " ";
}

// Function to update the guessed word based on the user's input
void updateGuessedWord(char wordToGuess[], char guess, char guessedWord[], int length)
{
    for (int i = 0; i < length; i++)
    {
        if (wordToGuess[i] == guess)
        {
            guessedWord[i] = guess;
        }
    }
}

// Function to check if the word has been completely guessed
bool isWordGuessed(const char wordToGuess[], const char guessedWord[], int length)
{
    for (int i = 0; i < length; i++)
    {
        if (guessedWord[i] != wordToGuess[i])
        {
            return false;
        }
    }
    return true;
}

// Main function
int main()
{
	// Seed the random number generator with the current time
    srand(time(0));
    
    // Array of words for the game
    char wordList[7][20] = {"smooth", "hangman", "programming", "random", "solution", "language", "computer"};
    
	char guess;
	
	// Randomly select an index from the wordList array
    int wordIndex = rand() % 7;
    
    // Determine the length of the word to guess
    int wordLength = strlen(wordList[wordIndex]);
    
    // Initialize the number of incorrect attempts
    int incorrectAttempts = 0;

	// Array to store the word to guess
    char wordToGuess[20];
    strcpy(wordToGuess, wordList[wordIndex]);

	// Array to store the guessed word
    char guessedWord[20] = "\0";
    
    // Fill the guessed word array with underscores
    fillArray(guessedWord, wordLength);

	// Display initial game information
    cout << "Hello! Welcome to the word guessing game:\n";
    cout << "Below are the first and last levels of the game.\n";
    cout << "At the bottom is the number of dashes representing the length of the word you are supposed to guess.\n";
    cout << "BEST OF LUCK!\n";
    displayHangman(0);
    displayHangman(6);
    displayWord(guessedWord, wordLength);

	// Game loop
    for (int attempt = 0; attempt < 7; attempt++)
    {
        int j = 0;
        cout << "\nEnter a character: ";
        cin >> guess;
        bool correctGuess = false;

		// Check if the guessed character is in the word
        for (j = 0; wordToGuess[j] != '\0'; j++)
        {
            if (guess == wordToGuess[j])
            {
            	// If correct, update the guessed word and display the hangman figure
                system("CLS");
                cout << "\nCongratulations !!!! You guessed the correct character!\n";
                updateGuessedWord(wordToGuess, guess, guessedWord, wordLength);
                correctGuess = true;
                int x = (incorrectAttempts > 0) ? (incorrectAttempts - 1) : incorrectAttempts;
                displayHangman(x);
                break;
            }
        }

		// If the guess is incorrect, decrement attempts and display relevant information
        if (!correctGuess)
        {
            attempt--;
            system("CLS");
            cout << "OOPS !! Your guessed character is not in the array. "
                 << "Try again\n";
            displayHangman(incorrectAttempts);
            cout << "Remaining tries are " << (6 - incorrectAttempts) << "\n";
            incorrectAttempts++;
        }

		// Display the current state of the guessed word
        displayWord(guessedWord, wordLength);

		// Check if the entire word has been guessed
        if (isWordGuessed(wordToGuess, guessedWord, wordLength))
        {
            cout << "\nCongratulations! You guessed the word: " << wordToGuess << endl;
            break;
        }

		// Check if the maximum number of incorrect attempts has been reached
        if (incorrectAttempts == 7)
        {
            cout << "\nRemaining tries: 0\n"
                 << "You failed! The word was: " << wordToGuess << "\nBetter luck next time.\n";
            break;
        }
    }
    return 0;
}

