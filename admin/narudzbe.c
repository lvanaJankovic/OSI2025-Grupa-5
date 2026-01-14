#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "narudzbe.h"

Stavka meni[MAX_MENI];
int brojStavkiMenija = 0;
Narudzba narudzbe[MAX_NARUDZBI];
int brojNarudzbi = 0;

int ucitajMeni(const char *imeFajla) {
    FILE *f = fopen(imeFajla, "r");
    if (!f) return 0;
    brojStavkiMenija = 0;
    while (fscanf(f, "%d,%29[^,],%lf\n",
           &meni[brojStavkiMenija].rb,
           meni[brojStavkiMenija].naziv,
           &meni[brojStavkiMenija].cijena) == 3) {
        brojStavkiMenija++;
    }
    fclose(f);
    return 1;
}

int ucitajNarudzbe(const char *imeFajla) {
    FILE *f = fopen(imeFajla, "r");
    if (!f) return 0;
    brojNarudzbi = 0;
    char linija[512];
    fgets(linija, sizeof(linija), f); // header
    while (fgets(linija, sizeof(linija), f)) {
        Narudzba *n = &narudzbe[brojNarudzbi];
        char stavkeStr[256];
        sscanf(linija, "%d,%19[^,],%ld,%255[^\n]",
               &n->stoID, n->stanje, &n->vrijeme, stavkeStr);
        n->brojStavki = 0;
        char *p = strtok(stavkeStr, "[],");

        while (p && n->brojStavki < MAX_STAVKI) {
            n->stavke[n->brojStavki++] = atoi(p);
            p = strtok(NULL, "[],");
        }
        brojNarudzbi++;
    }
    fclose(f);
    return 1;
}

void sacuvajNarudzbe(const char *imeFajla) {
    FILE *f = fopen(imeFajla, "w");
    fprintf(f, "stoID,stanje,vrijeme,stavke\n");
    for (int i = 0; i < brojNarudzbi; i++) {
        Narudzba *n = &narudzbe[i];
        fprintf(f, "%d,%s,%ld,[", n->stoID, n->stanje, n->vrijeme);
        for (int j = 0; j < n->brojStavki; j++) {
            fprintf(f, "%d", n->stavke[j]);
            if (j < n->brojStavki - 1) fprintf(f, ",");
        }
        fprintf(f, "]\n");
    }
    fclose(f);
}

void prikaziAktivneNarudzbe() {
    for (int i = 0; i < brojNarudzbi; i++) {
        if (strcmp(narudzbe[i].stanje, "spremna") != 0) {
            printf("Sto %d (%s)\n",
                   narudzbe[i].stoID,
                   narudzbe[i].stanje);
        }
    }
}

void pripremiNarudzbu() {
    int sto;
    scanf("%d", &sto);
    for (int i = 0; i < brojNarudzbi; i++) {
        if (narudzbe[i].stoID == sto) {
            strcpy(narudzbe[i].stanje, "spremna");
            sacuvajNarudzbe("narudzbe.csv");
            break;
        }
    }
}

void finansijskiIzvjestaj(time_t od, time_t do_) {
    double ukupno = 0;
    for (int i = 0; i < brojNarudzbi; i++) {
        if (narudzbe[i].vrijeme >= od && narudzbe[i].vrijeme <= do_) {
            for (int j = 0; j < narudzbe[i].brojStavki; j++) {
                for (int k = 0; k < brojStavkiMenija; k++) {
                    if (meni[k].rb == narudzbe[i].stavke[j])
                        ukupno += meni[k].cijena;
                }
            }
        }
    }
    printf("Ukupan promet: %.2f KM\n", ukupno);
}

void izvjestajNarudzbi(time_t od, time_t do_) {
    int broj = 0;
    for (int i = 0; i < brojNarudzbi; i++)
        if (narudzbe[i].vrijeme >= od && narudzbe[i].vrijeme <= do_)
            broj++;
    printf("Broj narudzbi: %d\n", broj);
}
