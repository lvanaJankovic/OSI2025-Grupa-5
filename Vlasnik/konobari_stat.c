#include <stdio.h>
#include "konobari_stat.h"

#define BAZA "konobari.txt"

int ucitaj_konobare(KonobarStat k[]) {
    FILE *f = fopen(BAZA, "r");
    int n;
    if (!f) { printf("Greska pri otvaranju fajla!\n"); return 0; }
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

void ispis_konobara(KonobarStat k[], int n) {
    printf("\nLista konobara:\n");
    for (int i = 0; i < n; i++)
        printf("%d. %s\n", i+1, k[i].ime);
}

float faktor_perioda(Period p) {
    if (p == DNEVNI) return 1.0f / 30.0f;
    if (p == GODISNJI) return 12.0f;
    return 1.0f; // mjesecni
}

void obrada_podataka(KonobarStat k, Period p) {
    int izbor;
    float faktor = faktor_perioda(p);
    printf("\nPodaci za konobara: %s\n", k.ime);
    printf("\nIzaberite vrstu podataka:\n");
    printf("1. Broj usluzenih stolova\n2. Broj narudzbi\n3. Ostvareni promet\n4. Radno vrijeme\nIzbor: ");
    scanf("%d", &izbor);
    switch (izbor) {
        case 1: printf("Broj usluzenih stolova: %.0f\n", k.stolovi*faktor); break;
        case 2: printf("Broj narudzbi: %.0f\n", k.narudzbe*faktor); break;
        case 3: printf("Ostvareni promet: %.2f KM\n", k.promet*faktor); break;
        case 4: printf("Radno vrijeme: %.0f sati\n", k.sati*faktor); break;
        default: printf("Pogresan izbor.\n");
    }
}

void pracenjeKonobara() {
    KonobarStat konobari[MAX_KONOBARA_STAT];
    int n = ucitaj_konobare(konobari);
    if(n==0){printf("Nema konobara.\n");return;}
    char nastavi;
    do {
        printf("\n=== PRACENJE RADA KONOBARA ===\n");
        ispis_konobara(konobari,n);
        int izbor;
        printf("\nIzaberite konobara: ");
        scanf("%d",&izbor);
        if(izbor<1||izbor>n){printf("Neispravan izbor!\n"); continue;}
        printf("\nIzaberite vremenski period:\n1. Dnevni\n2. Mjesecni\n3. Godisnji\nIzbor: ");
        Period p; scanf("%d",(int*)&p);
        obrada_podataka(konobari[izbor-1],p);
        printf("\nNastaviti pracenje? (d/n): ");
        scanf(" %c",&nastavi);
    } while(nastavi=='d'||nastavi=='D');
}
