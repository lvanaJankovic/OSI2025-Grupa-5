#pragma once
#include <stdio.h>
#include <string.h>

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
int brojStavkiMenija = 0;
Narudzba narudzbe[MAX_NARUDZBI];
int brojNarudzbi = 0;
int ucitajMeni(const char *imeFajla){
    FILE *f = fopen(imeFajla, "r");
    if (!f) {
        perror("Greska pri otvaranju fajla");
        return 0;
    }
    brojStavkiMenija = 0;
    char linija[256];
    while (fgets(linija, sizeof(linija), f)){
        int rb;
        double cijena;
        char naziv[30];
        if (sscanf(linija, "%d,%29[^,],%lf", &rb, naziv, &cijena) == 3){
            meni[brojStavkiMenija].rb = rb;
            strncpy(meni[brojStavkiMenija].naziv, naziv, 30);
            meni[brojStavkiMenija].naziv[29] = '\0';
            meni[brojStavkiMenija].cijena = cijena;
            brojStavkiMenija++;
            if (brojStavkiMenija >= MAX_MENI) break;
        }
    }
    fclose(f);
    return 1;
}
void ispisiMeni(){
    printf("\n--- MENI ---\n");
    for (int i = 0; i < brojStavkiMenija; i++) {
        printf("%d. %s - %.2f KM\n",
               meni[i].rb,
               meni[i].naziv,
               meni[i].cijena);
    }
}
int nadjiNarudzbu(int stoID){
    for (int i = 0; i < brojNarudzbi; i++) {
        if (narudzbe[i].stoID == stoID) {
            return i;
        }
    }
    return -1;
}
void kreirajNarudzbu(){
    int stoID;
    printf("\nUnesite ID stola/gosta: ");
    scanf("%d", &stoID);
    int index = nadjiNarudzbu(stoID);
    if (index == -1) {
        index = brojNarudzbi;
        narudzbe[index].stoID = stoID;
        narudzbe[index].brojStavki = 0;
        strcpy(narudzbe[index].stanje, "u pripremi");
        brojNarudzbi++;
    }
    ispisiMeni();
    int izbor;
    printf("Unosite RB stavke (0 za kraj): ");
    while (1) {
        scanf("%d", &izbor);
        if (izbor == 0)
            break;
        int validan = 0;
        for (int i = 0; i < brojStavkiMenija; i++){
            if (meni[i].rb == izbor) {
                validan = 1;
                break;
            }
        }
        if (!validan) {
            printf("Nepostojeca stavka! Pokusajte ponovo.\n");
            continue;
        }
        if (narudzbe[index].brojStavki < MAX_STAVKI) {
            narudzbe[index].stavke[narudzbe[index].brojStavki++] = izbor;
        } else {
            printf("Narudzba je puna, ne mozete dodati vise stavki.\n");
            break;
        }
    }
    printf("Narudzba uspjesno evidentirana. Stanje: %s\n",
           narudzbe[index].stanje);
}
void prikaziNarudzbu(){
    int stoID;
    printf("\nUnesite ID stola/gosta: ");
    scanf("%d", &stoID);
    int index = nadjiNarudzbu(stoID);
    if (index == -1) {
        printf("Ne postoji narudzba za sto sa ID %d.\n", stoID);
        return;
    }
    Narudzba *n= &narudzbe[index];
    printf("\n--- Narudzba za sto %d ---\n", stoID);
    double ukupno = 0.0;
    for (int i = 0; i < n->brojStavki; i++) {
        int rb = n->stavke[i];
        int pronadjeno = 0;
        for (int j = 0; j < brojStavkiMenija; j++) {
            if (meni[j].rb == rb) {
                printf("%s - %.2f KM\n", meni[j].naziv, meni[j].cijena);
                ukupno += meni[j].cijena;
                pronadjeno = 1;
                break;
            }
        }
        if (!pronadjeno) {
            printf("%d. Nepoznata stavka\n", rb);
        }
    }
    printf("Ukupno: %.2f KM\n", ukupno);
    printf("Stanje narudzbe: %s\n", n->stanje);
}
