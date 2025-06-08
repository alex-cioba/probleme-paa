#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define teams 64

typedef struct arboreBinar
{
    int ID;
    struct arboreBinar* stanga;
    struct arboreBinar* dreapta;
}arbore;


arbore* castigator(arbore* echipa1, arbore* echipa2)
{
    arbore* new = (arbore*)malloc(sizeof(arbore));

    if(rand() % 2)
    {
        new->ID = echipa1->ID;
    }
    else
    {
        new->ID = echipa2->ID;
    }
    new->stanga = echipa1;
    new->dreapta = echipa2;

    return new;
}


void traseu(arbore* castigator)
{
    arbore* aux = castigator;

    int nrMeciuri = log2(teams);
    int* adversari = (int*)malloc(sizeof(int) * nrMeciuri);

    if(adversari == NULL)
    {
        perror("eroare malloc");
        return;
    }

    for(int i=nrMeciuri-1; i>=0; i--)
    {
        if(aux == NULL || aux->stanga == NULL || aux->dreapta == NULL)
        {
            break;
        }

        if(aux->ID == aux->stanga->ID)
        {
            adversari[i] = aux->dreapta->ID;
            aux = aux->stanga;
        }
        else
        {
            adversari[i] = aux->stanga->ID;
            aux = aux->dreapta;
        }

    }

    for(int i=0; i<nrMeciuri; i++)
    {
        printf("Runda %d: %d vs %d\n", i+1, aux->ID, adversari[i]);
    }

    free(adversari);
    printf("Castigatorul turneului: %d\n", aux->ID);
}

int meciuriTotale(int echipe)
{
    int meciuri = 0;

    while(echipe > 1)
    {
        echipe = echipe/2;
        meciuri = meciuri + echipe;
    }
    return meciuri;
}

void echipeEliminate(arbore* castigator)
{
    arbore* aux = castigator;

    printf("Echipe eliminate de castigator:");
    while(aux->stanga != NULL && aux->dreapta != NULL)
    {
        if(aux->stanga->ID == aux->ID)
        {
            printf(" %d", aux->dreapta->ID);
            aux = aux->stanga;
        }
        else
        {
            printf(" %d", aux->stanga->ID);
            aux = aux->dreapta;
        }
    }
}

arbore* desfasurareTurneu()
{
    arbore** rundaCurenta = (arbore**)malloc(sizeof(arbore*) * teams); //retine echipele rundei curente
    arbore** castigatori = (arbore**)malloc(sizeof(arbore*) * teams / 2); //retine castigatorii rundei curente
    int echipeRamase = teams;

    for(int i=0; i<teams; i++) //echipele de start
    {
        rundaCurenta[i] = (arbore*)malloc(sizeof(arbore));
        rundaCurenta[i]->ID = i;
        rundaCurenta[i]->stanga = NULL;
        rundaCurenta[i]->dreapta = NULL;
    }

    int runda=1;
    while(echipeRamase > 1)
    {
        printf("Runda %d\n", runda);
        for(int i=0; i<echipeRamase; i = i+2) //desfasurarea unei runde
        {
            castigatori[i/2] = castigator(rundaCurenta[i], rundaCurenta[i+1]);
            printf("%d vs %d | Castigator: %d\n", rundaCurenta[i]->ID, rundaCurenta[i+1]->ID, castigatori[i/2]->ID);
        }

        echipeRamase = echipeRamase/2;

        for(int i=0; i<echipeRamase; i++) //se actualizeaza rundaCurenta cu castigatorii
        {
            rundaCurenta[i] = castigatori[i];
        }
        runda++;
    }

    return castigatori[0];
}


int main()
{
    srand(time(NULL));
    arbore* turneu = desfasurareTurneu();
    printf("\nTraseu castigator:\n");
    traseu(turneu);
    printf("Numarul minim de meciuri necesare: %d\n", meciuriTotale(teams));
    echipeEliminate(turneu);

    return 0;
}
