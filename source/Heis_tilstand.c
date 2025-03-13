#include "Heis_tilstand.h"

volatile int etasje_tilstand = 0;   // -1 : mellom etasjer  | 0 : 1. etasje  | 1 : 2. etasje osv
volatile int sist_etasje = 0;
extern volatile int retning=0;  // -1 : kjører ned  |  0 : står i ro  |  1 : kjører opp


int er_i_neste_etasje(int sist_etasje, int neste_stopp, int etasje_tilstand) {
    if (sist_etasje == neste_stopp && etasje_tilstand != -1) {
        return 1;
    } else {
        return 0;
    }
}

