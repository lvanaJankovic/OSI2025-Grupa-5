#ifndef MENI_H
#define MENI_H

#define MAX_MENI 50

typedef struct {
    int rb;
    char naziv[30];
    double cijena;
} Stavka;


extern Stavka meni[MAX_MENI];
extern int brojStavkiMenija;


int ucitajMeni(const char *imeFajla);
void sacuvajMeni(const char *imeFajla);

void prikaziMeni();
void dodajStavku();
void izmijeniStavku();
void obrisiStavku();

void administratorMeni();

#endif
