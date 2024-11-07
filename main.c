#include "main.h"

int chargerData(int tabNumEtu[], int tabRefStage[], int tabNoteFinale[], int tabDept[], int tailleTab)
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

void decalerADroite(int tab[], int indice, int tlog)
{
    int j;
    for(j=tlog-1;j>=indice;j--)
        tab[j+1]=tab[j];
}
void decalerAGauche(int tab[], int indice, int tlog)
{
    int j;
    for(j=indice;j<tlog-1;j--)
        tab[j]=tab[j+1];
}

void sauvegarde(int tabMatieres[], int tabCoef[], int tlog)
{
    int i=0;
    FILE *flot;
    flot = fopen("data.txt","w");
    if(flot==NULL)
        printf("Pbm écriture fichier !");
    
    while(i<=tlog-1)
    {
        fprintf(flot,"%d\t%d\n",tabMatieres[i],tabCoef[i]);
        i=i+1;
    }
}

int affichageGlobal(void)
{
    int choix=0,n=0;
    

    while(choix<1||choix>4)
    {
        clearScreen();
        if(n==1)
            printf("Mauvais choix ! Ressaisissez :\n\n");
        printf("1. Vous êtes un membre du jury.\n");
        printf("2. Vous êtes un étudiant\n");
        printf("3. Vous êtes un responsable des stages\n");
        printf("4. Quitter\n\n");

        scanf("%d",&choix);
        n=1;
    }
    return choix;
}

int affichageJury(void)
{
    int choix=0,n=0;

    while(choix<1||choix>3)
    {
        clearScreen();
        printf("--------------------------------------------\n");
        printf("Vous êtes en tant que : Jury\n");
        printf("--------------------------------------------\n\n");
        if(n==1)
            printf("Mauvais choix ! Ressaisissez :\n\n");
        printf("1. Noter un étudiant\n");
        printf("2. Visualiser les notes d'un étudiant\n");
        printf("3. Quitter le programme\n\n");

        scanf("%d",&choix);
        n=1;
    }

    return choix;
}

void globalJury(void)
{
    int choix = affichageJury();
    int quit = 0;

    while (quit==0)
    {
        printf("%d",choix);
        switch (choix)
        {
            case 1:
                choix = affichageJury();
                break;
            case 2:
                choix = affichageJury();
                break;
            case 3:
                quit=1;
                printf("\n\nAu revoir !\n");
                break;
        }
    }
}

int affichageEtudiant(int stageRestant)
{
    int choix=0,n=0;

    while(choix<1||choix>5)
    {
        clearScreen();
        printf("--------------------------------------------\n");
        printf("Vous êtes en tant que : Etudiant\n");
        printf("--------------------------------------------\n\n");
        if(n==1)
            printf("Mauvais choix ! Ressaisissez :\n\n");
        printf("1. Consulter les stages éligibles (sans localisation)\n");
        printf("2. Consulter les stages éligibles (avec localisation par n° de département)\n");
        printf("3. Postuler à un stage (%d restants)\n",stageRestant);
        printf("4. Visualiser mes candidatures\n");
        printf("5. Quitter le programme\n\n");

        scanf("%d",&choix);
        n=1;
    }

    return choix;
}

/*[!] Faudra mettre à la place de 'void' la variable de stage restant*/
void globalEtudiant(void)
{
    int choix = affichageEtudiant(3);
    int quit = 0;

    while (quit==0)
    {
        switch (choix)
        {
            case 1:
                choix = affichageEtudiant(3);
                break;
            case 2:
                choix = affichageEtudiant(3);
                break;
            case 3:
                choix = affichageEtudiant(3);
                break;
            case 4:
                choix = affichageEtudiant(3);
                break;
            case 5:
                quit=1;
                printf("\n\nAu revoir !\n");
                break;
        }
        
    }
}

int affichageResponsable(void)
{
    int choix=0,n=0;

    while(choix<1||choix>8)
    {
        clearScreen();
        printf("--------------------------------------------\n");
        printf("Vous êtes en tant que : Responsable de stage\n");
        printf("--------------------------------------------\n\n");
        if(n==1)
            printf("Mauvais choix ! Ressaisissez :\n\n");
        printf("1. Ajouter ou supprimer une offre de stage\n");
        printf("2. Affecter un étudiant à un stage\n");
        printf("3. Consulter la liste des stages pourvus et non pourvus\n");
        printf("4. Consulter la liste des étudiants sans affectation\n");
        printf("5. Rechercher un stage par critère (numéro ou département)\n");
        printf("6. Saisir les notes finales des stages\n");
        printf("7. Afficher les notes par ordre décroissant\n");
        printf("8. Quitter le programme\n\n");

        scanf("%d",&choix);
        n=1;
    }

    return choix;
}

void globalResponsable(void)
{
    int choix = affichageResponsable();
    int quit = 0;

    while (quit==0)
    {
        switch (choix)
        {
            case 1:
                choix = affichageResponsable();
                break;
            case 2:
                choix = affichageResponsable();
                break;
            case 3:
                choix = affichageResponsable();
                break;
            case 4:
                choix = affichageResponsable();
                break;
            case 5:
                choix = affichageResponsable();
                break;
            case 6:
                choix = affichageResponsable();
                break;
            case 7:
                choix = affichageResponsable();
                break;
            case 8:
                quit=1;
                printf("\n\nAu revoir !\n");
                break;
        }
        
    }
}

void global(void)
{
    int choix=affichageGlobal();
    int quit=0;

    while (quit == 0)
    {
        switch (choix)
        {
            case 1:
                globalJury();
                quit=1;
                break;
            case 2:
                globalEtudiant();
                quit=1;
                break;
            case 3:
                globalResponsable();
                quit=1;
                break;
            case 4:
                quit=1;
                printf("\n\nAu revoir !\n");
                break;
        }
    }
}

void clearScreen(void) 
{
    for (int i = 0; i < 50; i++) {
        printf("\n");
    }
}