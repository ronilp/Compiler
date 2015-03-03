#include<stdio.h>
#include "parser.h"
#include "stack.h"

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
  printStack(S);
  return 0;  
}
