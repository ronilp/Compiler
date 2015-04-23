// Team number 38
// MOHIT GUPTA (2012A7PS021P)
// RONIL PANCHOLIA (2012C6PS629P)

#include <stdbool.h>

struct st
{
  int scope;
  char *data;
  char *dataType;
  int declared;
};

int STEntries = 0;

struct st SymbolTable[128];

extern struct st *searchInSymbolTable(char data[], int scope);

extern void insertInSymbolTable(char *data, char *dataType, int scope, int line);

extern bool verifyInSymbolTable(char *data, int scope, int line);

extern int calculateScope(int index);

extern void deleteEntries(int scope);

extern void printSymbolTable();

extern void operators(char buffer[][100],int bufferindex);

extern char *getType(char token[], int scope);

extern char *tokenType(char token[]);