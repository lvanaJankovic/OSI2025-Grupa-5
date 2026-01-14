#include <stdio.h>
#include <string.h>
#include "upravljanje-meni.h"

Stavka meni[MAX_MENI];
int brojStavkiMenija = 0;

int ucitajMeni(const char *imeFajla) {
    FILE *f=fopen(imeFajla,"r");
    if(!f){printf("Greska pri otvaranju menija\n");return 0;}
    brojStavkiMenija=0;
    char linija[256]; fgets(linija,sizeof(linija),f);
    while(fgets(linija,sizeof(linija),f)){
        Stavka s;
        if(sscanf(linija,"%d,%29[^,],%lf",&s.rb,s.naziv,&s.cijena)==3)
            meni[brojStavkiMenija++]=s;
        if(brojStavkiMenija>=MAX_MENI) break;
    }
    fclose(f); return 1;
}

void sacuvajMeni(const char *imeFajla) {
    FILE *f=fopen(imeFajla,"w");
    if(!f){printf("Ne mogu sacuvati meni!\n");return;}
    fprintf(f,"rb,naziv,cijena\n");
    for(int i=0;i<brojStavkiMenija;i++)
        fprintf(f,"%d,%s,%.2f\n",meni[i].rb,meni[i].naziv,meni[i].cijena);
    fclose(f);
}

void prikaziMeni(){printf("\n--- MENI ---\n");for(int i=0;i<brojStavkiMenija;i++)
    printf("%d. %s - %.2f KM\n",meni[i].rb,meni[i].naziv,meni[i].cijena);}

void dodajStavku(){
    if(brojStavkiMenija>=MAX_MENI){printf("Meni je pun!\n");return;}
    Stavka s; s.rb=(brojStavkiMenija==0)?1:meni[brojStavkiMenija-1].rb+1;
    printf("Naziv: "); scanf(" %29[^\n]",s.naziv);
    printf("Cijena: "); scanf("%lf",&s.cijena);
    meni[brojStavkiMenija++]=s; sacuvajMeni("meni.csv");
    printf("✔ Stavka dodana!\n");
}

void izmijeniStavku(){int rb; prikaziMeni(); printf("RB stavke za izmjenu: "); scanf("%d",&rb);
for(int i=0;i<brojStavkiMenija;i++){if(meni[i].rb==rb){
printf("Novi naziv: "); scanf(" %29[^\n]",meni[i].naziv);
printf("Nova cijena: "); scanf("%lf",&meni[i].cijena);
sacuvajMeni("meni.csv"); printf("✔ Stavka izmijenjena!\n"); return;}}
printf("Stavka nije pronadjena!\n");}

void obrisiStavku(){int rb; prikaziMeni(); printf("RB stavke za brisanje: "); scanf("%d",&rb);
for(int i=0;i<brojStavkiMenija;i++){if(meni[i].rb==rb){
for(int j=i;j<brojStavkiMenija-1;j++) meni[j]=meni[j+1];
brojStavkiMenija--; sacuvajMeni("meni.csv"); printf("✔ Stavka obrisana!\n"); return;}}
printf("Stavka nije pronadjena!\n");}

void administratorMeni(){
    int izbor;
    do{
        printf("\n--- ADMINISTRATOR MENI ---\n1. Pregled menija\n2. Dodaj stavku\n3. Izmijeni stavku\n4. Obrisi stavku\n0. Odjava\nIzbor: ");
        scanf("%d",&izbor);
        switch(izbor){case 1: prikaziMeni(); break; case 2: dodajStavku(); break; case 3: izmijeniStavku(); break; case 4: obrisiStavku(); break; case 0: printf("Odjava...\n"); break; default: printf("Pogresan izbor!\n");}
    }while(izbor!=0);
}
