#include <stdio.h>
#include <string.h>

#define MAX 50
#define BAZA "korisnici.txt"

int provjeriKorisnika(char email[], char lozinka[]){
    FILE *f=fopen(BAZA, "r");
    if(f==NULL) {
        printf("Greska pri otvaranju baze.\n");
        return 0;
    }

    char ime[MAX], prezime[MAX], telefon[MAX], mail[MAX], pass[MAX];
    int d, m, g;
    int status;

    while(fscanf(f, "%s %s %s %d %d %d %s %s %d",
                     ime, prezime, telefon, &d, &m, &g, mail, pass)!= EOF){
        if(strcmp(mail, email)==0 && strcmp(pass, lozinka)==0){
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}

int zeliPrekinutiPrijavu(){
    char odgovor[10];

    printf("Da li zelite nastaviti prijavljivanje? (DA / NE): ");
    scanf("%s", odgovor);

    if(strcmp(odgovor, "NE")==0){
        printf("Prijavljivanje prekinuto. Podaci su odbačeni.\n");
        printf("Prijava na sistem nije uspjesna.\n");
        return 1;
    }
    return 0;
}


void prijava(){
    char email[MAX], lozinka[MAX];
    int blokiran=0;
    int validno=0;

    printf("\n=== PRIJAVA NA SISTEM ===\n");

    do{
        printf("Email adresa: ");
        scanf("%s", email);
        if(zeliPrekinutiPrijavu())return;

        printf("Lozinka: ");
        scanf("%s", lozinka);
        if(zeliPrekinutiPrijavu())return;

        validno=provjeriKorisnika(email, lozinka);
        if(!validno){
            printf("Poruka: Netacna email adresa ili lozinka.\n");
        }
        if(!validno && zeliPrekinutiPrijavu())return;
    }while(!validno);

    

    printf("Poruka: Uspjesna prijava na sistem.\n");
    printf("Dodjela privremenog pristupa funkcionalnostima...\n");
}


