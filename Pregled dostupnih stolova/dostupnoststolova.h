#include <stdio.h>
#pragma once
#include"../Rezervisanje/rezervisanje.h"
#define MAX_KAPACITET_STOLA 16

void pregledDostupnihStolova(
        Sto stolovi[], int brojStolova,
        Rezervacija rezervacije[], int brojRezervacija,
        int dan, int mjesec, int godina,
        int sat, int minut,
        int brojGostiju){
    if(brojGostiju<=0 || brojGostiju>MAX_KAPACITET_STOLA){
        printf("Nevalidan broj gostiju.\n");
        return;
    }
    printf("\n=== PREGLED DOSTUPNIH STOLOVA ===\n");
    int postoji=0;
    for (int i=0; i<brojStolova; i++){
        if(stolovi[i].kapacitet < brojGostiju)continue;
        if(stoSlobodanUTerminu(rezervacije, brojRezervacija,
                               stolovi[i].id,
                               dan, mjesec, godina, sat, minut)){

            printf("Sto ID: %d | Kapacitet: %d\n",
                   stolovi[i].id, stolovi[i].kapacitet);
            postoji=1;
        }
    }
    if (!postoji){
        printf("Nema slobodnih stolova za trazeni termin.\n");
    }
}
