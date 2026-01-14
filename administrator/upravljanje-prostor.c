#include <stdio.h>
#include <string.h>
#include "upravljanje-prostor.h"

Prostor prostori[MAX_PROSTORA];
int brojProstora=0;

void prikaziProstore(){printf("\n--- PROSTORI ---\n"); for(int i=0;i<brojProstora;i++) printf("%d. %s\n",prostori[i].id,prostori[i].naziv);}

void dodajProstor(){Prostor p; p.id=brojProstora+1; p.brojStolova=0; printf("Naziv prostora: "); scanf(" %29[^\n]",p.naziv); prostori[brojProstora++]=p; printf("✔ Prostor dodat\n");}

void izmijeniProstor(){int id; prikaziProstore(); printf("ID prostora: "); scanf("%d",&id); for(int i=0;i<brojProstora;i++){if(prostori[i].id==id){printf("Novi naziv: "); scanf(" %29[^\n]",prostori[i].naziv); printf("✔ Izmjena uspjesna\n"); return;}}}

void obrisiProstor(){int id; prikaziProstore(); printf("ID prostora za brisanje: "); scanf("%d",&id); for(int i=0;i<brojProstora;i++){if(prostori[i].id==id){if(prostori[i].brojStolova>0){printf("❌ Brisanje onemoguceno – prostor ima stolove\n"); return;} for(int j=i;j<brojProstora-1;j++) prostori[j]=prostori[j+1]; brojProstora--; printf("✔ Prostor obrisan\n"); return;}}}

void prikaziStolove(Prostor *p){printf("\n--- STOLOVI (%s) ---\n",p->naziv); for(int i=0;i<p->brojStolova;i++){printf("Sto ID: %d\n",p->stolovi[i]);}}

void dodajSto(Prostor *p){int id; printf("Unesite ID novog stola: "); scanf("%d",&id); p->stolovi[p->brojStolova++]=id; printf("✔ Sto dodat\n");}

void izmijeniSto(Prostor *p){int stari,novi; prikaziStolove(p); printf("ID stola za izmjenu: "); scanf("%d",&stari); for(int i=0;i<p->brojStolova;i++){if(p->stolovi[i]==stari){printf("Novi ID stola: "); scanf("%d",&novi); p->stolovi[i]=novi; printf("✔ Sto izmijenjen\n"); return;}}}

void obrisiSto(Prostor *p){int id; prikaziStolove(p); printf("ID stola za brisanje: "); scanf("%d",&id); for(int i=0;i<p->brojStolova;i++){if(p->stolovi[i]==id){for(int j=i;j<p->brojStolova-1;j++) p->stolovi[j]=p->stolovi[j+1]; p->brojStolova--; printf("✔ Sto obrisan\n"); return;}}}

void meniStolova(Prostor *p){int izbor; do{printf("\n--- STOLOVI (%s) ---\n1. Prikaz stolova\n2. Dodaj sto\n3. Izmijeni sto\n4. Obrisi sto\n0. Povratak\nIzbor: ",p->naziv); scanf("%d",&izbor); switch(izbor){case 1: prikaziStolove(p); break; case 2: dodajSto(p); break; case 3: izmijeniSto(p); break; case 4: obrisiSto(p); break;}}while(izbor!=0);}

void upravljanjeProstorima(){int izbor,id; do{printf("\n--- UPRAVLJANJE PROSTORIMA ---\n1. Prikaz prostora\n2. Dodaj prostor\n3. Izmijeni prostor\n4. Obrisi prostor\n5. Upravljaj stolovima\n0. Odjava\nIzbor: "); scanf("%d",&izbor);
switch(izbor){case 1: prikaziProstore(); break; case 2: dodajProstor(); break; case 3: izmijeniProstor(); break; case 4: obrisiProstor(); break;
case 5: prikaziProstore(); printf("ID prostora: "); scanf("%d",&id); for(int i=0;i<brojProstora;i++) if(prostori[i].id==id) meniStolova(&prostori[i]); break;}}while(izbor!=0);}
