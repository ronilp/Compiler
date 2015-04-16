// Team number 38
// MOHIT GUPTA (2012A7PS021P)

// RONIL PANCHOLIA (2012C6PS629P)


#include "stack.h"
#include "n-tree.h"
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

char auxTokenStream[MAX_NUM_TOKENS][MAX_TOKEN_LENGTH];

extern void initialize();

extern void parse();

extern void parser();

extern int terminalPosition(char *str);

int hashNonTerminals(char str[]);

int hashTerminals(char str[]);

extern int nonterminalPosition(char *str);

char **split(char *a_str, const char a_delim);

struct tree *root;

// Hashing - Mohit -- DONE
// < > handling -- DONE
// <TK_ID,abc> handling  -- DONE
// lexer symbol table
// parser symbol table
// parse tree
