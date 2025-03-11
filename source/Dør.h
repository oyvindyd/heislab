#pragma once
#include <stdbool.h>
#include <time.h>
#include "Heis_tilstand.h"
#include <stdio.h>
#include "Kø.h"
#include "heispanel.h"

extern volatile int dør_åpen;


void start_nedtelling(Kø *aKø, int* p_stoppknapp);
