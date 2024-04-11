SDL
Installation de SDL :
sudo apt-get install libsdl2-dev
sudo apt-get update
sudo apt-get install libsdl2-ttf-dev

Compilation : 
gcc -o test type.c Sudoku.c main.c interface.c $(sdl2-config --cflags --libs) -lSDL2_ttf
./test
