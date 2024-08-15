
#include"constants.h"
#include"address.h"
#ifndef MAP_H
#define MAP_H

typedef struct{
  char * key;
  Addr address;
  struct cell_t * next; // point to the next cell in case of colision

} cell_t, *Cell;

typedef struct {
  Cell * table;
  int size;

}map_t, *Map;

Map mapCreate(int size);
void mapInsert(Map map, char* key, Addr value);
Addr mapGet(Map map, const char* key);
void mapFree(Map map);


#endif