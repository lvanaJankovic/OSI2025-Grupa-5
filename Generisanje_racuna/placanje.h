#pragma once
#include<stdio.h>

int placanjeGotovina(double iznos) {
    double uplaceno;
    printf("Unesite iznos koji je gost dao: ");
    scanf("%lf", &uplaceno);
    if(uplaceno < iznos){
        printf("Nedovoljan iznos!\n");
        return 0;
    }
    printf("Povrat: %.2f KM\n", uplaceno - iznos);
    return 1;
}
int placanjeKartica() {
    printf("Ubacite/Prislonite karticu.\n");
    int pin;
    printf("Unesite PIN kod: ");
    scanf("%d", &pin);
    if (pin < 1000 || pin > 9999) 
    {
        printf("Neispravan PIN! PIN mora imati 4 cifre.\n");
        return 0;
    } 
    printf("Autorizacija u toku...\n");
    printf("Transakcija odobrena!\n");
    return 1;
}
int placanjeDigitalniNovac() {
    int pin;
    printf("Autorizacija u toku...");
    printf("Transakcija odobrena!\n");
    return 1;
}
void placanje()
{
    int stoID;
    char putanjaNeplaceni[100];
    char putanjaPlaceni[100];
    char linija[256];
    double iznos = 0.0;
    printf("\nUnesite broj stola: ");
    scanf("%d", &stoID);
    sprintf(putanjaNeplaceni, "neplaceni/racun_sto_%d.txt", stoID);
    sprintf(putanjaPlaceni, "placeni/racun_sto_%d.txt", stoID);
    FILE *f = fopen(putanjaNeplaceni, "r");
    if (!f) {
        printf("Ne postoji neplaceni racun za ovaj sto.\n");
        return;
    }
    while (fgets(linija, sizeof(linija), f)) {
        printf("%s", linija);
        if (sscanf(linija, "UKUPNO ZA PLACANJE: %lf", &iznos) == 1) {
        }
    }
    fclose(f);
    char potvrda;
    printf("\nDa li je ovo racun koji zelite naplatiti? (d/n): ");
    scanf(" %c", &potvrda);
    if (potvrda != 'd') 
    {
    printf("Placanje otkazano.\n");
    return;
    }
    int izbor, uspjeh = 0;
    printf("\nIzaberite nacin placanja:\n");
    printf("1. Gotovina\n");
    printf("2. Kartica\n");
    printf("3. Digitalni novac\n");
    printf("Izbor: ");
    scanf("%d", &izbor);
    switch (izbor) {
        case 1:
            uspjeh = placanjeGotovina(iznos);
            break;
        case 2:
            uspjeh = placanjeKartica();
            break;
        case 3:
            uspjeh = placanjeDigitalniNovac();
            break;
        default:
            printf("Neispravan izbor.\n");
            return;
    }
    if (!uspjeh) {
        printf("Placanje nije uspjesno.\n");
        return;
    }
    FILE *src = fopen(putanjaNeplaceni, "r");
    FILE *dst = fopen(putanjaPlaceni, "w");
    if (!src || !dst) {
        printf("Greska pri premjestanju racuna.\n");
        return;
    }
    while (fgets(linija, sizeof(linija), src))
        fputs(linija, dst);
    fclose(src);
    fclose(dst);
    remove(putanjaNeplaceni);
    printf("\nPlacanje uspjesno evidentirano.\n");
}

