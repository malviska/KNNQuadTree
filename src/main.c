#include"constants.h"
#include"map.h"
#include"address.h"

#include<stdio.h>
#include<stdlib.h>

/*
char * idend;
  long id_logrado;
  char * sigla_tipo;
  char * nome_logra;
  int numero_imo;
  char * nome_bairr;
  char * nome_regio;
  int cep;
  double x;
  double y;
  bool active;

 */

int main(int argc, char ** argv){

  FILE * file = fopen("/home/mak/hw-2024-01/estrutura_de_dados/tp3/geracarga.base", "r");

  if(file == NULL){
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }
  char BUFFER[1000];
  int entrys = 0;
  if(fgets(BUFFER, sizeof(BUFFER), file) != NULL){
    sscanf(BUFFER, "%d", &entrys);
  }
  Map map = mapCreate(entrys);
  Addr * addresses = malloc(sizeof(Addr)*entrys);
  for(int i = 0; i< entrys; i++){
    addresses[i] = NULL;
  }
  int i = 0;
  while(i < entrys && fgets(BUFFER, sizeof(BUFFER), file) != NULL){
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
    cep, x, y);
    addresses[i] = address;
    mapInsert(map, idend, address);
    i++;
  }

  Addr val = mapGet(map, "02229400211");
  printf("%s\n", val->nome_logra);
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
  fclose(file);

  return 0;

}