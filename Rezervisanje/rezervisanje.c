#include <stdio.h>

#define MAX_REZERVACIJA 100
#define MAX_STOLOVA 50

typedef struct{
    int id;
    int kapacitet;
    int status;  // 0-slobodan, 1-zauzet
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
    printf("Zaposleni: 1=ODOBRI, 0=ODBIJ: ");
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
    for(int i=0;i<brojStolova;i++){
        if(stolovi[i].id==stoId){
            izabraniSto=&stolovi[i];
            break;
        }
    }

    if(!izabraniSto){
        printf("Sto ne postoji.\n");
        printf("Povratak na odabir stola.\n");
        return;
    }

    if(izabraniSto->kapacitet<brojGostiju){
        printf("Sto nema dovoljan kapacitet.\n");
        printf("Povratak na odabir stola.\n");
        return;
    }

    if(izabraniSto->status==1){
        printf("Sto više nije dostupan.\n");
        printf("Povratak na odabir stola.\n");
        return;
    }

    Zahtjev noviZahtjev;
    noviZahtjev.zahtjevId=(*brojZahtjeva)+1;
    noviZahtjev.gostId=gostId;
    noviZahtjev.stoId=stoId;
    noviZahtjev.dan=dan;
    noviZahtjev.mjesec=mjesec;
    noviZahtjev.godina=godina;
    noviZahtjev.sat=sat;
    noviZahtjev.minut=minut;
    noviZahtjev.brojGostiju=brojGostiju;
    noviZahtjev.zaposleniId=zaposleniId;

    zahtjevi[*brojZahtjeva]=noviZahtjev;
    (*brojZahtjeva)++;

    int odluka=odlukaZaposlenog();

    if(!odluka){
        printf("Zaposleni je odbio rezervaciju.\n");
        printf("Povratak na odabir stola.\n");
        return;
    }

    Rezervacija novaRezervacija;
    novaRezervacija.stoId=stoId;
    novaRezervacija.dan=dan;
    novaRezervacija.mjesec=mjesec;
    novaRezervacija.godina=godina;
    novaRezervacija.sat=sat;
    novaRezervacija.minut=minut;

    rezervacije[*brojRezervacija]=novaRezervacija;
    (*brojRezervacija)++;

    izabraniSto->status=1;

    printf("Rezervacija uspješna.\n");
    printf("Sto je zauzet.\n");
}
