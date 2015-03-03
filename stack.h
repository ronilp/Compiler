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
