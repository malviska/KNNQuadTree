#include"address.h"
#ifndef QUADTREE_H
#define QUADTREE_H

typedef struct {
  int capacity;
  int size;
  Addr * tree;

}quadtree_t, *Qt;


Qt qtNew(int capacity, Addr * adresses);
Addr * qtNearest(Qt qt, double x, double y, int quantity);
void qtInsert(Qt qt, Addr address);
void qtResize(Qt quadTree);
Addr qtRemove(Qt quadTree);

#endif