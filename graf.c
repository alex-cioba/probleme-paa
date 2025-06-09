#include <stdio.h>
#include <limits.h>
#include <stdlib.h>


typedef struct graf
{
    int nrCartiere;
    int** matrice;
}graf;


graf* initializare(int nrCartiere)
{
    graf* nou = (graf*)malloc(sizeof(graf));
    nou->nrCartiere = nrCartiere;

    nou->matrice = (int**)malloc(sizeof(int*) * nrCartiere);
    for(int i=0; i<nrCartiere; i++)
    {
        nou->matrice[i] = (int*)malloc(sizeof(int) * nrCartiere);
        for(int j=0; j<nrCartiere; j++) //initializare cu 0
        {
            nou->matrice[i][j] = 0;
        }
    }

    return nou;
}


int cautaNod(int* vizitat, int* costuri, int nrCartiere)
{
    int min = INT_MAX;
    int ind = -1;
    for(int i=0; i<nrCartiere; i++)
    {
        if(vizitat[i] == 0 && costuri[i] < min)
        {
            min = costuri[i];
            ind = i;
        }
    }

    return ind;
}


void mst(graf* harta, int nrCartiere)
{
    int* cost = (int*)malloc(sizeof(int) * nrCartiere);
    int* vizitat = (int*)malloc(sizeof(int) * nrCartiere);
    int* parinte = (int*)malloc(sizeof(int) * nrCartiere);

    for(int i=0; i<nrCartiere; i++)
    {
        cost[i] = INT_MAX;
        vizitat[i] = 0;
        parinte[i] = -1;
    }

    cost[0] = 0;

    for(int i=0; i<nrCartiere; i++)
    {
        int ind = cautaNod(vizitat, cost, nrCartiere);
        vizitat[ind] = 1;
        
        //actualizare vecini
        for(int j=0; j<nrCartiere; j++)
        {
            if(vizitat[j] == 0 && harta->matrice[ind][j] < cost[j] && harta->matrice[ind][j] > 0)
            {
                cost[j] = harta->matrice[ind][j];
                parinte[j] = ind;
            }
        }
    }

    int s = 0;
    for(int i=1; i<nrCartiere; i++)
    {
        printf("%d - %d, cost %d\n", parinte[i], i, harta->matrice[i][parinte[i]]);
        s = s + cost[i];
    }

    printf("Suma totala: %d\n", s);
}


void eliberareGraf(graf* g)
{
    if (g == NULL)
    {
        return;
    }

    for(int i=0; i<g->nrCartiere; i++)
    {
        free(g->matrice[i]);
    }

    free(g->matrice);
    free(g);
}


int main()
{
    FILE* f;
    f = fopen("costuri.txt", "r");
    if (f == NULL)
    {
        perror("eroare deschidere fisier");
    }

    int nrCartiere = 0;
    fscanf(f, "%d", &nrCartiere);

    graf* harta = initializare(nrCartiere);


    for (int i=0; i<nrCartiere; i++)
    {
        for (int j=0; j<nrCartiere; j++)
        {
            fscanf(f, "%d", &harta->matrice[i][j]);
        }
    }

    fclose(f);

    mst(harta, nrCartiere);
    eliberareGraf(harta);

    return 0;
}
