#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include"../Kreiranje_narudzbi/KreiranjeNarudzbi.h"
#include"../Generisanje_racuna/generisanjeRacuna.h"


void prikaziAktivneNarudzbe(){
    printf("\n--- Aktivne narudzbe ---\n");
    for (int i = 0; i < brojNarudzbi; i++) {
        Narudzba *n = &narudzbe[i];
         if (strcmp(n->stanje, "spremna") == 0)
            continue;
        printf("Sto %d (%s): [", n->stoID, n->stanje);
        for (int j = 0; j < n->brojStavki; j++) {
            int rb = n->stavke[j];
            for (int k = 0; k < brojStavkiMenija; k++) {
                if (meni[k].rb == rb) {
                    printf("%s", meni[k].naziv);
                    break;
                }
            }
            if (j < n->brojStavki - 1) printf(", ");
        }
        printf("]\n");
    }
}
void pripremiNarudzbu(){
    int stoID;
    printf("Unesite ID stola narudzbe koju pripremate: ");
    scanf("%d", &stoID);
    int nadjena = 0;
    for (int i = 0; i < brojNarudzbi; i++) {
        if (narudzbe[i].stoID == stoID && strcmp(narudzbe[i].stanje, "u pripremi") == 0) {
            strcpy(narudzbe[i].stanje, "spremna");
            printf("Narudzba za sto %d je sada SPREMNA!\n", stoID);
            nadjena = 1;
            sacuvajNarudzbe("narudzbe.csv");
            break;
        }
    }
    if (!nadjena) printf("Narudzba nije aktivna ili ne postoji.\n");
}
