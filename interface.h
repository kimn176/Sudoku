#ifndef INTERFACE_INCLUDED
#define INTERFACE_INCLUDED

#include "Sudoku.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define SCREEN_WIDTH 540 // 9x9 grid with cells of size 60
#define SCREEN_HEIGHT 540
#define GRID_SIZE 60 // Taille d'une cellule de la grille
#define GRID_ROWS 9
#define GRID_COLS 9
#define SUBGRID_SIZE 180 // Taille de la grille 3x3

#define EASY 1
#define MEDIUM 25
#define HARD 5
#define EMPTY 0

typedef struct {
    SDL_Rect rect;
    SDL_Color color;
    char* text;
    SDL_Color textColor;
} Button;

StructSudoku grille(int level);

void drawGrid(SDL_Renderer* renderer);
void drawNumbers(SDL_Renderer* renderer, StructSudoku sudo);
void drawNumber(SDL_Renderer* renderer, StructSudoku sudo, int i, int j);
void drawNumberR(SDL_Renderer* renderer, StructSudoku sudo, int i, int j);

void drawGridNote(SDL_Renderer* renderer, int posX, int posY);
void drawNumbersNote(SDL_Renderer* renderer, StructSudoku sudo, int x, int y);

bool isInside(SDL_Point point, SDL_Rect rect);
void drawButton(SDL_Renderer* renderer, Button button, TTF_Font* font);


StructSudoku clickButtonFacile(SDL_Renderer* renderer);
StructSudoku clickButtonMoyen(SDL_Renderer* renderer);
StructSudoku clickButtonDifficile(SDL_Renderer* renderer);


StructSudoku clickButtonRessoudre(SDL_Renderer* renderer, StructSudoku sudo, int regles);
StructSudoku clickButtonBacktracking(SDL_Renderer* renderer, StructSudoku sudo);

StructSudoku clickButtonRegle1(SDL_Renderer* renderer, StructSudoku sudo);
StructSudoku clickButtonRegle2(SDL_Renderer* renderer, StructSudoku sudo);
StructSudoku clickButtonRegle3(SDL_Renderer* renderer, StructSudoku sudo);
StructSudoku clickButtonRegle4(SDL_Renderer* renderer, StructSudoku sudo);
StructSudoku clickButtonRegle5(SDL_Renderer* renderer, StructSudoku sudo);
StructSudoku clickButtonRegle6(SDL_Renderer* renderer, StructSudoku sudo);
StructSudoku clickButtonRegle7(SDL_Renderer* renderer, StructSudoku sudo);
StructSudoku clickButtonRegle8(SDL_Renderer* renderer, StructSudoku sudo);
StructSudoku clickButtonRegle9(SDL_Renderer* renderer, StructSudoku sudo);
StructSudoku clickButtonRegle10(SDL_Renderer* renderer, StructSudoku sudo);
StructSudoku clickButtonRegle11(SDL_Renderer* renderer, StructSudoku sudo);


bool BacktrackingI(StructSudoku sudoku, int x, int y, SDL_Renderer* renderer);

bool ajout(SDL_Renderer* renderer, StructSudoku sudo, SDL_Event event, int num);




#endif