// Team number 38
// MOHIT GUPTA (2012A7PS021P)
// RONIL PANCHOLIA (2012C6PS629P)

#include <stdio.h>
#include <string.h>
#include "CodeGeneration.h"

int k=0;
char done[100][100];

void add(char str[])
{
  strcpy(done[k],str);
  k++;
}

int present(char str[])
{
  int h=0,i;
  for(i=0;i<k;i++)
    if(strcmp(done[i],str) == 0)
     h = 1;
  return h;
}

void code()
{
	FILE *fp = fopen("code.asm","w");
	FILE *fp1 = fopen("auxTokenList.txt","r");
  	fprintf(fp,".MODEL TINY\n");
	fprintf(fp,".DATA\n;\n\n");
	fprintf(fp,".STACK\n\n");
 
  if(fp1 == NULL)
    printf("auxTokenList.txt not found\n");
  int i,j;
  char tokenList[100][100];
  char tk[100];
  int tokenCount = 0,ind;
  int msgcounter = 0;

  while(!feof(fp1))
  {
    char temp[100];
    fgets(tokenList[tokenCount],100,fp1);
    strtok(tokenList[tokenCount],"\n");
    tokenCount++;
  }
  tokenCount--;

  for(ind=0; ind<tokenCount; ind++)
  {
    char temp[100];
    memset(temp,0,100);
    strcpy(temp,tokenList[ind]);

    char *tkB;
    char tkb[10][100];

    for(i=0; i<10; i++)
    {
      for(j=0; j<100; j++)
      {
        strcpy(&tkb[i][j],"");
      }
    }

		tkB = strtok(temp,",\n");
    j=0;
    while(tkB != NULL)
	  {
      strcpy(tkb[j],tkB);
      tkB = strtok(NULL,",\n");
      j++;
    } 
  
    if(tkb[0][0] == '"')
    {
      if(!present(tkb[0]))
      {
        add(tkb[0]);
        fprintf(fp,"msg%d  db %s,0xa\n",msgcounter++,tkb[0]);
      }
    } 
    else if(tkb[0][4] == 'D')
    {
      if(!present(tkb[1]))
      {
        add(tkb[1]);
        fprintf(fp,"%s DB ?\n",tkb[1]);
      }
    }
  }
  fprintf(fp,"\n.CODE\n\n");
}
