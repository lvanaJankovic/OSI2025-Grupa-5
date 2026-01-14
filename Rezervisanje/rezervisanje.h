#include <stdio.h>
#pragma once


#define MAX_REZERVACIJA 100
#define MAX_STOLOVA 50
#define MAX_GOSTI 50
#define TRAJANJE_REZERVACIJE 120

typedef struct{
    int id;
    int kapacitet;
    int status;
}Sto;

typedef struct{
    int id;
    char ime[50];
    char telefon[20];
} Gost;

typedef struct{
    int rezervacijaId;
    int gostId;
    int stoId;
    int dan, mjesec, godina;
    int sat, minut;
    int aktivna;
} Rezervacija;


typedef struct{
    int zahtjevId;
    int gostId;
    int stoId;
    int dan, mjesec, godina;
    int sat, minut;
    int brojGostiju;
    int zaposleniId;
}Zahtjev;



int ucitajGoste(const char *imeFajla, Gost gosti[], int *brojGostiju) {
    FILE *f = fopen(imeFajla, "r");
    if (!f) {
        printf("Greska pri otvaranju fajla %s\n", imeFajla);
        return 0;
    }

    *brojGostiju = 0;
    while (fscanf(f, "%d,%49[^,],%19[^\n]\n",
                  &gosti[*brojGostiju].id,
                  gosti[*brojGostiju].ime,
                  gosti[*brojGostiju].telefon) == 3) {
        (*brojGostiju)++;
        if (*brojGostiju >= MAX_GOSTI) break;
    }

    fclose(f);
    return 1;
}
int ucitajStolove(const char *imeFajla, Sto stolovi[], int *brojStolova) {
    FILE *f = fopen(imeFajla, "r");
    if (!f) {
        printf("Greska pri otvaranju fajla %s\n", imeFajla);
        return 0;
    }
    *brojStolova = 0;
    char buffer[100];
    fgets(buffer, sizeof(buffer), f);
    int id, kapacitet, status;
    while (fscanf(f, "%d,%d,%d\n", &id, &kapacitet, &status) == 3) {
        stolovi[*brojStolova].id = id;
        stolovi[*brojStolova].kapacitet = kapacitet;
        stolovi[*brojStolova].status = status;
        (*brojStolova)++;
        if (*brojStolova >= MAX_STOLOVA) break;
    }

    fclose(f);
    return 1;
}
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
    if(!stoSlobodanUTerminu(rezervacije, *brojRezervacija, stoId,
                         dan, mjesec, godina, sat, minut)) {
    printf("Sto više nije dostupan za taj termin.\n");
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
    int idRezervacije;
    int postoji;
    do {
        postoji = 0;
        printf("Unesite ID rezervacije: ");
        scanf("%d", &idRezervacije);
        for(int i=0;i<*brojRezervacija;i++){
            if(rezervacije[i].rezervacijaId == idRezervacije){
                printf("Taj ID je već zauzet. Unesite drugi.\n");
                postoji = 1;
                break;
            }
        }
    } while(postoji);

    Rezervacija novaRezervacija;
    novaRezervacija.rezervacijaId = idRezervacije;
    novaRezervacija.gostId = gostId;
    novaRezervacija.stoId=stoId;
    novaRezervacija.dan=dan;
    novaRezervacija.mjesec=mjesec;
    novaRezervacija.godina=godina;
    novaRezervacija.sat=sat;
    novaRezervacija.minut=minut;
    novaRezervacija.aktivna = 1;

    rezervacije[*brojRezervacija]=novaRezervacija;
    (*brojRezervacija)++;

    izabraniSto->status=1;

    printf("Rezervacija uspjesna.\n");
    printf("Sto je zauzet.\n");
}
