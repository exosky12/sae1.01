#include <stdio.h>
#include <stdlib.h>

// Chargement des donnÃ©es
int chargerDataEtu(int tabNumEtu[], int tabRefStageEtu[], float tabNoteFinale[], int tailleTab);
int chargerDataStage(int tabNumEtu[], int tabRefStageEtu[], int tabRefStage[], int tabDept[], int tabPourvu[], int tabNBCand[], int listeCand[][3], int tlogListeCand[], int tailleTab, int tlog);

// Fonctions de recherche
int rechercherSansTriage(int val, int tab[], int tlog, int *trouve);

// Fonctions de manipulation de tableaux
void floatDecalerAGauche(float tab[], int indice, int tlog);
void intDecalerAGauche(int tab[], int indice, int tlog);

// Fonction de sauvegarde
int sauvegarder(int tabNumEtu[], int tabRefStageEtu[], float tabNoteFinale[], int *tailleEtu,
                 int tabRefStage[], int tabDept[], int tabPourvu[], int tabNBCand[], 
                 int listeCand[][3], int tlogListeCand[], int tlog);
// Menus d'affichage
int affichageGlobal(void);
int affichageJury(void);
int affichageEtudiant(int stageRestant);
int affichageResponsable(void);

// Fonctions globales de gestion
void globalJury(int tabNumEtu[], int tabRefStageEtu[], float tabNoteFinale[], int tailleTab, int tailleEtu);
void globalEtudiant(int tabNumEtu[], int tabRefStageEtu[], float tabNoteFinale[],int tabRefStage[],
                    int tabDept[], int tabPourvu[], int tabNBCand[], int listeCand[][3],
                    int tailleTab, int tailleEtu, int tlog, int tlogListeCand[] );
void globalResponsable(int tabNumEtu[], int tabRefStageEtu[], float tabNoteFinale[],
                        int tabRefStage[], int tabDept[], int tabPourvu[], int tabNBCand[],
                        int listeCand[][3], int tlogListeCand[], int tailleTab, int tailleEtu, int *tlog);
void global(void);

// Fonctions de gestion des stages
int ajouteOuSupprimeStage(int refs[], int dpt[], int status[], int nbCandidatures[], 
                         int tailleEtu, int *tlog, int numEtu[], int refsEtuStage[], 
                         float notesEtu[], int tailleTab, int listeCand[][3], int tlogListeCand[]);
int affecterEtu(int numEtu[], int refsEtuStage[], int refs[], int status[], int tailleEtu, int *tlog, int listeCand[][3], int tlogListeCand[]);
void afficherListeStages(int refs[], int dpt[], int status[], int *tlog);
void afficherEtudiantsSansAffectation(int numEtu[], int refsEtuStage[], int tailleEtu);
void rechercherStageParCritere(int refs[], int dpt[], int status[], int nbCandidatures[], int *tlog);

// Fonctions menu étudiant
void consulterStagesEligibles(int refs[], int dpt[], int status[], int tlog,int tlogListeCand[]);
void consulterStagesParDepartement(int refs[], int dpt[], int status[], int tlog,int tlogListeCand[]);
int postulerStage(int numEtudiant, int refs[], int status[], int nbCandidatures[], 
                  int listeCand[][3], int tlogListeCand[], int *tlog, int stagesRestants);
void visualiserCandidatures(int numEtudiant, int refs[], int dpt[], 
                          int listeCand[][3], int tlogListeCand[], int tlog);

// Fonctions menu jury
int noterEtudiant(int numEtu[], int refsEtuStage[], float notesFinales[], int tailleEtu);
void visualiserNotesEtudiant(int numEtu[], int refsEtuStage[], float notesFinales[], int tailleEtu);

// Fonctions de tri
void rangerParNoteFinale(int tabNumEtu[], int tabRefStageEtu[], float tabNoteFinale[], int tailleEtu);
void echangerElements(int tabNumEtu[], int tabRefStageEtu[], float tabNoteFinale[], int i, int j);



// utilitaires
void clearScreen(void);