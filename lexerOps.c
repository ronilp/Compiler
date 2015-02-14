#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "lexer.h"

void readTokens()
{
  int i=0; 
  FILE *f = fopen("tokenList.txt","r");
  int n = numTokens;
  while(n > 0)
  {
    fscanf(f,"%s %s",TokenTable.symbols[i],TokenTable.tokens[i]);
    i++;
    n--;
  }
  fclose(f);

  //for(i=0;i<numTokens;i++)
    //printf("%s   %s\n",TokenTable.symbols[i],TokenTable.tokens[i]);
  printf("Token reading complete...\n");
}

void search(char c[])
{
  bool found = false;
  int i;
  for(i=0;i<numTokens;i++)
  {
    if(strcmp(c,TokenTable.symbols[i])==0)
    {
      found = true;
      printf("%s %s\n",TokenTable.tokens[i],c);
      break;
    }
  }
  if(!found)
    printf("identifier %s\n",c);
}

void dfa()
{
  int state = start;
  bool shouldread = true;
  int i=0;

  char str[20];
  char c;
  FILE *f = fopen("input.txt","r");
  fgets(str,20,f);
  while(str[i] != '\0')
  {
    switch(state)
    {
      case start:
        
          //printf("\nstart\n");
          if(shouldread)
            c = str[i];
          
          if(c==32)
          {
            state = space;
            shouldread = true;
            i++;
            break;
          }

          if(isdigit(c)==0 && isalpha(c)==0)
          { // Neither digit nor alphabet
            state = symbol;
            shouldread = false;
            break;
          }
          
          if(isalpha(c)!=0)
          { // Starts with an alphabet
            state = keyword_identifier;  
            shouldread = false;
          }
          break;

      case symbol:
         
          if(shouldread)
            c = str[i];
          if(c>32)
          {
            search(&c);
            shouldread = true;
            state = start;
          }
          i++; 
          break;

      case keyword_identifier:
       
          i++;
          if(shouldread)
          {
            c = str[i];
            i++;
          }
          
          //printf("\nc = %s\n", &c);
          char new[20];
          memset(new,0,20);
          int j=0;

          while((isalpha(c)!=0 || isdigit(c)!=0))// && str[i] != '\0')
          { // c is not a symbol
            new[j] = c;
            c = str[i]; 
            if(isdigit(c)!=0 || isalpha(c)!=0)
            { // c is not a symbol
              i++;j++;
            }
          }
          search(new);
          state = start;
          shouldread = false;
          break;

      case space:
        
          //printf("space state i = %c\n",str[i]);
          i--;
          while(c<=32)
          {
            i++;
            c = str[i];
          }
          //printf("\nc = %c i = %c\n",c,str[i]);
          state = start;
          shouldread = false;
          break;
    }
  }
}

int main()
{
  readTokens();
  dfa();
  return 0;  
}
