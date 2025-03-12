#pragma once
#include <stdlib.h>
#include "driver/elevio.h"

extern volatile int neste_stopp;                // extern fordi den deklareres i h fila, men defineres i en annen fil

typedef struct {
  int etasje;
  int retning;                                  // -1 nedover, 1 oppover, 0 ingen retning (for heispanelet)
} Etasje;

typedef struct{
    Etasje* liste;
    int lengde;
} Kø;


void legg_til_etasje_i_kø(Kø *aKø, Etasje aEtasje);
int etasje_finnes_i_kø(Kø *aKø, Etasje aEtasje);
void tøm_kø(Kø *aKø);
int finn_neste_stopp(Kø *aKø, int sist_etasje, int retning);
void fjern_etasjer_fra_kø(Kø *aKø, int aEtasje);


