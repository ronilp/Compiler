struct st
{
  int scope;
  char *data;
  char *dataType;
  int declared;
  int referenced[20];
  struct st *next;
};

struct st SymbolTable[128];
