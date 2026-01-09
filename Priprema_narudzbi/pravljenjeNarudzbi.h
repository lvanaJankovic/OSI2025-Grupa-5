#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
    if (!f) { perror("Greska pri otvaranju fajla"); return 0; }
    brojStavkiMenija = 0;
    char linija[256];
    while(fgets(linija, sizeof(linija), f)){
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
    if (!f) 
    {
        printf("Ne mogu otvoriti fajl za pisanje"); 
        return; 
    }
    fprintf(f, "stoID,stanje,stavke\n");
    for (int i = 0; i < brojNarudzbi; i++) {
        Narudzba *n = &narudzbe[i];
        fprintf(f, "%d,%s,[", n->stoID, n->stanje);
        for (int j = 0; j < n->brojStavki; j++){
            fprintf(f, "%d", n->stavke[j]);
            if (j < n->brojStavki - 1) fprintf(f, ",");
        }
        fprintf(f, "]\n");
    }
    fclose(f);
}
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
