#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct Nod
{
    struct Nod* copii[26]; //literele a-z
    int sfarsit; //0 - nu, 1 - da
}Nod_t;


int max = -1;
int nr_pagini = 1;


Nod_t* creaza_nod()
{
    Nod_t* nod_nou = (Nod_t*)malloc(sizeof(Nod_t));
    
    if(nod_nou == NULL)
    {
        perror("eroare malloc");
        return NULL;
    }

    nod_nou->sfarsit = 0;

    for(int i=0; i<26; i++)
    {
        nod_nou->copii[i] = NULL;
    }

    return nod_nou;
}


void adauga_cuvant(Nod_t* radacina, char* cuvant)
{
    int index;
    Nod_t* nod_curent = radacina;
    for(int i=0; i<strlen(cuvant); i++)
    {
        //verificam fiecare litera din cuvant
        index = cuvant[i] - 'a';

        //daca nu exista litera respectiva o cream
        if(nod_curent->copii[index] == NULL)
        {
            //trebuie adaugat nodul cu litera index
            nod_curent->copii[index] = creaza_nod();
        }

        //deplasam pe litera noua pt. a adauga urmatoarea litera ca si copilul aceste litere
        nod_curent = nod_curent->copii[index];
    }

    nod_curent->sfarsit = 1;
}


void afisare(Nod_t* radacina, char* cuvant, int index)
{
    if(radacina == NULL)
    {
        return;
    }

    if(radacina->sfarsit == 1)
    {
        cuvant[index] = '\0';
        printf("%s\n", cuvant);
    }

    for(int i=0; i<26; i++)
    {
        if(radacina->copii[i] != NULL)
        {
            cuvant[index] = 'a' + i;
            //printf("%c", i+'a');
            afisare(radacina->copii[i], cuvant, index+1);
        }
    }
}


void inaltime(Nod_t* radacina, int ct) //afisare() adaptata
{
    if(radacina == NULL)
    {
        return;
    }

    if(radacina->sfarsit == 1)
    {
        if(ct > max)
        {
            max = ct;
        }
    }

    for(int i=0; i<26; i++)
    {
        if(radacina->copii[i] != NULL)
        {
            inaltime(radacina->copii[i], ct+1);
        }
    }
}


int get_inaltime(Nod_t* arbore)
{
    max = -1;
    inaltime(arbore, 1);
    return max;
}


void pagini(Nod_t* radacina)
{
    if(radacina == NULL)
    {
        return;
    }

    for(int i=0; i<26; i++)
    {
        if(radacina->copii[i] != NULL)
        {
            nr_pagini++;
            pagini(radacina->copii[i]);
        }
    }
}


int get_pagini(Nod_t* radacina)
{
    nr_pagini = 1;
    pagini(radacina);
    return nr_pagini;
}


int main()
{
    Nod_t* arbore = creaza_nod();

    adauga_cuvant(arbore, "arma");
    adauga_cuvant(arbore, "armata");
    adauga_cuvant(arbore, "zi");
    adauga_cuvant(arbore, "zinc");

    char cuvant[50];
    afisare(arbore, cuvant, 0);

    printf("Inaltime arbore: %d\n", get_inaltime(arbore));
    printf("Nr. de pagini: %d\n", get_pagini(arbore));

    return 0;
}
