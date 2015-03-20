#define ASTOperators 15
#define ASTOthers 15

char astops[119][20];

char astothers[119][20];

struct tree *traverseAST(struct tree *node);

int searchops(char c[]);

int searchothers(char c[]);

int hashOperators(char c[]);

void readInput();
