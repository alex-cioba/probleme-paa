#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Student
{
    char* nume;
    char* email;
}Student_t;


typedef struct Nod
{
    int id; //cheie
    char* titlu;
    char* profesor;
    Student_t** studenti;
    struct Nod* stanga;
    struct Nod* dreapta;
}Nod_t;


Nod_t* creare_nod(int cheie, char* titlu, char* profesor)
{
    Nod_t* nod_nou = (Nod_t*)malloc(sizeof(Nod_t));

    nod_nou->id = cheie;

    nod_nou->titlu = (char*)malloc(strlen(titlu) + 1);
    nod_nou->profesor = (char*)malloc(strlen(profesor) + 1);
    strcpy(nod_nou->titlu, titlu);
    strcpy(nod_nou->profesor, profesor);

    nod_nou->studenti = NULL;
    nod_nou->stanga = NULL;
    nod_nou->dreapta = NULL;

    return nod_nou;
}


Nod_t* adaugare_nod(Nod_t* radacina, Nod_t* nod_nou)
{
    if(radacina == NULL)
    {
        return nod_nou;
    }

    if(nod_nou->id < radacina->id)
    {
        radacina->stanga = adaugare_nod(radacina->stanga, nod_nou);
    }
    else
    {
        radacina->dreapta = adaugare_nod(radacina->dreapta, nod_nou);
    }

    return radacina;
}

void afisare_studenti(Student_t** studenti)
{
    if(studenti == NULL)
    {
        printf(" -\n");
    }
    else
    {
        printf("%s (%s)", studenti[0]->nume, studenti[0]->email);

        int i=1;
        while(studenti[i] != NULL)
        {
            printf(", %s (%s)", studenti[i]->nume, studenti[i]->email);
            i++;
        }
        printf("\n");
    }
}

void afisare_nod(Nod_t* node)
{
    printf("ID: %d\n", node->id);
    printf("Titlu: %s\n", node->titlu);
    printf("Profesor: %s\n", node->profesor);
    printf("Studenti: ");
    afisare_studenti(node->studenti);
    printf("\n");
}


void afisare(Nod_t* arbore) //inordine
{
    if(arbore != NULL)
    {
        afisare(arbore->stanga);
        afisare_nod(arbore);
        afisare(arbore->dreapta);
    }
}



int main()
{
    Nod_t* arbore = NULL;
    
    arbore = adaugare_nod(arbore, creare_nod(23, "matematica", "Popescu Alexandru"));
    arbore = adaugare_nod(arbore, creare_nod(13, "romana", "Andrei Sirbu"));
    arbore = adaugare_nod(arbore, creare_nod(24, "istorie", "Mihaela Toader"));
    return 0;
}
