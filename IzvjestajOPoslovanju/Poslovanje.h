#ifndef NARUDZBE_H
#define NARUDZBE_H

#include <time.h>

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
    time_t vrijeme;
} Narudzba;


extern Stavka meni[MAX_MENI];
extern int brojStavkiMenija;
extern Narudzba narudzbe[MAX_NARUDZBI];
extern int brojNarudzbi;


int ucitajMeni(const char *imeFajla);
int ucitajNarudzbe(const char *imeFajla);
void sacuvajNarudzbe(const char *imeFajla);

void prikaziAktivneNarudzbe();
void pripremiNarudzbu();


void finansijskiIzvjestaj(time_t od, time_t do_);
void izvjestajNarudzbi(time_t od, time_t do_);

#endif
