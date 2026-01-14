#include <stdio.h>
#include <string.h>
#include <direct.h>
#include "../Kreiranje_narudzbi/KreiranjeNarudzbi.h"
#include "../Generisanje_racuna/placanje.h"
#include"../Prijava na sistem/prijava.c"
#include"../Generisanje_racuna/generisanjeRacuna.h"
#include"../Priprema_narudzbi/pravljenjeNarudzbi.h"

int main() {

    prijava();
    int uloga;
    int izbor;
    printf("\nIzaberite ulogu:\n");
    printf("1. Konobar\n");
    printf("2. Kuhinjsko osoblje\n");
    printf("Izbor: ");
    scanf("%d", &uloga);

    if (!ucitajMeni("meni.csv")) {
        printf("Ne mogu ucitati meni!\n");
        return 1;
    }
    ucitajNarudzbe("narudzbe.csv");
    _mkdir("placeni");
    _mkdir("neplaceni");
   if(uloga == 1){
    do {
        printf("\n===== KONOBAR =====\n");
        printf("1. Prikazi meni\n");
        printf("2. Kreiraj narudzbu\n");
        printf("3. Prikazi narudzbu za sto\n");
        printf("4. Generisi racun\n");
        printf("5. Placanje\n");
        printf("0. Izlaz\n");
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
                generisiRacun();
                break;
            case 5:
                placanje();
                break;
            case 0:
                printf("Izlaz iz sistema.\n");
                break;
            default:
                printf("Nepoznata opcija.\n");
        }
     } while (izbor != 0);
   }
   else if(uloga == 2) {
    do{
        printf("\n==== KUHINJSKO OSOBLJE ====\n");
        printf("1. Prikazi aktivne narudzbe\n");
        printf("2. Pripremi narudzbu\n");
        printf("3. Izlaz\n");
        printf("Izbor: ");
        scanf("%d", &izbor);
        switch (izbor) {
            case 1: prikaziAktivneNarudzbe(); break;
            case 2: pripremiNarudzbu(); break;
            case 3: printf("Izlaz.\n"); return 0;
            default: printf("Nepoznata opcija, pokusajte ponovo.\n");
        }
    } while (izbor != 0);
   }
    else {
        printf("Nepostojeca uloga.\n");
    }
    return 0;
}
