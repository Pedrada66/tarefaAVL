#include <stdio.h>
#include "bst.h"
#include "bst.c" // mudanca

int main () {
  Tree t = createTree();
  link x;
  AVLinsert(t, 10);
  AVLinsert(t, 4);
  AVLinsert(t, 20);
  AVLinsert(t, 11); 
  AVLinsert(t, 14);
  
  // Reduzir os varios imprime a somente um
  imprime(t, "oi");

  return 0;
}
