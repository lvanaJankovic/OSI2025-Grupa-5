#ifndef KONOBARI_STAT_H
#define KONOBARI_STAT_H

#define MAX_KONOBARA_STAT 20

typedef struct {
    int id;
    char ime[50];
    int stolovi;
    int narudzbe;
    float promet;
    int sati;
} KonobarStat;

typedef enum {
    DNEVNI = 1,
    MJESECNI,
    GODISNJI
} Period;

int ucitaj_konobare(KonobarStat k[]);
void ispis_konobara(KonobarStat k[], int n);
void obrada_podataka(KonobarStat k, Period p);

void pracenjeKonobara(); // funkcija koju poziva glavni meni

#endif
