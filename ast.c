// Team number 38
// MOHIT GUPTA (2012A7PS021P)
// RONIL PANCHOLIA (2012C6PS629P)

#include<stdio.h>
#include<stdlib.h>
#include "ast.h"
#include<string.h>
#include "parser.h"

void readInput()
{
  FILE *f1 = fopen("ast_ops.txt","r");
  FILE *f2 = fopen("ast_others.txt","r");
  
  int i=0,j,n = ASTOperators;
  while(n > 0)
  {
    char op[100];
    fscanf(f1,"%s",op);
    int key;
    key = hashOperators(op);
    i++;

    strcpy(astops[key],op);
    n--; 
  }
  
  i=0;n = ASTOthers;
  while(n > 0)
  {
    char op[100];
    fscanf(f2,"%s",op);
    int key;
    key = hashOperators(op);
    i++;

    strcpy(astothers[key],op);
    n--; 
  }

  fcloseall();
}

int hashOperators(char c[])
{
  int i,sum=0;
  for(i=0; i<strlen(c); i++)
  {
    sum += (i+1)*c[i];
  }
  return sum % 119;
}

int searchops(char c[])
{
  int key;
  key = hashOperators(c);
  if(strcmp(astops[key],c) == 0)
    return 1;
  else
    return 0;
}

int searchothers(char c[])
{
  
  int key;
  key = hashOperators(c);
  if(strcmp(astothers[key],c) == 0)
    return 1;
  else
    return 0;
}

char *childInOperators(struct tree *p)
{
  int i,j;

  for(j=0; j<p->children; j++)
    for(i=0; i<120; i++)
    {
      if(strcmp(p->child[j]->data, astops[i]) == 0)
        return astops[i];
    }
  return NULL;
}

int valid(struct tree *p)
{
  int i;
  for(i=0; i<120; i++)
  {
    if(strcmp(p->data,astothers[i]) == 0)
      return 0;
    if(strcmp(p->data,astops[i]) == 0)
      return 0; 
  }
  
  return 1;
}

void preorderAST(struct tree *p,FILE *fp)
{
  int i;
  if(p == NULL)
    return;
  if((valid(p) == 1) && (strcmp(p->data,"e")!=0))
  {
    if(childInOperators(p) != NULL)
    {
      fprintf(fp,"%s ",childInOperators(p));
    }
    else
      fprintf(fp,"%s ",p->data);
  }
  for(i=0; i<p->children; i++)
    preorderAST(p->child[i],fp);
}

struct tree *traverseAST(struct tree *node)
{
  if(node == NULL)
    return ;
   
  while((node->parent != NULL) && (node->parent->children == 1))
  {
    if(node->parent->parent != NULL)
    {
      strcpy(node->parent->data, node->data);
      node->parent->child = node->child;
      node->parent->children = node->children;
      //node->parent->child = NULL;
    }
  }

///////////////////////////
/*
  if(node->parent != NULL)
  {
    if(searchothers(node->data) == 1)
    { 
      // If node is in others
      int ID = node->childID;
      int i;
   
      for(i=ID-1; i<node->parent->children; i++)
      {
        printf("i = %d, data = %s\n",i,node->parent->child[i]->data);
        printf("copying %s to %s\n",node->parent->child[i+1]->data,node->parent->child[i]->data);
        strcpy(node->parent->child[i]->data,node->parent->child[i+1]->data);
        node->parent->child[i] = node->parent->child[i+1];
        node->parent->child[i]->children = node->parent->child[i+1]->children;
      }
      node->parent->children--;
    }
  }
*/  
/////////////////////////
  //printf("node %s (children = %d) crossed while loop,\n",node->data,node->children);
 
  int i=0;

  for(i=0; i<node->children; i++)
  {
    //printf("\nTraversing i = %d %s\n",i,node->child[i]->data);
    traverseAST(node->child[i]);
  }
}

void ast()
{
  readInput();
  FILE *fp = stdout;
  printf("\n\n");
  preorder(root,fp);
  traverseAST(root);
  printf("\n\n");
  preorder(root,fp);
  printf("\n");
  /*
  FILE *fp = fopen("abstractSyntaxTree.txt","w");
  fprintf(fp,"PREORDER TRAVERSAL OF AST\n\n");
  preorderAST(root,fp);
  preorder(root,fp);
  printf(" \n Check abstractSyntaxTree.txt for ast output \n");
  */
}

