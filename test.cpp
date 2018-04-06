/* system example : DIR */
#include <stdio.h>      /* printf */
#include <stdlib.h>     /* system, NULL, EXIT_FAILURE */

int main ()
{
  int i;
  printf ("Checking if processor is available...");
  if (system(NULL)) puts ("Ok");
    else exit (EXIT_FAILURE);
  printf ("Executing command ls...\n");
  i=system ("./hola > \"hola.txt\" ");
  printf ("The value returned was: %d.\n",i);
  return 0;
}