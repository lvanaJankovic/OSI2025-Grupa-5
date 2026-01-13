#include <stdio.h>
#include <time.h>
#include "poslovanje.h"

int main() {
    int izbor;
    time_t sada = time(NULL);
    time_t dan = sada - 24 * 3600;

    ucitajMeni("meni.csv");
    ucitajNarudzbe("narudzbe.csv");

    do {
        printf("\n1. Finansijski izvjestaj\n");
        printf("2. Izvjestaj o narudzbama\n");
        printf("0. Izlaz\n");
        scanf("%d", &izbor);

        switch (izbor) {
            case 1:
                finansijskiIzvjestaj(dan, sada);
                break;
            case 2:
                izvjestajNarudzbi(dan, sada);
                break;
        }
    } while (izbor != 0);

    return 0;
}
