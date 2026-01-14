#include <stdio.h>
#include <string.h>

#include "registracija.c"
#include "prijava.c"
#include "dostupnoststolova.h"
#include "rezervisanje.h"

#define FAJL_STOLOVI "stolovi.csv"
#define FAJL_GOSTI "gosti.csv"

int main(){
    Sto stolovi[MAX_STOLOVA];
    Rezervacija rezervacije[MAX_REZERVACIJA];
    Zahtjev zahtjevi[MAX_REZERVACIJA];
    Gost gosti[MAX_GOSTI];

    int brojStolova=0;
    int brojRezervacija=0;
    int brojZahtjeva=0;
    int brojGostijuUBazi=0;
    int izbor;

    ucitajStolove(FAJL_STOLOVI, stolovi, &brojStolova);
    ucitajGoste(FAJL_GOSTI, gosti, &brojGostijuUBazi);

    do{
        printf("\n===GOST APLIKACIJA===\n");
        printf("1. Registracija\n");
        printf("2. Prijava\n");
        printf("0. Izlaz\n");
        printf("Izbor: ");
        scanf("%d", &izbor);

        if(izbor==1){
            registracija();
        }
        else if(izbor==2){
            prijava();
            int dan, mjesec, godina, sat, minut, brojGostiju;
            int stoId;
            int gostId=1;
            int zaposleniId=1;

            printf("\nUnesite datum (dd mm gggg): ");
            scanf("%d %d %d", &dan, &mjesec, &godina);

            printf("Unesite vrijeme (sat minut): ");
            scanf("%d %d", &sat, &minut);

            printf("Broj gostiju: ");
            scanf("%d", &brojGostiju);

            pregledDostupnihStolova(
                stolovi, brojStolova,
                rezervacije, brojRezervacija,
                dan, mjesec, godina,
                sat, minut,
                brojGostiju
            );

            printf("\nUnesite ID stola za rezervaciju: ");
            scanf("%d", &stoId);

            rezervisiSto(
                stolovi, brojStolova,
                rezervacije, &brojRezervacija,
                zahtjevi, &brojZahtjeva,
                gostId, zaposleniId,
                stoId,
                dan, mjesec, godina,
                sat, minut,
                brojGostiju
            );
        }

    } while(izbor!=0);

    printf("Izlaz iz gost aplikacije.\n");
    return 0;
}
