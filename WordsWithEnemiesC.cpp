// Reddit Dailyprogrammer
// Easy #198: Words with Enemies
// Link to problem: http://redd.it/2syz7y


#include "stdafx.h"
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 255
#define NO_INPUT -1
#define OK 0
#define TOO_LONG 1
#define ALPHABET_SIZE 26
#define COUNT_UP 1
#define COUNT_DOWN -1
#define LEFT_SIDE 1
#define RIGHT_SIDE -1

int getline(char *prompt, char *buff, size_t size);
int count_letters(char *word, int *count, int nValue);
int sum(int *count);
int print_remaining(int* letters);

int _tmain(int argc, _TCHAR* argv[])
{
	int nSum;
	int nAlphabet[ALPHABET_SIZE] = { 0 };
	char szRightWord[BUFFER_SIZE], szLeftWord[BUFFER_SIZE];
	char again ='y';
	
	while (again == 'y')
	{		
		//get words
		getline("Enter the first word:", szLeftWord, sizeof(szLeftWord));
		getline("Enter the second word:", szRightWord, sizeof(szRightWord));

		//+- letter count
		count_letters(szLeftWord, nAlphabet, COUNT_UP);
		count_letters(szRightWord, nAlphabet, COUNT_DOWN);

		//if +, left wins, if -, right wins
		nSum = sum(nAlphabet);
		print_remaining(nAlphabet);

		printf("\nSum is:%d", nSum);
		if (nSum == 0)
			printf("\nTie Game!");
		else
		if (nSum >= LEFT_SIDE)
			printf("\nLeft side Wins!");
		else
		if (nSum <= RIGHT_SIDE)
			printf("\nRight side Wins!");

		printf("\nPlay again? (y):");
		again = getc(stdin);
		fflush(stdin);
		memset(nAlphabet, 0, sizeof(nAlphabet));
	} 

	return 0;
}

int getline(char *prompt, char *buff, size_t size)
{
	char chChar, chExtra;
	//Send prompt to user
	if (prompt != NULL)
	{
		printf("%s", prompt);
		fflush(stdout);
	}
	if (fgets(buff, size, stdin) == NULL)
		return NO_INPUT;

	if (buff[strlen(buff) - 1] != '\n')
	{
		chExtra = OK;
		while (((chChar = getchar()) != '\n') && (chChar != EOF))
			chExtra = TOO_LONG;
		return (chExtra == TOO_LONG) ? TOO_LONG : OK;
	}

	
	buff[strlen(buff) - 1] = '\0';
	return OK;
}

int count_letters(char *word, int *count, int nValue)
{
	int nIndex=0;
	while (strlen(word) > nIndex)
	{
		//Cover Lower Case
		if (word[nIndex] >= 'a' && word[nIndex] <= 'z')
			count[word[nIndex] - 'a'] += nValue;
		else //Cover Upper Case
		if (word[nIndex] >= 'A' && word[nIndex] <= 'Z')
			count[word[nIndex] - 'a'] += nValue;
		
		nIndex++;
	}
	return OK;	
}

int sum(int *count)
{

	int nIndex = 0, sum = 0;
	for (nIndex == 0; nIndex < ALPHABET_SIZE; nIndex++)
		sum += count[nIndex];
	return sum;
}

int print_remaining(int* letters)
{
	int nIndex = 0;
	
	printf("Left Side has ");
	for (nIndex = 0; nIndex < ALPHABET_SIZE; nIndex++)
	{
		if (letters[nIndex] >= LEFT_SIDE)
			printf("%d %c(s) ", letters[nIndex], (nIndex + 'a'));
	}
	printf("remaining");

	printf("\nRight Side has ");
	for (nIndex = 0; nIndex < ALPHABET_SIZE; nIndex++)
	{
		if (letters[nIndex] <= RIGHT_SIDE)
			printf("%d %c(s) ", (letters[nIndex] * -1), (nIndex + 'a'));
	}
	printf("remaining");
	return 0;

}