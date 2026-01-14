#include <stdio.h>
#include <string.h>
#include <direct.h>
#include "../Kreiranje_narudzbi/KreiranjeNarudzbi.h"
#include "../Generisanje_racuna/placanje.h"
#include"../Prijava na sistem/prijava.c"
#include"../Generisanje_racuna/generisanjeRacuna.h"
#include"../Priprema_narudzbi/pravljenjeNarudzbi.h"
#include"../Rezervisanje/rezervisanje.h"
#include"../Pregled dostupnih stolova/dostupnoststolova.h"
#include"../Otkazivanje rezervacije/otkazivanje.h"

Rezervacija rezervacije[MAX_REZERVACIJA];
int brojRezervacija = 0;
Zahtjev zahtjevi[MAX_REZERVACIJA];
int brojZahtjeva = 0;
Sto stolovi[MAX_STOLOVA];
int brojStolova = 0;

int main() {

    prijava();
    int uloga;
    int izbor;
    printf("\nIzaberite ulogu:\n");
    printf("1. Konobar\n");
    printf("2. Kuhinjsko osoblje\n");
    printf("3. Menadzer sale\n");
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
    Gost gosti[MAX_GOSTI];
    int brojGostiju = 0;
    if (!ucitajGoste("gosti.csv", gosti, &brojGostiju)) {
        printf("Ne mogu ucitati goste!\n");
        return 1;
    }

    if (!ucitajStolove("stolovi.csv", stolovi, &brojStolova)) {
        printf("Ne mogu ucitati stolove!\n");
        return 1;
    }
    do {
        printf("\n===== KONOBAR =====\n");
        printf("1. Prikazi meni\n");
        printf("2. Kreiraj narudzbu\n");
        printf("3. Prikazi narudzbu za sto\n");
        printf("4. Generisi racun\n");
        printf("5. Placanje\n");
        printf("6. Pregled dostupnih stolova\n");
        printf("7. Napravi rezervaciju\n");
        printf("8. Otkazi rezervaciju\n");
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
            case 6: {
            int dan, mjesec, godina, sat, minut, brojGostijuZaSto;
            printf("Unesite datum i vrijeme (dd mm yyyy hh mm): ");
            scanf("%d %d %d %d %d", &dan, &mjesec, &godina, &sat, &minut);
            printf("Unesite broj gostiju: ");
            scanf("%d", &brojGostijuZaSto);

            pregledDostupnihStolova(stolovi, brojStolova, rezervacije, brojRezervacija,
                                     dan, mjesec, godina, sat, minut, brojGostijuZaSto);
            break;
        }

        case 7: {
            int gostId, stoId, dan, mjesec, godina, sat, minut, brojGostijuZaSto, zaposleniId;
            printf("Unesite ID gosta: ");
            scanf("%d", &gostId);
            printf("Unesite ID stola: ");
            scanf("%d", &stoId);
            printf("Unesite datum i vrijeme (dd mm yyyy hh mm): ");
            scanf("%d %d %d %d %d", &dan, &mjesec, &godina, &sat, &minut);
            printf("Unesite broj gostiju: ");
            scanf("%d", &brojGostijuZaSto);
            printf("Unesite ID konobara: ");
            scanf("%d", &zaposleniId);

            rezervisiSto(stolovi, brojStolova, rezervacije, &brojRezervacija,
                         zahtjevi, &brojZahtjeva, gostId, zaposleniId,
                         stoId, dan, mjesec, godina, sat, minut, brojGostijuZaSto);
            break;
        }
        case 8: {
            int gostId, rezervacijaId, satiDoRezervacije;
            printf("Unesite ID gosta: ");
            scanf("%d", &gostId);
            printf("Unesite ID rezervacije: ");
            scanf("%d", &rezervacijaId);
            printf("Unesite broj sati do rezervacije: ");
            scanf("%d", &satiDoRezervacije);
            otkaziRezervaciju(rezervacije, brojRezervacija, stolovi, brojStolova,
                              gostId, rezervacijaId, satiDoRezervacije);
            break;
        }
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
   else if(uloga == 3)
   {
    Gost gosti[MAX_GOSTI];
    int brojGostiju = 0;
    if (!ucitajGoste("gosti.csv", gosti, &brojGostiju)) {
        printf("Ne mogu ucitati goste!\n");
        return 1;
    }

    if (!ucitajStolove("stolovi.csv", stolovi, &brojStolova)) {
        printf("Ne mogu ucitati stolove!\n");
        return 1;
    }
    do {
        printf("\n===== MENADZER SALE =====\n");
        printf("1. Pregled dostupnih stolova\n");
        printf("2. Napravi rezervaciju\n");
        printf("3. Otkazi rezervaciju\n");
        printf("0. Izlaz\n");
        printf("Izbor: ");
        scanf("%d", &izbor);

        switch (izbor) {
            case 1: {
            int dan, mjesec, godina, sat, minut, brojGostijuZaSto;
            printf("Unesite datum i vrijeme (dd mm yyyy hh mm): ");
            scanf("%d %d %d %d %d", &dan, &mjesec, &godina, &sat, &minut);
            printf("Unesite broj gostiju: ");
            scanf("%d", &brojGostijuZaSto);

            pregledDostupnihStolova(stolovi, brojStolova, rezervacije, brojRezervacija,
                                     dan, mjesec, godina, sat, minut, brojGostijuZaSto);
            break;
        }
        case 2: {
            int gostId, stoId, dan, mjesec, godina, sat, minut, brojGostijuZaSto, zaposleniId;
            printf("Unesite ID gosta: ");
            scanf("%d", &gostId);
            printf("Unesite ID stola: ");
            scanf("%d", &stoId);
            printf("Unesite datum i vrijeme (dd mm yyyy hh mm): ");
            scanf("%d %d %d %d %d", &dan, &mjesec, &godina, &sat, &minut);
            printf("Unesite broj gostiju: ");
            scanf("%d", &brojGostijuZaSto);
            printf("Unesite ID konobara: ");
            scanf("%d", &zaposleniId);

            rezervisiSto(stolovi, brojStolova, rezervacije, &brojRezervacija,
                         zahtjevi, &brojZahtjeva, gostId, zaposleniId,
                         stoId, dan, mjesec, godina, sat, minut, brojGostijuZaSto);
            break;
        }
        case 3: {
            int gostId, rezervacijaId, satiDoRezervacije;
            printf("Unesite ID gosta: ");
            scanf("%d", &gostId);
            printf("Unesite ID rezervacije: ");
            scanf("%d", &rezervacijaId);
            printf("Unesite broj sati do rezervacije: ");
            scanf("%d", &satiDoRezervacije);
            otkaziRezervaciju(rezervacije, brojRezervacija, stolovi, brojStolova,
                              gostId, rezervacijaId, satiDoRezervacije);
            break;
        }
            case 0:
                printf("Izlaz iz sistema.\n");
                break;
            default:
                printf("Nepoznata opcija.\n");
        }
     } while (izbor != 0);
   }
    else {
        printf("Nepostojeca uloga.\n");
    }
    return 0;
}
