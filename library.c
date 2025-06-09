#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max 5


typedef struct nod
{
    int eFrunza; //0 - nu, 1 - da
    int nrChei; //numarul de cuvinte din nodul acesta
    char *chei[max]; //cuvintele din nodul acesta
    struct nod* copii[max+1]; //copiii nodului
}nod;


nod* creare_nod()
{
    nod* nou = (nod*)malloc(sizeof(nod));
    nou->nrChei = 0;
    nou->eFrunza = 1;
    for(int i=0; i<=max; i++)
    {
        nou->copii[i] = NULL;
    }

    return nou;
}


nod* adaugare_nod(nod* arbore, char* cuvant)
{
    nod* aux = arbore;

    if(aux->eFrunza == 0) //daca nu e frunza trebuie sa mergem pe un copil
    {
        int i=0;
        while(i < aux->nrChei)
        {
            if(strcmp(cuvant, aux->chei[i]) < 0) //inseamna ca aici e cuvantul in ordinea alfabetica
            {
                break;
            }
            i++;
        }
        //daca s-a intrat pe if si s-a facut break inseamna ca i e indexul unde trebuie, altfel i e ultimul index si pe ala trebuie mers
        nod* rezultat = adaugare_nod(aux->copii[i], cuvant);
        if(rezultat != aux->copii[i])
        {
            char* cheie_urcata = rezultat->chei[0];
            nod* noul_copil_dreapta = rezultat->copii[1];

            for (int j = aux->nrChei; j > i; j--)
            {
                aux->copii[j + 1] = aux->copii[j];
            }
            
            for (int j = aux->nrChei - 1; j >= i; j--)
            {
                aux->chei[j + 1] = aux->chei[j];
            }

            aux->chei[i] = cheie_urcata;
            aux->copii[i + 1] = noul_copil_dreapta;

            aux->nrChei++;
            free(rezultat);
        }
        return aux;
    }
    else
    {
        if(aux->nrChei < max) //inseamna ca e loc
        {
            int i = aux->nrChei - 1;
            for(; i>=0; i--)
            {
                if(strcmp(cuvant, aux->chei[i]) < 0) //inseamna ca "cuvant" e inainte de chei[i]
                {
                    aux->chei[i+1] = aux->chei[i]; //muta cuvantul (pointerul catre el) o pozitie in dreapta
                }
                else //inseamna ca "cuvant" e dupa chei[i]
                {
                    break;
                }
            }

            //adaugam cuvantul la locul creat
            aux->chei[i+1] = (char*)malloc(strlen(cuvant) * sizeof(char) + 1);
            strcpy(aux->chei[i+1], cuvant);

            aux->nrChei++;
            return aux;
        }
        else //daca nu e loc (scindarea)
        {
            char* temp[max+1];
            for(int i=0; i<max; i++) //copiez cheile din aux->chei in vectorul temporar
            {
                temp[i] = aux->chei[i];
            }

            int i=aux->nrChei-1;
            for(; i>=0; i--) //adaugarea "cuvant" la locul potrivit in temp
            {
                if(strcmp(cuvant, temp[i]) < 0)
                {
                    temp[i+1] = temp[i]; //mutam cuvantul o pozitie la dreapta
                }
                else
                {
                    break;
                }

            }
            temp[i+1] = (char*)malloc(strlen(cuvant) * sizeof(char) + 1);
            strcpy(temp[i+1], cuvant);

            //al doilea nod de dupa scindare
            nod* frate_dreapta = creare_nod();
            frate_dreapta->eFrunza = 1;

            aux->nrChei = 0; //golim nodul aux (fratele din stanga de dupa scindare)

            //populare nod din stanga
            for(int j=0; j<2; j++) //pana la cheia promovata (2)
            {
                aux->chei[j] = temp[j];
                aux->nrChei++;
            }

            //populare nod din dreapta
            for(int j=3; j<=max; j++) //de la indicele urmator cheii promovate (2+1 = 3) la max (5)
            {
                frate_dreapta->chei[frate_dreapta->nrChei] = temp[j];
                frate_dreapta->nrChei++;
            }

            //nodul nou (parintele scindarii)
            char* cheie_promovata = temp[2];
            nod* parinte = creare_nod();
            parinte->chei[0] = cheie_promovata;
            parinte->nrChei = 1;
            parinte->eFrunza = 0;
            parinte->copii[0] = aux;
            parinte->copii[1] = frate_dreapta;

            return parinte;
        }
    }
}


void afisare_arbore(nod* arbore, int nivel) //DE LA GEMINI
{
    if (arbore == NULL)
    {
        return;
    }

    printf("Nivel %d (%d chei): [", nivel, arbore->nrChei);
    for (int i = 0; i < arbore->nrChei; i++)
    {
        printf("'%s'", arbore->chei[i]);
        if (i < arbore->nrChei - 1)
        {
            printf(", ");
        }
    }
    printf("]\n");
    if (!arbore->eFrunza)
    {
        for (int i = 0; i <= arbore->nrChei; i++)
        {
            afisare_arbore(arbore->copii[i], nivel + 1);
        }
    }
}



int main()
{
    nod* arboreB = creare_nod();

    arboreB = adaugare_nod(arboreB, "G");
    arboreB = adaugare_nod(arboreB, "M");
    arboreB = adaugare_nod(arboreB, "P");
    arboreB = adaugare_nod(arboreB, "X");
    arboreB = adaugare_nod(arboreB, "C");

    printf("Arborele initial:\n");
    afisare_arbore(arboreB, 0);

    arboreB = adaugare_nod(arboreB, "J");

    printf("\nArborele dupa insertia 'J':\n");
    afisare_arbore(arboreB, 0);

    return 0;
}
