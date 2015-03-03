typedef struct ArrayStack{
  int capacity;
  int top;
  int *array;
}Stack;

void printStack(Stack *S);

Stack *createStack();

int isEmpty(Stack *S);

int isFull(Stack *S);

void deleteStack(Stack *S);

void doubleStack(Stack *S);

int Top(Stack *S);

void Push(Stack *S, int data);

int Pop(Stack *S);
