#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"stack.h"

void printStack(Stack *S)
{
  Stack *A = S;
  while(A->top!=-1)
  {
    printf("%d ",A->array[A->top]);
    A->top--;
  }
  printf("\n");
}

Stack *createStack()  
{
  Stack *S = malloc(sizeof(Stack));
  S->capacity = 1;
  S->top = -1;
  S->array = malloc(sizeof(int)*S->capacity);
  return S;
}

int isEmpty(Stack *S)
{
  if(S->top == -1)
    return true;
  else
    return false;
}

int isFull(Stack *S)
{
  if(S->top == S->capacity-1)
    return true;
  else
    return false;
}

void deleteStack(Stack *S)
{
  if(S!=NULL)
  {
   if(S->array!=NULL)
     free(S->array);
   free(S);
  }
}

void doubleStack(Stack *S)
{
  S->capacity *= 2;
  S->array = realloc(S->array,S->capacity);
}

int Top(Stack *S)
{
  if(!isEmpty(S))
    return S->array[S->top];  
}

void Push(Stack *S, int data)
{
  if(isFull(S))
    doubleStack(S);
  S->top++;
  S->array[S->top] = data;
}

int Pop(Stack *S)
{
  if(isEmpty(S))
  {
    printf("Stack Empty");
    return -1;
  }
  else
  {
    int d = S->array[S->top];
    S->top--;
    return d;
  }
}
