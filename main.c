#include <stdio.h>
#include "bst.h"
#include "bst.c" // mudanca

int main () {
  Tree t = createTree();
  link x;
  insert(t, 99);
  insert(t, 88);
  insert(t, 77);
  //insert(t, 66);
  AVLinsert(t, 66);
  
  // Reduzir os varios imprime a somente um
  imprime(t, "oi");

  return 0;
}
