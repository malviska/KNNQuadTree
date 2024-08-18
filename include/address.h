#include<stdbool.h>
#ifndef ADDRESS_H
#define ADDRESS_H

typedef long addr_index;
typedef long addr_ne;
typedef long addr_nw;
typedef long addr_se;
typedef long addr_sw;

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
  addr_index index;
  addr_ne ne;
  addr_nw nw;
  addr_se se;
  addr_sw sw;

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
 double y,
 addr_index index);

void printAddress(Addr address);

#endif