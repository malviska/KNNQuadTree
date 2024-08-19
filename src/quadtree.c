#include"quadtree.h"
#include"priority_queue.h"

#include<math.h>
#include<stdlib.h>
#include<stdio.h>

double euclideanDistance(double x, double y, double px, double py){
  double result = sqrt(pow(x - px, 2) + pow(y - py, 2));

  return result;
}

void qtGenerateRecursive(Qt qt, addr_index root, addr_index indx){
  double x = qt->tree[root]->x;
  double y = qt->tree[root]->y;

  double x_new = qt->tree[indx]->x;
  double y_new = qt->tree[indx]->y;

  if(x_new>x && y_new>y){
    addr_ne ne = qt->tree[root]->ne;
    if(ne != -1){
      qtGenerateRecursive(qt, ne, indx);
    }else{
      qt->tree[root]->ne = indx;
    }
    return;
  }
  if(x_new<x && y_new>y){
    addr_nw nw = qt->tree[root]->nw;
    if(nw != -1){
      qtGenerateRecursive(qt, nw, indx);
    }else{
      qt->tree[root]->nw = indx;
    }
    return;
  }
  if(x_new>x && y_new<y){
    addr_se se = qt->tree[root]->se;
    if(se != -1){
      qtGenerateRecursive(qt, se, indx);
    }else{
      qt->tree[root]->se = indx;
    }
    return;
  }
  if(x_new<x && y_new<y){
    addr_sw sw = qt->tree[root]->sw;
    if(sw != -1){
      qtGenerateRecursive(qt, sw, indx);
    }else{
      qt->tree[root]->sw = indx;
    }
    return;
  }
}

void qtGenerate(Qt qt){
  ul size = qt->size;

  for(ul i = 1; i <size; i++){
    qtGenerateRecursive(qt, 0, i);
  }

}

Qt qtNew(ul size, Addr * addresses){
  Qt qt = malloc(sizeof(quadtree_t));
  qt->size = size;
  qt->tree = addresses;
  qtGenerate(qt);
  return qt;
}

void qtSmartSearch(Qt qt, double px, double py, addr_index root, PQ pq){
  double x = qt->tree[root]->x;
  double y = qt->tree[root]->y;

  addr_ne ne = qt->tree[root]->ne;
  addr_nw nw = qt->tree[root]->nw;
  addr_se se = qt->tree[root]->se;
  addr_sw sw = qt->tree[root]->sw;
  double distance = euclideanDistance(x, y, px, py);

  if(qt->tree[root]->active){
    pqInsert(pq, qt->tree[root], distance);
  }

  if(px>x && py>y){
    double nwBound = nw != -1 ? euclideanDistance(qt->tree[root]->x, py, px, py) : -1;
    double seBound = se != -1 ? euclideanDistance(px, qt->tree[root]->y, px, py) : -1;
    if(ne != -1){
      qtSmartSearch(qt, px, py, ne, pq);  
    }
    if(nwBound != -1 && nwBound < pq->queue[0]->distance){
      qtSmartSearch(qt, px, py, nw, pq);
    }
    if(seBound != -1 && seBound < pq->queue[0]->distance){
      qtSmartSearch(qt, px, py, se, pq);
    }
    if(sw != -1 && distance < pq->queue[0]->distance){
      qtSmartSearch(qt, px, py, sw, pq);
    }
    return;
  }
  if(px<x && py>y){
    double neBound = ne != -1 ? euclideanDistance(qt->tree[root]->x, py, px, py) : -1;
    double swBound = sw != -1 ? euclideanDistance(px, qt->tree[root]->y, px, py) : -1;
    if(nw != -1){
      qtSmartSearch(qt, px, py, nw, pq);
    }
    if(neBound != -1 && neBound < pq->queue[0]->distance){
      qtSmartSearch(qt, px, py, ne, pq);
    }
    if(swBound != -1 && swBound < pq->queue[0]->distance){
      qtSmartSearch(qt, px, py, sw, pq);
    }
    if(se != -1 && distance < pq->queue[0]->distance){
      qtSmartSearch(qt, px, py, se, pq);
    }
    return;
  }
  if(px>x && py<y){
    double swBound = sw != -1 ? euclideanDistance(qt->tree[root]->x, py, px, py) : -1;
    double neBound = ne != -1 ? euclideanDistance(px, qt->tree[root]->y, px, py) : -1;
    if(se != -1){
      qtSmartSearch(qt, px, py, se, pq);
    }
    if(neBound != -1 && neBound < pq->queue[0]->distance){
      qtSmartSearch(qt, px, py, ne, pq);
    }
    if(swBound != -1 && swBound < pq->queue[0]->distance){
      qtSmartSearch(qt, px, py, sw, pq);
    }
    if(nw != -1 && distance < pq->queue[0]->distance){
      qtSmartSearch(qt, px, py, nw, pq);
    }
    return;
  }
  if(px<x && py<y){
    double seBound = se != -1 ? euclideanDistance(qt->tree[root]->x, py, px, py) : -1;
    double nwBound = nw != -1 ? euclideanDistance(px, qt->tree[root]->y, px, py) : -1;
    if(sw != -1){
      qtSmartSearch(qt, px, py, sw, pq);
    }
    if(seBound != -1 && seBound < pq->queue[0]->distance){
      qtSmartSearch(qt, px, py, se, pq);
    }
    if(nwBound != -1 && nwBound < pq->queue[0]->distance){
      qtSmartSearch(qt, px, py, nw, pq);
    }
    if(ne != -1 && distance < pq->queue[0]->distance){
      qtSmartSearch(qt, px, py, ne, pq);
    }
    return;
  }
}

void qtDumbSearch(Qt qt, PQ pq, addr_index root, double px, double py, int n){
  if(root < 0){
    return;
  }
  if(pq->size == n){
    qtSmartSearch(qt, px, py, root, pq);
    return;
  }
  addr_ne ne = qt->tree[root]->ne;
  addr_nw nw = qt->tree[root]->nw;
  addr_se se = qt->tree[root]->se;
  addr_sw sw = qt->tree[root]->sw;
  double distance = euclideanDistance(qt->tree[root]->x, qt->tree[root]->y, px, py);
  if(qt->tree[root]->active){
    pqInsert(pq, qt->tree[root], distance);
  }
  qtDumbSearch(qt, pq, ne, px, py, n);
  qtDumbSearch(qt, pq, nw, px, py, n);
  qtDumbSearch(qt, pq, se, px, py, n);
  qtDumbSearch(qt, pq, sw, px, py, n);
}

PQ qtKNN(Qt qt, double px, double py, int n){
  PQ pq = pqNew(n);
  qtDumbSearch(qt, pq, 0, px, py, n);

  return pq;
}

void qtDestroy(Qt qt){
  free(qt);
}