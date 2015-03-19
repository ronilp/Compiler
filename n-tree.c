#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "n-tree.h"

void preorder(struct tree *p)
{
  int i;
  if(p == NULL)
    return;
  printf("%s ",p->data);
  for(i=0; i<p->children; i++)
    preorder(p->child[i]);
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

struct tree *insert(struct tree *parent, char *data)
{
  if(parent == NULL)
  {
    parent = createNode(data);
    return parent;
  }

  int i=0;

  if(parent->child == NULL)
    parent = setChildren(parent,20);
  else
  {
    while(parent->child[i] != NULL)
      i++;
  }

  struct tree *new = NULL;
  new = createNode(data);
  parent->child[i] = new;
  parent->child[i]->childID = i+1;
  parent->child[i]->parent = parent;
  return parent;
}

/*
struct tree *root = NULL;

void main()
{
  root = createNode("A");
  insert(root,"E");
  insert(root,"B");
  insert(root,"F");

  insert(root->child[1],"C");
  insert(root->child[1]->child[0],"G");
  insert(root->child[1]->child[0]->child[0],"H");
  insert(root->child[2],"D");

  preorder(root);
}
*/
