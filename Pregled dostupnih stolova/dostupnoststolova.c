#include <stdio.h>

#define MAX_STOLOVA 30
#define MAX_KAPACITET_STOLA 16
#define TRAJANJE_REZERVACIJE 120

typedef struct{
    int id;
    int kapacitet;
}Sto;

typedef struct{
    int stoId;
    int dan, mjesec, godina;
    int sat, minut;
}Rezervacija;

int uMinute(int sat, int minut){
    return sat*60+minut;
}

int istiDatum(Rezervacija r, int d, int m, int g){
    return r.dan==d && r.mjesec==m && r.godina==g;
}

int preklapanje(int s1, int e1, int s2, int e2){
    return (s1<e2) && (s2<e1);
}

int stoSlobodanUTerminu(
        Rezervacija rezervacije[], int brojRezervacija,
        int stoId,
        int dan, int mjesec, int godina,
        int sat, int minut){

    int noviStart=uMinute(sat, minut);
    int noviEnd=noviStart+TRAJANJE_REZERVACIJE;

    for(int i=0; i<brojRezervacija; i++){
        if(rezervacije[i].stoId!=stoId)continue;
        if(!istiDatum(rezervacije[i], dan, mjesec, godina))continue;

        int postStart=uMinute(rezervacije[i].sat, rezervacije[i].minut);
        int postEnd=postStart+TRAJANJE_REZERVACIJE;

        if(preklapanje(noviStart, noviEnd, postStart, postEnd)){
            return 0;
        }
    }
    return 1;
}

void pregledDostupnihStolova(
        Sto stolovi[], int brojStolova,
        Rezervacija rezervacije[], int brojRezervacija,
        int dan, int mjesec, int godina,
        int sat, int minut,
        int brojGostiju){

    if(brojGostiju<=0 || brojGostiju>MAX_KAPACITET_STOLA){
        printf("Nevalidan broj gostiju.\n");
        return;
    }

    printf("\n=== PREGLED DOSTUPNIH STOLOVA ===\n");

    int postoji=0;
    for (int i=0; i<brojStolova; i++){
        if(stolovi[i].kapacitet < brojGostiju)continue;
        if(stoSlobodanUTerminu(rezervacije, brojRezervacija,
                               stolovi[i].id,
                               dan, mjesec, godina, sat, minut)){

            printf("Sto ID: %d | Kapacitet: %d\n",
                   stolovi[i].id, stolovi[i].kapacitet);
            postoji=1;
        }
    }

    if (!postoji){
        printf("Nema slobodnih stolova za trazeni termin.\n");
    }
}
