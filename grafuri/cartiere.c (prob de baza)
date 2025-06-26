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
    int* cost = (int*)malloc(sizeof(int) * nrCartiere); //cost[i] = k, k e cel mai ieftin cost posibil pt a conecta i la retea
    int* vizitat = (int*)malloc(sizeof(int) * nrCartiere); //vector cu nodurile vizitate, 1 da, 0 nu
    int* parinte = (int*)malloc(sizeof(int) * nrCartiere); //harta grafului pe care il construim, unde parinte[i] = j inseamna ruta i -- j

    for(int i=0; i<nrCartiere; i++) //initializare
    {
        cost[i] = INT_MAX;
        vizitat[i] = 0;
        parinte[i] = -1;
    }

    cost[0] = 0; //primul nod conectat, pornim din 0

    for(int i=0; i<nrCartiere; i++)
    {
        int ind = cautaNod(vizitat, cost, nrCartiere); //cautam cel mai ieftin nod de adaugat la moment
        vizitat[ind] = 1; //il marcam ca vizitat / adaugat
        
        //actualizare vecini cu noile costuri daca s-au ieftinit
        for(int j=0; j<nrCartiere; j++)
        {
            //nu a fost vizitat + costul noii conexiuni < cel mai mic cost de pana acum + exista ruta (>0)
            if(vizitat[j] == 0 && harta->matrice[ind][j] < cost[j] && harta->matrice[ind][j] > 0)
            {
                cost[j] = harta->matrice[ind][j]; //cel mai mic cost pt j (cost[j]) e acum ruta ind -- j
                parinte[j] = ind; //setam pe harta ruta ind -- j
            }
        }
    }

    //calculam costul total SI afisam graful creat (minim)
    int s = 0;
    for(int i=1; i<nrCartiere; i++)
    {
        printf("%d - %d, cost %d\n", parinte[i], i, harta->matrice[i][parinte[i]]);
        s = s + cost[i];
    }

    printf("Suma totala: %d\n", s);
}



void dfs(graf* g, int nod_curent, int* vizitat)
{
    //afisam nodul curent si il marcam ca vizitat
    printf("%d ", nod_curent);
    vizitat[nod_curent] = 1;

    for(int i=0; i<g->nrCartiere; i++) //parcurgem toata linia cu nodul curent
    {
        if(g->matrice[nod_curent][i] == 1 && vizitat[i] == 0) //daca exista muchie de la nodul curent la un altul i, si nu am vizitat i, il vizitam
        {
            dsf(g, i, vizitat);
        }
    }
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
