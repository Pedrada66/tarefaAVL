#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

int id = 0;
link novoNo (int item, link l, link r) {
  link t = malloc(sizeof(struct node));
  t->item = item;
  t->l = l;
  t->r = r;
  t->N = 1;
  t->id = id++;
  return t;
}
Tree createTree(){
  Tree t = malloc (sizeof (struct tree));
  t->z = malloc (sizeof(struct node));
  t->head = t->z;
  t->z->l = t->z;
  t->z->N = 0;
  t->z->r = t->z;
  return t;
}

link rotR (Tree t, link h) {
  link x = h->l;
  h->l = x->r;
  x->r = h;
  return x;
}

link rotL (Tree t, link h) {
  link x = h->r;
  h->r = x->l;
  x->l = h;
  return x;
}

link searchR(Tree t, link h, int query) {
  if (h == t->z) {
    return NULL;
  }
  if(h->item == query) 
    return h;
  if (h->item >= query) 
    return searchR(t, h->l, query);
  return searchR(t, h->r, query);
} 


link search (Tree t, int query){
   return searchR(t, t->head, query);
}

link insertR (Tree t, link h, link n) {
  if (h == t->z) {
    return  n;
  }

  if(h->item >= n->item)
    h->l = insertR(t, h->l, n);
  else 
    h->r = insertR(t, h->r, n);
  (h->N)++;
  return h;
}

link insert (Tree t, int item){
  if(t->head == t->z) {
    return (t->head =novoNo(item, t->z, t->z));
  }
  return insertR(t, t->head, novoNo(item, t->z, t->z));
}

void imprimeEmOrdem (Tree t, link h){
  if(h == t->z) return;
  imprimeEmOrdem (t, h->l);
  printf("<chave: %d N: %d>", h->item, h->N); 
  imprimeEmOrdem (t, h->r);
}

void imprimePosOrdem (Tree t, link h){
  if(h == t->z) return;
  imprimePosOrdem (t, h->l);
  imprimePosOrdem (t, h->r);
  printf("<chave: %d N: %d>", h->item, h->N); 
}
void imprimePreOrdem (Tree t, link h, int k) {
  if(h == t->z) return;
  int i; //mudanca
  for(i = 0; i <= k; i++)
    printf (" . ");
  printf("<chave: %d N: %d>\n", h->item, h->N); 
  imprimePreOrdem (t, h->l, k + 1); 
  imprimePreOrdem (t, h->r, k + 1);
}


void printnode (char  *x, int h) {
    int i;
    for(i = 0; i < h; i++)
        printf("\t");
    printf("%s\n", x);
}
int c = 0;
void imprimeR(Tree a, link t){
    char s[255];
    if(t==a->z) { return;}
    imprimeR(a,t->r);
    printf ("%d [ label = \"<f0>| <f1> %d (%d) | <f2>\" ]\n", t->id, t->item, t->N);
    if(t->l != a->z){
        printf("%d:f0->%d:f1;\n", t->id, t->l->id);
    } else {
        printf("z%d [ shape=point ];\n", c);
        printf("%d:f0->z%d;\n", t->id, c);
        c++;
    }
    if(t->r != a->z){
        printf("%d:f2->%d:f1;\n", t->id, t->r->id);
    } else {
        printf("z%d [ shape=point ];\n", c);
        printf("%d:f2->z%d;\n", t->id, c );
        c++;
    }
    imprimeR(a,t->l);
}
void imprime(Tree a, char *s) {
    c = 0;
    printf("digraph %s {\n", s);
    printf ("node [shape=record,style=rounded, height=.1]\n");
    imprimeR(a, a->head);
    printf("}\n");
}
void imprimeFromNode(Tree a, link h, char *s) {
  c = 0;
  printf("digraph  {\n" );
  printf ("name [label = \"%s\",shape=plaintext]\n", s);
  printf ("node [shape=record,style=rounded, height=.1]\n");
  imprimeR(a, h);
  printf("}\n");
}

link AVLinsertR(Tree t, link h, int item){
    if (h == t->z) {
    return novoNo(item, t->z, t->z);
  }

  if (item < h->item) {
    h->l = AVLinsertR(t, h->l, item);
  } else {
    h->r = AVLinsertR(t, h->r, item);
  }

  // Atualize a altura (N) do nó corrente
  h->N = 1 + ((h->l->N > h->r->N) ? h->l->N : h->r->N);

  // Verifique o fator de equilíbrio do nó
  int balance = h->l->N - h->r->N;

  // Realize as rotações necessárias para manter o equilíbrio da árvore
  if (balance > 1) {
    if (item < h->l->item) {
      // Rotação simples direita
      return rotR(t, h);
    } else {
      // Rotação dupla esquerda-direita
      h->l = rotL(t, h->l);
      return rotR(t, h);
    }
  } else if (balance < -1) {
    if (item > h->r->item) {
      // Rotação simples esquerda
      return rotL(t, h);
    } else {
      // Rotação dupla direita-esquerda
      h->r = rotR(t, h->r);
      return rotL(t, h);
    }
  }
  return h;
}

// nova funcao
link AVLinsert(Tree t, int item) {
  t->head = AVLinsertR(t, t->head, item);
  return t->head;
}

