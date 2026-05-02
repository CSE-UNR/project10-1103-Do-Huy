/* Author: Huy Do
Purpose: Wordle Game SImulation
Date: 5-1-2026
*/

#include<stdio.h>
#include<stdbool.h>
#define WORDLENGTH 5
#define ATTEMPTS 6

bool getWord(char word[]);
void lowercase(char str[]);
int strLength(char str[]);
bool validGuess(char guess[]);
void getGuess(char guess[], int guessNum);
void wordleHint(char guess[], char word[], char hint[]);
void printGuess(char guess[], char word[], bool showUpper);
void printLine();
void displayBoard(char guesses[][WORDLENGTH + 1], int numGuess, char word[], bool won);
bool win(char guess[], char word[]);
void printUppercase(char word[]);

int main(){
	char word[WORDLENGTH + 1];
	char guess[ATTEMPTS][WORDLENGTH + 1];
	int numGuess = 0;
	bool won = false;
	
	if(!getWord(word)){
		return 1;
	}
	
	while(numGuess < ATTEMPTS && !won){
		getGuess(guess[numGuess], numGuess + 1);
		numGuess++;
		displayBoard(guess, numGuess, word, won);
		if(win(guess[numGuess - 1], word)){
			won = true;
		}
	}
	if(won){
		printLine();
		printf("		%s\n", word);
		printf("	You won in %d guesses!\n", numGuess);
		if(numGuess == 1){
			printf("		GOATED!\n");
		} else if(numGuess <= 3){
			printf("		Amazing!\n");
		} else if(numGuess <= 5){
			printf("		Nice!\n");
		}
	} else {
		printf("You lost. better luck next time.\n");
	}
	return 0;
}

bool getWord(char word[]){
	FILE* input = fopen("mystery.txt", "r");
	if(input == NULL){
		printf("Could not retrieve word.\n");
		return 0;
	}
	fscanf(input, "%5s", word);
	fclose(input);
	lowercase(word);
	return 1;
}

void lowercase(char str[]){
	int i = 0;
	while(str[i] != '\0'){
		if(str[i] >= 'A' && str[i] <= 'Z'){
			str[i] = str[i] + ('a' - 'A');
		}
		i++;
	}
}

int strLength(char str[]){
	int length = 0;
	while(str[length] != '\0'){
		length++;
	}
	return length;
}

bool validGuess(char guess[]){
	if(strLength(guess) != WORDLENGTH){
		return false;
	}
	for(int i = 0; i < WORDLENGTH; i++){
		if(!((guess[i] >= 'a' && guess[i] <= 'z') || (guess[i] >= 'A' && guess[i] <= 'Z'))){
			return false;
		}
	}
	return true;
}

void getGuess(char guess[], int guessNum){
	char input[50];
	bool valid = false;
	while(!valid){
		printf("Guess %d! Enter guess: ", guessNum);
		scanf("%s", input);
		lowercase(input);
		if(!validGuess(input)){
			printf("Your guess must be 5 letters long\n");
		} else {
			valid = true;
		}
	}
	for(int i = 0; i <= WORDLENGTH; i++){
		guess[i] = input[i];
	}
}

void wordleHint(char guess[], char word[], char hint[]){
	for(int i = 0; i < WORDLENGTH; i++){
		hint[i] = ' ';
	}
	hint[WORDLENGTH] = '\0';
	for(int i = 0; i < WORDLENGTH; i++){
		if(guess[i] != word[i]){
			for(int j = 0; j < WORDLENGTH; j++){
				if(guess[i] == word[j]){
					hint[i] = '^';
					break;
				}
			}
		}
	}
}

void printGuess(char guess[], char word[], bool showUpper){
	for(int i = 0; i < WORDLENGTH; i++){
		if(showUpper && guess[i] == word[i]){
			char uppercase = guess[i]-('a' - 'A');
			printf("%c", uppercase);
		} else {
			printf("%c", guess[i]);
		}
	}
	printf("\n");
}

void printLine(){
	printf("=========================================\n");
}

void displayBoard(char guesses[][WORDLENGTH + 1], int numGuess, char word[], bool won){
	printLine();
	for(int i = 0; i < numGuess; i++){
		bool guessed = won && (i == numGuess - 1);
		printGuess(guesses[i], word, !guessed);
		char hintRow[WORDLENGTH + 1];
		wordleHint(guesses[i], word, hintRow);
		printf("%s\n", hintRow);
	}
}

bool win(char guess[], char word[]){
	for(int i = 0; i < WORDLENGTH; i++){
		if(guess[i] != word[i]){
			return false;
		}
	}
	return true;
}

void printUppercase(char word[]){
	for(int i = 0; i < WORDLENGTH; i++){
		printf("%c", word[i] - ('a' - 'A'));
	}
	printf("\n");
}
