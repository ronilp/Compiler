// Team number 38
// MOHIT GUPTA (2012A7PS021P)
// RONIL PANCHOLIA (2012C6PS629P)

#include <stdio.h>
#include "lexer.h"
#include "parser.h"

int main()
{
  lexer();
  symbolTable();
  parser();
  ast();
  return 0;  
}
