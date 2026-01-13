#ifndef PROSTOR_H
#define PROSTOR_H

#define MAX_PROSTORA 10
#define MAX_STOLOVA 50

typedef struct {
    int id;
    char naziv[30];
    int stolovi[MAX_STOLOVA];   // ID-evi stolova
    int brojStolova;
} Prostor;

extern Prostor prostori[MAX_PROSTORA];
extern int brojProstora;


void prikaziProstore();
void dodajProstor();
void izmijeniProstor();
void obrisiProstor();

void meniStolova(Prostor *p);
void dodajSto(Prostor *p);
void izmijeniSto(Prostor *p);
void obrisiSto(Prostor *p);
void prikaziStolove(Prostor *p);


void upravljanjeProstorima();

#endif
