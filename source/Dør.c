#include "Dør.h"


// starter 3 sekunder nedtelling. int stoppmodus sier om funksjonen kalles pga. stoppknapp
void start_nedtelling(Kø *aKø) {
  int i=0;                                              // hjelpevariabel for hakkete heis
  time_t start_tid = time(NULL);                        // start tid    


  // while løkke på 3 sekunder
  while (time(NULL) - start_tid < 3) {        
    heispanel_etasjetrykk(aKø);
    if (etasje_tilstand != -1) {elevio_doorOpenLamp(1);}          // døra skal åpnes så lenge den ikke er mellom etasjer når stoppknappen trykkes
    sett_lys(aKø, sist_etasje);
    
    i++;
    if (i%10 == 0) {
      printf("Dør åpen/nedtelling:\n");
    }

    // for at heisen ikke skal hakke nedover under obstruksjon
    if(i%10 == 0){
      if (elevio_obstruction()) { 
        start_nedtelling(aKø);
      }
    }

    if (elevio_stopButton()) { 
      printf("Stoppknapp trykket\n");
      elevio_motorDirection(DIRN_STOP);

      // skrur på lyset så lenge stoppknappen er inne
      elevio_stopLamp(1);
      tøm_kø(aKø);
      skru_av_alle_lys();
      start_nedtelling(aKø);
      elevio_stopLamp(0);
    } else {
      elevio_stopLamp(0);                             // skrur av stopplyset som skrus på i main
    }
  };

  elevio_doorOpenLamp(0);                             // skrur av lyset etter 3 sekunder
}

