#include"address.h"

#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>

Addr addrNew(char * inded,
 long id_logrado,
 char * sigla_tipo,
 char * nome_logra,
 int numero_imo,
 char * nome_bairr,
 char * nome_regio,
 int cep,
 double x,
 double y,
 addr_index index){
  Addr address = malloc(sizeof(address_t));
  address->idend = inded;
  address->sigla_tipo = sigla_tipo;
  address->nome_logra = nome_logra;
  address->numero_imo = numero_imo;
  address->nome_bairr = nome_bairr;
  address->nome_regio = nome_regio;
  address->cep = cep;
  address->x = x;
  address->y = y;
  address->active = true;
  address->index = index;
  address->ne = -1;
  address->nw = -1;
  address->se = -1;
  address->sw = -1;

  return address;
 }

 void printAddress(Addr addr){
  printf("%s %s, %d, %s, %s, %d",
   addr->sigla_tipo, addr->nome_logra, addr->numero_imo, addr->nome_bairr,
    addr->nome_regio, addr->cep);
 }