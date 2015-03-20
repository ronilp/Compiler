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
  if(strcmp(astops[key],c))
    return 1;
  else
    return 0;
}

int searchothers(char c[])
{
  int key;
  key = hashOperators(c);
  if(strcmp(astothers[key],c))
    return 1;
  else
    return 0;
}

struct tree *traverseAST(struct tree *node)
{
  if(node == NULL)
    return ;
   
  ///* 
  if(node->parent == NULL)
    printf("node->parent = NULL for %s\n",node->data);
  else if(node->parent->children == 1)
    printf("node->parent->children = 1 for %s's parent\n",node->data);
  else
    printf("node->parent->children = %d for %s's parent\n",node->parent->children,node->data);
  //*/

  while((node->parent != NULL) && (node->parent->children == 1))
  {
    printf("reducing node %s's parent %s\n", node->data,node->parent->data);
    if(strcmp(node->data,"e")==0)
    {
      node->parent->child[node->parent->childID] = NULL;
      node->parent->children--;
      //free(node);
    }
    else if(node->parent->parent != NULL)
    {
      struct tree *temp;
      printf("node gparent not null for %s, parent = %s, gparent = %s\n",node->data,node->parent->data,node->parent->parent->data);
      temp = node->parent;
      int ID;
      ID = temp->childID;
      temp->parent->child[ID] = node;
      node->parent = temp->parent;
      node->childID = ID;
      //free(temp);
    }
  }
/*
  if(searchothers(node->data) == 1)
  {
    int ID = node->childID;
    int i;
    for(i=ID; i<node->parent->children; i++)
    {
      node->parent->child[i] = node->parent->child[i+1];
      node->parent->child[i]--;
    }
    node->parent->children--;
  }
*/
  int i;
  for(i=0; i<node->children; i++)
    traverseAST(node->child[i]);
  return node;
}

void ast()
{
  readInput();
  traverseAST(root);
  FILE *fp = stdout;
  //preorder(root,fp);
}
