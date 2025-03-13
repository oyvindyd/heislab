#pragma once
#include "Kø.h"
#include "driver/elevio.h"
#include "heispanel.h"
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

void sett_lys(Kø *aKø, int etasje);
void kjører_til_neste_stopp(int etasje, int neste_stopp, int etasje_tilstand);

void skru_av_alle_lys();
void skru_av_etasjelys();
void go_to_default(Kø aKø);
