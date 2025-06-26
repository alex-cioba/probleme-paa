#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Nod
{
    struct Nod* copii[26]; // a-z
    int sfarsit; // 0 - nu, 1 - da
}Nod_t;


float nr_cuvinte = 0;
float suma_litere = 0;


Nod_t* creeaza_nod()
{
    Nod_t* nod_nou = (Nod_t*)malloc(sizeof(Nod_t));
    for(int i=0; i<26; i++)
    {
        nod_nou->copii[i] = NULL;
    }
    nod_nou->sfarsit = 0;

    return nod_nou;
}


void adauga_cuvant(Nod_t* radacina, char* cuvant)
{
    Nod_t* nod_curent = radacina;
    int index;

    for(int i=0; i<strlen(cuvant); i++)
    {
        index = cuvant[i] - 'a';
        if(nod_curent->copii[index] == NULL)
        {
            //nu exista litera -> o adaugam
            nod_curent->copii[index] = creeaza_nod();
        }

        nod_curent = nod_curent->copii[index];
    }

    nod_curent->sfarsit = 1;
}


void afisare_helper(Nod_t* radacina, char* buffer, int index)
{
    if(radacina->sfarsit == 1)
    {
        buffer[index] = '\0';
        printf("%s\n", buffer);
    }

    for(int i=0; i<26; i++)
    {
        if(radacina->copii[i] != NULL)
        {
            buffer[index] = i + 'a';
            afisare_helper(radacina->copii[i], buffer, index+1);
        }
    }
}


void afisare(Nod_t* arbore)
{
    if(arbore == NULL)
    {
        printf("Arborele este gol\n");
        return;
    }

    printf("Cuvintele din arbore sunt:\n");
    char buffer[26];
    afisare_helper(arbore, buffer, 0);
}


void dimensiuni(Nod_t* radacina, int ct) //afisare adaptata
{
    if(radacina->sfarsit == 1)
    {
        nr_cuvinte++;
        suma_litere = suma_litere + ct;
    }

    for(int i=0; i<26; i++)
    {
        if(radacina->copii[i] != NULL)
        {
            dimensiuni(radacina->copii[i], ct+1);
        }
    }
}


float lungime_medie(Nod_t* arbore)
{
    if(arbore == NULL)
    {
        return 0;
    }
    
    nr_cuvinte = 0;
    suma_litere = 0;
    dimensiuni(arbore, 0);
    
    return (float)suma_litere/nr_cuvinte;
}



int main()
{
    Nod_t* arbore = creeaza_nod();

    adauga_cuvant(arbore, "aur");
    adauga_cuvant(arbore, "argint");
    adauga_cuvant(arbore, "hidrogen");
    adauga_cuvant(arbore, "heliu");
    adauga_cuvant(arbore, "fier");

    afisare(arbore);
    printf("Lungimea medie a cuvintelor: %f\n", lungime_medie(arbore));

    return 0;
}
