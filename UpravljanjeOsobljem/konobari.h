#ifndef KONOBARI_H
#define KONOBARI_H

#define MAX_KONOBARA 50
#define BAZA "osoblje.txt"

typedef struct {
    int id;
    char ime[50];
    int aktivan; // 1 = aktivan, 0 = deaktiviran
} Konobar;


extern Konobar konobari[MAX_KONOBARA];
extern int brojKonobara;


void ucitajKonobare();
void sacuvajKonobare();

void ispisiKonobare();
void dodajKonobara();
void izmijeniKonobara();
void deaktivirajKonobara();
void obrisiKonobara();

#endif
