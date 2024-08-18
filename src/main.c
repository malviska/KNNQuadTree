#include"constants.h"
#include"map.h"
#include"address.h"
#include"quadtree.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

void activate(Map map, char BUFFER[1000]){
  char order;
  char * id = malloc(sizeof(char) * 50);
  sscanf(BUFFER, "%c %s", &order, id);
  Addr addr = mapGet(map, id);
  bool active = addr->active;
  if(!active){
    addr->active = true;
    printf("Ponto de recarga %s ativado.\n", id);
  }else{
    printf("Ponto de recarga %s já estava ativo.\n", id);
  }
  free(id);
}

void deactivate(Map map, char BUFFER[1000]){
  char order;
  char * id = malloc(sizeof(char) * 50);
  sscanf(BUFFER, "%c %s", &order, id);
  Addr addr = mapGet(map, id);
  bool active = addr->active;
  if(active){
    addr->active = false;
    printf("Ponto de recarga %s desativado.\n", id);
  }else{
    printf("Ponto de recarga %s já estava desativado.\n", id);
  }
}

void nearestNeighbours(Qt qt, char BUFFER[1000]){
  char order;
  double px;
  double py;
  int locations;
  sscanf(BUFFER, "%c %lf %lf %d", &order, &px, &py, &locations);
  PQ pq = qtKNN(qt, px, py, locations);
  pqDump(pq);
}

int main(int argc, char ** argv){

  char * BASE = NULL;
  char * COMMANDS = NULL;
  int i = 0;
  while(i< argc){
    if(strcmp(argv[i], "-b") == 0){
      BASE = argv[++i];
    }else if(strcmp(argv[i], "-e") == 0){
      COMMANDS = argv[++i];
    }
    ++i;
  }

  if(BASE == NULL || COMMANDS == NULL){
    return 1;
  }

  FILE * base = fopen(BASE, "r");

  FILE * commands = fopen(COMMANDS, "r");

  if(base == NULL || commands == NULL){
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }
  char BUFFER[1000];
  int entrys = 0;
  if(fgets(BUFFER, sizeof(BUFFER), base) != NULL){
    sscanf(BUFFER, "%d", &entrys);
  }
  Map map = mapCreate(entrys);
  Addr * addresses = malloc(sizeof(Addr)*entrys);
  for(int i = 0; i< entrys; i++){
    addresses[i] = NULL;
  }
  i = 0;
  while(i < entrys && fgets(BUFFER, sizeof(BUFFER), base) != NULL){
    char * idend = malloc(sizeof(char) * 50);
    long id_logrado;
    char * sigla_tipo = malloc(sizeof(char) * 50);
    char * nome_logra = malloc(sizeof(char) * 50);
    int numero_imo;
    char * nome_bairr = malloc(sizeof(char) * 50);
    char * nome_regio = malloc(sizeof(char) * 50);
    int cep;
    double x;
    double y;
    sscanf(BUFFER, "%[^;];%ld;%[^;];%[^;];%d;%[^;];%[^;];%d;%lf;%lf", idend, &id_logrado, sigla_tipo,
    nome_logra, &numero_imo, nome_bairr, nome_regio, &cep, &x, &y);
    Addr address = addrNew(idend, id_logrado, sigla_tipo, nome_logra, numero_imo, nome_bairr, nome_regio,
    cep, x, y, i);
    addresses[i] = address;
    mapInsert(map, idend, address);
    i++;
  }
  Qt qt = qtNew(entrys, addresses);
  int ncomm;
  if(fgets(BUFFER, sizeof(BUFFER), commands) != NULL){
    sscanf(BUFFER, "%d", &ncomm);
  }
  int j = 0;
  while(j< ncomm && fgets(BUFFER, sizeof(BUFFER), commands) != NULL){
    char order;
    sscanf(BUFFER, "%c", &order);
    switch(order){
      case 'C':
        nearestNeighbours(qt, BUFFER);
        break;
      case 'D':
        deactivate(map, BUFFER);
        break;
      case 'A':
        activate(map, BUFFER);
        break;
    }
  }
  mapFree(map);
  for(int i = 0; i<entrys; i++){
    free(addresses[i]->idend);
    free(addresses[i]->sigla_tipo);
    free(addresses[i]->nome_logra);
    free(addresses[i]->nome_bairr);
    free(addresses[i]->nome_regio);
    free(addresses[i]);
  }
  free(addresses);
  fclose(base);

  return 0;

}