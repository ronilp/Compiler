#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include "stack.h"

void printStack(Stack *S)
{
  Stack *A = S;
  while(A->top!=-1)
  {
    printf("%s ",A->array[A->top]);
    A->top--;
  }
  printf("\n");
}

Stack *createStack()  
{
  Stack *S = malloc(sizeof(Stack));
  S->capacity = 10;
  S->top = -1;
  S->array = malloc(sizeof(char *)*S->capacity);
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

char *Top(Stack *S)
{
  if(!isEmpty(S))
    return S->array[S->top];
}

void Push(Stack *S, char *data)
{
  if(isFull(S))
    doubleStack(S);
  S->top++;
  S->array[S->top] = malloc(sizeof(char)*strlen(data));
  strcpy(S->array[S->top],data);
}

char *Pop(Stack *S)
{
  if(isEmpty(S))
  {
    printf("Stack Empty");
    return NULL;
  }
  else
    return S->array[S->top--];
}
