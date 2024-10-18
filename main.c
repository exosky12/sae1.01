#include "main.h"


int chargerData(int tabNumEtu[], int tabRefStage[], int tabNoteFinale[], int tailleTab)
{
    int i = 0;
    FILE *fichier = NULL;
    fichier = fopen("data.txt", "r");
    if (fichier == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier");
        return 0;
    }
    fscanf(fichier, "%d %d %d", &tabNumEtu[i], &tabRefStage[i], &tabNoteFinale[i]);
    while(!feof(fichier))
    {
        if (i > tailleTab)
        {
            printf("Erreur: taille du tableau depassée");
            return -1;
        }
        fscanf(fichier, "%d\t%d\t%d", &tabNumEtu[i], &tabRefStage[i], &tabNoteFinale[i]);
        i ++;
    }
    return i;
}

int rechercher(int val, int tab[], int nb, int *trouve)
{
    int i=0;
    for(i=0;i<nb;i++)
    {
        if(tab[i]==val)
        {
            *trouve = 1;
            return i;
        }
        else if(tab[i]>val)
        {
            *trouve = 0;
            return i;
        }
    }
    *trouve = 0;
    return i;
}

void decalerADroite(int tab[], int indice, int nbMatieres)
{
    int j;
    for(j=nbMatieres-1;j>=indice;j--)
        tab[j+1]=tab[j];
}
void decalerAGauche(int tab[], int indice, int nbMatieres)
{
    int j;
    for(j=indice;j<nbMatieres-1;j--)
        tab[j]=tab[j+1];
}

void sauvegarde(int tabMatieres[], int tabCoef[], int nbMatieres)
{
    int i=0;
    FILE *flot;
    flot = fopen("data.txt","w");
    if(flot==NULL)
        printf("Pbm écriture fichier !");
    
    while(i<=nbMatieres-1)
    {
        fprintf(flot,"%d\t%d\n",tabMatieres[i],tabCoef[i]);
        i=i+1;
    }
}