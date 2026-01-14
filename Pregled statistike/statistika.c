#include <stdio.h>

void statistika(){
    int izborStatistike;
    int podizbor;
    int nastaviti;
    int promijeniPeriod;
    int pocetakPerioda, krajPerioda;
    int imaPristup;
    int imaPodataka;

    printf("=== PREGLED STATISTIKE ===\n");

    printf("Da li korisnik ima pravo pristupa statistici?\n");
    printf("1. Da\n0. Ne\nUnos: ");
    scanf("%d", &imaPristup);

    if(imaPristup==0){
        printf("\n[SISTEM]Pristup statistici nije dozvoljen.\n");
        printf("Slučaj upotrebe je prekinut.\n");
        return;
    }

    do{
        printf("\nIzaberite vrstu statistike:\n");
        printf("1.Promet i prihodi\n");
        printf("2.Broj narudzbi\n");
        printf("Unos: ");
        scanf("%d", &izborStatistike);

        if(izborStatistike!=1 && izborStatistike!=2)
            continue;

        if(izborStatistike==1){
            printf("\n1.Najprodavanije stavke\n");
            printf("2.Zauzetost prostora\n");
            printf("Unos: ");
            scanf("%d", &podizbor);

            if(podizbor!=1 && podizbor!=2)
                continue;
        }

        do{
            printf("\nUnesite vremenski period:\n");
            printf("Pocetak: ");
            scanf("%d", &pocetakPerioda);
            printf("Kraj: ");
            scanf("%d", &krajPerioda);

            printf("\n[SISTEM]Uzimanje podataka iz baze...\n");
            printf("Postoje li podaci za uneseni period?\n");
            printf("1. Da\n0. Ne\nUnos: ");
            scanf("%d", &imaPodataka);

            if(imaPodataka==0){
                printf("\n[SISTEM] Statistika nije dostupna za uneseni vremenski period.\n");
            }else{
                printf("[SISTEM]Obrada podataka...\n");
                printf("\n=== STATISTIKA ===\n");

                if(izborStatistike==1 && podizbor==1)
                    printf("Najprodavanije stavke (%d - %d)\n", pocetakPerioda, krajPerioda);
                else if(izborStatistike==1 && podizbor==2)
                    printf("Zauzetost prostora (%d - %d)\n", pocetakPerioda, krajPerioda);
                else
                    printf("Broj narudzbi (%d - %d)\n", pocetakPerioda, krajPerioda);
            }
            printf("\nZelite li promijeniti vremenski period?\n");
            printf("1. Da\n0. Ne\nUnos: ");
            scanf("%d", &promijeniPeriod);
        }while(promijeniPeriod==1);
        printf("\nZelite li nastaviti pregled statistike?\n");
        printf("1. Da\n0. Ne\nUnos: ");
        scanf("%d", &nastaviti);
    }while(nastaviti==1);
    printf("\nPregled statistike zavrsen.\n");
}


