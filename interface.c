#include "Sudoku.h"
#include "interface.h"
#include "type.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>


bool BacktrackingI(StructSudoku sudoku, int x, int y, SDL_Renderer* renderer) {
    if (x == NB_LONGUEUR && y == 0) {                                                               // Vérifie si on a atteint la fin de la grille
        return true;                                                                                // La grille est fini
    }
    if (get_value(sudoku, x, y) != 0) {                                                             // Passe à la prochaine case si la case actuelle est déjà remplie
        if (y == NB_LONGUEUR-1) {                                                                   // Si nous sommes à la dernière colonne on passe à la ligne suivante
            return BacktrackingI(sudoku, x + 1, 0, renderer);
        } else {
            return BacktrackingI(sudoku, x, y + 1, renderer);
        }
    }
    for (int valeur = 1; valeur <= NB_LONGUEUR; valeur++) {                                         //Essaye de placer les valeurs de 1 à 9 dans la case
        if (sudoku_valid(sudoku)) {
            add_value(sudoku, x, y, valeur);
            
            if (BacktrackingI(sudoku, x, y, renderer) && sudoku_valid(sudoku)) {                               // Si la grille est résolue, retourner true
                drawNumber(renderer, sudoku, x, y);
                return true;
            }
            rem_value(sudoku, x, y);                                                                // Si la solution échoue, retirer la valeur de la cellule
        }
    }
    return false;                                                                                   // Aucune solution trouvée pour cette configuration
}

void drawGrid(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE); // Couleur noire

    // Dessiner les lignes verticales
    for (int x = GRID_SIZE / 2; x <= SCREEN_WIDTH + GRID_SIZE / 2; x += GRID_SIZE) {
        SDL_RenderDrawLine(renderer, x, GRID_SIZE / 2, x, SCREEN_HEIGHT + GRID_SIZE / 2);
        if ((x - GRID_SIZE / 2) % (3 * GRID_SIZE) == 0) { // Dessiner une ligne plus épaisse pour chaque 3 colonnes
            SDL_RenderDrawLine(renderer, x - 1, GRID_SIZE / 2, x - 1, SCREEN_HEIGHT + GRID_SIZE / 2);
            SDL_RenderDrawLine(renderer, x + 1, GRID_SIZE / 2, x + 1, SCREEN_HEIGHT + GRID_SIZE / 2);
        }
    }

    // Dessiner les lignes horizontales
    for (int y = GRID_SIZE / 2; y <= SCREEN_HEIGHT + GRID_SIZE / 2; y += GRID_SIZE) {
        SDL_RenderDrawLine(renderer, GRID_SIZE / 2, y, SCREEN_WIDTH + GRID_SIZE / 2, y);
        if ((y - GRID_SIZE / 2) % (3 * GRID_SIZE) == 0) { // Dessiner une ligne plus épaisse pour chaque 3 lignes
            SDL_RenderDrawLine(renderer, GRID_SIZE / 2, y - 1, SCREEN_WIDTH + GRID_SIZE / 2, y - 1);
            SDL_RenderDrawLine(renderer, GRID_SIZE / 2, y + 1, SCREEN_WIDTH + GRID_SIZE / 2, y + 1);
        }
    }
}

void drawGridNote(SDL_Renderer* renderer, int posX, int posY) {
    // Dessiner les lignes verticales et horizontales pour la grille de sudoku 3x3
    SDL_Rect rect = {posX, posY, SUBGRID_SIZE, SUBGRID_SIZE};
    SDL_RenderDrawRect(renderer, &rect); // Dessiner le contour de la grille

    for (int x = posX + GRID_SIZE; x <= posX + SUBGRID_SIZE; x += GRID_SIZE) {
        SDL_RenderDrawLine(renderer, x, posY, x, posY + SUBGRID_SIZE);
    }
    for (int y = posY + GRID_SIZE; y <= posY + SUBGRID_SIZE; y += GRID_SIZE) {
        SDL_RenderDrawLine(renderer, posX, y, posX + SUBGRID_SIZE, y);
    }
}

