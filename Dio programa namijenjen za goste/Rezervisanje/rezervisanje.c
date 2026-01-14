#include <stdio.h>

#define MAX_REZERVACIJA 100

typedef struct{
    int id;
    int kapacitet;
}Sto;

typedef struct{
    int stoId;
    int dan, mjesec, godina;
    int sat, minut;
}Rezervacija;

typedef struct{
    int zahtjevId;
    int gostId;
    int stoId;
    int dan, mjesec, godina;
    int sat, minut;
    int brojGostiju;
    int zaposleniId;
}Zahtjev;

int odlukaZaposlenog(){
    int x;
    printf("Zaposleni: 1 = ODO BRI, 0 = ODBIJ: ");
    scanf("%d", &x);
    return x==1;
}

void rezervisiSto(
        Sto stolovi[], int brojStolova,
        Rezervacija rezervacije[], int *brojRezervacija,
        Zahtjev zahtjevi[], int *brojZahtjeva,
        int gostId, int zaposleniId,
        int stoId,
        int dan, int mjesec, int godina,
        int sat, int minut,
        int brojGostiju){

    Sto *izabraniSto=NULL;
    for(int i=0; i<brojStolova; i++){
        if(stolovi[i].id==stoId){
            izabraniSto=&stolovi[i];
            break;
        }
    }

    if(!izabraniSto){
        printf("Sto ne postoji.\n");
        return;
    }

    if(izabraniSto->kapacitet<brojGostiju){
        printf("Sto nema dovoljan kapacitet.\n");
        return;
    }

    Zahtjev z;
    z.zahtjevId = (*brojZahtjeva) + 1;
// #5 Rezervisanje
