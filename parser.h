#include "stack.h"
#define numTerminals 42
#define numNonTerminals 47
#define numRules 91
#define MAX_TERMINAL_SIZE 100
#define MAX_NONTERMINAL_SIZE 100
#define MAX_RULE_LENGTH 200
#define MAX_NUM_TOKENS 1000
#define MAX_TOKEN_LENGTH 100

char terminal[numTerminals][MAX_TERMINAL_SIZE];

char nonterminal[numNonTerminals][MAX_NONTERMINAL_SIZE];

int parseTable[numNonTerminals][numTerminals];

char Grammar[numRules][MAX_RULE_LENGTH];

char TokenStream[MAX_NUM_TOKENS][MAX_TOKEN_LENGTH];

extern void initialize();

extern void parse();

extern void parser();

extern int terminalPosition(char *str);

extern int nonterminalPosition(char *str);

extern int hashNonTerminals(char str[]);

//int tokenCount = 0;

//int tokenIndex = 0;