void drawNumbersNote(SDL_Renderer* renderer, StructSudoku sudo, int x, int y) {
    SDL_Color textColor = {0, 0, 0, SDL_ALPHA_OPAQUE}; // Couleur du texte (rouge)
    SDL_Color textColorn = {0, 0, 0, SDL_ALPHA_OPAQUE};
    TTF_Font* font = TTF_OpenFont("/usr/share/fonts/truetype/liberation2/LiberationSerif-Bold.ttf", 28); // Charger une police
    TTF_Font* fontn = TTF_OpenFont("/usr/share/fonts/truetype/liberation2/LiberationSerif-Bold.ttf", 10); // Charger une police

    if (!font) {
        printf("Erreur de chargement de la police : %s\n", TTF_GetError());
        return;
    }

    SDL_Surface* surface;
    SDL_Texture* texture;
    int posi=0;
    int posj=0;
    for (int i = 0; i < NB_LONGUEUR; ++i) {
        int value = get_note(sudo, x, y,i);
        if ((value != 1)||(value == 0)) {
            char numberStr[2];
            sprintf(numberStr, "%d", i+1);
            surface = TTF_RenderText_Solid(font, numberStr, textColor);
            texture = SDL_CreateTextureFromSurface(renderer, surface);

            SDL_Rect dstRect = {(710 + GRID_SIZE + GRID_SIZE / 4 + GRID_SIZE / 2) + (posi*GRID_SIZE), (410 + GRID_SIZE + GRID_SIZE / 4 + GRID_SIZE / 2) + (posj*GRID_SIZE), GRID_SIZE / 2 + GRID_SIZE / 2, GRID_SIZE / 2 + GRID_SIZE / 2};
            SDL_QueryTexture(texture, NULL, NULL, &dstRect.w, &dstRect.h);

            SDL_RenderCopy(renderer, texture, NULL, &dstRect);

            SDL_FreeSurface(surface);
            SDL_DestroyTexture(texture);
        } 
        if (posi == 2){
            posi =0;
            posj++;
        }
        else{
            posi++;
        }
    }
    
    TTF_CloseFont(font);
}

void drawNumbers(SDL_Renderer* renderer, StructSudoku sudo) {
    SDL_Color textColor = {255, 0, 0, SDL_ALPHA_OPAQUE}; // Couleur du texte (rouge)
    SDL_Color textColorn = {0, 0, 0, SDL_ALPHA_OPAQUE};
    TTF_Font* font = TTF_OpenFont("/usr/share/fonts/truetype/liberation2/LiberationSerif-Bold.ttf", 28); // Charger une police
    TTF_Font* fontn = TTF_OpenFont("/usr/share/fonts/truetype/liberation2/LiberationSerif-Bold.ttf", 10); // Charger une police

    if (!font) {
        printf("Erreur de chargement de la police : %s\n", TTF_GetError());
        return;
    }

    SDL_Surface* surface;
    SDL_Texture* texture;
    for (int i = 0; i < GRID_ROWS; ++i) {
        for (int j = 0; j < GRID_COLS; ++j) {
            int value = get_value(sudo, i, j);
            if (value != 0) {
                // Si la case contient un numéro, dessinez-le
                char numberStr[2];
                sprintf(numberStr, "%d", value);
                surface = TTF_RenderText_Solid(font, numberStr, textColor);
                texture = SDL_CreateTextureFromSurface(renderer, surface);

                SDL_Rect dstRect = {j * GRID_SIZE + GRID_SIZE / 4 + GRID_SIZE / 2, i * GRID_SIZE + GRID_SIZE / 4 + GRID_SIZE / 2, GRID_SIZE / 2 + GRID_SIZE / 2, GRID_SIZE / 2 + GRID_SIZE / 2};
                SDL_QueryTexture(texture, NULL, NULL, &dstRect.w, &dstRect.h);

                SDL_RenderCopy(renderer, texture, NULL, &dstRect);

                SDL_FreeSurface(surface);
                SDL_DestroyTexture(texture);
            } 
        }
    }
    TTF_CloseFont(font);
}

