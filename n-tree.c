#include<stdio.h>
#include<stdlib.h>
#include "n-tree.h"

void preorder(struct tree*p)
{
  if(p == NULL)
    return;
  printf("%d ",p->data);
  preorder(p->child);
  preorder(p->sibling);
}

struct tree *search(struct tree* root,int data)
{
  if(root == NULL)
    return;
  if(data == root->data)
    return root;
  struct tree *t = search(root->child,data);
  if(t == NULL)
     t = search(root->sibling,data);
  return t;

}

struct tree *createNode(int data)
{
  struct tree *newnode = (struct tree*)malloc(sizeof(struct tree));
  newnode->child = NULL;
  newnode->sibling = NULL;
  newnode->data = data;
  return newnode;
}

struct tree *insert(struct tree *root, int parent, int data)
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
  
  root = insert(root,0,1);
  root = insert(root,1,5);
  root = insert(root,1,2);
  root = insert(root,1,6);
  root = insert(root,2,3);
  root = insert(root,3,7);
  root = insert(root,7,8);
  root = insert(root,6,4);

  preorder(root);
}
*/
