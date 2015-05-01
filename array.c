// Team number 38
// MOHIT GUPTA (2012A7PS021P)
// RONIL PANCHOLIA (2012C6PS629P)

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct ArrayStack{
  int capacity;
  int top;
  int *array;
}Stack;

Stack *createStack()  
{
  Stack *S = malloc(sizeof(Stack));
  S->capacity = 5;
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

void Push(Stack *S, int data)
{
  if(isFull(S))
  {
    printf("Stack full\n");
  }
  else
  {
    S->top++;
    S->array[S->top] = data;
  }
}

int Pop(Stack *S)
{
  if(isEmpty(S))
  {
    printf("Stack is Empty\n");
    return -1;
  }
  else
  {
    int d = S->array[S->top];
    S->top--;  
    return d;
  }
}

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

int Top(Stack *S)
{
  if(!isEmpty(S))
    return S->array[S->top];  
}

int size(Stack *S)
{
  int count=0;
  while(!isEmpty(S))  
  {
    count++;
    Pop(S);
  }
  return count;
}

int getMin(Stack *S)
{
  int min,i;
  min = S->array[0];
  for(i=0;i<size(S);i++)
  {
    if(min > S->array[i])
      min = S->array[i]; 
  }
  return min;
}

void insertAtBottom(Stack *s, int data)
{ 
  if(isEmpty(s))
  {
    Push(s,data);
    return ;
  }
  int temp = Top(s);
  Pop(s);
  insertAtBottom(s,data);
  Push(s,temp);
}

void reverse(Stack *s)
{
  int data;
  if(isEmpty(s))
    return ;
  data = Top(s);
  Pop(s);
  reverse(s);
  insertAtBottom(s,data);
}

int main()
{
  Stack *S;
  S = createStack();
  Push(S,5);
  Push(S,4);
  Push(S,3);
  Push(S,2);
  Push(S,1);
  Push(S,10);
  Pop(S);
  Pop(S);
  Push(S,10);
 //printStack(S);

  reverse(S);
  printStack(S);
  return 0;  
}
