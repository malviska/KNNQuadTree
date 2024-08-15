#include<stdbool.h>
#ifndef ADDRESS_H
#define ADDRESS_H

typedef struct {
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

}address_t, *Addr;

Addr addrNew(char * inded,
 long id_logrado,
 char * sigla_tipo,
 char * nome_logra,
 int numero_imo,
 char * nome_bairr,
 char * nome_regio,
 int cep,
 double x,
 double y);

#endif