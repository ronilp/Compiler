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
  int i;
  
  if(c[0] == '"')
  {
    printf("<TK_STRINGLITERAL, %s>\n",c); 
    return;
  }
  
  for(i=0;i<numTokens;i++)
  {
    if(strcmp(c,TokenTable.symbols[i])==0)
    {
      printf("<%s>\n",TokenTable.tokens[i]);
      return;
    }
  }
  
  printf("<TK_ID, %s>\n",c);
}

void dfa()
{
  int state = start;
  bool shouldread = true;
  char str[1000];
  char c;
  bool flag = false,lastNewline = false,error = false;
  FILE *f = fopen("input.txt","r");
  while(1)
  { 
    memset(str,0,sizeof(str));
    if(!fgets(str,1000,f))
      flag = true;
    //printf("str = %s\n",str);
    int i=0;

    while(str[i] != '\0')
    {
      //printf("state = %d\n",state)
      switch(state)
      {
        case start:
        
          if(shouldread)
            c = str[i];
         
          if(c == '"')
          {
            state = string_literal;
            shouldread = true;
            break;
          }


          if(c<=32)
          { 
            // space or newline
            if(c==10)
              state = newline;
            else
              state = space;
            shouldread = true;
            i++;
            break;
          }

          if(isdigit(c)==0 && isalpha(c)==0)
          { // Neither digit nor alphabet
            state = symbol;
          }
          
          if(isdigit(c)!=0)
          {// Is a digit
            state = number;
          }

          if(isalpha(c)!=0)
          { // Starts with an alphabet
            state = keyword_identifier;  
          }
          shouldread = false;
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
          lastNewline = false;
          break;


        case keyword_identifier:
         
          i++;
          if(shouldread)
          {
            c = str[i];
            i++;
          }
          
          char new[200];
          memset(new,0,200);
          int j=0;

          while((isalpha(c)!=0 || isdigit(c)!=0))
          { 
            // c is not a symbol
            new[j] = c;
            c = str[i]; 
            
            if(isdigit(c)!=0 || isalpha(c)!=0)
            {
            // c is not a symbol
              i++;j++;
            }
          }
          search(new);
          state = start;
          shouldread = false;
          lastNewline = false;
          break;


        case space:
          
          i--;
          while(c<=32 && c!=10 && str[i] !='\0')
          {
            i++;
            c = str[i];
          }
          if(c==10)
          {
            state = newline;
            i--;
          }
          state = start;
          shouldread = false;
          lastNewline = false;
          break;


        case newline:
        
          if(!lastNewline)
            search("newline");
          c = str[i];
          
          while(c<=32 && str[i]!='\0')
          {
            i++;
            c = str[i];
          }

          if(str[i]=='\0')
            lastNewline = true;
          else
            lastNewline = false;
          
          state = start;
          shouldread = true;
          break;
        

        case number:
          
          i--;
          bool floatingPoint = false;
          
          while(c>=48 && c<=57)
          {
            i++;
            c = str[i];
            if(c==46)
            {
              // Decimal Point
              i++;
              c = str[i];
              floatingPoint = true;
            }
          }

          if(floatingPoint)
            search("floatingPoint");
          else
            search("integer");
          
          state = start;
          shouldread = false;
          lastNewline = false;
          
          break;


        case string_literal:
          
          memset(new,0,200);
          j=1;
          new[0] = '"';
          i++;

          while(str[i] != '"')
          {
            new[j] = str[i];
            i++;j++;
          
            if(str[i] == '\0')
            { 
              printf("string error\n"); 
              error = true;
              break;
            }
          }
          
          if(!error)
          {
            new[j] = c;
            search(new);
          }
          else
          {
            state = start;
            shouldread = true;
            lastNewline = false;
            error = false;
            break;
          }
 
          i++;
          error = false;
          state = start;
          shouldread = true;
          lastNewline = false;
          break;

        case comment:
          lastNewline = false;
          break;

      }
    }
    if(flag)
      break;
  }
}

int main()
{
  readTokens();
  dfa();
  return 0;  
}
