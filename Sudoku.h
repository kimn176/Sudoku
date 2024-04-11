#ifndef SUDOKU_H_INCLUDED
#define SUDOKU_H_INCLUDED
#include <stdbool.h>
#include <math.h>

#define NB_LONGUEUR 9
#define NB_CASE NB_LONGUEUR*NB_LONGUEUR
#define NB_CARRE (int)sqrt(NB_LONGUEUR)


typedef struct {
   int valeur;
   int note[NB_LONGUEUR];
} StructCellule;

typedef struct {
    StructCellule **cell;
} StructSudoku ;

void AfficheTab(StructSudoku tab);
StructSudoku initSudoku();

void update_note(StructSudoku tab, int x, int y, int val, int b);

void Print_Tiret(int n);

void add_value(StructSudoku tab, int x, int y, int val);
void rem_value(StructSudoku tab, int x, int y);


bool valid(StructSudoku tab, int xmin, int ymin, int xmax, int ymax);
bool line_valid(StructSudoku tab, int x);
bool column_valid(StructSudoku tab, int y);
bool square_valid(StructSudoku tab, int x, int y);
bool sudoku_valid(StructSudoku tab);

int ValeurManquante(StructSudoku tab, int x, int y);
bool regle(StructSudoku tab, int x, int y);



/// /// /// /// K-uplet nus /// /// /// /// ///
int nb_true(int *tab);
bool verif_case_note(StructSudoku tab, int x, int y, int note1, int note2, int note3);

bool singleton_nus(StructSudoku tab, int xmin, int xmax, int ymin, int ymax);
bool paires_nus(StructSudoku tab, int xmin, int xmax, int ymin, int ymax);
bool triplets_nus(StructSudoku tab, int xmin, int xmax, int ymin, int ymax);


/// /// /// /// K-uplet cach�s /// /// /// /// ///
bool singleton_cache(StructSudoku tab, int xmin, int xmax, int ymin, int ymax);
bool verif_case_note_cache(StructSudoku tab, int x, int y, int note1, int note2, int note3);
bool suppr_note(StructSudoku tab, int xmin, int xmax, int ymin, int ymax, int note1, int note2, int note3);
bool paires_cache(StructSudoku tab, int xmin, int xmax, int ymin, int ymax);
bool triplets_cache(StructSudoku tab, int xmin, int xmax, int ymin, int ymax);


/// /// /// /// LE MAIN /// /// /// ///
void afficherMenu();
void affiche_tab_note(StructSudoku tab, int xmin, int xmax, int ymin, int ymax);

bool regle_nus_valid(StructSudoku tab, int k, int x, int y);
bool regle_cache_valid(StructSudoku tab, int k, int x, int y);
bool findEmptyCell(StructSudoku tab);
void applyRules(StructSudoku tab);


///poitant
bool pointante (StructSudoku tab);

bool X_wing(StructSudoku tab);

bool Backtracking(StructSudoku sudoku, int x, int y) ;


#endif // SUDOKU_H_INCLUDED
