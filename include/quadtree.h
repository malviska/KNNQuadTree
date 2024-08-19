#include"address.h"
#include"constants.h"
#include"priority_queue.h"
#ifndef QUADTREE_H
#define QUADTREE_H


typedef struct {
  ul size;
  Addr * tree;

}quadtree_t, *Qt;


Qt qtNew(ul size, Addr * addresses);
PQ qtKNN(Qt qt, double px, double py, int n);
void qtDestroy(Qt qt);

#endif