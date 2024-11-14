#include "main.h"

int chargerDataEtu(int tabNumEtu[], int tabRefStageEtu[], float tabNoteFinale[], int tailleTab)
{
    // Format attendu dans data_etu.txt : numEtudiant refStage note
    // Une ligne par étudiant, séparés par des espaces
    // Exemple : 12345 67890 15
    
    int i = 0;
    FILE *fichier_etu;
    
    fichier_etu = fopen("data_etu.txt", "r");
    
    if (fichier_etu == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier 'data_etu.txt' !");
        return 0;
    }
    fscanf(fichier_etu, "%d %d %f", &tabNumEtu[i], &tabRefStageEtu[i], &tabNoteFinale[i]);
    while(!feof(fichier_etu))
    { 
        i ++;
        if (i > tailleTab)
        {
            printf("Erreur: taille du tableau depassée");
            return -1;
        }
        fscanf(fichier_etu, "%d %d %f", &tabNumEtu[i], &tabRefStageEtu[i], &tabNoteFinale[i]);
    }
    fclose(fichier_etu);
    return i;
}

int chargerDataStage(int tabNumEtu[], int tabRefStageEtu[], int tabRefStage[] , int tabDept[], int tabPourvu[], int tabNBCand[], int listeCand[][3], int tlogListeCand[], int tailleTab, int tlog)
{
    // Format attendu dans data_stage.txt :
    // refStage departement estPourvu(0/1) [nbCandidatures candidat1 candidat2 ...]
    // La partie entre [] n'existe que si estPourvu = 0
    
    int j;
    int i = 0;
    FILE *fichier_stage;
    fichier_stage = fopen("data_stage.txt","r");
    
    if (fichier_stage == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier 'data_stage.txt' !");
        return 0;
    }
    fscanf(fichier_stage, "%d %d %d",&tabRefStage[i], &tabDept[i],&tabPourvu[i]);
    if(tabPourvu[i] == 0)
    {
        if(tabNBCand[i] > 0)
        {
            fscanf(fichier_stage,"%d",&tabNBCand[i]);
            printf("%d\n",tabNBCand[i]);
            for(j = 0; j<tabNBCand[i];j++)
            {
                fscanf(fichier_stage, "%d", &listeCand[i][j]);
                printf("%d\n",listeCand[i][j]);
            }
            tlogListeCand[i]=j;
        }
    }
    else if (tabPourvu[i] == 1) 
    {
        int tmp; // variable temporaire pour lire et ignorer
        fscanf(fichier_stage, "%d", &tmp); // ignorer le nombre d'étudiants
    }
    
    while(!feof(fichier_stage))
    {
        i ++;
        if (i > tailleTab)
        {
            printf("Erreur: taille du tableau depassée");
            return -1;
        }
        fscanf(fichier_stage, "%d %d %d",&tabRefStage[i], &tabDept[i],&tabPourvu[i]);
        if(tabPourvu[i] == 0)
        {
            fscanf(fichier_stage,"%d",&tabNBCand[i]);
            printf("%d\n",tabNBCand[i]);
            if(tabNBCand[i] > 0)
            {
                for(j = 0; j<tabNBCand[i];j++)
                {
                    fscanf(fichier_stage, "%d", &listeCand[i][j]);
                    printf("%d\n",listeCand[i][j]);
                }
                tlogListeCand[i]=j;
            }
        }
        else if (tabPourvu[i] == 1) 
        {
            int tmp; // variable temporaire pour lire et ignorer
            fscanf(fichier_stage, "%d", &tmp);  // ignorer le nombre d'étudiants
        }
    }
    fclose(fichier_stage);
    return i;
}

int RechercheIndiceMax(float tabNote[],int debut, int tlog)
{
    int indice_max = debut;
    for (int i = debut + 1; i < tlog; i++)
    {
        if (tabNote[i] > tabNote[indice_max])
        {
            indice_max = i;
        }
    }
    return indice_max;
}

int rechercherSansTriage(int val, int tab[], int tlog, int *trouve)
{
    // trouve = 1 si valeur trouvée, 0 sinon
    // retourne l'index si trouvé, -1 sinon
    
    int i;
    for(i=0;i<=tlog;i++)
    {
        if(tab[i]==val)
        {
            *trouve = 1;
            return i;
        }
    }
    *trouve = 0;
    return -1;
}

void floatDecalerAGauche(float tab[], int indice, int tlog)
{
    // ATTENTION: Cette fonction écrase la valeur à l'indice spécifié
    // Les éléments sont décalés de droite à gauche à partir de l'indice
    // Exemple: [1,2,3,4,5] avec indice=2 devient [1,2,4,5,_]
    
    int j;
    for(j=indice;j<tlog-1;j++)
        tab[j]=tab[j+1];
}

void intDecalerAGauche(int tab[], int indice, int tlog)
{
    // ATTENTION: Cette fonction écrase la valeur à l'indice spécifié
    // Les éléments sont décalés de droite à gauche à partir de l'indice
    // Exemple: [1,2,3,4,5] avec indice=2 devient [1,2,4,5,_]
    
    int j;
    for(j=indice;j<tlog-1;j++)
        tab[j]=tab[j+1];
}

