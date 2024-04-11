#ifndef TYPE_H_INCLUDED
#define TYPE_H_INCLUDED

int get_value(StructSudoku tab, int x, int y);
void set_value(StructSudoku *tab, int x, int y, int value);


void set_note(StructSudoku *tab, int x, int y, int i, int value);
int get_note(StructSudoku tab, int x, int y, int i);


int* get_tab_note(StructSudoku tab, int x, int y);

bool note_update(StructSudoku *tab, int x, int y, int note1, int note2, int note3);

int check_note(StructSudoku tab, int x, int y);

int nb_note_ligne(StructSudoku tab, int x, int note);
int nb_note_colonne(StructSudoku tab, int x, int note);

StructSudoku generateSudoku(int nb_filledCells);

#endif // TYPE_H_INCLUDED
