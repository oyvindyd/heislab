#include "Dør.h"
#include "Heis_tilstand.h"
#include "Heiskontroller.h"


int main() {
  int stoppknapp_i_etasje = 0;                            // variabel som brukes dersom man trykker på stoppknappen i en etasje
  int *p_stoppknapp = &stoppknapp_i_etasje;

  elevio_init();
  Kø aKø = {NULL, 0};                                   // initialiserer en tom kø
  Heistilstand heistilstand = står_stille_i_etasje;     // initialiserer heistilstanden
  skru_av_alle_lys();
  go_to_default(aKø);
  
  printf("=== Example Program ===\n");
  printf("Press the stop button on the elevator panel to exit\n");
  int i=0;


  while (1) {
    if(!elevio_stopButton() || !stoppknapp_i_etasje){

    heispanel_etasjetrykk(&aKø);
    etasje_tilstand = elevio_floorSensor();
    neste_stopp = finn_neste_stopp(&aKø, sist_etasje, retning);
    
    if (elevio_obstruction()) {
      heistilstand = obstruksjon;
      elevio_motorDirection(DIRN_STOP);
      start_nedtelling(&aKø, p_stoppknapp);
    }

    
    // setter sist_etasje til etasjen heisen er/var sist i. For å komme unna etasje_tilstand = -1
    if (etasje_tilstand != -1) {
      sist_etasje = etasje_tilstand;
    };

    sett_lys(&aKø, sist_etasje, dør_åpen);


    kjører_til_neste_stopp(sist_etasje, neste_stopp, etasje_tilstand);
    // hvis kommet fram til neste etasje - kall fjern_etasje_fra_kø()
    if (er_i_neste_etasje(sist_etasje, neste_stopp, etasje_tilstand)) {
      heistilstand = står_stille_i_etasje;
      fjern_etasjer_fra_kø(&aKø, sist_etasje);
      start_nedtelling(&aKø, p_stoppknapp);
      
    }
    
    /*
    if ((i%9)==0){
      printf("etasje: %d. Neste stopp: %d\n", sist_etasje, neste_stopp);
      printf("Kjøreretning: %d\n", retning);
      printf("Lengde kø: %d\n", aKø.lengde);
    }
      */
    i++;

    nanosleep(&(struct timespec){0, 20 * 1000 * 1000}, NULL);

  } else{
    printf("Hei stoppknapp i etasje\n");
    elevio_motorDirection(DIRN_STOP);
    heistilstand = stoppmodus;
    tøm_kø(&aKø);

    if (!stoppknapp_i_etasje) {
      start_nedtelling(&aKø, p_stoppknapp);
    }

    stoppknapp_i_etasje = 0;

  }


  }
  return 0;
}
