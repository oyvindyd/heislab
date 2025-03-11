#pragma once
#include <stdbool.h>
#include "Kø.h"
#include "Heis_tilstand.h"
#include "driver/elevio.h"
#include <stdio.h>



typedef struct {
    bool etasje_lys1;
    bool etasje_lys2;
    bool etasje_lys3;
    bool etasje_lys4;
    bool stoppknapp_lys; 
} Heispanel_lys;

void heispanel_etasjetrykk(Kø *aKø);
void endre_tilstand_stoppmodus(Heistilstand *tilstand);


