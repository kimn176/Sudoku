#include <time.h>
#include <stdlib.h>

#include "Sudoku.h"

///Retourne la valeur
int get_value(StructSudoku tab, int x, int y){
    return tab.cell[x][y].valeur;
}

///Change la valeur
void set_value(StructSudoku *tab, int x, int y, int value){
    (*tab).cell[x][y].valeur = value;
}

///Change une valeur dans la note
void set_note(StructSudoku *tab, int x, int y, int i, int value){
    (*tab).cell[x][y].note[i] = value;
}

///Retourne une valeur dans la note
int get_note(StructSudoku tab, int x, int y, int i){
    return tab.cell[x][y].note[i];
}

///Retourne le tableau de notes
int* get_tab_note(StructSudoku tab, int x, int y)
{
    return tab.cell[x][y].note;
}

///Change le tableau de note par un nouveau
bool note_update(StructSudoku *tab, int x, int y, int note1, int note2, int note3)
{
    bool b = false;
    for(int i=0; i<NB_LONGUEUR; i++){
        if(i!=note1 && i!=note2 && i!=note3){
            if(get_note(*tab, x, y, i) == 0){
                set_note(tab, x, y, i, 1);
                b = true;
            }
        }
    }
    return b;
}

///Retourne le nombre de notes qu'il reste dans une case
int check_note(StructSudoku tab, int x, int y)
{
    int compte = 0;
    for(int i=0; i < NB_LONGUEUR; i++)
    {
        if(get_note(tab, x, y, i) == 0)
        {
            compte++;
        }
    }
    return compte;
}

//Retourne le nombre ou la note existe dans une ligne
int nb_note_ligne(StructSudoku tab, int x, int note){
    int res=0;
    for(int i=0; i<NB_LONGUEUR; i++){
        if (get_note(tab,x,i,note) == 0){
            res++;
        }
    }
    return res;
}

//Retourne le nombre ou la note existe dans une colonne
int nb_note_colonne(StructSudoku tab, int x, int note){
    int res=0;
    for(int i=0; i<NB_LONGUEUR; i++){
        if (get_note(tab,i,x,note) == 0){
            res++;
        }
    }
    return res;
}

StructSudoku generateSudoku(int nb_filledCells) {
    srand(time(NULL));

    StructSudoku sudo = initSudoku();

    // Remplir des cellules aléatoires avec des valeurs valides
    int cpt = 0;
    while (cpt < nb_filledCells) {
        int x = rand() % NB_LONGUEUR;
        int y = rand() % NB_LONGUEUR;
        int value = rand() % NB_LONGUEUR + 1; // Générer une valeur entre 1 et 9
        if (get_value(sudo, x,y) == 0){
            set_value(&sudo, x, y, value);
        }
        // Vérifier si la valeur est valide dans cette cellule
        if(sudoku_valid(sudo)){
            cpt++;
        }
        else {
            set_value(&sudo, x, y, 0);
            cpt--;
        }
    }
    return sudo;
}



