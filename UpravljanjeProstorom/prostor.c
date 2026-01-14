#include <stdio.h>
#include <string.h>
#include "prostor.h"
#include "rezervisanje.c"


extern Sto stolovi[MAX_STOLOVA];
extern int brojRezervacija;
extern Rezervacija rezervacije[];

Prostor prostori[MAX_PROSTORA];
int brojProstora = 0;

/* Provjera da li je sto rezervisan */
int stoImaRezervaciju(int stoId) {
    for (int i = 0; i < brojRezervacija; i++) {
        if (rezervacije[i].stoId == stoId)
            return 1;
    }
    return 0;
}



void prikaziProstore() {
    printf("\n--- PROSTORI ---\n");
    for (int i = 0; i < brojProstora; i++) {
        printf("%d. %s\n", prostori[i].id, prostori[i].naziv);
    }
}

void dodajProstor() {
    Prostor p;
    p.id = brojProstora + 1;
    p.brojStolova = 0;

    printf("Naziv prostora: ");
    scanf(" %29[^\n]", p.naziv);

    prostori[brojProstora++] = p;
    printf("✔ Prostor dodat\n");
}

void izmijeniProstor() {
    int id;
    prikaziProstore();

    printf("ID prostora: ");
    scanf("%d", &id);

    for (int i = 0; i < brojProstora; i++) {
        if (prostori[i].id == id) {
            printf("Novi naziv: ");
            scanf(" %29[^\n]", prostori[i].naziv);
            printf("✔ Izmjena uspješna\n");
            return;
        }
    }
}

void obrisiProstor() {
    int id;
    prikaziProstore();

    printf("ID prostora za brisanje: ");
    scanf("%d", &id);

    for (int i = 0; i < brojProstora; i++) {
        if (prostori[i].id == id) {
            if (prostori[i].brojStolova > 0) {
                printf("❌ Brisanje onemogućeno – prostor ima stolove\n");
                return;
            }
            for (int j = i; j < brojProstora - 1; j++)
                prostori[j] = prostori[j + 1];
            brojProstora--;
            printf("✔ Prostor obrisan\n");
            return;
        }
    }
}



void prikaziStolove(Prostor *p) {
    printf("\n--- STOLOVI (%s) ---\n", p->naziv);
    for (int i = 0; i < p->brojStolova; i++) {
        int id = p->stolovi[i];
        printf("Sto ID: %d", id);
        if (stoImaRezervaciju(id))
            printf(" [REZERVISAN]");
        printf("\n");
    }
}

void dodajSto(Prostor *p) {
    int id;
    printf("Unesite ID novog stola: ");
    scanf("%d", &id);

    p->stolovi[p->brojStolova++] = id;
    printf("✔ Sto dodat\n");
}

void izmijeniSto(Prostor *p) {
    int stari, novi;
    prikaziStolove(p);

    printf("ID stola za izmjenu: ");
    scanf("%d", &stari);

    for (int i = 0; i < p->brojStolova; i++) {
        if (p->stolovi[i] == stari) {
            printf("Novi ID stola: ");
            scanf("%d", &novi);
            p->stolovi[i] = novi;
            printf("✔ Sto izmijenjen\n");
            return;
        }
    }
}

void obrisiSto(Prostor *p) {
    int id;
    prikaziStolove(p);

    printf("ID stola za brisanje: ");
    scanf("%d", &id);

    if (stoImaRezervaciju(id)) {
        printf("❌ Brisanje onemogućeno – sto je rezervisan\n");
        return;
    }

    for (int i = 0; i < p->brojStolova; i++) {
        if (p->stolovi[i] == id) {
            for (int j = i; j < p->brojStolova - 1; j++)
                p->stolovi[j] = p->stolovi[j + 1];
            p->brojStolova--;
            printf("✔ Sto obrisan\n");
            return;
        }
    }
}



void meniStolova(Prostor *p) {
    int izbor;
    do {
        printf("\n--- STOLOVI (%s) ---\n", p->naziv);
        printf("1. Prikaz stolova\n");
        printf("2. Dodaj sto\n");
        printf("3. Izmijeni sto\n");
        printf("4. Obrisi sto\n");
        printf("0. Povratak\n");
        printf("Izbor: ");
        scanf("%d", &izbor);

        switch (izbor) {
            case 1: prikaziStolove(p); break;
            case 2: dodajSto(p); break;
            case 3: izmijeniSto(p); break;
            case 4: obrisiSto(p); break;
        }
    } while (izbor != 0);
}

void upravljanjeProstorima() {
    int izbor, id;
    do {
        printf("\n--- UPRAVLJANJE PROSTORIMA ---\n");
        printf("1. Prikaz prostora\n");
        printf("2. Dodaj prostor\n");
        printf("3. Izmijeni prostor\n");
        printf("4. Obrisi prostor\n");
        printf("5. Upravljaj stolovima\n");
        printf("0. Odjava\n");
        printf("Izbor: ");
        scanf("%d", &izbor);

        switch (izbor) {
            case 1: prikaziProstore(); break;
            case 2: dodajProstor(); break;
            case 3: izmijeniProstor(); break;
            case 4: obrisiProstor(); break;
            case 5:
                prikaziProstore();
                printf("ID prostora: ");
                scanf("%d", &id);
                for (int i = 0; i < brojProstora; i++)
                    if (prostori[i].id == id)
                        meniStolova(&prostori[i]);
                break;
        }
    } while (izbor != 0);
}
