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

  for(i=0;i<numTokens;i++)
    printf("%s   %s\n",TokenTable.symbols[i],TokenTable.tokens[i]);
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
  scanf("%s",str);

  while(str[i] != '\0')
  {
    switch(state)
    {
      case start:
        
          if(shouldread)
            c = str[i];
          
          if(isdigit(c)==0 && isalpha(c)==0)
          { // Neither digit nor alphabet
            state = symbol;
            shouldread = false;
          }
          
          if(isalpha(c)!=0)
          { // Starts with an alphabet
            state = keyword_identifier;  
            shouldread = false;
          }
          
          i++;
          break;

      case symbol:
          
          if(shouldread)
            c = str[i];
          
          search(&c);
          shouldread = true;
          state = start;
          
          break;

      case keyword_identifier:
        
          if(shouldread)
            c = str[i];
          
          char new[20];
          int j=0;
          
          while((isalpha(c)!=0 || isdigit(c)!=0) && str[i] != '\0')
          { // Either digit or alphabet
            if(shouldread)
              c = str[i];
            new[j] = c;
            i++;j++;
            shouldread = true;
            //c = str[i];
          }
          
          search(new);
          state = start;
          shouldread = false;
          
          i++;
          break;

      case trap:
        
          printf("trap state\n");
          
          i++;
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
