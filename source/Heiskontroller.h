#pragma once
#include "driver/elevio.h"
#include "Kø.h"
#include "heispanel.h"
#include "Etasjepanel.h"
#include "driver/elevio.h"
#include <signal.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

void sett_lys(Kø *aKø, int etasje);
void kjører_til_neste_stopp(int etasje, int neste_stopp, int etasje_tilstand);

void skru_av_alle_lys();                                    
void go_to_default(Kø aKø);