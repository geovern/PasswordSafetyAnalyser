#include <cstdio>
#include <string>
#include <cstring>
#include <cmath>
#include <cstdlib> //ASCII library
#include <unordered_map> //why??
#include <utility>
#include "password_utils.h"
using namespace std;

int metrics (char input[]) {
	int strength = 0;
	int lowerC = 0;
	int highC = 0;
	int num = 0;
	int specialC = 0;

	int range = 0; //for password entropy calculation

	if (strlen(input) > 8) 
		strength++;
	for (int i = 0; i < strlen(input); ++i) {
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
		} else {
			//could just make it just else, since all other types are taken into account
			//has "!#$%&*?@
			specialC++;
		}
	}
	if (lowerC > 0) {
		range += 26;
		strength++;
	}
	if (highC > 0) {
		range += 26;
		strength++;
	}
	if (num > 0) {
		range += 10;
		strength++;
	}
	if (specialC > 0) {
		range += 32;
		strength++;
	}
	

	if (strength == 5) { //this applies only for bruteforce?
		printf("Strength: %d, \x1b[32mStrong\x1b[0m\n", strength);
	} else if (strength == 3 || strength == 4) {
		printf("Strength: %d, \x1b[33mModerate\x1b[0m\n", strength);
	} else {
		printf("Strength: %d, \x1b[1;31mWeak\x1b[0m\n", strength);
	}

	if(strlen(input) <= 8)
		printf("\x1b[1;31m > \x1b[0mPlease make a longer password to increase safety.\n");
	if (lowerC == 0)
		printf("\x1b[1;31m > \x1b[0mPlease add lower case characters to increase password safety.\n");
	if (highC == 0) 
		printf("\x1b[1;31m > \x1b[0mPlease add high case characters to increase password safety.\n");
	if (num == 0) 
		printf("\x1b[1;31m > \x1b[0mPlease add numbers to increase password safety.\n");
	if (specialC == 0) 
		printf("\x1b[1;31m > \x1b[0mPlease add special characters to increase password safety.\n");
	return range;
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

pair<double, double> entropy(const char* input, int range) { // calculates both shannon and password entropies
	string s(input);
	pair<double, double> p;
	unordered_map<char, int> freq;

	for (char c : s)
        	freq[c]++;

	double sEntropy = 0.0;//shannon
	double pEntropy = 0.0;//password
	int R = range; // pool of unique characters
	int len = s.size();
	for (const auto& p : freq) {
		double f = (double)p.second / len;
		sEntropy -= f * (log2(f));
	}
	
	pEntropy = log2(R) * len;
	p.first = sEntropy * len;
	p.second = pEntropy;
	return p;
}

void printShannon(double entropy) {
	if (entropy >= 49.0) {
		printf("Shannon Entropy: %.1f bits, \x1b[32mVery strong\x1b[0m\n", entropy); //who nose
	} else if (entropy >= 29.0) {
		printf("Shannon Entropy: %.1f bits, \x1b[33mModerately strong\x1b[0m\n", entropy); //RFC 4086, "Randomness Requirements for Security"
	} else {
		printf("Shannon Entropy: %.1f bits, \x1b[1;31mWeak\x1b[0m\n", entropy);
	}
}

void printPassEnt(double entropy) {
	//password entropy and compare it to research suggested bit values
	if (entropy >= 100.0) {
		printf("Password Entropy: %.1f bits, \x1b[32mVery strong\x1b[0m\n", entropy); //Proton
	} else if (entropy >= 80) {
		printf("Password Entropy: %.1f bits, \x1b[33mModerately strong\x1b[0m\n", entropy);
	} else {
		printf("Password Entropy: %.1f bits, \x1b[1;31mWeak\x1b[0m\n", entropy);
	}
}

void estimateBFT(const char* input, int range) { // estimate brute force time
	int length = strlen(input);
	// Use logarithms to prevent overflow:
	//long double logCombinations = length * log10(range);
	//long double totalGuesses = pow(10, log_combinations);
	long double totalGuesses = pow(range, length);
	double guessesPerSec = 1e9; // 1B guesses/sec
	long double seconds = totalGuesses / guessesPerSec;

	printf("Estimated brute-force time(1B g/s): ");

	if (seconds < 1) printf("Instantly crackable\n");
	else if (seconds < 60) printf("%.2Lf seconds\n", seconds);
	else if (seconds < 3600) printf("%.2Lf minutes\n", seconds / 60);
	else if (seconds < 86400) printf("%.2Lf hours\n", seconds / 3600);
	else if (seconds < 31536000) printf("%.2Lf days\n", seconds / 86400);
	else if (seconds < 3.1536e10) printf("%.2Lf years\n", seconds / 31536000);
	else if (seconds < 3.1536e13) printf("%.2Lf millennia\n", seconds / 3.1536e10);
	else if (seconds < 3.1536e16) printf("%.2Lf Million years\n", seconds / 3.1536e13);
	else if (seconds < 3.1536e19) printf("%.2Lf Billion years\n", seconds / 3.1536e16);
	else if (seconds < 3.1536e22) printf("%.2Lf Trillion years\n", seconds / 3.1536e19);
	else if (seconds < 3.1536e25) printf("%.2Lf Quadrillion years\n", seconds / 3.1536e22);
	else printf("%.2Lf Quintillion years\n", seconds / 3.1536e25);
}

void printCommonPW(const char* input) {
	if (isCommonPassword(input, "Pwdb_top-10000000.txt")) {
		printf("\x1b[1;31m > \x1b[0mThis password is too common. It is weak against Dictionary attacks. Please choose another.\n");
	} else {
        	printf("\x1b[32m > \x1b[0mThis password is not in the common password list.\n");
	}
}


