#include"constants.h"
#include"map.h"

#include <string.h>
#include <stdlib.h>

ui hash(const char* key, int size) {
  /*
  DJB2 algorithm
  */
  ul hash = 5381;
  int c;
  while ((c = *key++)) {
      hash = ((hash << 5) + hash) + c; // hash * 33 + c
  }
  return hash % size;
}

Map mapCreate(int size){
  Map map = malloc(sizeof(map_t));
  map->size = size;
  map->table = malloc(sizeof(Cell) * size);

  for(int i = 0; i<size; i++){
    map->table[i] = NULL;
  }

  return map;
}

void mapInsert(Map map, char* key, Addr value){
  ui index = hash(key, map->size);
  Cell newCell = malloc(sizeof(cell_t));
  newCell->key = key;
  newCell->address = value;
  newCell->next = NULL;

  if(map->table[index] == NULL){
    map->table[index] = newCell;
  }else{
    Cell current = map->table[index];
    Cell prev = NULL;
    while(current != NULL){
      if(strcmp(current->key, key) == 0){
        current->address = value;
        free(newCell->address);
        free(newCell);
        return;
      }
      prev = current;
      current = current->next;
    }
    prev->next = newCell;
  }

}
Addr mapGet(Map map, const char* key){
  ui index = hash(key, map->size);
  Cell current = map->table[index];
  while(current != NULL){
    if(strcmp(current->key, key) == 0){
      return current->address;
    }
    current = current->next;
  }

  return NULL;
}
void mapFree(Map map){
  /*
  In this free I only free the variables not used in other applications
  */
  for(int i = 0; i<map->size; i++){
    Cell current = map->table[i];
    while(current != NULL){
      Cell aux = current;
      current = current->next;
      free(aux);
    }
  }
  free(map->table);
  free(map);
}