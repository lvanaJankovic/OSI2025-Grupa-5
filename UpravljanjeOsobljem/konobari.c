#include <stdio.h>
#include <string.h>
#include "konobari.h"

Konobar konobari[MAX_KONOBARA];
int brojKonobara = 0;

void ucitajKonobare() {
    FILE *f = fopen(BAZA, "r");
    if (!f) return;

    fscanf(f, "%d", &brojKonobara);
    for (int i = 0; i < brojKonobara; i++) {
        fscanf(f, "%d %s %d",
               &konobari[i].id,
               konobari[i].ime,
               &konobari[i].aktivan);
    }
    fclose(f);
}

void sacuvajKonobare() {
    FILE *f = fopen(BAZA, "w");
    fprintf(f, "%d\n", brojKonobara);
    for (int i = 0; i < brojKonobara; i++) {
        fprintf(f, "%d %s %d\n",
                konobari[i].id,
                konobari[i].ime,
                konobari[i].aktivan);
    }
    fclose(f);
}

void ispisiKonobare() {
    printf("\n--- Lista zaposlenih ---\n");
    for (int i = 0; i < brojKonobara; i++) {
        printf("%d. %s [%s]\n",
               konobari[i].id,
               konobari[i].ime,
               konobari[i].aktivan ? "AKTIVAN" : "DEAKTIVIRAN");
    }
}

void dodajKonobara() {
    Konobar k;
    k.id = (brojKonobara > 0) ? konobari[brojKonobara - 1].id + 1 : 1;

    printf("Unesite ime i prezime (Ime_Prezime): ");
    scanf("%s", k.ime);
    k.aktivan = 1;

    konobari[brojKonobara++] = k;
    sacuvajKonobare();
    printf("Konobar uspješno dodan.\n");
}

void izmijeniKonobara() {
    int id;
    printf("Unesite ID konobara: ");
    scanf("%d", &id);

    for (int i = 0; i < brojKonobara; i++) {
        if (konobari[i].id == id) {
            printf("Novo ime (Ime_Prezime): ");
            scanf("%s", konobari[i].ime);
            sacuvajKonobare();
            printf("Podaci izmijenjeni.\n");
            return;
        }
    }
    printf("Konobar nije pronađen.\n");
}

void deaktivirajKonobara() {
    int id;
    printf("Unesite ID konobara: ");
    scanf("%d", &id);

    for (int i = 0; i < brojKonobara; i++) {
        if (konobari[i].id == id) {
            konobari[i].aktivan = 0;
            sacuvajKonobare();
            printf("Konobar deaktiviran.\n");
            return;
        }
    }
    printf("Konobar nije pronađen.\n");
}

void obrisiKonobara() {
    int id;
    printf("Unesite ID konobara: ");
    scanf("%d", &id);

    for (int i = 0; i < brojKonobara; i++) {
        if (konobari[i].id == id) {
            for (int j = i; j < brojKonobara - 1; j++) {
                konobari[j] = konobari[j + 1];
            }
            brojKonobara--;
            sacuvajKonobare();
            printf("Konobar obrisan.\n");
            return;
        }
    }
    printf("Konobar nije pronađen.\n");
}
