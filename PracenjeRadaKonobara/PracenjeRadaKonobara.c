#include <stdio.h>
#include <stdlib.h>


#define MAX 20
#define BAZA "konobari.txt"


typedef struct {
    int id;
    char ime[50];
    int stolovi;
    int narudzbe;
    float promet;
    int sati;
} Konobar;


typedef enum {
    DNEVNI = 1,
    MJESECNI,
    GODISNJI
} Period;


int ucitaj_konobare(Konobar k[]) {
    FILE *f = fopen(BAZA, "r");
    int n;

    if (f == NULL) {
        printf("Greska pri otvaranju fajla %s!\n", BAZA);
        exit(1);
    }

    fscanf(f, "%d", &n);

    for (int i = 0; i < n; i++) {
        fscanf(f, "%d %s %d %d %f %d",
               &k[i].id,
               k[i].ime,
               &k[i].stolovi,
               &k[i].narudzbe,
               &k[i].promet,
               &k[i].sati);
    }

    fclose(f);
    return n;
}

void ispis_konobara(Konobar k[], int n) {
    printf("\nLista konobara:\n");
    for (int i = 0; i < n; i++) {
        printf("%d. %s\n", i + 1, k[i].ime);
    }
}


float faktor_perioda(Period p) {
    if (p == DNEVNI) return 1.0f / 30.0f;
    if (p == GODISNJI) return 12.0f;
    return 1.0f; // mjesecni
}


void obrada_podataka(Konobar k, Period p) {
    int izbor;
    float faktor = faktor_perioda(p);

    printf("\nPodaci za konobara: %s\n", k.ime);

    printf("\nIzaberite vrstu podataka:\n");
    printf("1. Broj usluzenih stolova\n");
    printf("2. Broj narudzbi\n");
    printf("3. Ostvareni promet\n");
    printf("4. Radno vrijeme\n");
    printf("Izbor: ");
    scanf("%d", &izbor);

    printf("\n--- Filtrirani podaci ---\n");

    switch (izbor) {
        case 1:
            printf("Broj usluzenih stolova: %.0f\n", k.stolovi * faktor);
            break;
        case 2:
            printf("Broj narudzbi: %.0f\n", k.narudzbe * faktor);
            break;
        case 3:
            printf("Ostvareni promet: %.2f KM\n", k.promet * faktor);
            break;
        case 4:
            printf("Radno vrijeme: %.0f sati\n", k.sati * faktor);
            break;
        default:
            printf("Pogresan izbor.\n");
    }
}
