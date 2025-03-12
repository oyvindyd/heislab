#include "Dør.h"
#include "Heis_tilstand.h"
#include "Heiskontroller.h"


int main() {

  elevio_init();
  Kø aKø = {NULL, 0};                                     // initialiserer en tom kø
  volatile int stoppmodus = 0;                            // [KAN FJERNES]
  skru_av_alle_lys();
  go_to_default(aKø);
  
  printf("=== Example Program ===\n");
  printf("Press the stop button on the elevator panel to exit\n");
  int i=0;


  while (1) {
    if(!elevio_stopButton()){

      heispanel_etasjetrykk(&aKø);
      etasje_tilstand = elevio_floorSensor();
      neste_stopp = finn_neste_stopp(&aKø, sist_etasje, retning);
      
      // hvis obstruksjon - stopp motor og start nedtelling
      if (elevio_obstruction()) {
        elevio_motorDirection(DIRN_STOP);
        start_nedtelling(&aKø);
      }

      // setter sist_etasje til etasjen heisen er/var sist i. For å komme unna etasje_tilstand = -1
      if (etasje_tilstand != -1) {
        sist_etasje = etasje_tilstand;
      };

      sett_lys(&aKø, sist_etasje);
      kjører_til_neste_stopp(sist_etasje, neste_stopp, etasje_tilstand);

      // hvis kommet fram til neste etasje - kall fjern_etasje_fra_kø()
      if (er_i_neste_etasje(sist_etasje, neste_stopp, etasje_tilstand)) {
        fjern_etasjer_fra_kø(&aKø, sist_etasje);
        start_nedtelling(&aKø);
      }
      
      /*
      i++;
      if ((i%9)==0){
        printf("etasje: %d. Neste stopp: %d\n", sist_etasje, neste_stopp);
        printf("Kjøreretning: %d\n", retning);
        printf("Lengde kø: %d\n", aKø.lengde);
      }
        */

      nanosleep(&(struct timespec){0, 20 * 1000 * 1000}, NULL);

    } else{
      printf("Stoppknapp aktiv i main\n");
      elevio_motorDirection(DIRN_STOP);

      // skrur på stoppknapplyset så lenge knappen er inne
      elevio_stopLamp(1);
      tøm_kø(&aKø);
      skru_av_alle_lys();
      start_nedtelling(&aKø);

      elevio_stopLamp(0);
    }
  }
  return 0;
}