void drawNumber(SDL_Renderer* renderer, StructSudoku sudo, int i, int j) {
    SDL_Color textColor = {0, 0, 0, SDL_ALPHA_OPAQUE}; 
    SDL_Color textColorn = {0, 0, 0, SDL_ALPHA_OPAQUE};
    TTF_Font* font = TTF_OpenFont("/usr/share/fonts/truetype/liberation2/LiberationSerif-Bold.ttf", 28); // Charger une police
    TTF_Font* fontn = TTF_OpenFont("/usr/share/fonts/truetype/liberation2/LiberationSerif-Bold.ttf", 10); // Charger une police

    if (!font) {
        printf("Erreur de chargement de la police : %s\n", TTF_GetError());
        // Gestion de l'erreur de chargement de la police
        return;
    }

    SDL_Surface* surface;
    SDL_Texture* texture;
    int value = get_value(sudo, i, j);
    // Si la case contient un numéro, dessinez-le
    char numberStr[2];
    sprintf(numberStr, "%d", value);
    surface = TTF_RenderText_Solid(font, numberStr, textColor);
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect dstRect = {j * GRID_SIZE + GRID_SIZE / 4 + GRID_SIZE / 2, i * GRID_SIZE + GRID_SIZE / 4 + GRID_SIZE / 2, GRID_SIZE / 2 + GRID_SIZE / 2, GRID_SIZE / 2 + GRID_SIZE / 2};
    SDL_QueryTexture(texture, NULL, NULL, &dstRect.w, &dstRect.h);

    SDL_RenderCopy(renderer, texture, NULL, &dstRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
}


void drawNumberR(SDL_Renderer* renderer, StructSudoku sudo, int i, int j) {
    SDL_Color textColor = {255, 0, 0, SDL_ALPHA_OPAQUE}; // Couleur du texte (rouge)
    TTF_Font* font = TTF_OpenFont("/usr/share/fonts/truetype/liberation2/LiberationSerif-Bold.ttf", 28); // Charger une police
    
    if (!font) {
        printf("Erreur de chargement de la police : %s\n", TTF_GetError());
        // Gestion de l'erreur de chargement de la police
        return;
    }

    SDL_Surface* surface;
    SDL_Texture* texture;
    int value = get_value(sudo, i, j);
    // Si la case contient un numéro, dessinez-le
    char numberStr[2];
    sprintf(numberStr, "%d", value);
    surface = TTF_RenderText_Solid(font, numberStr, textColor);
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect dstRect = {j * GRID_SIZE + GRID_SIZE / 4 + GRID_SIZE / 2, i * GRID_SIZE + GRID_SIZE / 4 + GRID_SIZE / 2, GRID_SIZE / 2 + GRID_SIZE / 2, GRID_SIZE / 2 + GRID_SIZE / 2};
    SDL_QueryTexture(texture, NULL, NULL, &dstRect.w, &dstRect.h);

    SDL_RenderCopy(renderer, texture, NULL, &dstRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
}

bool isInside(SDL_Point point, SDL_Rect rect) {
    return point.x >= rect.x && point.x <= rect.x + rect.w &&
           point.y >= rect.y && point.y <= rect.y + rect.h;
}

void drawButton(SDL_Renderer* renderer, Button button, TTF_Font* font) {
    // Dessiner le rectangle du bouton
    SDL_SetRenderDrawColor(renderer, button.color.r, button.color.g, button.color.b, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &button.rect);

    // Dessiner le texte du bouton
    SDL_Surface* surface = TTF_RenderText_Solid(font, button.text, button.textColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect textRect = {button.rect.x + button.rect.w / 2 - surface->w / 2, button.rect.y + button.rect.h / 2 - surface->h / 2, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &textRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

StructSudoku clickButtonFacile(SDL_Renderer* renderer){
    StructSudoku sudo = initSudoku();
    add_value(sudo, 0, 0, 4);
    add_value(sudo, 0, 2, 3);
    add_value(sudo, 0, 4, 2);
    add_value(sudo, 0, 7, 7);
    add_value(sudo, 0, 8, 1);

    add_value(sudo, 1, 0, 2);
    add_value(sudo, 1, 1, 6);
    add_value(sudo, 1, 4, 5);
    add_value(sudo, 1, 7, 4);
    add_value(sudo, 1, 8, 9);

    add_value(sudo, 2, 0, 9);
    add_value(sudo, 2, 2, 8);
    add_value(sudo, 2, 3, 4);
    add_value(sudo, 2, 7, 5);
    add_value(sudo, 2, 8, 6);

    add_value(sudo, 3, 1, 4);
    add_value(sudo, 3, 2, 2);
    add_value(sudo, 3, 5, 7);

    add_value(sudo, 4, 4, 4);
    add_value(sudo, 4, 6, 9);
    add_value(sudo, 4, 7, 1);
    add_value(sudo, 4, 8, 5);

    add_value(sudo, 5, 0, 1);
    add_value(sudo, 5, 2, 9);
    add_value(sudo, 5, 3, 5);
    add_value(sudo, 5, 8, 7);

    add_value(sudo, 6, 0, 3);
    add_value(sudo, 6, 1, 8);
    add_value(sudo, 6, 3, 2);
    add_value(sudo, 6, 5, 9);
    add_value(sudo, 6, 6, 7);

    add_value(sudo, 7, 1, 2);
    add_value(sudo, 7, 2, 1);
    add_value(sudo, 7, 4, 3);
    add_value(sudo, 7, 6, 5);
    add_value(sudo, 7, 8, 8);

    add_value(sudo, 8, 0, 7);
    add_value(sudo, 8, 1, 9);

    return sudo;
}

StructSudoku clickButtonMoyen(SDL_Renderer* renderer){
    StructSudoku sudo = initSudoku();
    add_value(sudo, 0, 0, 9);
    add_value(sudo, 0, 3, 7);
    add_value(sudo, 0, 4, 2);

    add_value(sudo, 1, 6, 3);
    add_value(sudo, 1, 7, 4);

    add_value(sudo, 2, 0, 2);
    add_value(sudo, 2, 1, 5);
    add_value(sudo, 2, 5, 6);

    add_value(sudo, 3, 1, 3);
    add_value(sudo, 3, 2, 8);
    add_value(sudo, 3, 4, 6);
    add_value(sudo, 3, 6, 2);
    add_value(sudo, 3, 7, 1);

    add_value(sudo, 4, 6, 7);

    add_value(sudo, 5, 4, 3);
    add_value(sudo, 5, 5, 1);
    add_value(sudo, 5, 8, 5);

    add_value(sudo, 6, 0, 7);
    add_value(sudo, 6, 2, 6);
    add_value(sudo, 6, 3, 9);
    add_value(sudo, 6, 4, 4);
    add_value(sudo, 6, 6, 8);
    add_value(sudo, 6, 8, 1);

    add_value(sudo, 7, 1, 4);
    add_value(sudo, 7, 2, 5);
    add_value(sudo, 7, 3, 1);
    add_value(sudo, 7, 6, 9);
    add_value(sudo, 7, 7, 2);

    add_value(sudo, 8, 1, 9);
    add_value(sudo, 8, 6, 4);
    
    return sudo;
}

StructSudoku clickButtonDifficile(SDL_Renderer* renderer){
    StructSudoku sudo = initSudoku();
    add_value(sudo, 0, 3, 5);
    add_value(sudo, 0, 4, 6);
    add_value(sudo, 0, 7, 7);

    add_value(sudo, 1, 0, 4);
    add_value(sudo, 1, 1, 5);
    add_value(sudo, 1, 4, 9);
    add_value(sudo, 1, 5, 7);

    add_value(sudo, 2, 2, 6);
    add_value(sudo, 2, 8, 1);

    add_value(sudo, 3, 0, 5);
    add_value(sudo, 3, 1, 4);
    add_value(sudo, 3, 3, 9);
    add_value(sudo, 3, 8, 7);

    add_value(sudo, 4, 7, 9);
    add_value(sudo, 4, 8, 4);

    add_value(sudo, 5, 0, 1);
    add_value(sudo, 5, 1, 9);
    add_value(sudo, 5, 4, 7);
    add_value(sudo, 5, 5, 3);

    add_value(sudo, 6, 1, 7);
    add_value(sudo, 6, 2, 4);
    add_value(sudo, 6, 6, 1);
    add_value(sudo, 6, 8, 3);

    add_value(sudo, 7, 0, 2);
    add_value(sudo, 7, 8, 9);

    add_value(sudo, 8, 3, 2);
    add_value(sudo, 8, 4, 1);
    add_value(sudo, 8, 8, 6);
    
    return sudo;
}

StructSudoku clickButtonRessoudre(SDL_Renderer* renderer, StructSudoku sudo, int regles){
    regle(sudo,0,0);
    applyRules(sudo);
    pointante(sudo);
    X_wing(sudo);
    drawNumbers(renderer, sudo);
    SDL_RenderPresent(renderer);
    return sudo;
}

StructSudoku clickButtonBacktracking(SDL_Renderer* renderer, StructSudoku sudo){
    BacktrackingI(sudo,0,0,renderer);
    SDL_RenderPresent(renderer);
    return sudo;
}

StructSudoku clickButtonRegle1(SDL_Renderer* renderer, StructSudoku sudo){
    for(int i=0; i<NB_LONGUEUR; i++){
        for(int j=0; j<NB_LONGUEUR; j++){
            if (regle(sudo, i,j)){
                drawNumber(renderer,sudo,i,j);
                SDL_RenderPresent(renderer);
                return sudo;
            };
        }
    }
}

StructSudoku clickButtonRegle2(SDL_Renderer* renderer, StructSudoku sudo){
    for(int i=0; i<NB_LONGUEUR; i++){
        for(int j=0; j<NB_LONGUEUR; j++){
            if (regle(sudo, i,j)){
                drawNumber(renderer,sudo,i,j);
                SDL_RenderPresent(renderer);
                return sudo;
            };
        }
    }
}

StructSudoku clickButtonRegle3(SDL_Renderer* renderer, StructSudoku sudo){
    for(int i=0; i<NB_LONGUEUR; i++){
        for(int j=0; j<NB_LONGUEUR; j++){
            if (regle(sudo, i,j)){
                drawNumber(renderer,sudo,i,j);
                SDL_RenderPresent(renderer);
                return sudo;
            };
        }
    }
}

StructSudoku clickButtonRegle4(SDL_Renderer* renderer, StructSudoku sudo){
    for(int i=0; i<NB_LONGUEUR; i++){
        if(singleton_nus(sudo, i, i, 0, NB_LONGUEUR-1))
            return sudo;
        if(singleton_nus(sudo, 0, NB_LONGUEUR-1, i, i))
            return sudo;
        if(i%NB_CARRE == 0){
            if(singleton_nus(sudo, i, NB_CARRE-1, 0, NB_CARRE-1))
                return sudo;
            if(singleton_nus(sudo, i, NB_CARRE-1, NB_CARRE, NB_CARRE+2))
                return sudo;
            if(singleton_nus(sudo, i, NB_CARRE-1, NB_CARRE*2, NB_CARRE*2-1))
                return sudo;
        }
    }
}

StructSudoku clickButtonRegle5(SDL_Renderer* renderer, StructSudoku sudo){
    for(int i=0; i<NB_LONGUEUR; i++){
        if(paires_nus(sudo, i, i, 0, NB_LONGUEUR-1))
            return sudo;
        if(paires_nus(sudo, 0, NB_LONGUEUR-1, i, i))
            return sudo;
        if(i%NB_CARRE == 0){
            if(paires_nus(sudo, i, NB_CARRE-1, 0, NB_CARRE-1))
                return sudo;
            if(paires_nus(sudo, i, NB_CARRE-1, NB_CARRE, NB_CARRE+2))
                return sudo;
            if(paires_nus(sudo, i, NB_CARRE-1, NB_CARRE*2, NB_CARRE*2-1))
                return sudo;
        }
    }
}

StructSudoku clickButtonRegle6(SDL_Renderer* renderer, StructSudoku sudo){
    for(int i=0; i<NB_LONGUEUR; i++){
        if(triplets_nus(sudo, i, i, 0, NB_LONGUEUR-1))
            return sudo;
        if(triplets_nus(sudo, 0, NB_LONGUEUR-1, i, i))
            return sudo;
        if(i%NB_CARRE == 0){
            if(triplets_nus(sudo, i, NB_CARRE-1, 0, NB_CARRE-1))
                return sudo;
            if(triplets_nus(sudo, i, NB_CARRE-1, NB_CARRE, NB_CARRE+2))
                return sudo;
            if(triplets_nus(sudo, i, NB_CARRE-1, NB_CARRE*2, NB_CARRE*2-1))
                return sudo;
        }
    }
}

StructSudoku clickButtonRegle7(SDL_Renderer* renderer, StructSudoku sudo){
    for(int i=0; i<NB_LONGUEUR; i++){
        if(singleton_cache(sudo, i, i, 0, NB_LONGUEUR-1))
            return sudo;
        if(singleton_cache(sudo, 0, NB_LONGUEUR-1, i, i))
            return sudo;
        if(i%NB_CARRE == 0){
            if(singleton_cache(sudo, i, NB_CARRE-1, 0, NB_CARRE-1))
                return sudo;
            if(singleton_cache(sudo, i, NB_CARRE-1, NB_CARRE, NB_CARRE+2))
                return sudo;
            if(singleton_cache(sudo, i, NB_CARRE-1, NB_CARRE*2, NB_CARRE*2-1))
                return sudo;
        }
    }
}

StructSudoku clickButtonRegle8(SDL_Renderer* renderer, StructSudoku sudo){
    for(int i=0; i<NB_LONGUEUR; i++){
        if(paires_cache(sudo, i, i, 0, NB_LONGUEUR-1))
            return sudo;
        if(paires_cache(sudo, 0, NB_LONGUEUR-1, i, i))
            return sudo;
        if(i%NB_CARRE == 0){
            if(paires_cache(sudo, i, NB_CARRE-1, 0, NB_CARRE-1))
                return sudo;
            if(paires_cache(sudo, i, NB_CARRE-1, NB_CARRE, NB_CARRE+2))
                return sudo;
            if(paires_cache(sudo, i, NB_CARRE-1, NB_CARRE*2, NB_CARRE*2-1))
                return sudo;
        }
    }
}

StructSudoku clickButtonRegle9(SDL_Renderer* renderer, StructSudoku sudo){
    for(int i=0; i<NB_LONGUEUR; i++){
        if(triplets_cache(sudo, i, i, 0, NB_LONGUEUR-1))
            return sudo;
        if(triplets_cache(sudo, 0, NB_LONGUEUR-1, i, i))
            return sudo;
        if(i%NB_CARRE == 0){
            if(triplets_cache(sudo, i, NB_CARRE-1, 0, NB_CARRE-1))
                return sudo;
            if(triplets_cache(sudo, i, NB_CARRE-1, NB_CARRE, NB_CARRE+2))
                return sudo;
            if(triplets_cache(sudo, i, NB_CARRE-1, NB_CARRE*2, NB_CARRE*2-1))
                return sudo;
        }
    }
}

StructSudoku clickButtonRegle10(SDL_Renderer* renderer, StructSudoku sudo){
    if (pointante(sudo))
        return sudo;
}

StructSudoku clickButtonRegle11(SDL_Renderer* renderer, StructSudoku sudo){
    if (X_wing(sudo))
        return sudo;
}