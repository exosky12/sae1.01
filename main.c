#include "main.h"

<<<<<<< HEAD
=======

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
>>>>>>> e87738e (s)
