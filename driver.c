#include<stdio.h>
#include"lexer.h"
#include"parser.h"

int main()
{
  lexer();
  parser();
  ast();
  return 0;  
}
