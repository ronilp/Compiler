#include "stack.h"
#define numTerminals 5
#define numNonTerminals 5
#define numRules 8
#define MAX_TERMINAL_SIZE 100
#define MAX_NONTERMINAL_SIZE 100
#define MAX_RULE_LENGTH 100
#define MAX_NUM_TOKENS 1000
#define MAX_TOKEN_LENGTH 100

char terminal[numTerminals][MAX_TERMINAL_SIZE];

char nonterminal[numNonTerminals][MAX_NONTERMINAL_SIZE];

int parseTable[numNonTerminals][numTerminals];

char Grammar[numRules][MAX_RULE_LENGTH];

char TokenStream[MAX_NUM_TOKENS][MAX_TOKEN_LENGTH];

extern void initialize();

extern void parse();

extern int terminalPosition(char *str);

extern int nonterminalPosition(char *str);

int numTokens = 0;

int tokenIndex = 0;
