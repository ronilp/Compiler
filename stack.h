// Team number 38
// MOHIT GUPTA (2012A7PS021P)
// RONIL PANCHOLIA (2012C6PS629P)


typedef struct ArrayStack{
  int capacity;
  int top;
  char **array;
}Stack;

extern void printStack(Stack *S);

extern Stack *createStack();

extern int isEmpty(Stack *S);

extern int isFull(Stack *S);

extern void deleteStack(Stack *S);

extern void doubleStack(Stack *S);

extern char *Top(Stack *S);

extern void Push(Stack *S, char *data);

extern char *Pop(Stack *S);