// Fonction pour échanger les éléments de trois tableaux aux indices donnés
void echangerElements(int tabNumEtu[], int tabRefStageEtu[], float tabNoteFinale[], int i, int j)
{
    // échange des numéros d'étudiants
    int tmpNumEtu = tabNumEtu[i];
    tabNumEtu[i] = tabNumEtu[j];
    tabNumEtu[j] = tmpNumEtu;

    // échange des références de stage
    int tmpRefStage = tabRefStageEtu[i];
    tabRefStageEtu[i] = tabRefStageEtu[j];
    tabRefStageEtu[j] = tmpRefStage;

    // échange des notes finales
    float tmpNote = tabNoteFinale[i];
    tabNoteFinale[i] = tabNoteFinale[j];
    tabNoteFinale[j] = tmpNote;
}

int sauvegarder(int tabNumEtu[], int tabRefStageEtu[], float tabNoteFinale[], int *tailleEtu,
                 int tabRefStage[], int tabDept[], int tabPourvu[], int tabNBCand[], 
                 int listeCand[][3], int tlogListeCand[], int tlog) 
{
    FILE *fichier_etu, *fichier_stage;
    
    // Sauvegarde des données des étudiants
    fichier_etu = fopen("data_etu.txt", "w");
    if (fichier_etu == NULL) {
        printf("Erreur lors de l'ouverture du fichier 'data_etu.txt' !\n");
        return 0;
    }
    
    // Écriture de toutes les données étudiants, même si ref stage = 0
    for (int i = 0; i < *tailleEtu; i++) {
        fprintf(fichier_etu, "%d %d %.2f\n", tabNumEtu[i], tabRefStageEtu[i], tabNoteFinale[i]);
    }
    fclose(fichier_etu);
    
    // Sauvegarde des données des stages
    fichier_stage = fopen("data_stage.txt", "w");
    if (fichier_stage == NULL) 
    {
        printf("Erreur lors de l'ouverture du fichier 'data_stage.txt' !\n");
        return 0;
    }
    
    // Écriture de tous les stages, même si ref = 0
    for (int i = 0; i <= tlog; i++) {
        // Ligne vide entre chaque stage
        if(i>=1) 
            fprintf(fichier_stage, "\n");
        // Première ligne : référence et département
        fprintf(fichier_stage, "%d %02d\n", tabRefStage[i], tabDept[i]);
        
        // Deuxième ligne : statut
        fprintf(fichier_stage, "%d\n", tabPourvu[i]);
        
        // Troisième ligne : candidatures si non pourvu
        if (tabPourvu[i] == 0 && tabNBCand[i] >= 0) 
        {
            fprintf(fichier_stage, "%d", tabNBCand[i]);
            for (int j = 0; j < tlogListeCand[i]; j++) {
                fprintf(fichier_stage, "\n%d", listeCand[i][j]);
            }
        }
        else 
        {
            int trouve = 0;
            fprintf(fichier_stage, "%d", tabNumEtu[rechercherSansTriage(tabRefStage[i], tabRefStageEtu, *tailleEtu, &trouve)]);
        }  
    }
    fclose(fichier_stage);
    return 1;
}

