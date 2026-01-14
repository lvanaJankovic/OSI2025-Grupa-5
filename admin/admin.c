#include <stdio.h>
#include <time.h>
#include "narudzbe.h"
#include "konobari_stat.h"
#include "meni.h"
#include "konobari_nalog.h"
#include "prostor.h"

int main() {
    int izbor;
    do {
        printf("\n=== ADMINISTRATORSKI MENI ===\n");
        printf("1. Izvjestaji (promet i narudzbe)\n");
        printf("2. Pracenje rada konobara\n");
        printf("3. Upravljanje menijem\n");
        printf("4. Upravljanje osobljem\n");
        printf("5. Upravljanje prostorima i stolovima\n");
        printf("0. Izlaz\nIzbor: ");
        scanf("%d",&izbor);

        switch(izbor){
            case 1:{
                time_t sada=time(NULL);
                time_t dan=sada-24*3600;
                ucitajMeni("meni.csv");
                ucitajNarudzbe("narudzbe.csv");
                int opc;
                do{
                    printf("\n1. Finansijski izvjestaj\n2. Izvjestaj o narudzbama\n0. Povratak\nIzbor: ");
                    scanf("%d",&opc);
                    if(opc==1) finansijskiIzvjestaj(dan,sada);
                    else if(opc==2) izvjestajNarudzbi(dan,sada);
                }while(opc!=0);
                break;
            }
            case 2: pracenjeKonobara(); break;
            case 3: administratorMeni(); break;
            case 4: upravljanjeNalozima(); break;
            case 5: upravljanjeProstorima(); break;
            case 0: printf("Izlaz iz sistema...\n"); break;
            default: printf("Nepostojeca opcija!\n");
        }

    } while(izbor!=0);
    return 0;
}
