#include <stdio.h>


typedef struct {
    int id;
    char ime[50];
    int stolovi;
    int narudzbe;
    float promet;
    int sati;
} Konobar;

typedef enum {
    DNEVNI = 1,
    MJESECNI,
    GODISNJI
} Period;


int ucitaj_konobare(Konobar k[]);
void ispis_konobara(Konobar k[], int n);
void obrada_podataka(Konobar k, Period p);

#define MAX 20

int main() {
    Konobar konobari[MAX];
    int n, izbor;
    Period period;
    char nastavi;

    
    n = ucitaj_konobare(konobari);

    do {
        printf("\n=== PRACENJE RADA KONOBARA ===\n");

        ispis_konobara(konobari, n);

        printf("\nIzaberite konobara: ");
        scanf("%d", &izbor);

        if (izbor < 1 || izbor > n) {
            printf("Neispravan izbor!\n");
            continue;
        }

        printf("\nIzaberite vremenski period:\n");
        printf("1. Dnevni\n2. Mjesecni\n3. Godisnji\n");
        printf("Izbor: ");
        scanf("%d", (int*)&period);

        obrada_podataka(konobari[izbor - 1], period);

        printf("\nNastaviti pracenje? (d/n): ");
        scanf(" %c", &nastavi);

    } while (nastavi == 'd' || nastavi == 'D');

    printf("\nKraj programa.\n");
    return 0;
}
