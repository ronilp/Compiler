#include<stdio.h>
#include<string.h>
#include "symbolTable.h"

int STindex = 0;

void STinsert(char *id, char *type, int scope, int line)
{
  if(STsearch(id,scope) == -1)
  { /* search unsuccessful */
    strcpy(SymbolTable[STindex].data,id);
    strcpy(SymbolTable[STindex].dataType,type);
    SymbolTable[STindex].scope = scope;
    SymbolTable[STindex].declared = line;
    STindex++;
  }
  else
  { /* search successful */
    
  }
}

int STsearch(char id[],int scope)
{
  int key;
  key = SThash(id);

  /* Case : Already present in symbol table with same scope */
  if(strcmp(SymbolTable[key].data,id) == 0)
  {
    if(SymbolTable[key].scope == scope)
    {
      int i=0;
      while(SymbolTable[key].referenced[i] == 0)
        i++;
        
      SymbolTable[key].refrenced[i] = scope;  
    }
    else
    {
        
    }
  }
  return 1;
}

int SThash(char id[])
{
  int i,key;
  for(i=0; i<strlen(id); i++)
    key += id[i];

  return key%127;
}

int main()
{

  return 0;  
}
