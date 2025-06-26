#include <stdio.h>
#include <stdlib.h>


void dfs(int adj[21][21], int id, int n, int vizitat[21])
{
    vizitat[id] = 1;

    for(int i=1; i<=n; i++)
    {
        if(adj[id][i] != 0 && vizitat[i] == 0)
        {
            dfs(adj, i, n, vizitat);
        }
    }
}


int main(int argc, char** argv)
{
    FILE* f = NULL;
    if((f = fopen(argv[1], "r")) == NULL)
    {
        perror("eroare deschidere fisier");
        exit(1);
    }

    int adj[21][21];
    int risc = 0;
    int nrPermisiuni = 0;

    fscanf(f, "%d", &risc);
    fscanf(f, "%d", &nrPermisiuni);

    int id = 0;
    for(int i=1; i<=nrPermisiuni; i++)
    {
        for(int j=1; j<=nrPermisiuni; j++)
        {
            fscanf(f, "%d", &id);
            adj[i][j] = id;
        }
    }

    fclose(f);

    int ct;
    int max = -1;
    int maxId[21] = {0};
    int maxCt=0;
    int riscId[21] = {0};
    for(int i=1; i <= nrPermisiuni; i++)
    {
        int vizitat[21] = {0};
        dfs(adj, i, nrPermisiuni, vizitat);

        ct = 0;
        for(int j=1; j<=nrPermisiuni; j++)
        {
            if(vizitat[j] == 1)
            {
                ct++;
            }
        }

        if(ct == max)
        {
            maxId[maxCt] = i;
            maxCt++;
        }
        if(ct > max)
        {
            max = ct;
            for(int k=0; k<maxCt; k++)
            {
                maxId[k] = 0;
            }
            maxId[0] = i;
            maxCt = 1;
        }

        if(ct > risc)
        {
            riscId[i] = 1;
        }
    }

    printf("Cele mai mari permisiuni: ");
    for(int i=0; i<maxCt; i++)
    {
        printf("%d ", maxId[i]);
    }
    printf("\n\n");
    
    printf("Riscuri: ");
    for(int i=1; i<=nrPermisiuni; i++)
    {
        if(riscId[i] == 1)
        {
            printf("%d ", i);
        }
    }


    return 0;
}
