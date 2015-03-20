#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "lexer.h"

int line = 1;

bool lexicalError = false;

FILE *faux;

void readTokens()
{
  int i=0; 
  FILE *f = fopen("tokenList.txt","r");
  int n = numTokens;
  char sym[MAX_IDENTIFIER_LENGTH];
  char tok[MAX_IDENTIFIER_LENGTH];
  
  while(n > 0)
  {
    fscanf(f,"%s %s",sym,tok);
    int key;
    key = hash(sym);
    
    strcpy(TokenTable.symbols[key],sym);
    strcpy(TokenTable.tokens[key],tok);
    
    i++;
    n--;
  }
  
  fclose(f);
}

void searchToken(char c[],FILE *f)
{
  int i;
  
  if(c[0] == '"')
  {
    fprintf(f,"TK_STRINGLITERAL,%s\n",c); 
    fprintf(faux,"%s\n",c);
    return;
  }

  int key;
  key = hash(c);

  if(strcmp(c,TokenTable.symbols[key])==0)
  {
    fprintf(f,"%s\n",TokenTable.tokens[key]);
    return;
  }
  
  if(isalpha(c[0]) == 0)
  {
    lexicalError = true;
    printf("LEXICAL ERROR :\nInvalid character %s in line %d\n",c,line);
    return;
  }

  fprintf(f,"TK_ID,%s,%d\n",c,line);
  fprintf(faux,"%s\n",c);
}

void searchNumber(char c[], FILE *f, bool floatingPoint)
{
  if(!floatingPoint)
  {
    fprintf(f,"TK_INTEGERLITERAL,%s\n",c);
    fprintf(faux,"%s\n",c);
  }
  else
  {
    fprintf(f,"FLOATLITERAL,%s\n",c);
    fprintf(faux,"%s",c);
  }
}

int hash(char c[])
{
  int i,sum=0;
  for(i=0; i<strlen(c); i++)
  {
    sum += (i+1)*c[i];
  }
  return sum % 511;
}

void dfa()
{
  int state = START;
  bool shouldread = true;
  char str[BUFFER_LENGTH];
  char c;
  bool flag = false, lastNewline = false, error = false, lastComment = true;
  FILE *f = fopen("2.txt","r");
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
        case START:
        
          if(shouldread)
            c = str[i];
         
          if(c == '$')
          {
            state = COMMENT;
            break;
          }

          if(c == '"')
          {
            state = STRING_LITERAL;
            shouldread = true;
            break;
          }

          if(c<=32)
          { 
            // space or newline
            if(c==10)
              state = NEWLINE;
            else
              state = SPACE;
            shouldread = true;
            i++;
            break;
          }

          if(isdigit(c)==0 && isalpha(c)==0)
          { 
            // Neither digit nor alphabet
            state = SYMBOL;
          }
          
          if(isdigit(c)!=0)
          {
            // Is a digit
            state = NUMBER;
          }

          if(isalpha(c)!=0)
          {
            // Starts with an alphabet
            state = KEYWORD_IDENTIFIER;  
          }
          shouldread = false;
          break;


        case SYMBOL:
           
          if(shouldread)
            c = str[i];
          if(c>32)
          {
            searchToken(&c,o);
            shouldread = true;
            state = START;
          }
          i++; 
          lastNewline = false;
          lastComment = false;
          break;


        case KEYWORD_IDENTIFIER:
         
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

          searchToken(new,o);
          state = START;
          shouldread = false;
          lastNewline = false;
          lastComment = false;
          break;


        case SPACE:
          
          i--;
          while(c<=32 && c!=10 && str[i] !='\0')
          {
            i++;
            c = str[i];
          }
          if(c==10)
          {
            state = NEWLINE;
            i--;
          }
          state = START;
          shouldread = false;
          lastNewline = false;
          lastComment = false;
          break;


        case NEWLINE:
            
          line++;
          
          if(!lastNewline && !lastComment)
            searchToken("newline",o);
          
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
          
          state = START;
          shouldread = true;
          lastComment = false;
          break;
        

        case NUMBER:
          
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
          
          state = START;
          shouldread = false;
          lastNewline = false;
          lastComment = false;
          break;


        case STRING_LITERAL:
          
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
            searchToken(new,o);
          }
          else
          {
            state = START;
            shouldread = true;
            lastNewline = false;
            lastComment = false;
            error = false;
            break;
          }
 
          i++;
          error = false;
          state = START;
          shouldread = true;
          lastNewline = false;
          lastComment = false;
          break;

        case COMMENT:
          
          while(str[i] != '\0')
            i++;
            
          if(str[i] == 10)
            line++;
          line++;
          state = START;
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

void lexer()
{
  faux = fopen("auxTokenList.txt","w");
  readTokens();
  dfa();
}
/*
int main()
{
  readTokens();
  dfa();
  return 0;  
}
*/
