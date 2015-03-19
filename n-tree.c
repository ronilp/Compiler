#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "n-tree.h"

void preorder(struct tree *p)
{
  if(p == NULL)
    return;
  printf("%s ",p->data);
  preorder(p->child);
  preorder(p->sibling);
}

struct tree *search(struct tree* root,char *data)
{
  if(root == NULL)
    return;
  if(strcmp(data,root->data) == 0)
    return root;
  struct tree *t = search(root->child,data);
  if(t == NULL)
     t = search(root->sibling,data);
  return t;
}

struct tree *createNode(char *data)
{
  struct tree *newnode = (struct tree*)malloc(sizeof(struct tree));
  newnode->child = NULL;
  newnode->sibling = NULL;
  newnode->data = malloc(sizeof(char)*100);
  strcpy(newnode->data,data);
  return newnode;
}

struct tree *insert(struct tree *root, char *parent, char *data)
{
  struct tree *p = search(root,parent);

  if(p == NULL)
  {
    p = createNode(data);
    return p;
  }

  if(p->child == NULL)
  {
    p->child = createNode(data);
  }
  else
  {
    while(p->sibling != NULL)
      p = p->sibling;
    
    p->sibling = createNode(data);
  } 
  return root;
}

/*
void main()
{
  struct tree *root=NULL;
  
  root = insert(root," ","A");
  root = insert(root,"A","E");
  root = insert(root,"A","B");
  root = insert(root,"A","F");
  root = insert(root,"B","C");
  root = insert(root,"C","G");
  root = insert(root,"G","H");
  root = insert(root,"F","D");

  preorder(root);
}
*/
