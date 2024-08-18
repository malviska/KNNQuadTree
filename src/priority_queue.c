#include<stdlib.h>
#include<stdio.h>
#include"priority_queue.h"

int getAncestor(PQ pq, int pos){
  int ancestor = (pos-1)/2;
  return (ancestor >= 0) ? ancestor : -1;
}

int getLeft(PQ pq, int pos, ul size){
  int left = 2*pos+1;
  return (left < size) ? left :  -1;
}

int getRight(PQ pq, int pos, ul size){
  int right = 2*pos+2;
  return (right < size) ? right : -1;
}

Node nodeNew(Addr address, double distance){
  Node node = malloc(sizeof(node_t));
  node->address = address;
  node->distance = distance;

  return node;
}

PQ pqNew(ul sizeMax){
  PQ pq = malloc(sizeof(priority_queue_t));
  pq->size = 0;
  pq->capacity = sizeMax;
  pq->queue = malloc(sizeof(Node)*(sizeMax+1));
  for(int i = 0; i<sizeMax+1; i++){
    pq->queue[i] = NULL;
  }

  return pq;
}

void pqInsert(PQ pq, Addr address, double distance){
  ul pos = pq->size;
  pq->queue[pos] = nodeNew(address, distance);
  int ancestor = getAncestor(pq, pos);
  Node aux;
  while(ancestor != -1 && pq->queue[ancestor]->distance < pq->queue[pos]->distance){
    aux = pq->queue[ancestor];
    pq->queue[ancestor] = pq->queue[pos];
    pq->queue[pos] = aux;
    pos = ancestor;
    ancestor = getAncestor(pq, pos);
  }
  aux = NULL;
  pq->size++;
  if(pq->size > pq->capacity){
    Node nd = pqRemove(pq);
    free(nd);
  }
}

Node pqRemove(PQ pq){
  Node nd = pq->queue[0];
  pq->queue[0] = pq->queue[pq->size -1];
  pq->queue[pq->size -1] = NULL;
  pq->size--;
  int pos = 0;
  int tst;
  int left = getLeft(pq, pos, pq->size);
  int right = getRight(pq, pos, pq->size);
  Node aux;
  while(left != -1 || right != -1){
    if(right == -1){
      tst = left;
    }else if(left == -1){
      tst = right;
    }else if(pq->queue[right]->distance > pq->queue[left]->distance){
      tst = right;
    }else{
      tst = left;
    }
    if(pq->queue[pos]->distance < pq->queue[tst]->distance){
      aux = pq->queue[pos];
      pq->queue[pos] = pq->queue[tst];
      pq->queue[tst] = aux;
      pos = tst;
    }else{
      break;
    }
    left = getLeft(pq, pos, pq->size);
    right = getRight(pq, pos, pq->size);
  }
  aux = NULL;

  return nd;
}

void pqHeapfy(PQ pq, ul root, ul size){
  int pos = root;
  int tst;
  int left = getLeft(pq, pos, size);
  int right = getRight(pq, pos, size);
  Node aux;
  while(left != -1 || right != -1){
    if(right == -1){
      tst = left;
    }else if(left == -1){
      tst = right;
    }else if(pq->queue[right]->distance > pq->queue[left]->distance){
      tst = right;
    }else{
      tst = left;
    }
    if(pq->queue[pos]->distance < pq->queue[tst]->distance){
      aux = pq->queue[pos];
      pq->queue[pos] = pq->queue[tst];
      pq->queue[tst] = aux;
      pos = tst;
    }else{
      break;
    }
    left = getLeft(pq, pos, size);
    right = getRight(pq, pos, size);
  }
  aux = NULL;
}

void pqHeapSort(PQ pq){
  int t = pq->size -1;
  Node aux;
  while(t>0){
    aux = pq->queue[t];
    pq->queue[t] = pq->queue[0];
    pq->queue[0] = aux;
    t -=1;
    pqHeapfy(pq, 0, t);
  }
}

void pqDump(PQ pq){
  pqHeapSort(pq);
  for(int i = 0; i<pq->size; i++){
    printAddress(pq->queue[i]->address);
    printf(" (%.3lf)", pq->queue[i]->distance);
    printf("\n");
  }
}

void pqDestroy(PQ pq){
  /*
   Free only the Node pointers, Address is used by other applications
  */
  for(ul i = 0; i<pq->size; i++){
    free(pq->queue[i]);
  }
  free(pq->queue);
  free(pq);
}










