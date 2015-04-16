#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"st.h"

struct st *searchInSymbolTable(char data[], int scope)
{
  struct st *temp = NULL;
  int i;
  for(i=0; i<STEntries; i++)
  {
    if(strcmp(data,SymbolTable[i].data)==0)
    {
      if(scope == SymbolTable[i].scope)
        return &SymbolTable[i];
    }
  }
  return temp;
}

void insertInSymbolTable(char *data, char *dataType, int scope, int line)
{
  struct st *temp;
  temp = searchInSymbolTable(data,scope);
  if(temp == NULL)
  {
    strcpy(SymbolTable[STEntries].data,data);
    strcpy(SymbolTable[STEntries].dataType,dataType);
    SymbolTable[STEntries].scope = scope;
    SymbolTable[STEntries].declared = line;
    STEntries++;
  }
}

void printSymbolTable()
{
  int i;
  for(i=0; i<STEntries; i++)  
    printf("%s %s %d %d\n",SymbolTable[i].data,SymbolTable[i].dataType,SymbolTable[i].scope,SymbolTable[i].declared);
}

void fillSymbolTable(struct tree *root)
{
    
}

void SymbolTable()
{
  int i=0;
  for(i=0; i<128; i++)
  {
    SymbolTable[i].data = malloc(sizeof(char)*100);
    SymbolTable[i].dataType = malloc(sizeof(char)*100);
  }

  /* Testing ST
  insertInSymbolTable("hello","char",1,1);
  insertInSymbolTable("meow","char",2,1);
  insertInSymbolTable("meow","char",1,1);
  insertInSymbolTable("meow","char",1,1);
  printSymbolTable();
  */
  
  fillSymbolTable(root);
}
