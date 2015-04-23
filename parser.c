// Team number 38
// MOHIT GUPTA (2012A7PS021P)
// RONIL PANCHOLIA (2012C6PS629P)


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "parser.h"

int tokenCount = 0;

int tokenIndex = 0;

int auxTokenCount = 0;

int auxTokenIndex = 0;

void initialize()
{
  FILE *fp1 = fopen("terminals.txt","r");
  FILE *fp2 = fopen("nonterminals.txt","r");
  FILE *fp3 = fopen("tableparse.txt","r");
  FILE *fp4 = fopen("grammar.txt","r");
  FILE *fp5 = fopen("tokenstream.txt","r");
  FILE *fp6 = fopen("auxTokenList.txt","r");

  if(fp1 == NULL || fp2 == NULL || fp3 == NULL || fp4 == NULL || fp5 == NULL || fp6 == NULL)
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
    char temptoken;
    strtok(TokenStream[tokenCount],"\n");
    tokenCount++;
  }
  tokenCount--;

  /* Initializing auxToken Stream */
  while(!feof(fp6))
  {
    char temp[MAX_TOKEN_LENGTH];  
    fgets(auxTokenStream[auxTokenCount],MAX_TOKEN_LENGTH,fp6);
    strtok(auxTokenStream[auxTokenCount],"\n");
    auxTokenCount++;
  }
  auxTokenCount--;

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

char **split(char *a_str, const char a_delim)
{
  char **result = 0;
  size_t count = 0;
  char *tmp = a_str;
  char *last_comma = 0;
  char delim[2];
  delim[0] = a_delim;
  delim[1] = 0;

  /* Count how many elements will be extracted. */
  while(*tmp)
  {
    if(a_delim == *tmp)
    {
      count++;
      last_comma = tmp;
    }
    tmp++;
  }

  /* Add space for trailing token. */
  count += last_comma < (a_str + strlen(a_str) - 1);

  /* Add space for terminating null string so caller
     knows where the list of returned strings ends. */
  count++;

  result = malloc(sizeof(char*) * count);

  if(result)
  {
    size_t idx  = 0;
    char* token = strtok(a_str, delim);

    while(token)
    {
      assert(idx < count);
      *(result + idx++) = strdup(token);
      token = strtok(0, delim);
    }
    assert(idx == count-1);
    *(result + idx) = 0;
  }
  return result;
}

void parse()
{
  //int matchcount = 1;
  //int iter = 1;
  bool parseError = false;

  Stack *S;
  S = createStack();
  Push(S,nonterminal[0]);
  root = createNode(nonterminal[0]);

  FILE *f1 = fopen("parsetree.txt","w");

  fprintf(f1,"root = %s\n",root->data);

  int ruleNumber;
  struct tree *current = root;

  char tkn[MAX_TOKEN_LENGTH];
  while(!isEmpty(S))
  {
    int tpos,ntpos;
    char tk1[MAX_TOKEN_LENGTH];
    char **stripped;
    char tk2[MAX_TOKEN_LENGTH];
    char temptoken[200];

    //printf("Popped = %s\n",Top(S));

    strcpy(tk1,Pop(S));
    ntpos = nonterminalPosition(tk1);

    if(strchr(TokenStream[tokenIndex],44) == NULL)
    {   /* If comma not present in next token */
      tpos = terminalPosition(TokenStream[tokenIndex]);
    }
    else
    {   /* If comma present in next token */
      strcpy(temptoken,TokenStream[tokenIndex]);
      stripped = split(TokenStream[tokenIndex], ',');
      strcpy(tk2,stripped[0]);
      //strcpy(tkn,stripped[1]);
      //printf("tk2 = %s, tkn = %s\n ",tk2,tkn);
      tpos = terminalPosition(tk2);
    }
  
    ruleNumber = parseTable[ntpos][tpos];

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
    
    current = setChildren(current,j+1);
    //printf("current = %s, children set = %d\n",current->data,j+1);

    char commas[4][MAX_TOKEN_LENGTH];
    strcpy(commas[0],"TK_ID");
    strcpy(commas[1],"TK_STRINGLITERAL");
    strcpy(commas[2],"TK_FLOATLITERAL");
    strcpy(commas[3],"TK_INTEGERLITERAL");

    int k=j;
    for(k=0; k<=j; k++)
    {
      //printf("rule[k] = %s\n",rule[k]);
      
      if((strcmp(rule[k],commas[0]) == 0) || (strcmp(rule[k],commas[1]) == 0) || (strcmp(rule[k],commas[2]) == 0) || (strcmp(rule[k],commas[3]) == 0))
      {
        char temp[MAX_TOKEN_LENGTH];
        strcpy(temp,auxTokenStream[auxTokenIndex++]);
         insert(current,temp,j+1);
        fprintf(f1,"inserted %s in %s\n",temp,current->data);
      }
      else
      {
      	insert(current,rule[k],j+1);
        fprintf(f1,"inserted %s in %s\n",rule[k],current->data); 
      }
    }
    fprintf(f1,"----------------------------------\n");
    if(current->child[0] != NULL)
      current = current->child[0];

    while(1)
    {
      if(nonterminalPosition(current->data) != -1)
      { /* if current is a nonterminal */
        break;
      }
      else
      {
        current = getNextPreorder(current);
      }
    }

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
          //printf("%d matched %s\n",matchcount++,Top(S));
          Pop(S);
        }
        else if(strchr(TokenStream[tokenIndex],44) != NULL)
        {    /* If comma present in next token */
          char **stripped;
          stripped = split(TokenStream[tokenIndex], ',');
          strcpy(tk2,stripped[0]);
          tpos = terminalPosition(tk2);
          tokenIndex++;
          //printf("%d matched %s\n",matchcount++,Top(S));
          Pop(S);
        }
        else
        {  
          printf("PARSING ERROR :\n'%s' appeared when '%s' was expected!\n",TokenStream[tokenIndex],Top(S));
          break;
          parseError = true;
        }
        if(isEmpty(S))
          break;
      }
    }
  }
  // tokenIndex should be = numTokens now
  if(tokenIndex == tokenCount)
    printf("Parsing Complete\nPlease Check parstree.txt and parsetreetraversal.txt for parser output\n");
  else
  {
    while(tokenIndex != tokenCount)
    {
      printf("last error\n");
      if(strcmp(TokenStream[tokenIndex],"TK_NEWLINE"))
        tokenIndex++;
      else
        printf("Parsing Error\n");
    }
  }
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

int hashTerminals(char str[])
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
  FILE *f = fopen("parsetreetraversal.txt","w");
  fprintf(f,"PREORDER TRAVERSAL\n\n");
  preorder(root,f);
}
