// A program that analyses password security,
// provides password improvement advice
// and estimates bruteforce time.
//
#include <cstdio>
#include <cstring>
#include <utility>
#include <string>
#include "password_utils.h"
using namespace std;

// compile with:
// g++ pwrdSec.cpp password_utils.cpp -o xpwrdSec -std=c++20 -lm

int main() {

	char input[256];
	int overall;
	
	while (1) {
		
		overall = 0;
		
		printf("\nInput Password: ");
		
		//scanf("%s", input); //fgets is safer
		fgets(input, sizeof(input), stdin);

		if (strcmp(input, "\n") == 0) {
			fprintf(stderr, "Invalid Password Input.\n");
			continue;
		}
		if (strcmp(input, "exit\n") == 0) {
			break;
		}
		string s(input);
		if (s.find(" ") != s.npos) {
			fprintf(stderr, "Password cannot contain spaces.\n");
			continue;
		}

		stripNewline(input);

		int range = metrics(input);

		pair<double, double> ent = entropy(input, range);
	
		printShannon(ent.first);
		printPassEnt(ent.second);
		estimateBFT(input, range);
		printCommonPW(input);
	}
		
	return 0;
}


