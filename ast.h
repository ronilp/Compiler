#define ASTOperators 15
#define ASTOthers 15

char astops[120][20];

char astothers[120][20];

struct tree *traverseAST(struct tree *node);

extern int searchops(char c[]);

extern int searchothers(char c[]);

extern int hashOperators(char c[]);

extern void readInput();
