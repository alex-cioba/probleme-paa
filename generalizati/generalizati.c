#include <stdio.h>
#include <stdlib.h>


typedef struct Nod
{
    int cheie;
    struct Nod** copii;
    int nr_copii;
}Nod_t;



Nod_t* creare_nod(int cheie)
{
    Nod_t* nod_nou = (Nod_t*)malloc(sizeof(Nod_t));

    if(nod_nou == NULL)
    {
        perror("eroare malloc");
        return NULL;
    }

    nod_nou->cheie = cheie;
    nod_nou->copii = NULL;
    nod_nou->nr_copii = 0;

    return nod_nou;
}


Nod_t* cauta_parinte(Nod_t* arbore, int parinte)
{
    if(arbore == NULL)
    {
        return NULL;
    }

    if(arbore->cheie == parinte)
    {
        return arbore;
    }

    Nod_t* nod_gasit = NULL;
    for(int i=0; i<arbore->nr_copii; i++)
    {
        nod_gasit = cauta_parinte(arbore->copii[i], parinte);
        if(nod_gasit != NULL)
        {
            return nod_gasit;
        }
    }

    return NULL;
}



void adaugare_nod(Nod_t* radacina, int cheie, int parinte)
{
    Nod_t* nod_parinte = cauta_parinte(radacina, parinte);

    if(nod_parinte == NULL)
    {
        printf("parintele nu exista\n");
        return;
    }

    Nod_t* nod_nou = creare_nod(cheie);

    nod_parinte->nr_copii++; // 1 copil in plus, cel nou
    nod_parinte->copii = realloc(nod_parinte->copii, nod_parinte->nr_copii * sizeof(Nod_t*));
    nod_parinte->copii[nod_parinte->nr_copii - 1] = nod_nou;
}


void afisare(Nod_t* nod_curent, int nivel)
{
    if(nod_curent == NULL)
    {
        return;
    }

    for(int i=0; i<nivel; i++)
    {
        printf("  ");
    }

    printf("%d\n", nod_curent->cheie);

    for(int i=0; i<nod_curent->nr_copii; i++)
    {
        afisare(nod_curent->copii[i], nivel+1);
    }
}




int main()
{
    Nod_t* arbore = creare_nod(4);
    adaugare_nod(arbore, 5, 4);
    adaugare_nod(arbore, 6, 5);
    adaugare_nod(arbore, 3, 5);
    adaugare_nod(arbore, 10, 6);
    
    afisare(arbore, 0);
    return 0;
}
