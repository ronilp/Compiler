// Team number 38
// MOHIT GUPTA (2012A7PS021P)
// RONIL PANCHOLIA (2012C6PS629P)


#define ASTOperators 15
#define ASTOthers 15

char astops[120][20];

char astothers[120][20];

struct tree *traverseAST(struct tree *node);

extern int searchops(char c[]);

extern int searchothers(char c[]);

extern int hashOperators(char c[]);

extern void readInput();
