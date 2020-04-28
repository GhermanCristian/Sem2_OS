// Write a program that receives multiple words as arguments in the command line. The words contain letters and digits. Determine and display:
//
//     the lower case letter with the highest frequency;
//     the digit with the lowest frequency
//     the smallest digit 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isLowercase(char x){
	return (x >= 'a' && x <= 'z');
}

int isDigit(char x){
	return (x >= '0' && x <= '9');
}

int main(int argc, char **argv){
	int *digitFreq;
	int *letterFreq;
	char maxDigit = '0';
	int i, j; // iterators
	int length; // length of each string
	int highestFreq = -1;
        char highestFreqValue = 'a'; // for letters, 'a' by default
	char ch; // current character
	int lowestFreq = 1000, lowestFreqValue = 0; // for digits

	if (argc == 1){
		printf("No arguments were passed");
		return 0;
	}

	// allocate memory
	digitFreq = (int *)malloc(10 * sizeof(int));
	letterFreq = (int *)malloc(26 * sizeof(int));

	// initialise the arrays with 0 (bc initially no entities have been read)
	for (i = 0; i < 10; i++){
		digitFreq[i] = 0;
	}
	for (i = 0; i < 26; i++){
		letterFreq[i] = 0;
	}

	// traverse the strings passed as parameters
	for (i = 1; i < argc; i++){
		length = strlen(argv[i]);
		for (j = 0; j < length; j++){
			ch = argv[i][j];

			if (isLowercase(ch) == 1){
				letterFreq[ch - 'a'] ++;
			}

			else if (isDigit(ch) == 1){
				digitFreq[ch - '0'] ++;

				// check for the highest digit
				if (ch > maxDigit){
					maxDigit = ch;
				}
			}
		}
	}

	// check the letter with the highest frequency
	for (i = 0; i < 26; i++){
		if (letterFreq[i] > highestFreq){
			highestFreqValue = i + 'a';
			highestFreq = letterFreq[i];
		}
	}

	// check the digit with the lowest frequency (and which does appear)
	for (i = 0; i < 10; i++){
		if (digitFreq[i] > 0 && digitFreq[i] < lowestFreq){
			lowestFreqValue = i;
			lowestFreq = digitFreq[i];
		}
	}

	printf("The lowercase letter with the highest frequency is: %c\n", highestFreqValue);
	printf("The digit with the min nr of appearances (and which does appear) is: %d\n", lowestFreqValue);
	printf("The maximum digit is: %c\n", maxDigit);

	// de-allocate the memory
	free (digitFreq);
	free (letterFreq);

	return 0;
}
