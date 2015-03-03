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
}

void search(char c[],FILE *f)
{
  int i;
  
  if(c[0] == '"')
  {
    fprintf(f,"<TK_STRINGLITERAL, %s>\n",c); 
    return;
  }
  
  for(i=0;i<numTokens;i++)
  {
    if(strcmp(c,TokenTable.symbols[i])==0)
    {
      fprintf(f,"<%s>\n",TokenTable.tokens[i]);
      return;
    }
  }
    
  if(isalpha(c[0]) == 0)
  {
    lexicalError = true;
    printf("LEXICAL ERROR :\nInvalid character %s in line %d\n",c,line);
    return;
  }

  fprintf(f,"<TK_ID, %s>\n",c);
}

void searchNumber(char c[], FILE *f, bool floatingPoint)
{
  if(!floatingPoint)
    fprintf(f,"<TK_INTEGERLITERAL, %s>\n",c);
  else
    fprintf(f,"<TK_FLOATLITERAL, %s>\n",c);
}

void dfa()
{
  int state = start;
  bool shouldread = true;
  char str[BUFFER_LENGTH];
  char c;
  bool flag = false, lastNewline = false, error = false, lastComment = true;
  FILE *f = fopen("errors.txt","r");
  //FILE *f = fopen("input.txt","r");
  FILE *o = fopen("tokenstream.txt","w");

  while(1)
  { 
    memset(str,0,sizeof(str));
  
    if(!fgets(str,BUFFER_LENGTH,f))
      flag = true;
    
    int i=0;

    while(str[i] != '\0')
    {
      switch(state)
      {
        case start:
        
          if(shouldread)
            c = str[i];
         
          if(c == '$')
          {
            state = comment;
            break;
          }

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
          { 
            // Neither digit nor alphabet
            state = symbol;
          }
          
          if(isdigit(c)!=0)
          {
            // Is a digit
            state = number;
          }

          if(isalpha(c)!=0)
          {
            // Starts with an alphabet
            state = keyword_identifier;  
          }
          shouldread = false;
          break;


        case symbol:
           
          if(shouldread)
            c = str[i];
          if(c>32)
          {
            search(&c,o);
            shouldread = true;
            state = start;
          }
          i++; 
          lastNewline = false;
          lastComment = false;
          break;


        case keyword_identifier:
         
          i++;
          if(shouldread)
          {
            c = str[i];
            i++;
          }

          char new[MAX_IDENTIFIER_LENGTH];
          memset(new,0,MAX_IDENTIFIER_LENGTH);
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

            /* Error checking for max identifier length */
            if(j > MAX_IDENTIFIER_LENGTH)
            {
              lexicalError = true;
              printf("LEXICAL ERROR :\nIdentifier length exceeds maximum allowed length in line %d\n",line);
              break;
            }
          }

          search(new,o);
          state = start;
          shouldread = false;
          lastNewline = false;
          lastComment = false;
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
          lastComment = false;
          break;


        case newline:
            
          line++;
          
          if(!lastNewline && !lastComment)
            search("newline",o);
          
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
          lastComment = false;
          break;
        

        case number:
          
          i--;
          bool floatingPoint = false;
          char num[MAX_NUMBER_LENGTH];
          memset(num,0,MAX_NUMBER_LENGTH);
          int k=-1;
            
          while(c>=48 && c<=57)
          {
            i++;k++;
            c = str[i];

            if(isdigit(c) != 0 || c == 46)
              num[k] = c;

            if(c==46)
            {
              // Decimal Point
              i++;k++;
              c = str[i];
              if(isdigit(c) != 0 || c == 46)
                num[k] = c;
              floatingPoint = true;
            }
            
            /* Error checking for max string length */
            if(k >= MAX_NUMBER_LENGTH)
            {
              lexicalError = true;
              printf("LEXICAL ERROR :\nNumber length greater exceeds maximum allowed in line %d\n",line);
             
              // remove remaining numbers
              while(isdigit(str[i])!=0)
                i++;

              break;
            }
          }
          
          bool floaterror = false;

          /* Error checking for 2 decimal points */
          if(floatingPoint)
          {
            int decimalCount=0;
            int iter;
            
            for(iter = 0; iter < k; iter++)
            {
              if(num[iter] == '.')
                decimalCount++;
            }
            
            if(decimalCount > 1)
            {
              lexicalError = true;
              printf("LEXICAL ERROR :\nMore than 1 decimal points in the entered float literal in line %d\n",line);
              floaterror = true;
            }
          }
          
          bool illegalnumber = false;

          /* Error checking for illegal numbers like 12ab */
          if(isalpha(c))
          {
            lexicalError = true;
            printf("LEXICAL ERROR :\nIllegal Number in line %d\n",line);
            illegalnumber = true;
          }

          if(!floaterror && !illegalnumber)
            searchNumber(num,o,floatingPoint);
          
          state = start;
          shouldread = false;
          lastNewline = false;
          lastComment = false;
          break;


        case string_literal:
          
          memset(new,0,MAX_STRING_LENGTH);
          j=1;
          new[0] = '"';
          i++;

          while(str[i] != '"')
          {
            new[j] = str[i];
            i++;j++;
          
            /* Error checking for matching quotes */
            if(str[i] == '\0')
            { 
              lexicalError = true;
              printf("LEXICAL ERROR :\nMatching quotes not present in line %d\n", line); 
              error = true;
              break;
            }

            /* Error checking for max string length */
            if(j > MAX_STRING_LENGTH)
            {
              bool quoteserror = false;
              while(str[i] != '"')
              {
                if(str[i] == '\0')
                {
                  lexicalError = true;
                  printf("LEXICAL ERROR :\nMatching quotes not present in line %d\n", line); 
                  quoteserror = true;
                  line++;
                  break;
                }
                i++;
              }
              if(!quoteserror)
              {
                lexicalError = true;
                printf("LEXICAL ERROR :\nString length exceeds maximum allowed length in line %d\n",line);
              }
              break;
            }
          }
          
          if(!error)
          {
            new[j] = c;
            search(new,o);
          }
          else
          {
            state = start;
            shouldread = true;
            lastNewline = false;
            lastComment = false;
            error = false;
            break;
          }
 
          i++;
          error = false;
          state = start;
          shouldread = true;
          lastNewline = false;
          lastComment = false;
          break;

        case comment:
          
          while(str[i] != '\0')
            i++;
            
          if(str[i] == 10)
            line++;
          line++;
          state = start;
          shouldread = true;
          lastNewline = false;
          lastComment = true;
          break;

      }
    }
    if(flag)
      break;
  }
  
  fcloseall();
  if(lexicalError)
  {
    FILE *o = fopen("output.txt","w");
    fcloseall();
  }
}

int main()
{
  readTokens();
  dfa();
  return 0;  
}
