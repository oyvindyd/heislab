#include "Dør.h"

volatile int dør_åpen = 0;


// PROBLEM: hele programmet går i en "pause" i denne while løkka, som gjør at man ikke kan
// legge til nye etasjer i køen osv...
void start_nedtelling(Kø *aKø, int* p_stoppknapp) {
  int i=0;
  time_t start_tid = time(NULL);
  while (time(NULL) - start_tid < 3) {
    i++;
    heispanel_etasjetrykk(aKø);
    dør_åpen = 1;
    printf("Dør åpen: %d\n", dør_åpen);
    elevio_doorOpenLamp(1);

    // for at heisen ikke skal hakke nedover under obstruksjon
    if(i%10 == 0){
      if (elevio_obstruction()) { 
        start_nedtelling(aKø, p_stoppknapp);
      }
    }

    if (elevio_stopButton()) { 
      *p_stoppknapp = 1;
      printf("Stoppknapp trykket\n");
      elevio_motorDirection(DIRN_STOP);
      start_nedtelling(aKø, p_stoppknapp);
    }

  };

  elevio_doorOpenLamp(0);

  dør_åpen = 0;
}

