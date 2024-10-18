#include "main.h"

int main(void){
    int tabNumEtu[100], tabRefStage[100], tabNoteFinale[100], i;
    i = chargerData(tabNumEtu, tabRefStage,tabNoteFinale, 100);
    printf("%d", i);
    return 0;
}
