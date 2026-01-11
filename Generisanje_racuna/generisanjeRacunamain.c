#include "generisanjeRacuna.h"

int main() {
    ucitajMeni("meni.csv");
    ucitajNarudzbe("narudzbe.csv");
    int izbor;
    do{
        printf("\n1. Generisi racun\n0. Izlaz\nIzbor: ");
        scanf("%d", &izbor);
        if (izbor == 1)
            generisiRacun();
    } while(izbor != 0);
    return 0;
}
