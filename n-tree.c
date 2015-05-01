// Team number 38
// MOHIT GUPTA (2012A7PS021P)
// RONIL PANCHOLIA (2012C6PS629P)


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "n-tree.h"

void preorder(struct tree *p,FILE *fp)
{
  int i;
  if(p == NULL)
    return;
  fprintf(fp,"%s ",p->data);
  for(i=0; i<p->children; i++)
    preorder(p->child[i],fp);
}

struct tree *getNextPreorder(struct tree *p)
{
  if(p->parent != NULL)
  {
    while((p->parent != NULL) && (p->childID == p->parent->children))
    {
      if(p->parent != NULL)
        p = p->parent;
    }
  }
  int temp;
  temp = p->childID;
  if(p->parent == NULL)
    return p;  
  else
    p = p->parent->child[temp];
  return p;  
}

struct tree *createNode(char *data)
{
  struct tree *newnode = (struct tree *)malloc(sizeof(struct tree));
  newnode->child = NULL;
  newnode->parent = NULL;
  newnode->data = malloc(sizeof(char)*100);
  strcpy(newnode->data,data);
  newnode->children = 0;
  newnode->childID = 1;
  return newnode;
}

struct tree *setChildren(struct tree *parent, int children)
{
  if(parent == NULL)
  {
    printf("The parent whose children you are trying to set doesnot exists\n");
    return NULL;
  }

  int i;
  parent->children = children;
  parent->child = malloc(sizeof(struct tree *)*children);
  
  for(i=0; i<children; i++)
    parent->child[i] = NULL;
  
  if(parent->child == NULL)
    printf("Error allocating memory for children\n");
  return parent;
}

struct tree *insert(struct tree *p, char *data,int numchildren)
{
  if(p == NULL)
  {
    p = createNode(data);
    return p;
  }

  int i=0;

  if(p->child == NULL)
  {
    //printf("setting children for %s = %d\n",p->data,numchildren);
    p = setChildren(p,numchildren);
  }
  else
  {
    while(p->child[i] != NULL)
      i++;
  }

  struct tree *new = NULL;
  new = createNode(data);
  new->childID = i+1;
  new->parent = p;
  p->child[i] = new;
  return p;
}
/*
struct tree *root = NULL;

void main()
{
  root = createNode("A");
  setChildren(root,3);
  insert(root,"E",3);
  insert(root,"B",3);
  insert(root,"F",3);

  insert(root->child[1],"C",1);
  insert(root->child[1]->child[0],"G",1);
  insert(root->child[1]->child[0]->child[0],"H",1);
  insert(root->child[2],"D",1);

  preorder(root);
}
*/
