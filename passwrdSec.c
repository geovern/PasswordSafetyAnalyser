// A program that checks password strength,
// provides password improvement advice
// and simulates bruteforce time.
// HaveIBeenPwned integration via shell 
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h> //ASCII library
#include <math.h> //log function
//#include "uthash.h" //hashmap library


int metrics (char input[]) {
	int strength = 0;
	int lowerC = 0;
	int highC = 0;
	int num = 0;
	int specialC = 0;

	if (strlen(input) > 8) 
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
	
	if(strlen(input) <= 8)
		printf("Please make a longer password to increase safety.\n");
	if (lowerC == 0)
		printf("Please add lower case characters to increase password safety.\n");
	if (highC == 0) 
		printf("Please add high case characters to increase password safety.\n");
	if (num == 0) 
		printf("Please add numbers to increase password safety.\n");
	if (specialC == 0) 
		printf("Please add special characters to increase password safety.\n");

	return strength;
}

// Function to trim newline characters from file lines
void stripNewline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len-1] == '\n') {
        str[len-1] = '\0';
    }
}

// Returns 1 if password is found in common list, 0 otherwise
int isCommonPassword(const char *password, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening password database.");
        return 0;
    }

    char line[256];  // Adjust size if needed
    while (fgets(line, sizeof(line), file)) {
        stripNewline(line);
        if (strcmp(password, line) == 0) {
            fclose(file);
            return 1;  // Match found
        }
    }

    fclose(file);
    return 0;  // No match
}

int main() {

	// TO DO
	// 
	// DONE: get password DONE 
	// DONE: function that checks strength based on length, letter case, numbers, symbols
	// 
	// STUDY/DONE: Check for common words with File I/O, (make it work for substrings also?)
	// Shannon Entropy (hash map, check out code review)
	// Colored Output
	// Estimated Brute-force time (with John the ripper)
	// More special characters (to be more accurate with the estimation)
	// HaveIBeenPwned API 
	//
	
	char input[256];
	
	while (1) {
		
		printf("\n");

		//scanf("%s", input); fgets is safer
		fgets(input, sizeof(input), stdin);
		
		if (strcmp(input, "\n") == 0) {
			fprintf(stderr, "Invalid Password Input.\n");
			continue;
		}

		stripNewline(input);
		printf("Input: %s\n", input);
		metrics(input);
		
		if (isCommonPassword(input, "Pwdb_top-10000000.txt")) {
	      		printf("This password is too common. It is weak against Dictionary attacks. Please choose another.\n");
    		} else {
        		printf("This password is not in the common password list.\n");
    		}
	}
		
	return 0;
}


