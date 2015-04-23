// Team number 38
// MOHIT GUPTA (2012A7PS021P)
// RONIL PANCHOLIA (2012C6PS629P)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "symbolTable.h"
#include "parser.h"

int scope = 1;

int streamIndex = 0;

char stream[MAX_NUM_TOKENS][MAX_TOKEN_LENGTH];

struct st *searchInSymbolTable(char data[], int scope)
{
  struct st *temp = NULL;
  int i;
  for(i=0; i<STEntries; i++)
  {
    if(strcmp(data,SymbolTable[i].data) == 0)
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
  else
  {
    printf("SEMANTIC ERROR : Repeated declaration of the variable '%s' in the same scope in line %d\nPreviously declared in line %d\n", data,line,(*temp).declared);
    exit(0);
  }
}

bool verify(char *data, int scope,int line)
{
  if(searchInSymbolTable(data,scope) != NULL)
    return true;
  else
  {
    printf("SEMANTIC ERROR : ‘%s’ undeclared (first use in this function) in line %d\n",data,line);
    exit(0);
    return false;
  }
}

void printSymbolTable()
{
  int i;
  for(i=0; i<STEntries; i++)  
    printf("%s %s %d %d\n",SymbolTable[i].data,SymbolTable[i].dataType,SymbolTable[i].scope,SymbolTable[i].declared);
}

void deleteEntries(int scope)
{
  int i;
  for(i=0; i<STEntries; i++)
  {
    if(SymbolTable[i].scope == scope)
      strcpy(SymbolTable[i].data,"xxxxx");
  }
}

int calculateScope(int index)
{
  if(strcmp(stream[index],"{") == 0)
    scope++;

  if(strcmp(stream[index],"}") == 0)
  {
    deleteEntries(scope);
    scope--;
  }
  return scope;
}

char *getType(char token[], int scope)
{
	int i;
	for(i=0; i<STEntries; i++)
	{
		if(strcmp(token,SymbolTable[i].data) == 0)
		{
			if(SymbolTable[i].scope <= scope)
			{
				return SymbolTable[i].dataType;
			}
		}
	}
	printf("token = %s, scope = %d\nEntry does not exist in symbol table\n",token,scope);
	return "";
}

char *tokenType(char token[])
{
  if(token[5] == ',')
    return "ID";
  if(token[17] == ',')
    return "IntegerLiteral";
  if(token[16] == 'T')
    return "StringLiteral";
  if(token[15] == 'N')
    return "FloatLiteral"; 
  if(strcmp(token,"TK_LENGTH") == 0)
  	return "Length"; 
  return "None";
}

void operators(char buffer[][100], int bufferindex)
{
	int i;
	for(i=0;i<bufferindex;i++)
	{
		if((strcmp(buffer[i],"TK_MULTIPLY") == 0) || (strcmp(buffer[i],"TK_DIVIDE") == 0) || (strcmp(buffer[i],"TK_PLUS") == 0) || (strcmp(buffer[i],"TK_MINUS") == 0) || (strcmp(buffer[i],"TK_MOD") == 0) || (strcmp(buffer[i],"TK_COMPARE") == 0) || (strcmp(buffer[i],"TK_GT") == 0) || (strcmp(buffer[i],"TK_LT") == 0) || (strcmp(buffer[i],"TK_ASSIGNOP") == 0) || (strcmp(buffer[i],"TK_AND") == 0) || (strcmp(buffer[i],"TK_OR") == 0) || (strcmp(buffer[i],"TK_NOTEQUAL") == 0) || ((strcmp(tokenType(buffer[i]),"IntegerLiteral")  == 0) && (strcmp(tokenType(buffer[i-1]),"TK_LSQBRAC")  == 0)) || ((strcmp(tokenType(buffer[i]),"FloatLiteral")  == 0) && (strcmp(tokenType(buffer[i-1]),"TK_LSQBRAC")  == 0)) || (strcmp(tokenType(buffer[i]),"StringLiteral") == 0) || (strcmp(buffer[i],"TK_MOD") == 0))
		{
			//printf("For tokens %s %s %s\n",buffer[i-1],buffer[i],buffer[i+1]);

			int k,line,j=0;
			char typeA[100],typeB[100];
			char nameA[100],nameB[100];
		
			char *tkA,*tkB;
			char tka[10][100],tkb[10][100];

			memset(typeA,0,100);
			memset(typeB,0,100);
			memset(nameA,0,100);
			memset(nameB,0,100);

			for(k=0; k<10; k++)
				for(j=0; j<100; j++)
				{
					strcpy(&tka[k][j],"");
					strcpy(&tkb[k][j],"");
				}
			
			j=0;
			//printf("buffer[i+1] = %s\n", buffer[i+1]);
			char temp[100];
    		memset(temp,0,100);
    		if(buffer[i+1] != NULL)
    		if(strcmp(buffer[i+1],"TK_LPAR") != 0)
    			strcpy(temp,buffer[i+1]);
    		else
    			strcpy(temp,buffer[i+2]);
			tkB = strtok(temp,",\n");
    		while(tkB != NULL)
	    	{
      			strcpy(tkb[j],tkB);
      			tkB = strtok(NULL,",\n");
      			j++;
    		}
    		/*
    		for(k=0;k<j;k++)
    			printf("k = %d, %s\n", k,tkb[k]);
    			*/
    		strcpy(nameB,tkb[1]);

			if(strcmp(tkb[0],"TK_INTEGERLITERAL")  == 0)
			{
				strcpy(typeB,"TK_INT");
			}
			else if(strcmp(tkb[0],"TK_FLOATLITERAL")  == 0)
			{
				strcpy(typeB,"TK_FLOAT");	
			}
			else if(strcmp(tkb[0],"TK_STRINGLITERAL")  == 0)
			{
				strcpy(typeB,"TK_PROTEIN");
			}
			else if(strcmp(tkb[0],"TK_LENGTH")  == 0)
			{
				strcpy(typeB,"TK_INT");
			}
			else
			{
				strcpy(typeB,getType(nameB,scope));
			}

			//printf("buffer[i-1] = %s\n", buffer[i-1]);
    		if(strcmp(buffer[i-1],"TK_RSQBRAC") != 0)
    		{
    			char temp[100];
    			memset(temp,0,100);
    			if(buffer[i+1] != NULL)
    			if(strcmp(buffer[i-1],"TK_LPAR") != 0)
    				strcpy(temp,buffer[i-1]);
    			else	
    				strcpy(temp,buffer[i-2]);
    			tkA = strtok(temp,",\n");
    			j=0;
		    	while(tkA != NULL)
			    {
      				strcpy(tka[j],tkA);
      				tkA = strtok(NULL,",\n");
      				j++;
    			}
    			j--;
    			/*
    			for(k=0;k<j;k++)
    				printf("k = %d, %s\n", k,tka[k]);
    			*/
    			line = atoi(tka[2]);
    			strcpy(nameA,tka[1]);

    			if(strcmp(tokenType(buffer[i-1]),"IntegerLiteral")  == 0)
				{
					strcpy(typeA,"TK_INT");
				}
				else if(strcmp(tokenType(buffer[i-1]),"FloatLiteral")  == 0)
				{
					strcpy(typeA,"TK_FLOAT");	
				}
				else if(strcmp(tka[0],"TK_STRINGLITERAL")  == 0)
				{
					strcpy(typeA,"TK_PROTEIN");
				}
				else if(strcmp(tka[0],"TK_LENGTH")  == 0)
				{
					strcpy(typeA,"TK_INT");
				}
				else
				{
					//printf("token sent = %s\n", nameA);
					strcpy(typeA,getType(nameA,scope));
				}
    		}
    		else
    		{
     			//printf("buffer[i-4] = %s\n", buffer[i-4]);
    			char temp[100];
    			memset(temp,0,100);
    			strcpy(temp,buffer[i-4]);
	    		tkA = strtok(temp,",\n");
	    		j=0;
		    	while(tkA != NULL)
			    {
      				strcpy(tka[j],tkA);
      				tkA = strtok(NULL,",\n");
      				j++;
    			}
    			j--;
    			/*
    			for(k=0;k<j;k++)
    				printf("k = %d, %s\n", k,tkb[k]);
    			*/
    			line = atoi(tka[2]);
    			strcpy(nameA,tka[1]);

				if(strcmp(tokenType(buffer[i-4]),"IntegerLiteral")  == 0)
				{
					strcpy(typeA,"TK_INT");
				}
				else if(strcmp(tokenType(buffer[i-4]),"FloatLiteral")  == 0)
				{
					strcpy(typeA,"TK_FLOAT");	
				}
				else if(strcmp(tka[0],"TK_STRINGLITERAL")  == 0)
				{
					strcpy(typeA,"TK_PROTEIN");
				}
				else if(strcmp(tka[0],"TK_LENGTH")  == 0)
				{
					strcpy(typeA,"TK_INT");
				}
				else
				{
					//printf("token sent = %s\n", nameA);
					strcpy(typeA,getType(nameA,scope));
				}    		
			}

   			if(strcmp(typeA,typeB) != 0)
			{
				printf("TYPE ERROR : Type mismatch about operator %s for %s and %s in line %d\n",buffer[i],nameA,nameB,line);
				exit(0);
			}
			else
			{
				//printf("Type Check successful for %s %s\n", typeA, typeB);
			}
		}
	}
}

void symbolTable()
{
  int i=0;
  for(i=0; i<128; i++)
  {
    SymbolTable[i].data = malloc(sizeof(char)*100);
    SymbolTable[i].dataType = malloc(sizeof(char)*100);
  }

  FILE *fp = fopen("tokenstream.txt","r");
  if(fp == NULL)
  {
    printf("Error opening input files for symbolTable\n");
    exit(0);
  }

  int tokenCount = 0;
  char buffer[100][100];
  int bufferindex=0;
  int ls = 0;

  while(!feof(fp))
  {
    char temp[MAX_TOKEN_LENGTH];
    fgets(stream[tokenCount],MAX_TOKEN_LENGTH,fp);
    strtok(stream[tokenCount],"\n");
    tokenCount++;
  }
  tokenCount--;

  while(streamIndex < tokenCount)
  {
    calculateScope(streamIndex);
    char type[100];
    strcpy(type,tokenType(stream[streamIndex]));

    if(strcmp(stream[streamIndex],"length") == 0)
    {
      insertInSymbolTable("length","TK_INT",++ls,1);
    }

    if(strcmp(type,"ID") == 0)
    {
      char name[100],dataType[100],l[10];
      memset(l,0,10);
      memset(name,0,100);
      memset(dataType,0,100);
      
      int line,i=6;

      while(stream[streamIndex][i] != ',')
      {
        name[i-6] = stream[streamIndex][i];
        i++;
      }
      i++;
      int j=0;
      while(stream[streamIndex][i] != '\0')
      {
        l[j] = stream[streamIndex][i];
        i++;j++;
      }
      line = atoi(l);

      char prev[100];
      strcpy(prev,stream[streamIndex-1]);
      
      if((strcmp(prev,"TK_INT")==0) || (strcmp(prev,"TK_FLOAT")==0) || (strcmp(prev,"TK_PROTEIN")==0) || (strcmp(prev,"TK_SEQ")==0))
      {
        strcpy(dataType,prev);
        insertInSymbolTable(name,dataType,scope,line);
      }
      else
      {
        verify(name,scope,line);
      }
    }
    /*
    if(strcmp(type,"IntegerLiteral") == 0)
    { 
      char name[100];
      memset(name,0,100);

      int i=18;
      while(stream[streamIndex][i] != ',')
      {
        name[i-18] = stream[streamIndex][i];
        i++;
      }
      printf("%s\n", name);
    }

    if(strcmp(type,"FloatLiteral") == 0)
    { 
    	;
    }
    */
    if(strcmp(stream[streamIndex],"TK_NEWLINE") != 0)
    {
    	//printf("Added %s\n", stream[streamIndex]);
    	strcpy(buffer[bufferindex],stream[streamIndex]);
    	bufferindex++;
	}
	else
	{
		operators(buffer,bufferindex);
		int t;
		for(t=0; t<=bufferindex; t++)
			strcpy(buffer[t],"");
		bufferindex = 0;
	}
    streamIndex++;
  }

  /* Testing ST
  insertInSymbolTable("hello","char",1,1);
  insertInSymbolTable("meow","char",2,2);
  insertInSymbolTable("meow","char",1,3);
  insertInSymbolTable("meow","char",1,4);
  deleteEntries(1);
  printSymbolTable();
  */
  printf("Type Checking and Semantic Analysis Successful\n");
}
