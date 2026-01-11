#pragma once
#include <stdio.h>


double dodajPopust(double osnovniIznos, double *procenatPopusta){
    char izbor;
    *procenatPopusta = 0;
    printf("Zelite li dodati popust? (d/n): ");
    scanf(" %c", &izbor);
    if(izbor == 'd'){
        double p;
        do {
            printf("Unesite procenat popusta (0 - 100): ");
            scanf("%lf", &p);
            if (p < 0 || p > 100)
                printf("Neispravan procenat! Pokusajte ponovo.\n");
        } while (p < 0 || p > 100);
        *procenatPopusta = p;
        osnovniIznos=osnovniIznos * (1 - p / 100.0);
        printf("Trenutni iznos racuna : %.2f KM\n", osnovniIznos);
        return osnovniIznos;
    }
    return osnovniIznos;
}

double dodajNapojnicu(double trenutniIznos, double *napojnicaIznos) {
    char izbor;
    *napojnicaIznos = 0;
    printf("Zelite li dodati napojnicu? (d/n): ");
    scanf(" %c", &izbor);
    if (izbor == 'd') {
        double n;
        do {
            printf("Unesite iznos napojnice (>= 0): ");
            scanf("%lf", &n);
            if (n < 0)
                printf("Napojnica ne moze biti negativna!\n");
        } while (n < 0);
        *napojnicaIznos = n;
        trenutniIznos = trenutniIznos + n;
        printf("Trenutni iznos racuna : %.2f KM\n", trenutniIznos);
        return trenutniIznos;
    }
    return trenutniIznos;
}
