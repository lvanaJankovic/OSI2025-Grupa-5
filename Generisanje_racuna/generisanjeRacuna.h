#pragma once
#include <stdio.h>
#include <string.h>
#include "popust_napojnica.h"

#define MAX_STAVKI 50
#define MAX_NARUDZBI 50
#define MAX_MENI 50

typedef struct {
    int rb;
    char naziv[30];
    double cijena;
} Stavka;

typedef struct {
    int stoID;
    int stavke[MAX_STAVKI];
    int brojStavki;
    char stanje[20];
} Narudzba;
Stavka meni[MAX_MENI];
Narudzba narudzbe[MAX_NARUDZBI];
int brojStavkiMenija = 0;
int brojNarudzbi = 0;

int ucitajMeni(const char *imeFajla){
    FILE *f = fopen(imeFajla, "r");
    if (!f) return 0;
    char linija[256];
    brojStavkiMenija = 0;
    while (fgets(linija, sizeof(linija), f)) {
        if (sscanf(linija, "%d,%29[^,],%lf",
                   &meni[brojStavkiMenija].rb,
                   meni[brojStavkiMenija].naziv,
                   &meni[brojStavkiMenija].cijena) == 3) {
            brojStavkiMenija++;
        }
    }
    fclose(f);
    return 1;
}

int ucitajNarudzbe(const char *imeFajla) {
    FILE *f = fopen(imeFajla, "r");
    if (!f) {
        perror("Greska pri otvaranju fajla");
        return 0;
    }
    brojNarudzbi = 0;
    char linija[512];
    fgets(linija, sizeof(linija), f);
    while (fgets(linija, sizeof(linija), f)) {
        Narudzba *n = &narudzbe[brojNarudzbi];
        char stavkeStr[256];
        int stoID;
        if (sscanf(linija, "%d,%19[^,],%255[^\n]", &stoID, n->stanje, stavkeStr) == 3) {
            n->stoID = stoID;
            n->brojStavki = 0;
            char *p = stavkeStr;
            int len = strlen(p);
            if (p[0] == '[') p++;
            if (p[len - 1] == ']') p[len - 1] = '\0';
            int rb;
            while (sscanf(p, "%d", &rb) == 1 && n->brojStavki < MAX_STAVKI) {
                n->stavke[n->brojStavki++] = rb;
                char *q = strchr(p, ',');
                if (!q) break;
                p = q + 1;
            }
            brojNarudzbi++;
            if (brojNarudzbi >= MAX_NARUDZBI) break;
        }
    }
    fclose(f);
    return 1;
}
void sacuvajNarudzbe(const char *imeFajla) {
    FILE *f = fopen(imeFajla, "w");
    if (!f) {
        printf("Ne mogu otvoriti fajl za pisanje\n");
        return;
    }
    fprintf(f, "stoID,stanje,stavke\n");
    for(int i = 0; i < brojNarudzbi; i++){
        Narudzba *n = &narudzbe[i];
        fprintf(f, "%d,%s,[", n->stoID, n->stanje);
        for (int j = 0; j < n->brojStavki; j++) {
            fprintf(f, "%d", n->stavke[j]);
            if (j < n->brojStavki - 1) fprintf(f, ",");
        }
        fprintf(f, "]\n");
    }
    fclose(f);
}

double izracunajIznos(Narudzba *n){
    double suma = 0;
    for (int i = 0; i < n->brojStavki; i++) {
        for (int j = 0; j < brojStavkiMenija; j++) {
            if (meni[j].rb == n->stavke[i]) {
                suma += meni[j].cijena;
                break;
            }
        }
    }
    return suma;
}
void generisiRacun(){
    int indeksi[MAX_NARUDZBI];
    int brojSpremnih = 0;
    printf("\nStolovi sa spremnim narudzbama:\n");
    for (int i = 0; i < brojNarudzbi; i++) {
        if(strcmp(narudzbe[i].stanje, "spremna") == 0){
            printf(" - Sto %d\n", narudzbe[i].stoID);
            indeksi[brojSpremnih++] = i;
        }
    }
    if(brojSpremnih == 0) {
        printf("Trenutno nema spremnih narudzbi.\n");
        return;
    }
    int stoID;
    printf("\nUnesite ID stola: ");
    scanf("%d", &stoID);
    Narudzba *n = NULL;
    int indeks = -1;
    for(int i = 0; i < brojSpremnih; i++) {
        if(narudzbe[indeksi[i]].stoID == stoID) {
            n = &narudzbe[indeksi[i]];
            indeks = indeksi[i];
            break;
        }
    }
    if(!n) {
        printf("Neispravan izbor stola.\n");
        return;
    }
    double osnovniIznos = izracunajIznos(n);
    double popustProcenat, napojnicaIznos;
    double iznosNakonPopusta = dodajPopust(osnovniIznos, &popustProcenat);
    double iznosKonacni = dodajNapojnicu(iznosNakonPopusta, &napojnicaIznos);
    printf("\n----- PRIKAZ RACUNA -----\n");
    printf("Sto: %d\n\n", stoID);
    for (int i = 0; i < n->brojStavki; i++) {
    int rb = n->stavke[i];
    for (int j = 0; j < brojStavkiMenija; j++) {
        if (meni[j].rb == rb) {
            printf("%s - %.2f KM\n",
                   meni[j].naziv, meni[j].cijena);
            break;
        }
    }
}
   printf("\nOsnovni iznos: %.2f KM\n", osnovniIznos);
   printf("Popust: %.0f%%\n", popustProcenat);
   printf("Napojnica: %.2f KM\n", napojnicaIznos);
   printf("UKUPNO ZA PLACANJE: %.2f KM\n", iznosKonacni);
   char potvrda;
   printf("\nPotvrditi izdavanje racuna? (d/n): ");
   scanf(" %c", &potvrda);
   if (potvrda != 'd') {
    printf("Izdavanje racuna otkazano.\n");
    return;
    }
    int izborFormata;
    printf("\nIzaberite nacin cuvanja racuna:\n");
    printf("1. Tekstualni fajl (.txt)\n");
    printf("2. PDF fajl (.pdf)\n");
    printf("Izbor: ");
    scanf("%d", &izborFormata);
    char imeFajla[100];
     if (izborFormata == 2)
         sprintf(imeFajla, "racun_sto_%d.pdf", stoID);
     else
         sprintf(imeFajla, "racun_sto_%d.txt", stoID);
    FILE *f = fopen(imeFajla, "w");
    if (!f) { printf("Greska pri kreiranju racuna.\n"); return; }
    fprintf(f, "FISKALNI RACUN\nSto: %d\n\n", stoID);
    for (int i = 0; i < n->brojStavki; i++) {
        int rb = n->stavke[i];
        for (int j = 0; j < brojStavkiMenija; j++) {
            if (meni[j].rb == rb) {
                fprintf(f, "%s - %.2f KM\n", meni[j].naziv, meni[j].cijena);
                break;
            }
        }
    }
    fprintf(f, "\nOsnovni iznos: %.2f KM\n", osnovniIznos);
    fprintf(f, "Popust: %.0f%%\n", popustProcenat);
    fprintf(f, "Napojnica: %.2f KM\n", napojnicaIznos);
    fprintf(f, "UKUPNO ZA PLACANJE: %.2f KM\n", iznosKonacni);
    fclose(f);
    for (int i = indeks; i < brojNarudzbi - 1; i++)
        narudzbe[i] = narudzbe[i + 1];
    brojNarudzbi--;
    sacuvajNarudzbe("narudzbe.csv");
    printf("\nRacun uspjesno generisan i narudzba uklonjena iz sistema.\n");
}



