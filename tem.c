/* strtok example */
#include <stdio.h>
#include <string.h>

int main ()
{
  char str[100];// ="- This, a sample string.";
  FILE *f = fopen("grammar.txt","r");
  fgets(str,100,f);
  char * pch;
  //printf ("Splitting string \"%s\" into tokens:\n",str);
  int count=0;
  pch = strtok (str, " \n");
  while (pch != NULL)
  {
    count++;
    printf("%s %d\n",pch,count);
    pch = strtok (NULL, " \n");
  }
  return 0;
}
