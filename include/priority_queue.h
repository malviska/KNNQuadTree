#include"constants.h"
#include"address.h"

#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

typedef struct {
  Addr address;
  double distance;

} node_t, *Node;

typedef struct{
  ul size;
  ul capacity;
  Node * queue;

}priority_queue_t, *PQ;


Node nodeNew(Addr address, double distance);
PQ pqNew(ul size);
void pqInsert(PQ pq, Addr address, double distance);
Node pqRemove(PQ pq);
void pqDestroy(PQ pq);
void pqDump(PQ pq);



#endif