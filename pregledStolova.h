#include <stdio.h>
#pragma once

#define MAX_KAPACITET_STOLA 16

void pregledStolova(){
    int dan, mjesec, godina;
    int sat, minut;
    int brojGostiju;

    printf("\n=== PREGLED DOSTUPNIH STOLOVA ===\n");

    printf("Unesite datum (dd mm gggg): ");
    scanf("%d %d %d", &dan, &mjesec, &godina);

    printf("Unesite vrijeme (hh mm): ");
    scanf("%d %d", &sat, &minut);

    printf("Unesite broj gostiju: ");
    scanf("%d", &brojGostiju);

    printf("\nProvjera da li ima dostupnih stolova za unesene podatke...\n");

    if(brojGostiju <= MAX_KAPACITET_STOLA) {
        printf("Prikaz liste slobodnih stolova.\n");
        printf("Filtriranje dostupnih stolova po terminu i kapacitetu.\n");
        printf("Postoji sto za %d gostiju.\n", brojGostiju);
        printf("(Ovdje bi se nastavilo na: Rezervisanje stola)\n");
    }else{
        printf("Ispis poruke o nedostupnosti stolova.\n");
        printf("Nema slobodnog stola za %d gostiju.\n", brojGostiju);
    }
}