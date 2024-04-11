///CHIONI Cl�ment
///COUTANCEAU Martin
///HO Ngoc Kim Ngan
///AUDEBERT Dorine


#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "Sudoku.h"
#include "interface.h"
#include "type.h"
#include <SDL2/SDL.h>
#include <stdio.h>

int main(int argc, char* args[]) {
    StructSudoku sudo = initSudoku();

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    TTF_Font* font = NULL;
    SDL_Rect rectGrille = {GRID_SIZE, GRID_SIZE, SUBGRID_SIZE*3, SUBGRID_SIZE*3};

    // Initialisation SDL
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    int regle=0;
    font = TTF_OpenFont("/usr/share/fonts/truetype/liberation2/LiberationSerif-Bold.ttf", 24);
    Button buttonFacile = {{600, 30, 100, 50}, {255, 0, 0}, "Facile", {255, 255, 255}};
    Button buttonMoyen = {{600, 100, 100, 50}, {255, 0, 0}, "Moyen", {255, 255, 255}};
    Button buttonDifficile = {{600, 170, 100, 50}, {255, 0, 0}, "Difficile", {255, 255, 255}};
    Button buttonValid = {{600, 240, 100, 50}, {100, 100, 100}, "Valide", {255, 255, 255}};

    Button buttonRelge1 = {{750, 30, 260, 50}, {100, 100, 100}, "Derniere case libre", {255, 255, 255}};
    Button buttonRelge2 = {{1050, 30, 260, 50}, {100, 100, 100}, "Derniere case restante", {255, 255, 255}};
    Button buttonRelge3 = {{750, 100, 260, 50}, {100, 100, 100}, "Dernier nombre possible", {255, 255, 255}};
    Button buttonRelge4 = {{1050, 100, 260, 50}, {100, 100, 100}, "Singletons nus", {255, 255, 255}};
    Button buttonRelge5 = {{750, 170, 260, 50}, {100, 100, 100}, "Paires nus", {255, 255, 255}};
    Button buttonRelge6 = {{1050, 170, 260, 50}, {100, 100, 100}, "Triplets nus", {255, 255, 255}};
    Button buttonRelge7 = {{750, 240, 260, 50}, {100, 100, 100}, "Singleton cache", {255, 255, 255}};
    Button buttonRelge8 = {{1050, 240, 260, 50}, {100, 100, 100}, "Paires cache", {255, 255, 255}};
    Button buttonRelge9 = {{750, 310, 260, 50}, {100, 100, 100}, "Triplets cache", {255, 255, 255}};
    Button buttonRelge10 = {{1050, 310, 260, 50}, {100, 100, 100}, "Pointante", {255, 255, 255}};
    Button buttonRelge11 = {{750, 380, 260, 50}, {100, 100, 100}, "X-wing", {255, 255, 255}};

    Button button1 = {{25, 660, 40, 40}, {100, 100, 100}, "1", {255, 255, 255}};
    Button button2 = {{70, 660, 40, 40}, {100, 100, 100}, "2", {255, 255, 255}};
    Button button3 = {{115, 660, 40, 40}, {100, 100, 100}, "3", {255, 255, 255}};
    Button button4 = {{160, 660, 40, 40}, {100, 100, 100}, "4", {255, 255, 255}};
    Button button5 = {{205, 660, 40, 40}, {100, 100, 100}, "5", {255, 255, 255}};
    Button button6 = {{250, 660, 40, 40}, {100, 100, 100}, "6", {255, 255, 255}};
    Button button7 = {{295, 660, 40, 40}, {100, 100, 100}, "7", {255, 255, 255}};
    Button button8 = {{340, 660, 40, 40}, {100, 100, 100}, "8", {255, 255, 255}};
    Button button9 = {{385, 660, 40, 40}, {100, 100, 100}, "9", {255, 255, 255}};
    Button button0 = {{430, 660, 40, 40}, {100, 100, 100}, "0", {255, 255, 255}};

    Button buttonResoudre = {{25, 600, 100, 50}, {255, 255, 255}, "Ressoudre", {0, 0, 0}};
    Button buttonVide = {{150, 600, 100, 50}, {255, 255, 255}, "Vide", {0, 0, 0}};
    Button buttonBack = {{300, 600, 100, 50}, {255, 255, 255}, "Backtracking", {0, 0, 0}};



    // Création de la fenêtre et du renderer
    window = SDL_CreateWindow("Sudoku", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH+900, SCREEN_HEIGHT+200, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    // Rendre la fenêtre en blanc
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE); // Couleur blanche
    SDL_RenderClear(renderer);

    // Dessiner la grille
    drawGrid(renderer);
    // Dessiner les nombres
    //drawNumbers(renderer, sudo);

    // Dessine le bouton
    drawButton(renderer, buttonResoudre, font);
    drawButton(renderer, buttonVide, font);
    drawButton(renderer, buttonBack, font);

    drawButton(renderer, buttonFacile, font);
    drawButton(renderer, buttonDifficile, font);
    drawButton(renderer, buttonMoyen, font);
    drawButton(renderer, buttonValid, font);

    drawButton(renderer, buttonRelge1, font);
    drawButton(renderer, buttonRelge2, font);
    drawButton(renderer, buttonRelge3, font);
    drawButton(renderer, buttonRelge4, font);
    drawButton(renderer, buttonRelge5, font);
    drawButton(renderer, buttonRelge6, font);
    drawButton(renderer, buttonRelge7, font);
    drawButton(renderer, buttonRelge8, font);
    drawButton(renderer, buttonRelge9, font);
    drawButton(renderer, buttonRelge10, font);
    drawButton(renderer, buttonRelge11, font);

    drawButton(renderer, button1, font);
    drawButton(renderer, button2, font);
    drawButton(renderer, button3, font);
    drawButton(renderer, button4, font);
    drawButton(renderer, button5, font);
    drawButton(renderer, button6, font);
    drawButton(renderer, button7, font);
    drawButton(renderer, button8, font);
    drawButton(renderer, button9, font);
    drawButton(renderer, button0, font);


    SDL_RenderPresent(renderer);

    int i;
    int j;

    SDL_Event event;
    bool quit = false;
    while (!quit) {
        // Gestion des événements
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            // Gestion des clics de souris sur les boutons
            else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                SDL_Point point = {mouseX, mouseY};
                if (isInside(point, buttonResoudre.rect)) {
                    printf("Ressoudre\n");
                    sudo = clickButtonRessoudre(renderer, sudo, regle);
                }
                else if (isInside(point, buttonBack.rect)){
                    printf("Backtracking\n");
                    sudo = clickButtonBacktracking(renderer, sudo);
                }
                else if (isInside(point, buttonVide.rect)) {
                    printf("Vide\n");
                    sudo  = initSudoku();
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE); // Couleur blanche
                    SDL_RenderClear(renderer);

                    drawGrid(renderer);

                    drawButton(renderer, buttonResoudre, font);
                    drawButton(renderer, buttonVide, font);
                    drawButton(renderer, buttonBack, font);

                    drawButton(renderer, buttonFacile, font);
                    drawButton(renderer, buttonDifficile, font);
                    drawButton(renderer, buttonMoyen, font);
                    drawButton(renderer, buttonValid, font);

                    drawButton(renderer, buttonRelge1, font);
                    drawButton(renderer, buttonRelge2, font);
                    drawButton(renderer, buttonRelge3, font);
                    drawButton(renderer, buttonRelge4, font);
                    drawButton(renderer, buttonRelge5, font);
                    drawButton(renderer, buttonRelge6, font);
                    drawButton(renderer, buttonRelge7, font);
                    drawButton(renderer, buttonRelge8, font);
                    drawButton(renderer, buttonRelge9, font);
                    drawButton(renderer, buttonRelge10, font);
                    drawButton(renderer, buttonRelge11, font);

                    drawButton(renderer, button1, font);
                    drawButton(renderer, button2, font);
                    drawButton(renderer, button3, font);
                    drawButton(renderer, button4, font);
                    drawButton(renderer, button5, font);
                    drawButton(renderer, button6, font);
                    drawButton(renderer, button7, font);
                    drawButton(renderer, button8, font);
                    drawButton(renderer, button9, font);
                    drawButton(renderer, button0, font);

                    SDL_RenderPresent(renderer);
                    
                }
                else if (isInside(point, buttonFacile.rect)) {
                    printf("Bouton Facile\n");
                    sudo = clickButtonFacile(renderer);
                    drawNumbers(renderer, sudo);
                    SDL_RenderPresent(renderer);
                    
                }
                else if (isInside(point, buttonMoyen.rect)) {
                    printf("Bouton Moyen\n");
                    sudo = clickButtonMoyen(renderer);
                    drawNumbers(renderer, sudo);
                    SDL_RenderPresent(renderer);
                }
                else if (isInside(point, buttonDifficile.rect)) {
                    printf("Bouton difficile\n");
                    sudo = clickButtonDifficile(renderer);
                    drawNumbers(renderer, sudo);
                    SDL_RenderPresent(renderer);
                }
                else if (isInside(point, buttonValid.rect)){
                    printf("Bouton Valide\n");
                    if (sudoku_valid(sudo)){
                        Button buttonValid = {{600, 240, 100, 50}, {0, 255, 0}, "Valide", {255, 255, 255}};
                        drawButton(renderer, buttonValid, font);
                        SDL_RenderPresent(renderer);
                    }
                    else{
                        Button buttonValid = {{600, 240, 100, 50}, {255, 0, 0}, "Valide", {255, 255, 255}};
                        drawButton(renderer, buttonValid, font);
                        SDL_RenderPresent(renderer);
                    }
                }
                else if (isInside(point, buttonRelge1.rect)) {
                    printf("Derniere case libre\n");
                    sudo = clickButtonRegle1(renderer,sudo);
                }
                else if (isInside(point, buttonRelge2.rect)) {
                    printf("Derniere case restante\n");
                    sudo = clickButtonRegle2(renderer, sudo);
                }
                else if (isInside(point, buttonRelge3.rect)) {
                    printf("Dernier nombre possible\n");
                    sudo = clickButtonRegle3(renderer, sudo);
                }
                else if (isInside(point, buttonRelge4.rect)) {
                    printf("Singletons nus\n");
                    sudo = clickButtonRegle4(renderer, sudo);
                }
                else if (isInside(point, buttonRelge5.rect)) {
                    printf("Paires nus\n");
                    sudo = clickButtonRegle5(renderer, sudo);
                }
                else if (isInside(point, buttonRelge6.rect)) {
                    printf("Trplets nus\n");
                    sudo = clickButtonRegle6(renderer, sudo);
                }
                else if (isInside(point, buttonRelge7.rect)) {
                    printf("Singletons cache\n");
                    sudo = clickButtonRegle7(renderer, sudo);
                }
                else if (isInside(point, buttonRelge8.rect)) {
                    printf("Paires cache\n");
                    sudo = clickButtonRegle8(renderer, sudo);
                }
                else if (isInside(point, buttonRelge9.rect)) {
                    printf("Triplets cache\n");
                    sudo = clickButtonRegle9(renderer, sudo);
                }
                else if (isInside(point, buttonRelge10.rect)) {
                    printf("Pointante\n");
                    sudo = clickButtonRegle10(renderer, sudo);
                }
                else if (isInside(point, buttonRelge11.rect)) {
                    printf("X-wing\n");
                    sudo = clickButtonRegle11(renderer, sudo);
                }
                else if (isInside(point, button1.rect)){
                    printf("Button 1\n");
                    
                    add_value(sudo,i,j,1);
                    drawNumberR(renderer,sudo,i,j);                    
                    SDL_RenderPresent(renderer);
                }
                
                else if (isInside(point, button2.rect)){
                    printf("Button 2\n");

                    add_value(sudo,i,j,2);
                    drawNumberR(renderer,sudo,i,j);                    
                    SDL_RenderPresent(renderer);
                }
                else if (isInside(point, button3.rect)){
                    printf("Button 3\n");

                    add_value(sudo,i,j,3);
                    drawNumberR(renderer,sudo,i,j);                    
                    SDL_RenderPresent(renderer);
                }
                else if (isInside(point, button4.rect)){
                    printf("Button 4\n");

                    add_value(sudo,i,j,4);
                    drawNumberR(renderer,sudo,i,j);                    
                    SDL_RenderPresent(renderer);
                }
                else if (isInside(point, button5.rect)){
                    printf("Button 5\n");

                    add_value(sudo,i,j,5);
                    drawNumberR(renderer,sudo,i,j);                    
                    SDL_RenderPresent(renderer);
                }
                else if (isInside(point, button6.rect)){
                    printf("Button 6\n");

                    add_value(sudo,i,j,6);
                    drawNumberR(renderer,sudo,i,j);                    
                    SDL_RenderPresent(renderer);
                }
                else if (isInside(point, button7.rect)){
                    printf("Button 7\n");

                    add_value(sudo,i,j,7);
                    drawNumberR(renderer,sudo,i,j);                    
                    SDL_RenderPresent(renderer);
                }
                else if (isInside(point, button8.rect)){
                    printf("Button 8\n");

                    add_value(sudo,i,j,8);
                    drawNumberR(renderer,sudo,i,j);                    
                    SDL_RenderPresent(renderer);
                }
                else if (isInside(point, button9.rect)){
                    printf("Button 9\n");

                    add_value(sudo,i,j,9);
                    drawNumberR(renderer,sudo,i,j);                    
                    SDL_RenderPresent(renderer);
                }
                else if (isInside(point, button0.rect)){
                    printf("Button 0\n");

                    rem_value(sudo,i,j);
                    drawNumbers(renderer,sudo);                    
                    SDL_RenderPresent(renderer);
                }
                else if (isInside(point, rectGrille)){
                    
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE); // Couleur blanche
                    SDL_RenderClear(renderer);

                    drawGrid(renderer);
                    drawNumbers(renderer, sudo);

                    drawButton(renderer, buttonResoudre, font);
                    drawButton(renderer, buttonVide, font);
                    drawButton(renderer, buttonBack, font);

                    drawButton(renderer, buttonFacile, font);
                    drawButton(renderer, buttonDifficile, font);
                    drawButton(renderer, buttonMoyen, font);
                    drawButton(renderer, buttonValid, font);

                    drawButton(renderer, buttonRelge1, font);
                    drawButton(renderer, buttonRelge2, font);
                    drawButton(renderer, buttonRelge3, font);
                    drawButton(renderer, buttonRelge4, font);
                    drawButton(renderer, buttonRelge5, font);
                    drawButton(renderer, buttonRelge6, font);
                    drawButton(renderer, buttonRelge7, font);
                    drawButton(renderer, buttonRelge8, font);
                    drawButton(renderer, buttonRelge9, font);
                    drawButton(renderer, buttonRelge10, font);
                    drawButton(renderer, buttonRelge11, font);

                    drawButton(renderer, button1, font);
                    drawButton(renderer, button2, font);
                    drawButton(renderer, button3, font);
                    drawButton(renderer, button4, font);
                    drawButton(renderer, button5, font);
                    drawButton(renderer, button6, font);
                    drawButton(renderer, button7, font);
                    drawButton(renderer, button8, font);
                    drawButton(renderer, button9, font);
                    drawButton(renderer, button0, font);
                    

                    int mouseX = event.button.x;
                    int mouseY = event.button.y;

                    // Convertir les coordonnées du clic de la souris en coordonnées de case dans la grille de Sudoku
                    int clickedRow = (mouseY / GRID_SIZE)-1;
                    int clickedCol = (mouseX / GRID_SIZE)-1;

                    drawGridNote(renderer,800,500);
                    drawNumbersNote(renderer,sudo,clickedRow, clickedCol);

                    i = clickedRow;
                    j = clickedCol;

                    affiche_tab_note(sudo,clickedRow, clickedRow, clickedCol, clickedCol);
                    
                    SDL_RenderPresent(renderer);
                }
            }
        }
    }
    // Libération des ressources SDL_ttf
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}


