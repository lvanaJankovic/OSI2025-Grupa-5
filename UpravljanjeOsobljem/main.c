#include <stdio.h>
#include "konobari.h"

int main() {
    int izbor;

    ucitajKonobare();

    do {
        printf("\n--- Upravljanje osobljem ---\n");
        printf("1. Prikaz zaposlenih\n");
        printf("2. Dodavanje naloga\n");
        printf("3. Izmjena naloga\n");
        printf("4. Deaktivacija naloga\n");
        printf("5. Brisanje naloga\n");
        printf("0. Izlaz\n");
        printf("Izbor: ");
        scanf("%d", &izbor);

        switch (izbor) {
            case 1: ispisiKonobare(); break;
            case 2: dodajKonobara(); break;
            case 3: izmijeniKonobara(); break;
            case 4: deaktivirajKonobara(); break;
            case 5: obrisiKonobara(); break;
        }
    } while (izbor != 0);

    return 0;
}
