#include "heispanel.h"

// lager alle etasjer {e, etasjenummer, retning}: e-etasje, 0/1/2/3-etasjenummer, o/n/b-opp/ned/blank
Etasje e0b = {0, 0};
Etasje e1b = {1, 0};
Etasje e2b = {2, 0};
Etasje e3b = {3, 0};

Etasje e0o = {0, 1};
Etasje e1o = {1, 1};
Etasje e2o = {2, 1};

Etasje e1n = {1, -1};
Etasje e2n = {2, -1};
Etasje e3n = {3, -1};

// kalles i main-loopen - dersom en etasje i heispanelet er trykket, kalles legg_til_etasje 
void heispanel_etasjetrykk(Kø *aKøPtr) {
    // heispanel
    if (elevio_callButton(0, BUTTON_CAB)) {legg_til_etasje_i_kø(aKøPtr, e0b);};
    if (elevio_callButton(1, BUTTON_CAB)) {legg_til_etasje_i_kø(aKøPtr, e1b);};
    if (elevio_callButton(2, BUTTON_CAB)) {legg_til_etasje_i_kø(aKøPtr, e2b);};
    if (elevio_callButton(3, BUTTON_CAB)) {legg_til_etasje_i_kø(aKøPtr, e3b);};

    // etasjepanel opp
    if (elevio_callButton(0, BUTTON_HALL_UP)) {legg_til_etasje_i_kø(aKøPtr, e0o);};
    if (elevio_callButton(1, BUTTON_HALL_UP)) {legg_til_etasje_i_kø(aKøPtr, e1o);};
    if (elevio_callButton(2, BUTTON_HALL_UP)) {legg_til_etasje_i_kø(aKøPtr, e2o);};

    // etasjepanel ned
    if (elevio_callButton(1, BUTTON_HALL_DOWN)) {legg_til_etasje_i_kø(aKøPtr, e1n);};
    if (elevio_callButton(2, BUTTON_HALL_DOWN)) {legg_til_etasje_i_kø(aKøPtr, e2n);};
    if (elevio_callButton(3, BUTTON_HALL_DOWN)) {legg_til_etasje_i_kø(aKøPtr, e3n);};

    //printf("Lengde %d\n", aKøPtr->lengde);
};

