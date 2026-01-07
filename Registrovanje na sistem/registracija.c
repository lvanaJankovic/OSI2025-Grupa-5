#include <stdio.h>
#include <string.h>

#define MAX 50
#define BAZA "korisnici.txt"


int validanTelefon(char t[]){
    int i;
    if(strlen(t)<9)return 0;
    for(i=0; t[i]!='\0'; i++){
        if(t[i]<'0' || t[i]>'9')
            return 0;
    }
    return 1;
}

int validanDatum(int d, int m, int g){
    if(g<1900 || g>2026) return 0;
    if(m<1 || m>12) return 0;
    if(d<1 || d>31) return 0;
    return 1;
}

int validanEmail(char email[]){
    return strchr(email, '@')!=NULL && strchr(email, '.')!=NULL;
}

int validnaLozinka(char l[]){
    return strlen(l) >= 8;
}

int emailPostoji(char email[]){
    FILE *f=fopen(BAZA, "r");
    if(!f) return 0;

    char ime[MAX], prezime[MAX], telefon[MAX], mail[MAX], lozinka[MAX];
    int d, m, g;
    while(fscanf(f, "%s %s %s %d %d %d %s %s",
                    ime, prezime, telefon, &d, &m, &g, mail, lozinka)!= EOF){
        if (strcmp(mail, email) == 0){
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}

int zeliPrekinuti(){
    char odgovor[10];
    printf("Da li zelite nastaviti registraciju? (DA / NE): ");
    scanf("%s", odgovor);

    if(strcmp(odgovor, "NE")==0){
        printf("Registracija prekinuta. Podaci su odbačeni.\n");
        return 1;
    }
    return 0;
}

void registracija(){
    char ime[MAX], prezime[MAX];
    char telefon[15];
    int dan, mjesec, godina;
    char email[MAX];
    char lozinka[MAX], potvrda[MAX];

    printf("\n=== REGISTRACIJA NA SISTEM ===\n");

    printf("Ime: ");
    scanf("%s", ime);
    if(zeliPrekinuti())return;

    printf("Prezime: ");
    scanf("%s", prezime);
    if(zeliPrekinuti())return;

    do{
        printf("Broj telefona: ");
        scanf("%s", telefon);
        if(!validanTelefon(telefon))
            printf("Neispravan format tel. broja.\n");
        if(zeliPrekinuti())return;
    }while(!validanTelefon(telefon));

    do{
        printf("Datum rođenja (dd mm gggg): ");
        scanf("%d %d %d", &dan, &mjesec, &godina);
        if(!validanDatum(dan, mjesec, godina))
            printf("Nevalidan datum rođenja.\n");
        if(zeliPrekinuti())return;
    }while(!validanDatum(dan, mjesec, godina));

    do{
        printf("Email adresa: ");
        scanf("%s", email);
        if(!validanEmail(email))
            printf("Neispravan format email adrese.\n");
        else if(emailPostoji(email))
            printf("Korisnik sa tom email adresom već postoji.\n");
        if(zeliPrekinuti())return;
    }while(!validanEmail(email) || emailPostoji(email));

    do{
        printf("Lozinka: ");
        scanf("%s", lozinka);

        if(!validnaLozinka(lozinka))
            printf("Lozinka mora imati najmanje 8 znakova.\n");

        if(zeliPrekinuti())return;

    }while(!validnaLozinka(lozinka));

    do{
        printf("Potvrdi lozinku: ");
        scanf("%s", potvrda);

        if(strcmp(lozinka, potvrda)!=0)
            printf("Lozinke se ne podudaraju!\n");

        if(zeliPrekinuti())return;

    }while(strcmp(lozinka, potvrda)!=0);

    FILE *f=fopen(BAZA, "a");
    if(f==NULL){
        printf("Greska pri otvaranju baze.\n");
        return;
    }

    fprintf(f, "%s %s %s %d %d %d %s %s\n",
               ime, prezime, telefon, dan, mjesec, godina, email, lozinka);
    fclose(f);

    printf("\nRegistracija uspjesna.\n");
    printf("Prijavljivanje na sistem...\n");
}

