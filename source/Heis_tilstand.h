#pragma once
#include <stdbool.h>

extern volatile int etasje_tilstand;
extern volatile int sist_etasje;   
extern volatile int retning;                             // etasjen heisen er i eller forrige etasje dersom heisen er i bevegelse

int er_i_neste_etasje(int sist_etasje, int neste_stopp, int etasje_tilstand);    // sjekekr om etasje == neste_stopp



