#include <stdio.h>
#include <stdlib.h>


typedef struct Nod
{
    int cheie;
    struct Nod* stanga;
    struct Nod* dreapta;
}Nod_t;


Nod_t* creaza_nod(int cheie)
{
    Nod_t * nou = (Nod_t*)malloc(sizeof(Nod_t));

    nou->cheie = cheie;
    nou->stanga = NULL;
    nou->dreapta = NULL;

    return nou;
}

Nod_t* adauga_nod(Nod_t* radacina, int cheie)
{
    if(radacina == NULL)
    {
        return creaza_nod(cheie);
    }

    if(cheie < radacina->cheie)
    {
        radacina->stanga = adauga_nod(radacina->stanga, cheie);
    }
    else
    {
        radacina->dreapta = adauga_nod(radacina->dreapta, cheie);
    }

    return radacina;
}


void preordine(Nod_t* radacina)
{
    if(radacina == NULL)
    {
        return;
    }
    printf("%d ", radacina->cheie);
    preordine(radacina->stanga);
    preordine(radacina->dreapta);
}


int inaltime(Nod_t* arbore)
{
    if(arbore == NULL)
    {
        return 0;
    }

    int stanga = inaltime(arbore->stanga);
    int dreapta = inaltime(arbore->dreapta);

    if(stanga > dreapta)
    {
        return stanga + 1;
    }
    else
    {
        return dreapta + 1;
    }

}


int main()
{
    int n, cheie;
    printf("Nr. noduri: ");
    scanf("%d", &n);

    Nod_t* arbore = NULL;
    printf("Introduceti cheile: ");
    for(int i=0; i<n; i++)
    {
        scanf("%d", &cheie);
        arbore = adauga_nod(arbore, cheie);
    }

    /*
    arbore = adauga_nod(arbore, 5);
    arbore = adauga_nod(arbore, 3);
    arbore = adauga_nod(arbore, 4);
    arbore = adauga_nod(arbore, 1);
    arbore = adauga_nod(arbore, 7);
    arbore = adauga_nod(arbore, 6);
    arbore = adauga_nod(arbore, 8);
    arbore = adauga_nod(arbore, 2);
    */

    printf("Inaltimea: %d\n", inaltime(arbore));
    printf("Afisarea in preordine: ");
    preordine(arbore);
    printf("\n");

    return 0;
}
