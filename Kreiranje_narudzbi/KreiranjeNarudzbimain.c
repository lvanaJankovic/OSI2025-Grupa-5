#include "KreiranjeNarudzbi.h"
#include <stdio.h>
#include <string.h>

int main() {
    if (!ucitajMeni("meni.csv")) {
        printf("Ne mogu ucitati meni!\n");
        return 1;
    }
    int izbor;
    while (1) {
        printf("\n--- Opcija za kreiranje narudzbi ---\n");
        printf("1. Prikazi meni\n");
        printf("2. Kreiraj narudzbu\n");
        printf("3. Prikazi narudzbu za sto\n");
        printf("4. Izlaz\n");
        printf("Izbor: ");
        scanf("%d", &izbor);

        switch (izbor) {
            case 1:
                ispisiMeni();
                break;
            case 2:
                kreirajNarudzbu();
                break;
            case 3:
                prikaziNarudzbu();
                break;
            case 4:
                printf("Izlaz iz opcije.\n");
                return 0;
            default:
                printf("Nepoznata opcija, pokusajte ponovo.\n");
        }
    }
    return 0;
}
