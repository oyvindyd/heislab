#include "Dør.h"
#include "Heis_tilstand.h"
#include "Heiskontroller.h"


int main() {

  elevio_init();
  Kø aKø = {NULL, 0};                                     // initialiserer en tom kø
  skru_av_alle_lys();
  go_to_default(aKø);

  // fikser bug der stoppknappen veksler mellom 0 og 1 selvom den holdes inne. 
  
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
      
      nanosleep(&(struct timespec){0, 20 * 1000 * 1000}, NULL);

    } else{
      elevio_motorDirection(DIRN_STOP);

      // skrur på stoppknapplyset så lenge knappen er inne
      elevio_stopLamp(1);
      tøm_kø(&aKø);
    
      // skrur av alle lysene utenom dør åpen hvis man er i en etasje
      if (etasje_tilstand != -1) {
        skru_av_etasjelys();
      } else {
        skru_av_alle_lys();
      }

      start_nedtelling(&aKø);
      elevio_stopLamp(0);


      nanosleep(&(struct timespec){0, 20 * 1000 * 1000}, NULL);
    }
  } 
  return 0;
}
