#include"pravljenjeNarudzbi.h"

int main() {
    if (!ucitajMeni("meni.csv")) {
        printf("Ne mogu ucitati meni!\n");
        return 1;
    }
    if (!ucitajNarudzbe("narudzbe.csv")) {
        printf("Ne mogu ucitati narudzbe ili fajl ne postoji. Pocinjemo sa praznom listom.\n");
    }
    int izbor;
    while (1) {
        printf("\n--- Kuhinjsko osoblje ---\n");
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
    }
    return 0;
}