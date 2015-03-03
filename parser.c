#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "parser.h"

void initialize()
{
  FILE *fp1 = fopen("terminals.txt","r");
  FILE *fp2 = fopen("nonterminals.txt","r");
  FILE *fp3 = fopen("tableparse.txt","r");
  FILE *fp4 = fopen("grammar.txt","r");
  FILE *fp5 = fopen("tokenstream.txt","r");

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
  for(i=0; i < numTerminals; i++)
    for(j=0; j < numNonTerminals; j++)
      fscanf(fp3,"%d",&parseTable[i][j]);

  
  /* Initializing Grammar */
  char temp[MAX_RULE_LENGTH];
  for(i=0; i < numRules; i++)
  {
    fgets(temp,MAX_RULE_LENGTH,fp4);
    strcpy(Grammar[i],temp);
  }

  /* Initializing Token Stream */
  while(!feof(fp5))
  {
    char temp[MAX_TOKEN_LENGTH];
    fgets(TokenStream[numTokens],MAX_TOKEN_LENGTH,fp5);
    strtok(TokenStream[numTokens],"\n");
    numTokens++;
  }
  numTokens--;

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
  Stack *S;
  S = createStack();
  Push(S,nonterminal[0]);
  int ruleNumber;
  while(!isEmpty(S))
  {
    char tk[MAX_TOKEN_LENGTH];
    int tpos,ntpos;

    printf("Popped = %s\n",Top(S));
    //printf("token stream = %s\n",TokenStream[tokenIndex]);
    ntpos = nonterminalPosition(Pop(S));
    tpos = terminalPosition(TokenStream[tokenIndex]);

    ruleNumber = parseTable[ntpos][tpos];
    //printf("nt,t,rule = %d,%d, %d\n",ntpos,tpos,ruleNumber);
    //printf("rule %d = %s\n",ruleNumber,Grammar[ruleNumber-1]);

    int j=0,i;
    char *nt;
    char rule[numTerminals + numNonTerminals][MAX_TERMINAL_SIZE];
  
    //nt1 = strdup(Grammar[ruleNumber-1]);
    //nt = strtok(nt1," \n");
    nt = strtok(Grammar[ruleNumber-1]," \n");
    
    while(nt != NULL)
    {
      strcpy(rule[j],nt);
      nt = strtok(NULL," \n");
      j++;
    }
    j--;

    printf("Pushed = ");
    while(j>-1)
    {
      printf("%s ",rule[j]);
      Push(S,rule[j]);
      j--;
    }
    printf("\n");

    while(terminalPosition(Top(S)) != -1)
    {
      if(strcmp(Top(S),TokenStream[tokenIndex]) == 0)
      {
        tokenIndex++;
        Pop(S);
      }
    }
    
    while(strcmp(Top(S),"e") == 0)
      Pop(S);
  }
  // tokenIndex should be = numTokens now
}

int main()
{
  initialize();
  parse();
  return 0;  
}
