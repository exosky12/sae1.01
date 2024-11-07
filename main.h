#include "stdio.h"

int chargerData(int tabNumEtu[], int tabRefStage[], int tabNoteFinale[], int tabDept[], int tailleTab);
int rechercher(int val, int tab[], int nb, int *trouve);
void decalerADroite(int tab[], int indice, int nbMatieres);
void decalerAGauche(int tab[], int indice, int nbMatieres);
void sauvegarde(int tabMatieres[], int tabCoef[], int nbMatieres);
int affichageGlobal(void);
int affichageJury(void);
void globalJury(void);
void globalEtudiant(void);
void globalResponsable(void);
void clearScreen(void);
int affichageEtudiant(int stageRestant);
void global(void);