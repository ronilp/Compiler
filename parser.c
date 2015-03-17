#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include "parser.h"

int tokenCount = 0;

int tokenIndex = 0;

void initialize()
{
  FILE *fp1 = fopen("terminals.txt","r");
  FILE *fp2 = fopen("nonterminals.txt","r");
  FILE *fp3 = fopen("tableparse.txt","r");
  FILE *fp4 = fopen("grammar.txt","r");
  FILE *fp5 = fopen("tokenstream.txt","r");
  FILE *fpn = fopen("fn.txt","w");

  if(fp1 == NULL || fp2 == NULL || fp3 == NULL || fp4 == NULL || fp5 == NULL)
  {
    printf("Error opening input files\n");
    exit(0);
  }

  int i,j;
  
  /* Initializing Terminals */
  for(i=0; i < numTerminals; i++)
    fscanf(fp1,"%s",terminal[i]);

  /* Initializing NonTerminals */
  for(i=0; i < numNonTerminals; i++)
    fscanf(fp2,"%s",nonterminal[i]); 

  /* Initializing ParseTable */
  for(i=0; i < numNonTerminals; i++)
    for(j=0; j < numTerminals; j++)
      fscanf(fp3,"%d",&parseTable[i][j]);

  /* Initializing Grammar */
  char temp[MAX_RULE_LENGTH];
  for(i=0; i < numRules; i++)
  {
    fgets(temp,MAX_RULE_LENGTH,fp4);
    strcpy(Grammar[i],temp);
    //printf("%d %s",i,Grammar[i]);
  }

  /* Initializing Token Stream */
  while(!feof(fp5))
  {
    char temp[MAX_TOKEN_LENGTH];
    fgets(TokenStream[tokenCount],MAX_TOKEN_LENGTH,fp5);
    strtok(TokenStream[tokenCount],"\n");
    tokenCount++;
  }
  tokenCount--;

  fcloseall();
}

int terminalPosition(char *str)
{
  int i;
  for(i=0; i < numTerminals; i++)
  {
    if(strcmp(str,terminal[i]) == 0)
      return i;
  }
  //printf("Illegal Terminal Recieved, %s\n",str);
  return -1;
}

int nonterminalPosition(char *str)
{
  int i;
  for(i=0; i < numNonTerminals; i++)
  {
    if(strcmp(str,nonterminal[i]) == 0)
      return i;
  }
  //printf("Illegal NonTerminal Recieved, %s\n",str);
  return -1;
}

void parse()
{
  int matchcount = 1;
  int iter = 1;
  bool parseError = false;

  Stack *S;
  S = createStack();
  Push(S,nonterminal[0]);
  int ruleNumber;
  while(!isEmpty(S))
  {
    char tk[MAX_TOKEN_LENGTH];
    int tpos,ntpos;

    //strcpy(tk,Pop(S));

    //printf("Popped = %s\n",Top(S));

    ntpos = nonterminalPosition(Pop(S));
    tpos = terminalPosition(TokenStream[tokenIndex]);
  
    ruleNumber = parseTable[ntpos][tpos];

    //if(iter > 450)
    //{
      //printf("paused due to probable stack overflow");
      //break;
    //}
    //printf("iter = %d, nt = %d | %s,tp = %d | %s, rule = %d\n",iter++,ntpos,nonterminal[ntpos],tpos,terminal[tpos],ruleNumber);
    int j=0,i;
    char *nt;
    char rule[numTerminals + numNonTerminals][MAX_TERMINAL_SIZE];

    //printf("tokens = %s, rule = %s",TokenStream[tokenIndex],Grammar[ruleNumber-1]);

    char temp[MAX_RULE_LENGTH];
    strcpy(temp,Grammar[ruleNumber-1]);

    nt = strtok(temp," \n");
    while(nt != NULL)
    {
      strcpy(rule[j],nt);
      nt = strtok(NULL," \n");
      j++;
    }
    j--;

    //printf("Pushed = ");
    while(j>-1)
    {
      //printf("Pushed = ");
      //printf("%s\n",rule[j]);
      Push(S,rule[j]);
      j--;
    }
    //printf("\n");

    if(!isEmpty(S))
    {
      /* if Top(S) is a not a nonterminal */
      while(nonterminalPosition(Top(S)) == -1)
      {
        if(strcmp(Top(S),"e") == 0)
        {
          //printf("Popped = %s\n",Top(S));
          Pop(S);
        }
        else if(strcmp(Top(S),TokenStream[tokenIndex]) == 0)
        {
          tokenIndex++;
          printf("%d matched %s\n",matchcount++,Top(S));
          Pop(S);
          //if(!isEmpty(S))
          //{
            //printf("next = %s\n",Top(S));  
          //}
          //else
            //printf("stack empty");
        }
        else
        {  
          printf("PARSING ERROR :\n'%s' appeared when '%s' was expected!\n",TokenStream[tokenIndex],Top(S));
          break;
          parseError = true;
        }
      }
    }
  }
  // tokenIndex should be = numTokens now
  if(tokenIndex == tokenCount)
    printf("done\n");
  else
    printf("Parsing error\n");
}

int hashNonTerminals(char str[])
{
  int key,i;
  for(i=0; i<strlen(str); i++)
  {
    key += i*str[i];
  }
  return key%511;  
}

void parser()
{
  initialize();
  parse();  
}
