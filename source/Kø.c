#include "Kø.h"
#include <stdio.h>
#include <stdlib.h>

volatile int neste_stopp = 0;

int finn_neste_stopp(Kø *aKø, int sist_etasje, int kjøre_retning) {
  if (aKø == NULL || aKø->liste == NULL || aKø->lengde == 0)
    return -1;
  if (kjøre_retning == 0 && aKø->lengde == 1)
    return aKø->liste[0].etasje;

  if (kjøre_retning == 0 && aKø->lengde > 1) {
    if (sist_etasje < aKø->liste[0].etasje)
      kjøre_retning = 1;
    else
      kjøre_retning = -1;
  }

  int minste_avstand = 100;
  int neste_stopp = aKø->liste[0].etasje;
  int avstand = 0;

  for (int i = 0; i < aKø->lengde; i++) {
    if (kjøre_retning > 0) {
      if (((aKø->liste[i].retning == kjøre_retning) ||
           (aKø->liste[i].retning == 0)) &&
          (aKø->liste[i].etasje > sist_etasje)) {
        avstand = aKø->liste[i].etasje - sist_etasje;
        if (avstand < minste_avstand) {
          minste_avstand = avstand;
          neste_stopp = aKø->liste[i].etasje;
        }
      }
    }

    if (kjøre_retning < 0) {
      if (((aKø->liste[i].retning == kjøre_retning) ||
           (aKø->liste[i].retning == 0)) &&
          (aKø->liste[i].etasje < sist_etasje)) {
        avstand = sist_etasje - aKø->liste[i].etasje;
        // printf("avstand, %d\n", avstand);
        if (avstand < minste_avstand) {
          minste_avstand = avstand;
          neste_stopp = aKø->liste[i].etasje;
        }
      }
    }
  }

  return neste_stopp;
}

// tømmer hele køen
void tøm_kø(Kø *k) {
  if (k->liste != NULL) {
    free(k->liste);  // Frigjør minnet som er allokert til listen
    k->liste = NULL; // Nullstiller pekeren
  }
  k->lengde = 0; // Nullstiller lengden
}

// sjekker om en etasje ligger i køen
int etasje_finnes_i_kø(Kø *aKø, Etasje aEtasje) {
  for (int i = 0; i < aKø->lengde; i++) {
    if (aKø->liste[i].etasje == aEtasje.etasje &&
        aKø->liste[i].retning == aEtasje.retning) {
      return 1;
    }
  }
  return 0;
}

void legg_til_etasje_i_kø(Kø *aKø, Etasje aEtasje) {

  // filter for at ikke samme etasje legges inn flere ganger
  if (etasje_finnes_i_kø(aKø, aEtasje)) {
    return;
  } else {
    aKø->lengde++;

    aKø->liste = (Etasje *)realloc(
        aKø->liste,
        aKø->lengde *
            sizeof(Etasje)); // finner plass i minnet med plass til ant bytes
                             // fra der aKø->liste peker + ant etasjer ganget
                             // med etasjestørrelsen
    aKø->liste[aKø->lengde - 1] = aEtasje;
  }
}

void fjern_etasjer_fra_kø(Kø *aKø, int aEtasje) {

  // skrur av lyset til etasjen
  elevio_buttonLamp(aEtasje, BUTTON_CAB, 0);
  elevio_buttonLamp(aEtasje, BUTTON_HALL_DOWN, 0);
  elevio_buttonLamp(aEtasje, BUTTON_HALL_UP, 0);

  // lager plass til en ny liste. Her vil vi legge alle etasjene som ikke er
  // aEtasje
  Etasje *ny_liste = (Etasje *)malloc(aKø->lengde * sizeof(Etasje));
  int ny_lengde = 0;

  // går gjennom listen og legger de etasjene som IKKE er i aEtasje inn i den
  // nye listen
  for (int i = 0; i < aKø->lengde; i++) {
    if (aKø->liste[i].etasje != aEtasje) {
      ny_liste[ny_lengde] = aKø->liste[i];
      ny_lengde++;
    }
  }
  free(aKø->liste); // frigjør det gamle minnet vi ikke lenger har behov for
  aKø->liste = (Etasje *)realloc(
      ny_liste,
      ny_lengde *
          sizeof(Etasje)); // reallokerer minnet slik at aKø->liste peker til et
                           // nytt sted (sannsynligvis samme sted som ny_liste)
  aKø->lengde = ny_lengde;
}
