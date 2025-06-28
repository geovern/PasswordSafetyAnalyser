// A program that checks password strength,
// provides password improvement advice
// and simulates bruteforce time.
// HaveIBeenPwned integration via shell 
//
#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <cmath>
#include <cstdlib> //ASCII library
#include <unordered_map> //why??
#include <utility>
using namespace std;

// compile with:
// g++ pwrdSec.cpp -o xpwrdSec -std=c++20 -lm

void metrics (char input[]) {
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
			//could just make it just else, since all other types are taken into account
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
	

	if (strength == 5) { //this applies only for bruteforce?
		printf("Strength: %d, \x1b[32mStrong\x1b[0m\n", strength);
	} else if (strength == 3 || strength == 4) {
		printf("Strength: %d, \x1b[33mModerate\x1b[0m\n", strength);
	} else {
		printf("Strength: %d, \x1b[1;31mWeak\x1b[0m\n", strength);
	}

	if(strlen(input) <= 8)
		printf("\x1b[1;31mPlease make a longer password to increase safety.\x1b[0m\n");
	if (lowerC == 0)
		printf("\x1b[1;31mPlease add lower case characters to increase password safety.\x1b[0m\n");
	if (highC == 0) 
		printf("\x1b[1;31mPlease add high case characters to increase password safety.\x1b[0m\n");
	if (num == 0) 
		printf("\x1b[1;31mPlease add numbers to increase password safety.\x1b[0m\n");
	if (specialC == 0) 
		printf("\x1b[1;31mPlease add special characters to increase password safety.\x1b[0m\n");
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

pair<double, double> entropy(const char* input) { // calculates both shannon and password entropies
	string s(input);
	pair<double, double> p;
	unordered_map<char, int> freq;

	for (char c : s)
        	freq[c]++;

	double sEntropy = 0.0;//shannon
	double pEntropy = 0.0;//password
	int R = 0; //unique characters
	int len = s.size();
	for (const auto& p : freq) {
		double f = (double)p.second / len;
		R++;
		sEntropy -= f * (log2(f));
	}
	
	pEntropy = log2(R) * len;
	p.first = sEntropy * len;
	p.second = pEntropy;
	return p;
}

int main() {

	// TO DO
	// 
	// DONE: get password DONE 
	// DONE: function that checks strength based on length, letter case, numbers, symbols
	// 
	// STUDY/DONE: Check for common words with File I/O, (make it work for substrings also?)
	// STUDY/DONE: Shannon Entropy (hash map, check out code review)
	// IN PROCESS: Colored Output
	// Estimated Brute-force time (with John the ripper)
	// More special characters (to be more accurate with the estimation)
	// HaveIBeenPwned API 
	// Cmake file??
	// DONE: Password Entropy: E = log2(R^L)
	
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

		pair<double, double> ent = entropy(input);
		printf("Shannon Entropy: %.1f bits\n", ent.first); //colorize ??
		//password entropy and compare it to research suggested bit values
		printf("Password Entropy: %.1f bits\n", ent.second);
		metrics(input);
		
		if (isCommonPassword(input, "Pwdb_top-10000000.txt")) {
	      		printf("This password is too common. It is weak against Dictionary attacks. Please choose another.\n");
    		} else {
        		printf("This password is not in the common password list.\n");
    		}
	}
		
	return 0;
}


