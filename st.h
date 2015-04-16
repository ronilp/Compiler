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

extern void printSymbolTable();
