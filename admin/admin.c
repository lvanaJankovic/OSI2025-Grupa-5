#include <stdio.h>
#include "konobari_nalog.h"
#include "meni.h"
#include "prostor.h"

int main() {
    int izbor;
    do {
        printf("\n=== MENI ZA ADMINISTRATORA ===\n");
        printf("1. Upravljanje osobljem\n");
        printf("2. Upravljanje menijem\n");
        printf("3. Upravljanje prostorima i stolovima\n");
        printf("0. Izlaz\nIzbor: ");
        scanf("%d",&izbor);

        switch(izbor){
            case 1: upravljanjeNalozima(); break;
            case 2: administratorMeni(); break;
            case 3: upravljanjeProstorima(); break;
            case 0: printf("Izlaz iz sistema...\n"); break;
            default: printf("Nepostojeca opcija!\n");
        }

    } while(izbor!=0);

    return 0;
}
