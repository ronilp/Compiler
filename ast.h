#define ASTOperators 15
#define ASTOthers 15

char astops[120][20];

char astothers[120][20];

struct tree *traverseAST(struct tree *node);

int searchops(char c[]);

int searchothers(char c[]);

int hashOperators(char c[]);

void readInput();
