// A program that checks password strength,
// provides password improvement advice
// and simulates bruteforce time.
// HaveIBeenPwned integration via shell 
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h> //ASCII library

int metrics (char input[]) {
	int strength = 0;
	int lowerC = 0;
	int highC = 0;
	int num = 0;
	int specialC = 0;

	if (strlen(input) >= 8) 
		strength++;
	for (int i = 0; i <= strlen(input); ++i) {
		int charAscii = (int)input[i];
		if (charAscii >= 97 && charAscii <= 122) {
			//lower case
			lowerC++;
		} else if(charAscii >= 65 && charAscii <= 90) {
			//high case
			highC++;
		} else if(charAscii >= 48 && charAscii <= 57) {
			//number
			num++;
		} else if(charAscii == 33 || charAscii == 35 || charAscii == 36 ||
	    	charAscii == 37 || charAscii == 38 || charAscii == 42 || charAscii == 63 || charAscii == 64) {
			//has "!#$%&*?@
			specialC++;
		}
	}
	if (lowerC > 0) 
		strength++;
	if (highC > 0)
		strength++;
	if (num > 0) 
		strength++;
	if (specialC > 0)
		strength++;
	printf("strength: %d\n", strength);
	return strength;
}

int main() {

	// TO DO
	// get password
	// function that checks strength based on length, letter case, numbers, symbols
	// Check for common words with File I/O, (make it work for substrings also?)
	// Shannon Entropy
	// Colored Output
	// Estimated Brute-force time with Hydra or John the ripper
	// HaveIBeenPwned API 
	//
	
	char input[128];
	while (1) {
		scanf("%s", input);
		printf("Input: %s\n", input);
		metrics(input);
	}
	return 0;
}
