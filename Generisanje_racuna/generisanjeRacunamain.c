#include "generisanjeRacuna.h"
#include"placanje.h"
#include<direct.h>

int main() {
    ucitajMeni("meni.csv");
    ucitajNarudzbe("narudzbe.csv");
    _mkdir("placeni");
    _mkdir("neplaceni");
    int izbor;
    do{
        printf("\n1. Generisi racun\n2. Placanje\n0. Izlaz\nIzbor: ");
        scanf("%d", &izbor);
        if (izbor == 1)
            generisiRacun();
        if(izbor==2)
           placanje();
    } while(izbor != 0);
    return 0;
}