/*


int main()
{
    StructSudoku tab1 = initSudoku(tab1);

    add_value(tab1, 0,0,1);
    add_value(tab1, 0,1,2);
    add_value(tab1, 0,2,3);
    add_value(tab1, 1,0,4);
    add_value(tab1, 1,1,5);
    add_value(tab1, 1,2,6);
    add_value(tab1, 2,0,7);
    add_value(tab1, 2,1,8);

    StructSudoku tab2 = initSudoku(tab2);

    add_value(tab2, 4,2,8);
    add_value(tab2, 6,4,8);
    add_value(tab2, 8,0,9);
    add_value(tab2, 8,1,1);
    add_value(tab2, 7,1,6);

    StructSudoku tab3 = initSudoku(tab3);

    add_value(tab3, 0,0,2);
    add_value(tab3, 0,1,4);
    add_value(tab3, 0,2,6);
    add_value(tab3, 1,3,3);
    add_value(tab3, 1,5,6);
    add_value(tab3, 1,7,7);
    add_value(tab3, 1,8,4);
    add_value(tab3, 2,0,3);
    add_value(tab3, 2,0,3);
    add_value(tab3, 2,1,7);
    add_value(tab3, 4,0,1);
    add_value(tab3, 7,0,8);
    add_value(tab3, 8,0,9);

    ///Singletons nus
    StructSudoku tab4 = initSudoku();

    add_value(tab4, 0, 2, 8);
    add_value(tab4, 0, 5, 7);
    add_value(tab4, 0, 6, 9);

    add_value(tab4, 1, 1, 4);
    add_value(tab4, 1, 2, 2);
    add_value(tab4, 1, 5, 5);

    add_value(tab4, 2, 3, 6);
    add_value(tab4, 2, 7, 5);

    add_value(tab4, 3, 2, 3);
    add_value(tab4, 3, 5, 6);
    add_value(tab4, 3, 6, 8);
    add_value(tab4, 3, 8, 1);

    add_value(tab4, 4, 8, 6);

    add_value(tab4, 5, 0, 9);
    add_value(tab4, 5, 4, 7);

    add_value(tab4, 6, 1, 8);
    add_value(tab4, 6, 3, 1);
    add_value(tab4, 6, 4, 3);
    add_value(tab4, 6, 6, 4);
    add_value(tab4, 6, 7, 7);

    add_value(tab4, 7, 4, 9);

    add_value(tab4, 8, 1, 1);

    ///Paires nus
    StructSudoku tab5 = initSudoku();

    add_value(tab5, 0, 2, 2);
    add_value(tab5, 0, 4, 8);
    add_value(tab5, 0, 5, 5);
    add_value(tab5, 0, 8, 4);

    add_value(tab5, 1, 4, 3);
    add_value(tab5, 1, 7, 6);

    add_value(tab5, 2, 2, 4);
    add_value(tab5, 2, 3, 2);
    add_value(tab5, 2, 4, 1);
    add_value(tab5, 2, 7, 3);

    add_value(tab5, 3, 7, 5);
    add_value(tab5, 3, 8, 2);

    add_value(tab5, 4, 6, 3);
    add_value(tab5, 4, 7, 1);

    add_value(tab5, 5, 0, 9);

    add_value(tab5, 6, 0, 8);
    add_value(tab5, 6, 5, 6);

    add_value(tab5, 7, 0, 2);
    add_value(tab5, 7, 1, 5);
    add_value(tab5, 7, 3, 4);
    add_value(tab5, 7, 8, 8);

    add_value(tab5, 8, 5, 1);
    add_value(tab5, 8, 6, 6);

    ///triplets nus
    StructSudoku tab6 = initSudoku();

    add_value(tab6, 0, 0, 3);
    add_value(tab6, 0, 1, 7);
    add_value(tab6, 0, 7, 9);

    add_value(tab6, 1, 0, 9);
    add_value(tab6, 1, 4, 7);

    add_value(tab6, 2, 3, 4);
    add_value(tab6, 2, 4, 2);
    add_value(tab6, 2, 8, 6);

    add_value(tab6, 3, 2, 1);
    add_value(tab6, 3, 4, 8);
    add_value(tab6, 3, 5, 4);
    add_value(tab6, 3, 6, 2);

    add_value(tab6, 5, 0, 8);
    add_value(tab6, 5, 3, 6);
    add_value(tab6, 5, 7, 5);

    add_value(tab6, 6, 2, 6);
    add_value(tab6, 6, 5, 2);
    add_value(tab6, 6, 7, 1);

    add_value(tab6, 7, 7, 3);
    add_value(tab6, 7, 8, 9);

    add_value(tab6, 8, 1, 5);
    add_value(tab6, 8, 6, 4);

    ///Singleton cach�
    StructSudoku tab7 = initSudoku();

    add_value(tab7, 0, 2, 9);
    add_value(tab7, 0, 4, 3);
    add_value(tab7, 0, 5, 2);

    add_value(tab7, 1, 3, 7);

    add_value(tab7, 2, 0, 1);
    add_value(tab7, 2, 1, 6);
    add_value(tab7, 2, 2, 2);

    add_value(tab7, 3, 1, 1);
    add_value(tab7, 3, 4, 2);
    add_value(tab7, 3, 6, 5);
    add_value(tab7, 3, 7, 6);

    add_value(tab7, 4, 3, 9);

    add_value(tab7, 5, 1, 5);
    add_value(tab7, 5, 6, 1);
    add_value(tab7, 5, 8, 7);

    add_value(tab7, 6, 6, 4);
    add_value(tab7, 6, 8, 3);

    add_value(tab7, 7, 1, 2);
    add_value(tab7, 7, 2, 6);
    add_value(tab7, 7, 5, 9);

    add_value(tab7, 8, 2, 5);
    add_value(tab7, 8, 3, 8);
    add_value(tab7, 8, 4, 7);

    ///Paire cach�
    StructSudoku tab9 = initSudoku();

    add_value(tab9, 0, 2, 9);
    add_value(tab9, 0, 4, 3);
    add_value(tab9, 0, 5, 2);

    add_value(tab9, 1, 3, 7);

    add_value(tab9, 2, 0, 1);
    add_value(tab9, 2, 1, 6);
    add_value(tab9, 2, 2, 2);

    add_value(tab9, 3, 1, 1);
    add_value(tab9, 3, 4, 2);
    add_value(tab9, 3, 6, 5);
    add_value(tab9, 3, 7, 6);

    add_value(tab9, 4, 3, 9);

    add_value(tab9, 5, 1, 5);
    add_value(tab9, 5, 6, 1);
    add_value(tab9, 5, 8, 7);

    add_value(tab9, 6, 6, 4);
    add_value(tab9, 6, 8, 3);

    add_value(tab9, 7, 1, 2);
    add_value(tab9, 7, 2, 6);
    add_value(tab9, 7, 5, 9);

    add_value(tab9, 8, 2, 5);
    add_value(tab9, 8, 3, 8);
    add_value(tab9, 8, 4, 7);

    ///triplets cach�
    StructSudoku tab8 = initSudoku();

    add_value(tab8, 0, 2, 8);
    add_value(tab8, 0, 5, 7);

    add_value(tab8, 1, 1, 4);
    add_value(tab8, 1, 2, 2);
    add_value(tab8, 1, 5, 5);

    add_value(tab8, 3, 2, 3);
    add_value(tab8, 3, 5, 6);
    add_value(tab8, 3, 6, 8);
    add_value(tab8, 3, 8, 1);

    add_value(tab8, 4, 8, 6);

    add_value(tab8, 5, 0, 9);

    add_value(tab8, 6, 1, 8);
    add_value(tab8, 6, 3, 1);
    add_value(tab8, 6, 4, 3);
    add_value(tab8, 6, 6, 4);
    add_value(tab8, 6, 7, 7);

    add_value(tab8, 7, 4, 9);

    add_value(tab8, 8, 1, 1);

    ///paire pointants
    StructSudoku tab10 = initSudoku();

    add_value(tab10, 0, 2, 9);
    add_value(tab10, 0, 4, 7);

    add_value(tab10, 1, 1, 8);
    add_value(tab10, 1, 3, 4);

    add_value(tab10, 2, 2, 3);
    add_value(tab10, 2, 7, 2);
    add_value(tab10, 2, 8, 8);

    add_value(tab10, 3, 0, 1);
    add_value(tab10, 3, 6, 6);
    add_value(tab10, 3, 7, 7);

    add_value(tab10, 4, 1, 2);
    add_value(tab10, 4, 4, 1);
    add_value(tab10, 4, 5, 3);
    add_value(tab10, 4, 7, 4);

    add_value(tab10, 5, 1, 4);
    add_value(tab10, 5, 5, 7);
    add_value(tab10, 5, 6, 8);

    add_value(tab10, 6, 0, 6);
    add_value(tab10, 6, 4, 3);

    add_value(tab10, 7, 1, 1);

    add_value(tab10, 8, 6, 2);
    add_value(tab10, 8, 7, 8);
    add_value(tab10, 8, 8, 4);

    ///Compl�te le sudoku
    StructSudoku sudo = initSudoku();

    ///Facile
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
    //////////////////////////

    ///Moyen
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
    //////////////////////////

    ///Difficile
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

    //X-Wing
    StructSudoku x_wing = initSudoku();
    add_value(x_wing, 0, 2, 3);
    add_value(x_wing, 0, 3, 8);
    add_value(x_wing, 0, 6, 5);
    add_value(x_wing, 0, 7, 1);

    add_value(x_wing, 1, 2, 8);
    add_value(x_wing, 1, 3, 7);
    add_value(x_wing, 1, 6, 9);
    add_value(x_wing, 1, 7, 3);

    add_value(x_wing, 2, 0, 1);
    add_value(x_wing, 2, 3, 3);
    add_value(x_wing, 2, 5, 5);
    add_value(x_wing, 2, 6, 7);
    add_value(x_wing, 2, 7, 2);
    add_value(x_wing, 2, 8, 8);

    add_value(x_wing, 3, 3, 2);
    add_value(x_wing, 3, 6, 8);
    add_value(x_wing, 3, 7, 4);
    add_value(x_wing, 3, 8, 9);

    add_value(x_wing, 4, 0, 8);
    add_value(x_wing, 4, 2, 1);
    add_value(x_wing, 4, 3, 9);
    add_value(x_wing, 4, 5, 6);
    add_value(x_wing, 4, 6, 2);
    add_value(x_wing, 4, 7, 5);
    add_value(x_wing, 4, 8, 7);

    add_value(x_wing, 5, 3, 5);
    add_value(x_wing, 5, 6, 1);
    add_value(x_wing, 5, 7, 6);
    add_value(x_wing, 5, 8, 3);

    add_value(x_wing, 6, 0, 9);
    add_value(x_wing, 6, 1, 6);
    add_value(x_wing, 6, 2, 4);
    add_value(x_wing, 6, 3, 1);
    add_value(x_wing, 6, 4, 2);
    add_value(x_wing, 6, 5, 7);
    add_value(x_wing, 6, 6, 3);
    add_value(x_wing, 6, 7, 8);
    add_value(x_wing, 6, 8, 5);

    add_value(x_wing, 7, 0, 3);
    add_value(x_wing, 7, 1, 8);
    add_value(x_wing, 7, 2, 2);
    add_value(x_wing, 7, 3, 6);
    add_value(x_wing, 7, 4, 5);
    add_value(x_wing, 7, 5, 9);
    add_value(x_wing, 7, 6, 4);
    add_value(x_wing, 7, 7, 7);
    add_value(x_wing, 7, 8, 1);

    add_value(x_wing, 8, 1, 1);
    add_value(x_wing, 8, 3, 4);
    add_value(x_wing, 8, 6, 6);
    add_value(x_wing, 8, 7, 9);
    add_value(x_wing, 8, 8, 2);

    StructSudoku wing = initSudoku();
    add_value(wing, 0, 0, 7);
    add_value(wing, 0, 2, 1);
    add_value(wing, 0, 4, 5);

    add_value(wing, 1, 2, 6);
    add_value(wing, 1, 3, 7);
    add_value(wing, 1, 4, 1);
    add_value(wing, 1, 6, 9);
    add_value(wing, 1, 7, 5);
    add_value(wing, 1, 8, 3);

    add_value(wing, 2, 0, 5);
    add_value(wing, 2, 2, 3);
    add_value(wing, 2, 3, 8);
    add_value(wing, 2, 6, 4);
    add_value(wing, 2, 7, 7);
    add_value(wing, 2, 8, 1);

    add_value(wing, 3, 0, 6);
    add_value(wing, 3, 1, 7);
    add_value(wing, 3, 2, 8);
    add_value(wing, 3, 3, 1);
    add_value(wing, 3, 4, 4);
    add_value(wing, 3, 5, 9);
    add_value(wing, 3, 6, 5);
    add_value(wing, 3, 7, 3);
    add_value(wing, 3, 8, 2);

    add_value(wing, 4, 2, 9);
    add_value(wing, 4, 3, 2);
    add_value(wing, 4, 5, 5);

    add_value(wing, 5, 1, 5);
    add_value(wing, 5, 2, 2);
    add_value(wing, 5, 3, 6);
    add_value(wing, 5, 5, 7);
    add_value(wing, 5, 7, 4);
    add_value(wing, 5, 8, 9);

    add_value(wing, 6, 1, 1);
    add_value(wing, 6, 2, 4);
    add_value(wing, 6, 4, 7);
    add_value(wing, 6, 7, 5);

    add_value(wing, 7, 2, 5);
    add_value(wing, 7, 3, 4);
    add_value(wing, 7, 4, 2);
    add_value(wing, 7, 5, 1);

    add_value(wing, 8, 0, 2);
    add_value(wing, 8, 2, 7);
    add_value(wing, 8, 3, 5);
    add_value(wing, 8, 5, 8);
    add_value(wing, 8, 6, 3);
    add_value(wing, 8, 7, 1);
    add_value(wing, 8, 8, 4);

    StructSudoku wingv = initSudoku();
    add_value(wingv, 0, 0, 2);
    add_value(wingv, 0, 5, 6);
    add_value(wingv, 0, 6, 5);
    add_value(wingv, 0, 8, 7);

    add_value(wingv, 1, 2, 1);
    add_value(wingv, 1, 3, 5);
    add_value(wingv, 1, 5, 7);

    add_value(wingv, 2, 0, 7);
    add_value(wingv, 2, 1, 5);
    add_value(wingv, 2, 2, 4);
    add_value(wingv, 2, 3, 2);
    add_value(wingv, 2, 4, 9);
    add_value(wingv, 2, 5, 8);
    add_value(wingv, 2, 6, 3);
    add_value(wingv, 2, 7, 6);
    add_value(wingv, 2, 8, 1);

    add_value(wingv, 3, 0, 5);
    add_value(wingv, 3, 1, 4);
    add_value(wingv, 3, 3, 6);
    add_value(wingv, 3, 4, 2);
    add_value(wingv, 3, 5, 1);
    add_value(wingv, 3, 6, 8);
    add_value(wingv, 3, 7, 7);

    add_value(wingv, 4, 1, 2);
    add_value(wingv, 4, 2, 7);
    add_value(wingv, 4, 5, 4);
    add_value(wingv, 4, 7, 1);
    add_value(wingv, 4, 8, 5);

    add_value(wingv, 5, 0, 8);
    add_value(wingv, 5, 1, 1);
    add_value(wingv, 5, 3, 7);
    add_value(wingv, 5, 4, 5);
    add_value(wingv, 5, 5, 9);

    add_value(wingv, 6, 0, 3);
    add_value(wingv, 6, 5, 5);
    add_value(wingv, 6, 6, 4);
    add_value(wingv, 6, 7, 9);

    add_value(wingv, 7, 0, 1);
    add_value(wingv, 7, 3, 4);
    add_value(wingv, 7, 5, 3);
    add_value(wingv, 7, 6, 7);
    add_value(wingv, 7, 7, 5);

    add_value(wingv, 8, 0, 4);
    add_value(wingv, 8, 2, 5);
    add_value(wingv, 8, 3, 9);
    add_value(wingv, 8, 5, 2);
    add_value(wingv, 8, 6, 1);
    add_value(wingv, 8, 7, 3);



    /////////////////////////



    ///Possibilit� de d�clanche toutes les r�gles
    int option = 0;
    int k;

    do {
        afficherMenu();
        scanf("%d", &option);
        printf("\n");

        switch(option) {
        case 1:
            printf("**** Verification de la regle 1 ****\n");

            AfficheTab(tab1);
            regle(tab1, 2, 2);
            AfficheTab(tab1);
            break;
        case 2:
            printf("**** Verification de la regle 2 ****\n");

            AfficheTab(tab2);
            regle(tab2, 7, 0);
            AfficheTab(tab2);
            break;
        case 3:
            printf("**** Verification de la regle 3 ****\n");

            AfficheTab(tab3);
            regle(tab3, 1, 0);
            AfficheTab(tab3);
            break;
        case 4:
            printf ("Choisir le nombres de uplets (1, 2, 3): ");
            scanf("%d", &k);
            printf("\n");

            if (k == 1) {
                printf("\nAvant : ");
                AfficheTab(tab4);
                singleton_nus(tab4, 6, 8, 3, 5);
                printf("\nApres :");
                AfficheTab(tab4);
            }
            else if (k == 2){
                AfficheTab(tab5);
                printf("\nAvant : ");
                affiche_tab_note(tab5, 0, 2, 3, 5);
                paires_nus(tab5, 0, 2, 3, 5);
                printf("\nApres :");
                affiche_tab_note(tab5, 0, 2, 3, 5);
            }
            else if (k == 3){
                AfficheTab(tab6);
                printf("\nAvant : ");
                affiche_tab_note(tab6, 0, 2, 0, 2);
                triplets_nus(tab6, 0, 2, 0, 2);
                printf("\nApres :");
                affiche_tab_note(tab6, 0, 2, 0, 2);
            }
            else {
                printf("Ce k est pas possible. Rentrer 1 ou 2 ou 3 la prochaine fois.");
            }
            break;
        case 5:
            printf ("Choisir le nombres de uplets (1, 2, 3): ");
            scanf("%d", &k);
            printf("\n");

            if (k == 1){
                printf("\nAvant : ");
                AfficheTab(tab7);
                singleton_cache(tab7, 6, 8, 0, 2);
                printf("\nApres :");
                AfficheTab(tab7);
            }
            else if (k == 2){
                AfficheTab(tab9);
                printf("\nAvant : ");
                affiche_tab_note(tab9, 3, 5, 0, 2);
                paires_cache(tab9, 3, 5, 0, 2);
                printf("\nApres :");
                affiche_tab_note(tab9, 3, 5, 0, 2);
            }
            else if (k == 3) {
                AfficheTab(tab8);
                printf("\nAvant : ");
                affiche_tab_note(tab8, 6, 8, 3, 5);
                triplets_cache(tab8, 6, 8, 3, 5);
                printf("\nApres : ");
                affiche_tab_note(tab8, 6, 8, 3, 5);
            }
            else {
                printf("Ce k est pas possible. Rentrer 1 ou 2 ou 3 la prochaine fois.");
            }
            break;
        case 6 :
            printf("\nAvant resolution :\n");
            AfficheTab(sudo);
            applyRules(sudo);
            printf("\nApres resolution :\n");
            AfficheTab(sudo);
            printf("\nvalide : %d",sudoku_valid(sudo));
            break;
        case 7 :
            affiche_tab_note(tab10,0,8,0,0);
            affiche_tab_note(tab10,6,6,0,8);

            pointante(tab10);

            affiche_tab_note(tab10,0,8,0,0);
            affiche_tab_note(tab10,6,6,0,8);
            break;
        case 8 :
            AfficheTab(x_wing);

            affiche_tab_note(x_wing,0,0,1,1);
            affiche_tab_note(x_wing,0,0,4,4);

            affiche_tab_note(x_wing,1,1,1,1);
            affiche_tab_note(x_wing,1,1,4,4);

            affiche_tab_note(x_wing,5,5,1,1);
            affiche_tab_note(x_wing,5,5,4,4);

            X_wing(x_wing);

            affiche_tab_note(x_wing,0,0,1,1);
            affiche_tab_note(x_wing,0,0,4,4);

            affiche_tab_note(x_wing,1,1,1,1);
            affiche_tab_note(x_wing,1,1,4,4);

            affiche_tab_note(x_wing,5,5,1,1);
            affiche_tab_note(x_wing,5,5,4,4);
            
            printf("NE DOIS PAS ETRE MODIFIE\n");
            affiche_tab_note(x_wing,2,2,1,1);
            affiche_tab_note(x_wing,2,2,4,4);

            affiche_tab_note(x_wing,4,4,1,1);
            affiche_tab_note(x_wing,4,4,4,4);


            AfficheTab(wing);

            affiche_tab_note(wing,0,0,1,1);
            affiche_tab_note(wing,7,7,1,1);

            X_wing(wing);

            affiche_tab_note(wing,0,0,1,1);
            affiche_tab_note(wing,7,7,1,1);
            
            printf("NE DOIS PAS ETRE MODIFIE\n");
            affiche_tab_note(wing,2,2,1,1);
            affiche_tab_note(wing,2,2,4,4);

            affiche_tab_note(wing,8,8,1,1);
            affiche_tab_note(wing,8,8,4,4);



            AfficheTab(wingv);

            affiche_tab_note(wingv,1,1,1,1);
            affiche_tab_note(wingv,1,1,8,8);

            X_wing(wingv);

            affiche_tab_note(wingv,1,1,1,1);
            affiche_tab_note(wingv,1,1,8,8);
            
            printf("NE DOIS PAS ETRE MODIFIE\n");
            affiche_tab_note(wingv,1,1,0,0);
            affiche_tab_note(wingv,1,1,6,6);

            affiche_tab_note(wingv,4,4,0,0);
            affiche_tab_note(wingv,4,4,6,6);

            break;
        case 9:
            printf("Au revoir !\n");
            break;
        default :
            printf("Option invalide. Veuillez choisir une option valide.\n\n");
        }
    } while (option != 9);
    


    

    return 0;
}
*/