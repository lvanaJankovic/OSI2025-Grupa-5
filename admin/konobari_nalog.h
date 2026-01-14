#ifndef KONOBARI_NALOG_H
#define KONOBARI_NALOG_H

#define MAX_KONOBARA_NALOG 50
#define BAZA_OSOBLJE "osoblje.txt"

typedef struct {
    int id;
    char ime[50];
    int aktivan;
} KonobarNalog;

extern KonobarNalog konobari[MAX_KONOBARA_NALOG];
extern int brojKonobara;

void ucitajKonobare();
void sacuvajKonobare();

void ispisiKonobare();
void dodajKonobara();
void izmijeniKonobara();
void deaktivirajKonobara();
void obrisiKonobara();

void upravljanjeNalozima(); // funkcija koju poziva glavni meni

#endif
