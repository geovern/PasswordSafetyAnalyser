#ifndef PASSWORD_UTILS_HPP
#define PASSWORD_UTILS_HPP

#include <utility>
using namespace std;

int metrics (char input[]);
void stripNewline(char *str);
int isCommonPassword(const char *password, const char *filename);
pair<double, double> entropy(const char* input, int range);
void printShannon(double entropy);
void printPassEnt(double entropy);
void estimateBFT(const char* input, int range);
void printCommonPW(const char* input);

#endif
