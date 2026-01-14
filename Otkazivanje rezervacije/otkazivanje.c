#include <stdio.h>
#include <string.h>

#define MAX_REZERVACIJA 100
#define MIN_SATI_DO_REZERVACIJE 2

typedef struct{
    int id;
    int status; // 0-slobodan, 1-zauzet
}Sto;

typedef struct{
    int rezervacijaId;
    int gostId;
    int stoId;
    int dan, mjesec, godina;
    int sat, minut;
    int aktivna; // 1-aktivna, 0-otkazana
}Rezervacija;

int odlukaZaposlenog(){
    int x;
    printf("Zaposleni: 1=ODOBRI, 0=ODBIJ: ");
    scanf("%d", &x);
    return x==1;
}

int dovoljnoVremena(int satiDoRezervacije){
    if(satiDoRezervacije<MIN_SATI_DO_REZERVACIJE)
        return 0;
    return 1;
}

void otkaziRezervaciju(
        Rezervacija rezervacije[], int brojRezervacija,
        Sto stolovi[], int brojStolova,
        int gostId,
        int rezervacijaId,
        int satiDoRezervacije){

    Rezervacija *rez=NULL;

    for(int i=0; i<brojRezervacija; i++){
        if(rezervacije[i].rezervacijaId==rezervacijaId && rezervacije[i].gostId==gostId &&
           rezervacije[i].aktivna==1){
            rez=&rezervacije[i];
            break;
        }
    }

    if(!rez){
        printf("Greska: rezervacija ne postoji.\n");
        return;
    }

    if(!dovoljnoVremena(satiDoRezervacije)){
        printf("Otkazivanje nije moguce, ostalo je premalo vremena do rezervacije.\n");
        return;
    }

    int odluka=odlukaZaposlenog();

    if(!odluka){
        printf("Zaposleni je odbio otkazivanje rezervacije.\n");
        return;
    }

    rez->aktivna=0;

    for(int i=0;i<brojStolova;i++){
        if(stolovi[i].id==rez->stoId){
            stolovi[i].status=0;
            break;
        }
    }

    printf("Rezervacija je uspjesno otkazana.\n");
    printf("Sto je oslobodjen.\n");
}