void rangerParNoteFinale(int tabNumEtu[], int tabRefStageEtu[], float tabNoteFinale[], int tailleEtu)
{
    int indice_max = 0;

    // Tri par sélection
    for (int i = 0; i < tailleEtu - 1; i++) 
    {
        // Trouver l'indice de la note maximale dans la portion non triée
        indice_max = RechercheIndiceMax(tabNoteFinale, i, tailleEtu);
        
        // Échanger les éléments pour placer la note maximale au début de la portion non triée
        if (indice_max != i) 
        {
            echangerElements(tabNumEtu, tabRefStageEtu, tabNoteFinale, i, indice_max);
        }
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

    while(choix<1||choix>4)
    {
        clearScreen();
        printf("--------------------------------------------\n");
        printf("Vous êtes connecté en tant que : Jury\n");
        printf("--------------------------------------------\n\n");
        if(n==1)
            printf("Mauvais choix ! Ressaisissez :\n\n");
        printf("1. Noter un étudiant\n");
        printf("2. Visualiser les notes d'un étudiant\n");
        printf("3. Visualiser les notes des étudiants par ordre decroissant\n");
        printf("4. Quitter le programme\n\n");

        scanf("%d",&choix);
        n=1;
    }

    return choix;
}

int noterEtudiant(int numEtu[], int refsEtuStage[], float notesFinales[], int tailleEtu) 
{
    // IMPORTANT: Retourne 0 si succès, -1 si erreur, -2 si stage non affecté, -3 si note finale deja saisie
    int numEtudiant, trouve, position, nbNote;
    float note, somme=0, moyenne;
    
    printf("\nEntrez le numéro de l'étudiant à noter : ");
    scanf("%d", &numEtudiant);
    
    position = rechercherSansTriage(numEtudiant, numEtu, tailleEtu, &trouve);
    
    if(trouve == 0) {
        printf("Erreur : étudiant non trouvé.\n");
        return -1;
    }
    
    if(refsEtuStage[position] == -1) {
        printf("Erreur : cet étudiant n'a pas de stage affecté.\n");
        
        printf("\nAppuyez sur Entrée pour continuer...");
        getchar();
        getchar();
        return -2;
    }

    if(notesFinales[position] != -1) {
        printf("Erreur : cet étudiant a deja une note finale.\n");
        
        printf("\nAppuyez sur Entrée pour continuer...");
        getchar();
        getchar();
        return -3;
    }
    
    for(nbNote=1;nbNote<=3;nbNote++)
    {
        switch (nbNote)
        {
            case 1:
            {
                printf("Entrez la note d’entreprise (0-20) : ");
                scanf("%f", &note);
                while(note < 0 || note > 20) 
                {
                    printf("Erreur : la note doit être comprise entre 0 et 20.\nRéentrez la note d’entreprise (0-20) : ");
                    scanf("%f", &note);
                }
                somme = somme+note*2;
                break;
            }
            case 2:
            {
                printf("Entrez la note du rapport (0-20) : ");
                scanf("%f", &note);
                while(note < 0 || note > 20) 
                {
                    printf("Erreur : la note doit être comprise entre 0 et 20.\nRéentrez la note du rapport (0-20) : ");
                    scanf("%f", &note);
                }
                somme = somme+note;
                break;
            }
            case 3:
            {
                printf("Entrez la note de soutenance (0-20) : ");
                scanf("%f", &note);
                while(note < 0 || note > 20) 
                {
                    printf("Erreur : la note doit être comprise entre 0 et 20.\nRéentrez la note de soutenance (0-20) : ");
                    scanf("%f", &note);
                }
                somme = somme+note;
                break;
            }
        }
    }

    moyenne = somme / 4.0;
    notesFinales[position] = moyenne;
    rangerParNoteFinale(numEtu, refsEtuStage, notesFinales, tailleEtu);
    for(int i=0;i<tailleEtu;i++)
    {
        printf("%d\t%d\t%.2f\n", numEtu[i], refsEtuStage[i], notesFinales[i]);
    }
    printf("Note enregistrée avec succès.\n");

    
    printf("\nAppuyez sur Entrée pour continuer...");
    getchar();
    getchar();
    return 0;
}

void visualiserNotesEtudiant(int numEtu[], int refsEtuStage[], float notesFinales[], int tailleEtu) {
    // Affiche les informations d'un étudiant : numéro, stage, note
    // IMPORTANT: Indique si l'étudiant n'a pas de stage ou pas de note
    // Format d'affichage : Numéro | Ref Stage | Note
    
    int numEtudiant, trouve, position;
    
    printf("\nEntrez le numéro de l'étudiant : ");
    scanf("%d", &numEtudiant);
    
    position = rechercherSansTriage(numEtudiant, numEtu, tailleEtu, &trouve);
    
    if(trouve == 0) {
        printf("Erreur : étudiant non trouvé.\n");

        printf("\nAppuyez sur Entrée pour continuer...");
        getchar();
        getchar();
        return;
    }
    
    printf("\n-------- Informations de l'étudiant %d --------\n\n", numEtudiant);
    printf("Numéro étudiant : %d\n", numEtu[position]);
    
    if(refsEtuStage[position] == 0) {
        printf("Stage : Non affecté\n");
        printf("Note : Pas de note (pas de stage)\n");
    } else {
        printf("Référence du stage : %d\n", refsEtuStage[position]);
        if(notesFinales[position] == -1) {
            printf("Note : Pas encore noté\n");
        } else {
            printf("Note finale : %.2f/20\n", notesFinales[position]);
        }
    }
    
    printf("\nAppuyez sur Entrée pour continuer...");
    getchar();
    getchar();
}
void afficherNotesDecroissant(int numEtu[], int refsEtuStage[], float notesFinales[], int tailleEtu) 
{
    // IMPORTANT: Ne modifie pas les tableaux originaux
    // Utilise des tableaux temporaires pour le tri
    // N'affiche que les étudiants ayant :
    // 1. Un stage affecté (refsEtuStage != 0)
    // 2. Une note saisie (notesFinales != -1)
    
    int i, nbEtuAvecNote = 0, nbEtuSansNote = 0;
    
    printf("\n");
    
    for(i = 0; i < tailleEtu; i++) {
        if(refsEtuStage[i] != -1 && notesFinales[i] != -1) {
            nbEtuAvecNote = nbEtuAvecNote + 1;
            printf("%d\t%d\t%.2f\n", numEtu[i], refsEtuStage[i], notesFinales[i]);
        }
        else if(refsEtuStage[i] != -1 && notesFinales[i] == -1) {
            printf("%d\t%d\t%s\n", numEtu[i], refsEtuStage[i], "Stage en cours");
            nbEtuSansNote = nbEtuSansNote + 1;
        }
    }
    
    printf("\nNombre total d'étudiants notés : %d\n", nbEtuAvecNote);
    printf("Nombre total d'étudiants sans note : %d\n", nbEtuSansNote);
    
    printf("\nAppuyez sur Entrée pour continuer...");
    getchar();
    getchar();
}
void globalJury(int tabNumEtu[], int tabRefStageEtu[], float tabNoteFinale[], int tailleTab, int tailleEtu) {
    
    int choix = affichageJury();
    int quit = 0;

    while(quit == 0) {
        switch(choix) {
            case 1:
                noterEtudiant(tabNumEtu, tabRefStageEtu, tabNoteFinale, tailleEtu);
                choix = affichageJury();
                break;
            case 2:
                visualiserNotesEtudiant(tabNumEtu, tabRefStageEtu, tabNoteFinale, tailleEtu);
                choix = affichageJury();
                break;
            case 3:
                afficherNotesDecroissant(tabNumEtu, tabRefStageEtu, tabNoteFinale, tailleEtu);
                choix = affichageJury();
                break;
            case 4:
                quit = 1;
                printf("\n\nAu revoir !\n");
                break;
        }
    }
}


int affichageEtudiant(int stageRestant)
{
    int choix=0,n=0;

    while(choix<1||choix>6)
    {
        clearScreen();
        printf("--------------------------------------------\n");
        printf("Vous êtes connecté en tant que : Etudiant\n");
        printf("--------------------------------------------\n\n");
        if(n==1)
            printf("Mauvais choix ! Ressaisissez :\n\n");
        printf("1. Consulter les stages éligibles (sans localisation)\n");
        printf("2. Consulter les stages éligibles (avec localisation par n° de département)\n");
        if(stageRestant == -1)
        {
            printf("3. Postuler à un stage ([!] déjà affecté)\n");
            printf("4. Visualiser mes candidatures ([!] non disponibles)\n");
            printf("5. Voir le détail de mon affection\n");
            printf("6. Quitter le programme\n\n");
        }
        else
        {
            printf("3. Postuler à un stage (%d restants)\n",stageRestant);
            printf("4. Visualiser mes candidatures\n");
            printf("5. Quitter le programme\n\n");
        }
        scanf("%d",&choix);
        n=1;
    }

    return choix;
}

void consulterStagesEligibles(int refs[], int dpt[], int status[], int tlog, int tlogListeCand[]) 
{
    // Affiche tous les stages non pourvus
    // Format d'affichage : Ref Stage | Département
    // IMPORTANT: status[i] = 0 signifie non pourvu
    
    int i, nbStagesDispos = 0;
    
    printf("\n-------- Stages disponibles --------\n\n");
    printf("Ref Stage\tDépartement\n");
    printf("--------------------------------\n");
    
    for(i = 0; i <= tlog; i++) {
        if(status[i] == 0 && tlogListeCand[i] < 3) {
            printf("%d\t\t%02d\n", refs[i], dpt[i]);
            nbStagesDispos++;
        }
    }
    
    printf("\nNombre de stages disponibles : %d\n", nbStagesDispos);
    
    printf("\nAppuyez sur Entrée pour continuer...");
    getchar();
    getchar();
}

void consulterStagesParDepartement(int refs[], int dpt[], int status[], int tlog, int tlogListeCand[]) {
    // Affiche les stages non pourvus d'un département spécifique
    // Format d'affichage : Ref Stage | Département
    // IMPORTANT: status[i] = 0 signifie non pourvu
    
    int deptRecherche, i, nbStagesDispos = 0;
    
    printf("\nEntrez le numéro du département recherché : ");
    scanf("%d", &deptRecherche);
    
    printf("\n-------- Stages disponibles dans le département %d --------\n\n", deptRecherche);
    printf("Ref Stage\tDépartement\n");
    printf("--------------------------------\n");
    
    for(i = 0; i <= tlog; i++) {
        if(status[i] == 0 && dpt[i] == deptRecherche && tlogListeCand[i] < 3) {
            printf("%d\t\t%02d\n", refs[i], dpt[i]);
            nbStagesDispos++;
        }
    }
    
    printf("\nNombre de stages disponibles : %d\n", nbStagesDispos);
    
    printf("\nAppuyez sur Entrée pour continuer...");
    getchar();
    getchar();
}

int postulerStage(int numEtudiant, int refs[], int status[], int nbCandidatures[], 
                  int listeCand[][3], int tlogListeCand[], int *tlog, int stagesRestants) 
{
    // Permet à un étudiant de postuler à un stage disponible
    // IMPORTANT: Vérifie le nombre de stages restants
    // Retourne : 0 si ok, -1 si stage non trouvé, -2 si déjà pourvu, -3 si plus de stages dispo
    
    if(stagesRestants <= 0) {
        printf("Vous avez atteint le nombre maximum de candidatures autorisées.\n");
    
        printf("\nAppuyez sur Entrée pour continuer...");
        getchar();
        getchar();
        return -3;
    }
    
    int refStage, trouve = 0, i;
    printf("\nEntrez la référence du stage souhaité : ");
    scanf("%d", &refStage);
    
    // Recherche du stage
    for(i = 0; i <= *tlog; i++) {
        if(refs[i] == refStage) {
            trouve = 1;
            if(status[i] == 1) {
                printf("Ce stage est déjà pourvu.\n");
    
                printf("\nAppuyez sur Entrée pour continuer...");
                getchar();
                getchar();
                return -2;
            }
            // Ajout de la candidature
            listeCand[i][tlogListeCand[i]] = numEtudiant;
            tlogListeCand[i]++;
            nbCandidatures[i]++;
            printf("Candidature enregistrée avec succès.\n");
    
        printf("\nAppuyez sur Entrée pour continuer...");
        getchar();
        getchar();
            return 0;
        }
    }
    if(trouve == 0) {
        printf("Stage non trouvé.\n");

        printf("\nAppuyez sur Entrée pour continuer...");
        getchar();
        getchar();
        return -1;
    }
    return 0;
}

void visualiserCandidatures(int numEtudiant, int refs[], int dpt[], 
                          int listeCand[][3], int tlogListeCand[], int tlog) 
{
    // Affiche toutes les candidatures de l'étudiant
    // Format d'affichage : Ref Stage | Département
    // IMPORTANT: Parcourt la liste des candidatures de chaque stage
    
    int i, j, nbCandidatures = 0;
    
    printf("\n-------- Vos candidatures --------\n\n");
    printf("Ref Stage\tDépartement\n");
    printf("--------------------------------\n");
    
    for(i = 0; i < tlog; i++) {
        for(j = 0; j < tlogListeCand[i]; j++) {
            if(listeCand[i][j] == numEtudiant) {
                printf("%d\t\t%02d\n", refs[i], dpt[i]);
                nbCandidatures++;
                break;
            }
        }
    }
    
    printf("\nNombre total de candidatures : %d\n", nbCandidatures);
    printf("Candidatures restantes possibles : %d\n", 3 - nbCandidatures);
    
    printf("\nAppuyez sur Entrée pour continuer...");
    getchar();
    getchar();
}

void globalEtudiant(int tabNumEtu[], int tabRefStageEtu[], float tabNoteFinale[],int tabRefStage[],
                    int tabDept[], int tabPourvu[], int tabNBCand[], int listeCand[][3],
                    int tailleTab, int tailleEtu, int tlog, int tlogListeCand[] ) 
{
    int numEtudiant;
    
    printf("Entrez votre numéro étudiant : ");
    scanf("%d", &numEtudiant);

    int trouve = 0;
    int i = rechercherSansTriage(numEtudiant, tabNumEtu, tailleEtu, &trouve);
    int stagesRestants = 3-tlogListeCand[rechercherSansTriage(numEtudiant,tabNumEtu,tailleEtu,&trouve)];

    while(trouve == 0)
    {
        printf("Erreur d'entrée, l'étudiant n'existe pas !\nEntrez de nouveau votre numéro étudiant : ");
        scanf("%d", &numEtudiant);

        //Recherche si l'etudiant existe + récupérer son nb de candidature
        stagesRestants = tlogListeCand[rechercherSansTriage(numEtudiant,tabNumEtu,tailleEtu,&trouve)];
    }
    if(tabRefStageEtu[i] != -1)
    {
        stagesRestants = -1;
    }
    int choix = affichageEtudiant(stagesRestants);
    int quit = 0;

    while (quit == 0) {
        switch (choix) {
            case 1:
                consulterStagesEligibles(tabRefStage, tabDept, tabPourvu, tlog,tlogListeCand);
                choix = affichageEtudiant(stagesRestants);
                break;
            case 2:
                consulterStagesParDepartement(tabRefStage, tabDept, tabPourvu, tlog,tlogListeCand);
                choix = affichageEtudiant(stagesRestants);
                break;
            case 3:
                if(stagesRestants == -1)
                {
                    printf("\nVous êtes deja pourvu !\n");
                    printf("\nAppuyez sur Entrée pour continuer...");
                    getchar();
                    getchar();
                }
                else
                {
                    if(postulerStage(numEtudiant, tabRefStage, tabPourvu, tabNBCand, 
                                listeCand, tlogListeCand, &tlog, stagesRestants) == 0) {
                        stagesRestants--;
                    }
                }
                choix = affichageEtudiant(stagesRestants);
                break;
            case 4:
                if(stagesRestants == -1)
                {
                    printf("\nVous êtes deja pourvu !\n");
                    printf("\nAppuyez sur Entrée pour continuer...");
                    getchar();
                    getchar();
                }
                else
                {
                    visualiserCandidatures(numEtudiant, tabRefStage, tabDept,listeCand, tlogListeCand, tlog);
                }
                choix = affichageEtudiant(stagesRestants);
                break;
            case 5:
                if (stagesRestants == -1)
                {
                    printf("Numéro de stage auquel vous avez été affecté : %d\n", tabRefStageEtu[i]);
                    printf("\nAppuyez sur Entrée pour continuer...");
                    getchar();
                    getchar();
                    choix = affichageEtudiant(stagesRestants);
                    break;
                }
                else
                {
                    quit=1;
                    break;
                }
            case 6:
                quit=1;
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
        printf("Vous êtes connecté en tant que : Responsable de stage\n");
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

int ajouteOuSupprimeStage(int refs[], int dpt[], int status[], int nbCandidatures[], 
                         int tailleEtu, int *tlog, int numEtu[], int refsEtuStage[], 
                         float notesEtu[], int tailleTab, int listeCand[][3], int tlogListeCand[]) 
{
    int choix, ref, dept;
    printf("\n1. Ajouter un stage\n");
    printf("2. Supprimer un stage\n");
    printf("Votre choix : ");
    scanf("%d", &choix);

    while (choix < 1 || choix > 2)
    {
        printf("\nMauvais choix ! Ressaisissez :\n\n");
        printf("1. Ajouter un stage\n");
        printf("2. Supprimer un stage\n");
        printf("Votre choix : ");
        scanf("%d", &choix);
    }
    

    if (choix == 1) 
    {
        printf("\nEntrez la référence du stage : ");
        scanf("%d", &ref);
        printf("Entrez le département : ");
        scanf("%d", &dept);

        // Vérifier si le stage existe déjà
        for (int i = 0; i < *tlog; i++) {
            if (refs[i] == ref) {
                printf("Erreur : ce stage existe déjà.\n");

                printf("\nAppuyez sur Entrée pour continuer...");
                getchar();
                getchar();
                return -1;
            }
        }

        // Ajouter le nouveau stage

        //Verif taille logique > taille physique
        if (*tlog+1 >= tailleTab) {
            printf("Le tableau est plein. Impossible d'ajouter le stage.\n");
            return -1;
        }

        *tlog = *tlog + 1;
        refs[*tlog] = ref;
        dpt[*tlog] = dept;
        status[*tlog] = 0;  // Non pourvu par défaut
        nbCandidatures[*tlog] = 0;  // Pas de candidatures
        printf("Stage ajouté avec succès.\n");

    } 

    // Suppression d'un stage
    else if (choix == 2) 
    {  
        printf("\nEntrez la référence du stage à supprimer : ");
        scanf("%d", &ref);

        // Rechercher le stage
        int trouve = 0;
        int position = rechercherSansTriage(ref, refs, *tlog, &trouve);

        if (trouve == 0) {
            printf("Erreur : stage non trouvé.\n");
    
            printf("\nAppuyez sur Entrée pour continuer...");
            getchar();
            getchar();
            return -1;
        }

        // Vérifier si le stage est affecté à un étudiant
        for (int i = 0; i < tailleEtu; i++) {
            if (refsEtuStage[i] == ref) {
                printf("Erreur : impossible de supprimer un stage affecté à un étudiant.\n");

                printf("\nAppuyez sur Entrée pour continuer...");
                getchar();
                getchar();
                return -1;
            }
        }

        // Supprimer le stage en décalant les éléments
        intDecalerAGauche(refs, position, *tlog);
        intDecalerAGauche(dpt, position, *tlog);
        intDecalerAGauche(status, position, *tlog);
        intDecalerAGauche(nbCandidatures, position, *tlog);

        *tlog = *tlog - 1;

        // Suppimer les candidatures
        for (int i = 0; i < tailleEtu; i++) {
            for(int j = 0; j < tlogListeCand[i]; j++) {
                if(listeCand[i][j] == ref) {
                    intDecalerAGauche(listeCand[i], j, tlogListeCand[i]);
                    tlogListeCand[i] = tlogListeCand[i] - 1;
                }
            }
        }

        printf("Stage supprimé avec succès.\n");
    
        printf("\nAppuyez sur Entrée pour continuer...");
        getchar();
        getchar();
    }
    return 0;
}

int affecterEtu(int numEtu[], int refsEtuStage[], int refs[], int status[], 
                int tailleEtu, int *tlog, int listeCand[][3], int tlogListeCand[]) 
{
    // IMPORTANT: Retourne 0 si succès, -1 si erreur
    // Vérifie : existence étudiant, existence stage, stage non pourvu
    
    int numEtudiant, refStage;
    int trouve = 0, posEtu, posStage ;

    printf("\nEntrez le numéro de l'étudiant : ");
    scanf("%d", &numEtudiant);

    posEtu = rechercherSansTriage(numEtudiant, numEtu, tailleEtu, &trouve);

    if (trouve == 0) {
        printf("Erreur : étudiant non trouvé.\n");
    
        printf("\nAppuyez sur Entrée pour continuer...");
        getchar();
        getchar();
        return -1;
    }

    // Vérifier si l'étudiant a déjà un stage
    if (refsEtuStage[posEtu] != -1) {
        printf("Erreur : cet étudiant a déjà un stage affecté.\n");
    
        printf("\nAppuyez sur Entrée pour continuer...");
        getchar();
        getchar();
        return -1;
    }

    printf("Entrez la référence du stage : ");
    scanf("%d", &refStage);

    // Rechercher le stage
    posStage = rechercherSansTriage(refStage, refs, *tlog, &trouve);

    if (trouve == 0) {
        printf("Erreur : stage non trouvé.\n");
    
        printf("\nAppuyez sur Entrée pour continuer...");
        getchar();
        getchar();
        return -1;
    }

    // Vérifier si le stage est déjà pourvu
    if (status[posStage] == 1) {
        printf("Erreur : ce stage est déjà pourvu.\n");

        printf("\nAppuyez sur Entrée pour continuer...");
        getchar();
        getchar();
        return -1;
    }

    // Affecter le stage
    refsEtuStage[posEtu] = refStage;
    status[posStage] = 1;

    // Supprimer les candidatures associées au stage de tous les autres étudiants
    for (int i = 0; i < tailleEtu; i++) {
        for(int j = 0; j < tlogListeCand[i]; j++) {
            if(listeCand[i][j] == refStage) {
                intDecalerAGauche(listeCand[i], j, tlogListeCand[i]);
                tlogListeCand[i] = tlogListeCand[i] - 1;
            }
        }
    }

    printf("Stage affecté avec succès.\n");
    
    printf("\nAppuyez sur Entrée pour continuer...");
    getchar();
    getchar();
    return 0;
}

void afficherListeStages(int refs[], int dpt[], int status[], int *tlog) {
    // Format d'affichage : deux sections (pourvus et non pourvus)
    // Pour chaque section : Ref Dept (un stage par ligne)
    // Affiche à la fin : nombre de stages pourvus, non pourvus et total
    // IMPORTANT: status[i] = 1 signifie pourvu, 0 signifie non pourvu
    
    int i, nbPourvus = 0, nbNonPourvus = 0;
    
    printf("\n-------- Liste des stages --------\n\n");
    
    // Affichage des stages pourvus
    printf("Stages pourvus :\n");
    printf("Ref\tDepartement\n");
    printf("------------------------\n");
    for(i = 0; i <= *tlog; i++) {
        if(status[i] == 1) {
            printf("%d\t%02d\n", refs[i], dpt[i]);
            nbPourvus++;
        }
    }
    printf("\nNombre de stages pourvus : %d\n\n", nbPourvus);
    
    // Affichage des stages non pourvus
    printf("Stages non pourvus :\n");
    printf("Ref\tDepartement\n");
    printf("------------------------\n");
    for(i = 0; i < *tlog; i++) {
        if(status[i] == 0) {
            printf("%d\t%02d\n", refs[i], dpt[i]);
            nbNonPourvus++;
        }
    }
    printf("\nNombre de stages non pourvus : %d\n", nbNonPourvus);
    printf("\nNombre total de stages : %d\n", *tlog);
    
    printf("\nAppuyez sur Entrée pour continuer...");
    getchar();
    getchar();
}

void afficherEtudiantsSansAffectation(int numEtu[], int refsEtuStage[], int tailleEtu) {
    // Format d'affichage : numéro étudiant (un par ligne)
    // Affiche uniquement les étudiants avec refsEtuStage = 0
    // Affiche à la fin : nombre sans stage et nombre total d'étudiants
    // IMPORTANT: Suppose que refsEtuStage[i] = 0 signifie sans stage
    
    int i, nbSansStage = 0;
    
    printf("\n-------- Liste des étudiants sans affectation --------\n\n");
    printf("Numéro étudiant\n");
    printf("----------------\n");
    
    // Parcours du tableau des étudiants
    for(i = 0; i < tailleEtu; i++) {
        // Un étudiant sans affectation a une référence de stage à 0
        if(refsEtuStage[i] == -1) {
            printf("%d\n", numEtu[i]);
            nbSansStage++;
        }
    }
    
    printf("\nNombre total d'étudiants sans affectation : %d\n", nbSansStage);
    printf("Nombre total d'étudiants : %d\n", tailleEtu);
    
    printf("\nAppuyez sur Entrée pour continuer...");
    getchar();
    getchar();
}

void rechercherStageParCritere(int refs[], int dpt[], int status[], int nbCandidatures[], int *tlog) {
    // Format d'affichage : Ref Dept Status NbCandidatures
    // Critères possibles :
    // 1. Numéro de référence (affiche un stage exact)
    // 2. Département (affiche tous les stages du département)
    // IMPORTANT: Status affiché comme "Pourvu" ou "Non pourvu"
    
    int choix = 0, critere, i, trouve = 0;
    
    printf("\n-------- Recherche de stage --------\n\n");
    printf("1. Rechercher par numéro de référence\n");
    printf("2. Rechercher par département\n");
    printf("Votre choix : ");
    scanf("%d", &choix);
    
    switch(choix) {
        case 1:
            printf("\nEntrez le numéro de référence du stage : ");
            scanf("%d", &critere);
            
            printf("\nRésultats de la recherche :\n");
            printf("Ref\tDept\tStatus\tNb Candidatures\n");
            printf("----------------------------------------\n");
            
            for(i = 0; i < *tlog; i++) {
                if(refs[i] == critere) {
                    printf("%d\t%02d\t%s\t%d\n", refs[i], dpt[i], status[i] ? "Pourvu" : "Non pourvu", nbCandidatures[i]);
                    trouve = 1;
                    }
                    break;
                }
                
            printf("\nAppuyez sur Entrée pour continuer...");
            getchar();
            getchar();
            break;
            
        case 2:
            printf("\nEntrez le numéro de département : ");
            scanf("%d", &critere);
            
            printf("\nRésultats de la recherche :\n");
            printf("Ref\tDept\tStatus\tNb Candidatures\n");
            printf("----------------------------------------\n");
            
            for(i = 0; i < *tlog; i++) {
                if(dpt[i] == critere) {
                    printf("%d\t%02d\t%s\t%d\n", refs[i], dpt[i], status[i] ? "Pourvu" : "Non pourvu", nbCandidatures[i]);
                    trouve = 1;
                }
            }
            printf("\nAppuyez sur Entrée pour continuer...");
            getchar();
            getchar();
            break;
        default:
            printf("Erreur : choix invalide.\n");
            
            printf("\nAppuyez sur Entrée pour continuer...");
            getchar();
            getchar();
            break;
    }
    
    if(trouve == 0) {
        printf("\nAucun stage trouvé avec ce critère.\n");
    }
}

int saisirNotesFinales(int numEtu[], int refsEtuStage[], float notesFinales[], int tailleEtu) {
    // IMPORTANT: Retourne 0 si succès, -1 si erreur, -2 si stage non affecté, -3 si note finale deja saisie
    int numEtudiant, trouve, position, nbNote;
    float note, somme=0, moyenne;
    
    printf("\nEntrez le numéro de l'étudiant à noter : ");
    scanf("%d", &numEtudiant);
    
    position = rechercherSansTriage(numEtudiant, numEtu, tailleEtu, &trouve);
    
    if(trouve == 0) {
        printf("Erreur : étudiant non trouvé.\n");
        return -1;
    }
    
    if(refsEtuStage[position] == -1) {
        printf("Erreur : cet étudiant n'a pas de stage affecté.\n");
        
        printf("\nAppuyez sur Entrée pour continuer...");
        getchar();
        getchar();
        return -2;
    }

    if(notesFinales[position] != -1) {
        printf("Erreur : cet étudiant a deja une note finale.\n");
        
        printf("\nAppuyez sur Entrée pour continuer...");
        getchar();
        getchar();
        return -3;
    }
    
    for(nbNote=1;nbNote<=3;nbNote++)
    {
        switch (nbNote)
        {
            case 1:
            {
                printf("Entrez la note d’entreprise (0-20) : ");
                scanf("%f", &note);
                while(note < 0 || note > 20) 
                {
                    printf("Erreur : la note doit être comprise entre 0 et 20.\nRéentrez la note d’entreprise (0-20) : ");
                    scanf("%f", &note);
                }
                somme = somme+note*2;
                break;
            }
            case 2:
            {
                printf("Entrez la note du rapport (0-20) : ");
                scanf("%f", &note);
                while(note < 0 || note > 20) 
                {
                    printf("Erreur : la note doit être comprise entre 0 et 20.\nRéentrez la note du rapport (0-20) : ");
                    scanf("%f", &note);
                }
                somme = somme+note;
                break;
            }
            case 3:
            {
                printf("Entrez la note de soutenance (0-20) : ");
                scanf("%f", &note);
                while(note < 0 || note > 20) 
                {
                    printf("Erreur : la note doit être comprise entre 0 et 20.\nRéentrez la note de soutenance (0-20) : ");
                    scanf("%f", &note);
                }
                somme = somme+note;
                break;
            }
        }
    }

    moyenne = somme / 4.0;
    notesFinales[position] = moyenne;
    rangerParNoteFinale(numEtu, refsEtuStage, notesFinales, tailleEtu);
    printf("Note enregistrée avec succès.\n");

    
    printf("\nAppuyez sur Entrée pour continuer...");
    getchar();
    getchar();
    return 0;
}

void globalResponsable(int tabNumEtu[], int tabRefStageEtu[], float tabNoteFinale[],
                        int tabRefStage[], int tabDept[], int tabPourvu[], int tabNBCand[],
                        int listeCand[][3], int tlogListeCand[], int tailleTab, int tailleEtu, int *tlog) {

    int choix = affichageResponsable();
    int quit = 0;

    while (quit == 0) {
        switch (choix) 
        {
            case 1:
                ajouteOuSupprimeStage(tabRefStage, tabDept, tabPourvu, tabNBCand, 
                                    tailleEtu, tlog, tabNumEtu, tabRefStageEtu,
                                    tabNoteFinale, tailleTab, listeCand, tlogListeCand);
                choix = affichageResponsable();
                break;
            case 2:
                affecterEtu(tabNumEtu, tabRefStageEtu, tabRefStage, tabPourvu, 
                           tailleEtu, tlog, listeCand, tlogListeCand);
                choix = affichageResponsable();
                break;
            case 3:
                afficherListeStages(tabRefStage, tabDept, tabPourvu, tlog);
                choix = affichageResponsable();
                break;
            case 4:
                afficherEtudiantsSansAffectation(tabNumEtu, tabRefStageEtu, tailleEtu);
                choix = affichageResponsable();
                break;
            case 5:
                rechercherStageParCritere(tabRefStage, tabDept, tabPourvu, tabNBCand, tlog);
                choix = affichageResponsable();
                break;
            case 6:
                saisirNotesFinales(tabNumEtu, tabRefStageEtu, tabNoteFinale, tailleEtu);
                choix = affichageResponsable();
                break;
            case 7:
                afficherNotesDecroissant(tabNumEtu, tabRefStageEtu, tabNoteFinale, tailleEtu);
                choix = affichageResponsable();
                break;
            case 8:
                quit = 1;
                printf("\n\nAu revoir !\n");
                break;
        }
    }
}

void global(void) {
    // Déclaration des tableaux avec tailles maximales
    int tabNumEtu[200], tabRefStageEtu[200];
    float tabNoteFinale[200];
    int tabRefStage[200], tabDept[200], tabPourvu[200], tabNBCand[200];
    int listeCand[200][3], tlogListeCand[200];
    int tailleTab = 200;  // Taille maximale des tableaux
    int tailleEtu = 0;    // Taille logique pour les étudiants
    int tlog = 0;         // Taille logique pour les stages
    
    // Chargement initial des données
    tailleEtu = chargerDataEtu(tabNumEtu, tabRefStageEtu, tabNoteFinale, tailleTab);
    if (tailleEtu <= 0) {
        printf("Erreur lors du chargement des données étudiants\n");
        return;
    }
    
    tlog = chargerDataStage(tabNumEtu, tabRefStageEtu, tabRefStage, tabDept, tabPourvu, 
                           tabNBCand, listeCand, tlogListeCand, tailleTab, tailleEtu);
    if (tlog <= 0) {
        printf("Erreur lors du chargement des données stages\n");
        return;
    }
    int choix = affichageGlobal();
    int quit = 0;

    while (quit == 0) {
        switch (choix) {
            case 1:
                globalJury(tabNumEtu,tabRefStageEtu,tabNoteFinale,tailleTab,tailleEtu);
                choix = 4;
                break;
            case 2:
                globalEtudiant(tabNumEtu, tabRefStageEtu, tabNoteFinale, tabRefStage, tabDept, tabPourvu, tabNBCand, listeCand, tailleTab, tailleEtu, tlog, tlogListeCand);
                choix = 4;
                break;
            case 3:
                globalResponsable(tabNumEtu, tabRefStageEtu, tabNoteFinale, tabRefStage, tabDept, tabPourvu, tabNBCand, listeCand, tlogListeCand, tailleTab, tailleEtu, &tlog);
                choix = 4;
                break;
            case 4:
                // Sauvegarde unique à la fin du programme
                sauvegarder(tabNumEtu, tabRefStageEtu, tabNoteFinale, &tailleEtu,
                           tabRefStage, tabDept, tabPourvu, tabNBCand, 
                           listeCand, tlogListeCand, tlog);
                quit = 1;
                printf("\n\nDonnées sauvegardées. Au revoir !\n");
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