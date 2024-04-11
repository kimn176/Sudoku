#include <stdio.h>
#include <stdlib.h>

#include "Sudoku.h"
#include "type.h"

/// /// /// /// /// /// AFFICHAGE /// /// /// /// /// ///

///Pour l'affichage
void Print_Tiret(int n)
{
    for (int i=0; i <n+1; i++) {
        printf("---");
    }
}

///Affiche le Sudoku
void AfficheTab(StructSudoku tab)
{
    printf ("Votre grille: \n \n");

    Print_Tiret(NB_LONGUEUR);
    printf("\n");

    for(int i = 0; i < NB_LONGUEUR; i++) { //Première boucle pour le x
        printf ("|");
        for(int j = 0; j < NB_LONGUEUR; j++) { //Deuxième boucle pour le y
            printf("%2d ", get_value(tab, i, j));
            if (j%NB_CARRE == NB_CARRE - 1) {       //Sépare le sudoku en trois par trois colonnes
                printf ("|");
            }
        }
        if (i%NB_CARRE == NB_CARRE - 1) {           //Sépare le sudoku en trois par trois lignes
            printf("\n");
            Print_Tiret(NB_LONGUEUR);
        }
        printf("\n");
    }
}

/// /// /// /// /// /// CREATION DU TABLEAU /// /// /// /// /// ///


///Initialise les valeurs du tableau à 0
StructSudoku initSudoku()
{
    StructSudoku sudo;
    sudo.cell = (StructCellule **)malloc(NB_LONGUEUR * sizeof(StructCellule *));

    for(int i=0; i<NB_LONGUEUR; i++){
        sudo.cell[i] = (StructCellule *)malloc(NB_LONGUEUR * sizeof(StructCellule));
        for(int j=0; j<NB_LONGUEUR; j++){
            set_value(&sudo, i, j, 0);
            set_note(&sudo, i, j, j, 0);
        }
    }
    return sudo;
}


///Met à jour les notes
void update_note(StructSudoku tab, int x, int y, int val, int b)
{
    for(int i=0; i<NB_LONGUEUR; i++){
        set_note(&tab, x, i, val-1, b);         //Met à jour les notes des cellules de la ligne x
        set_note(&tab, i, y, val-1, b);         //Met à jour les notes des cellules de la colonne y
    }
    int imin = x - (x%NB_CARRE);                //Récupère la coordonnée de minimale de x d'un carré
    int jmin = y - (y%NB_CARRE);                //Récupère la coordonnée de minimale de y d'un carré
    int imax = imin + NB_CARRE-1;               //Récupère la coordonnée de maximale de x d'un carré
    int jmax = jmin + NB_CARRE-1;               //Récupère la coordonnée de maximale de y d'un carré
    for(int i = imin ; i<=imax; i++)
    {                                           //C'est 2 boucle nous permettent de se déplacer dans le carré
        for(int j = jmin; j<=jmax; j++)
        {
            set_note(&tab, i, j, val-1, b);    //Met à jour les notes des cellules du carré
        }
    }
}


///Ajoute une valeur donnée à la coordonnée donnée
void add_value(StructSudoku tab, int x, int y, int val)
{
    set_value(&tab, x, y, val);
    update_note(tab, x, y, val, 1);
    for (int i=0; i<NB_LONGUEUR; i++){
        set_note(&tab, x, y, i, 1);
    }
}


///Supprime la valeur d'une coordonnée donnée
void rem_value(StructSudoku tab, int x, int y)
{
    int a = get_value(tab, x, y);
    set_value(&tab,x, y, 0);
    update_note(tab, x, y, a, 0);
}
/// /// /// /// /// /// VERIFICATION DU TABLEAU /// /// /// /// /// ///

///Valide un rectangle
bool valid(StructSudoku tab, int xmin, int ymin, int xmax, int ymax)
{
    bool save[NB_LONGUEUR];                                         //Creation d'un tableau de bool
    for(int i=0; i < NB_LONGUEUR; i++) {
        save[i]=false;                                              //Initialisation du tableau a "false" pour toutes les cases
    }
    for(int x=xmin; x <= xmax; x++) {                               //Boucle pour naviguer entre les lignes
        for(int y=ymin; y <= ymax; y++) {                           //Boucle pour naviguer entre les colonnes
            if (get_value(tab, x, y) == 0) {}                       //Si la valeur est egal a 0 on ne fait rien
            else if (save[get_value(tab, x, y)-1] == false) {
                save[get_value(tab, x, y)-1] = true;                //Si la valeur est differente de 0 et que la case du tableau correspondante a la valeur est false
            }                                                       //alors on met true a la case du tableau
            else return false;                                      //Sinon on retourne false
        }
    }
    return true;                                                    //Si tout ce passe bien la fonction renvoie true
}

///Vérifie si la ligne donnée est bonne ou non
bool line_valid(StructSudoku tab, int x)
{
    return valid(tab, x, 0, x, NB_LONGUEUR-1);
}

///Vérifie si la colonne donnée est bonne ou non
bool column_valid(StructSudoku tab, int y)
{
    return valid(tab, 0, y, NB_LONGUEUR-1, y);
}

///Vérifie si le carré donnée est bon ou non
bool square_valid(StructSudoku tab, int x, int y)
{
    return valid(tab, x, y, x+(NB_CARRE-1), y+(NB_CARRE-1));
}

///Vérifie si le sudoku est valide ou non en appelant les trois fonctions précédentes
bool sudoku_valid(StructSudoku tab)
{
    for (int i = 0; i < NB_LONGUEUR; i++) {                                             //Boucle qui permet de se déplacer dans le Sudoku grâce à l'indice i
        if (line_valid(tab, i) == false || column_valid(tab, i) == false) {             //Condition qui permet de savoir si la ligne et la colonne sont valides
            return false;
        }
        if (i%(NB_LONGUEUR/NB_CARRE) == 0) {
            if (square_valid(tab, i, (NB_LONGUEUR/NB_CARRE)-NB_CARRE ) == false ||
                    square_valid(tab, i, (NB_LONGUEUR/NB_CARRE)   ) == false ||
                    square_valid(tab, i, (NB_LONGUEUR/NB_CARRE +NB_CARRE)) == false ) { //Condition qui permet de savoir si les carrés sont valides
                return false;
            }
        }
    }
    return true;
}


/// /// /// /// /// /// REGLE /// /// /// /// /// ///

///Retourne un indice par rapport à la valeur manquante
int ValeurManquante(StructSudoku tab, int x, int y)
{
    for (int i=0; i<NB_LONGUEUR; i++){
        if (get_note(tab,x,y,i) != 1){
            return i+1;
        }
    }
    return -1;
}


///Fonction qui complète la grille avec les 3 premières règles
bool regle(StructSudoku tab, int x, int y){
    int c=0;
    for (int i =0; i<NB_LONGUEUR; i++){
        if (get_note(tab, x, y, i) != 1){
            c++;
        }
    }
    if (c == 1){
        int v = ValeurManquante(tab, x, y);
        add_value(tab,x,y,v);
        printf("Regle : derniere case libre, Position : (%d, %d), Valeur ajoute : %d \n",x,y,v);
        return true;
    }
    else {
        int compteur;                               //Variable qui compte le nombre de notes à 0
        int imin = x - (x%NB_CARRE);                //Récupère la coordonnée de minimale de x d'un carré
        int jmin = y - (y%NB_CARRE);                //Récupère la coordonnée de minimale de y d'un carré
        int imax = imin + NB_CARRE-1;               //Récupère la coordonnée de maximale de x d'un carré
        int jmax = jmin + NB_CARRE-1;               //Récupère la coordonnée de maximale de y d'un carré
        for (int z=0; z<NB_LONGUEUR; z++){
            if (get_note(tab,x,y,z) != 1){
                compteur = 0;
                for(int i = imin ; i<=imax; i++)
                {                                   //C'est 2 boucle nous permettent de se déplacer dans le carré
                    for(int j = jmin; j<=jmax; j++)
                    {
                        if (get_note(tab, i, j, z) != 1){
                            compteur++;
                        }
                    }
                }
                if (compteur == 1){
                    add_value(tab,x,y,z+1);
                    printf("Regle : dernier nombre possible, Position : (%d, %d), Valeur ajoute : %d \n",x,y,z+1);
                    return true;
                }
            }
        }
    }
    return false;
}


/// /// /// /// K-uplet nus /// /// /// /// ///
///Compte le nombre de true dans le tableau
int nb_true(int* tab)
{
    int cpt=0;
    for(int i=0; i<NB_LONGUEUR; i++){
        if(tab[i] == true){
            cpt++;
        }
    }
    return cpt;
}

///Singleton nus
bool singleton_nus(StructSudoku tab, int xmin, int xmax, int ymin, int ymax)
{
    for(int i=xmin; i<=xmax; i++){
        for(int j=ymin; j<=ymax; j++){
            if(get_value(tab, i, j) == 0){
                if(check_note(tab, i, j) == 1){
                    int val = ValeurManquante(tab, i, j);
                    add_value(tab, i, j, val);
                    printf("Regle : singleton nus, Position : (%d, %d), Valeur ajoute : %d \n",i,j,val);
                    return true;
                }
            }
        }
    }
    return false;
}

///Paires nus
bool paires_nus(StructSudoku tab, int xmin, int xmax, int ymin, int ymax)
{
    bool b = false;                                                     //Ce bool nous retourne vrai ou faux si nous avons aplliquer la règle
    for(int note1=0; note1<NB_LONGUEUR; note1++){
        for(int note2=note1+1; note2<NB_LONGUEUR; note2++){             //Les 2 boucles servent pour les notes
            int cpt=0;;
            for(int i=xmin; i<=xmax; i++){
                for(int j=ymin; j<=ymax; j++){                          //Ici c'est pour les coordonnées
                    if(get_value(tab, i, j) == 0){
                        if(get_note(tab, i, j, note1) == 0 && get_note(tab, i, j, note2) == 0 && check_note(tab, i, j) == 2){
                            cpt++;
                        }
                    }
                }
            }
            if(cpt == 2){                                 //Fontion qui permet de savoir s'il dans notre tableau on a bien une paire
                for(int i=xmin; i<=xmax; i++){
                    for(int j=ymin; j<=ymax; j++){                      //Ici c'est pour les coordonnées
                        if(get_value(tab, i, j) == 0){
                            if(!(check_note(tab, i, j) == 2 && (get_note(tab, i, j, note1) == 0 && get_note(tab, i, j, note2) == 0))){       //Elémine les notes des autres case sans toucher au case qui contienne la paire nus
                                if(get_note(tab, i, j, note1) == 0 ){
                                    set_note(&tab, i, j, note1, 1);     //Modifie les notes
                                    printf("Regle : paires nus, Position : (%d, %d), Modif note : %d \n",i,j,note1+1);
                                    b = true;                           //Règle appliquer on passe notre bool à true
                                }
                                if(get_note(tab, i, j, note2) == 0 ){
                                    set_note(&tab, i, j, note2, 1);     //Modifie les notes
                                    printf("Regle : paires nus, Position : (%d, %d), Modif note : %d \n",i,j,note2+1);
                                    b = true;                           //Règle appliquer on passe notre bool à true
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return b;
}


/// Triplets nus
/// Cette fonction nous permet de savoir si la case donnée fait partie du triplet ou pas
bool verif_case_note(StructSudoku tab, int x, int y, int note1, int note2, int note3)
{
    bool res=false;
    for(int i=0; i<NB_LONGUEUR; i++){
        if(i != note1 && i != note2 && i != note3){
            if(get_note(tab, x, y, i) == 0){
                res = true;
            }
        }
    }
    return res;
}

bool triplets_nus(StructSudoku tab, int xmin, int xmax, int ymin, int ymax)
{
    bool b = false;                                                     //Ce bool nous retourne vrai ou faux si nous avons aplliquer la règle
    for(int note1=0; note1<NB_LONGUEUR; note1++){
        for(int note2=note1+1; note2<NB_LONGUEUR; note2++){             //Les 3 boucles servent pour les notes
            for(int note3=note2+1; note3<NB_LONGUEUR; note3++){
                int cpt_note1=0;
                int cpt_note2=0;                                            //Ces compteurs nous permets de savoir s'il on a bien trouver trois case qui forme le triplet nus
                int cpt_note3=0;
                for(int i=xmin; i<=xmax; i++){
                    for(int j=ymin; j<=ymax; j++){                          //Ici c'est pour les coordonnées
                        if(get_value(tab, i, j) == 0){
                            ///////////////////////////////////////////////////
                            if(get_note(tab, i, j, note1) == 0 && get_note(tab, i, j, note2) == 0 && get_note(tab, i, j, note3) == 0 && check_note(tab, i, j) == 3){
                                cpt_note1++;
                                cpt_note2++;
                                cpt_note3++;
                            }
                            /////////////////////////////////////////////////////           C'est "if" nous permette de trouver les notes et de modifier notre tableau en fonction ainsi que les compteurs de notes
                            if(get_note(tab, i, j, note1) == 0 && get_note(tab, i, j, note2) == 0 && check_note(tab, i, j) == 2){
                                cpt_note1++;
                                cpt_note2++;
                            }
                            ///////////////////////////////////////////////////
                            if(get_note(tab, i, j, note1) == 0 && get_note(tab, i, j, note3) == 0 && check_note(tab, i, j) == 2){
                                cpt_note1++;
                                cpt_note3++;
                            }
                            ///////////////////////////////////////////////////
                            if(get_note(tab, i, j, note2) == 0 && get_note(tab, i, j, note3) == 0 && check_note(tab, i, j) == 2){
                                cpt_note2++;
                                cpt_note3++;
                            }
                        }
                    }
                }
                if(cpt_note1 >= 2 && cpt_note2 >= 2 && cpt_note3 >= 2 && cpt_note1 <= 3 && cpt_note2 <= 3 && cpt_note3 <= 3){         //Fontion qui permet de savoir si dans notre tableau on a bien un triplet et regarde qu'on a bien trouver 3 cases qui le contient
                    for(int i=xmin; i<=xmax; i++){
                        for(int j=ymin; j<=ymax; j++){                      //Double for pour les coordonnées
                            if(get_value(tab, i, j) == 0){
                                if(verif_case_note(tab, i, j, note1, note2, note3)){
                                    if(get_note(tab, i, j, note1) == 0 ){
                                        set_note(&tab, i, j, note1, 1);     //Modifie les notes   
                                        printf("Regle : triplets nus, Position : (%d, %d), Modif note : %d \n",i,j,note1+1);
                                        b = true;                           //Règle appliquer on passe notre bool à true
                                    }
                                    if(get_note(tab, i, j, note2) == 0 ){
                                        set_note(&tab, i, j, note2, 1);     //Modifie les notes
                                        printf("Regle : triplets nus, Position : (%d, %d), Modif note : %d \n",i,j,note2+1);
                                        b = true;                           //Règle appliquer on passe notre bool à true
                                    }
                                    if(get_note(tab, i, j, note3) == 0 ){
                                        set_note(&tab, i, j, note3, 1);     //Modifie les notes
                                        printf("Regle : triplets nus, Position : (%d, %d), Modif note : %d \n",i,j,note3+1);
                                        b = true;                           //Règle appliquer on passe notre bool à true
                                    }
                                }
                            }
                        }
                    }
                    if(b){
                        return true;            //permet de mettre fin à la fonction dès qu'on a trouver et appliquer un triplet_nus
                    }
                }
            }
        }
    }
    return b;
}


/// /// /// /// K-uplet cachés /// /// /// /// ///
///Singleton cahcée
bool singleton_cache(StructSudoku tab, int xmin, int xmax, int ymin, int ymax)
{
    for(int note = 0; note<NB_LONGUEUR; note++){
        int cpt = 0;                                                //compteur pour savoir combien de fois la note apparait
        for(int i = xmin; i<=xmax; i++){
            for(int j = ymin; j<=ymax; j++){                        //boucle pour le déplacement
                if(get_value(tab, i, j) == 0){
                    if(get_note(tab, i, j, note) == 0){             //Condition pour savoir si la note est présente dans la case
                        cpt++;
                    }
                }

            }
        }
        if(cpt == 1){                                               //Condition pour savoir si on a bien trouver un singleton caché
            for(int i = xmin; i<=xmax; i++){
                for(int j = ymin; j<=ymax; j++){
                    if(get_value(tab, i, j) == 0){                  //boucle pour le déplacement
                        if(get_note(tab, i, j, note) == 0){
                            add_value(tab, i, j, note+1);           //Case trouvé on ajoute la valeur a la case
                            printf("Regle : singleton cache, Position : (%d, %d), Ajout valeur : %d \n",i,j,note+1);
                            return true;                            //on return vrai afin d'arreter la fonction
                        }
                    }
                }
            }
        }
    }
    return false;                                                   //Si on a pas trouvé de singleton on return faux
}

/// Cette fonction nous permet de savoir si on a notre paire ou triplet cache dans cette case
bool verif_case_note_cache(StructSudoku tab, int x, int y, int note1, int note2, int note3)
{
    bool res=false;
    for(int i=0; i<NB_LONGUEUR; i++){
        if(i == note1 || i == note2 || i == note3){
            if(get_note(tab, x, y, i) == 0){
                res = true;
            }
        }
    }
    return res;
}

///Fonction qui retrouve les cases contenants les paires ou triplets caché et enleve les notes en trop de celles-ci
bool suppr_note(StructSudoku tab, int xmin, int xmax, int ymin, int ymax, int note1, int note2, int note3)
{
    bool b = false;
    for(int i=xmin; i<=xmax; i++){
        for(int j=ymin; j<=ymax; j++){                      //Double for pour les coordonnées
            if(get_value(tab, i, j) == 0){
                if(verif_case_note_cache(tab, i, j, note1, note2, note3)){
                    b = note_update(&tab, i, j, note1, note2, note3);         //Modifie les notes et si modification faite retourne vrai
                }
            }
        }
    }
    return b;
}


///Paire cache
bool paires_cache(StructSudoku tab, int xmin, int xmax, int ymin, int ymax)
{
    bool b = false;                                                     //Ce bool nous retourne vrai ou faux si nous avons aplliquer la règle
    for(int note1=0; note1<NB_LONGUEUR; note1++){
        for(int note2=note1+1; note2<NB_LONGUEUR; note2++){             //Les 2 boucles servent pour les notes
           int cpt_note1 = 0;
           int cpt_note2 = 0;                                           //Compteur pour l'occurence des notes
           int cpt = 0;                                                 //Compteur pour savoir le nombre de fois que la paire est trouvé
            for(int i=xmin; i<=xmax; i++){
                for(int j=ymin; j<=ymax; j++){                          //Ici c'est pour les coordonnées
                    if(get_value(tab, i, j) == 0){
                        if(get_note(tab, i, j, note1) == 0){
                            cpt_note1++;
                        }
                        if(get_note(tab, i, j, note2) == 0){                                        //If pour les deux compteurs de notes
                            cpt_note2++;
                        }
                         if(get_note(tab, i, j, note1) == 0 && get_note(tab, i, j, note2) == 0){       //Condition pour savoir si notre paire est présente
                            cpt++;
                        }
                    }
                }
            }
            if(cpt_note1 == 2 && cpt_note2 == 2 && cpt == 2){                                 //Fontion qui permet de savoir s'il dans notre tableau on a bien une paire
                b = suppr_note(tab, xmin, xmax, ymin, ymax, note1, note2, -1);                //Appel cette fonction pour supprimer les notes car on a trouver une paire caché et le -1 sert pour ne pas faire planter la fonction avec une valeur qui ne sois pas dans les notes
            }
            if(b){
                return b;
            }
        }
    }
    return b;
}

///Triplet caché
bool triplets_cache(StructSudoku tab, int xmin, int xmax, int ymin, int ymax)
{
    bool b = false;                                                     //Ce bool nous retourne vrai ou faux si nous avons aplliquer la règle
    for(int note1=0; note1<NB_LONGUEUR; note1++){
        for(int note2=note1+1; note2<NB_LONGUEUR; note2++){             //Les 3 boucles servent pour les notes
            for(int note3=note2+1; note3<NB_LONGUEUR; note3++){
                int cpt_note1=0;
                int cpt_note2=0;                                            //Ces compteurs nous permets de savoir s'il on a bien trouver trois case qui forme le triplet nus
                int cpt_note3=0;
                int cpt_bis1=0;
                int cpt_bis2=0;                                             //Et ceux la pour compter lse occurences des 3 notes
                int cpt_bis3=0;
                for(int i=xmin; i<=xmax; i++){
                    for(int j=ymin; j<=ymax; j++){                          //Ici c'est pour les coordonnées
                        if(get_value(tab, i, j) == 0){
                            ///////////////////////////////////////////////////
                            if(get_note(tab, i, j, note1) == 0){
                                if(get_note(tab, i, j, note2) == 0){
                                    if(get_note(tab, i, j, note3) == 0){
                                        cpt_note1++;
                                        cpt_note2++;
                                        cpt_note3++;
                                    }
                                    else{                                       //C'est if nous permet de trouver une compo de triplet caché
                                        cpt_note1++;
                                        cpt_note2++;
                                    }
                                }
                                else if(get_note(tab, i, j, note3) == 0){
                                    cpt_note1++;
                                    cpt_note3++;
                                }
                            }
                            else if(get_note(tab, i, j, note2) == 0){
                                if(get_note(tab, i, j, note3) == 0){
                                    cpt_note2++;
                                    cpt_note3++;
                                }
                            }
                            ///////////////////////////////////////////////////
                            if(get_note(tab, i, j, note1) == 0){
                                cpt_bis1++;
                            }                                                   //Et ce là pour compter le nombre de fois que les notes apparaissent
                            ///////////////////////////////////////////////////
                            if(get_note(tab, i, j, note2) == 0){
                                cpt_bis2++;
                            }
                            ///////////////////////////////////////////////////
                            if(get_note(tab, i, j, note3) == 0){
                                cpt_bis3++;
                            }
                        }
                    }
                }

                if(cpt_note1 >= 2 && cpt_note2 >= 2 && cpt_note3 >= 2 && cpt_note1 <= 3 && cpt_note2 <= 3 && cpt_note3 <= 3
                   && cpt_bis1 == cpt_note1 && cpt_bis2 == cpt_note2 && cpt_bis3 == cpt_note3){      //Fontion qui permet de savoir si dans notre tableau on a bien un triplet et regarde qu'on a bien trouver 3 cases qui le contient

                    b = suppr_note(tab, xmin, xmax, ymin, ymax, note1, note2, note3);                //Appel cette fonction pour supprimer les notes car on a trouver un triplet caché

                    if(b){
                        return true;            //permet de mettre fin à la fonction dès qu'on a trouver et appliquer un triplet_nus
                    }
                }
            }
        }
    }
    return b;
}



/// /// /// /// LE MAIN /// /// /// ///
void afficherMenu()
{
    printf("\n\nMenu :\n");
    printf("1. Derniere case libre\n");
    printf("2. Derniere case restante\n");
    printf("3. Dernier nombre possible\n");
    printf("4. k-uplets nus\n");
    printf("5. k-uplets cache\n");
    printf("6. Resolution automatique d'un sudoku\n");
    printf("7. Pointant\n");
    printf("8. X-wing ligne\n");
    printf("9. Fin\n");
    printf("Choisissez une option (1-9): ");
}

///Fonction qui nous permet d'afficher les notes
void affiche_tab_note(StructSudoku tab, int xmin, int xmax, int ymin, int ymax)
{
    printf("\n");
    for(int i = xmin; i <= xmax; i++) {
        for(int j = ymin; j <= ymax; j++) {
                int *note = get_tab_note(tab, i, j);
                printf("\n(%d, %d) : [", i, j);
                for(int z = 0; z < NB_LONGUEUR; z++) {
                    printf("%d ", note[z]);
                }
                printf("]");
            
        }
    }
    printf("\n");
}



///Vérifie s'il reste de case vide dans le Sudoku
bool findEmptyCell(StructSudoku tab)
{
    for (int x = 0; x < NB_LONGUEUR; x++) {
        for (int y = 0; y < NB_LONGUEUR; y++) {
            if (get_value(tab, x, y) == 0)
                return true;
        }
    }
    return false;  // Aucune cellule vide trouvée
}


///Complète la grille avec un appel des fonctions en boucles
void applyRules(StructSudoku tab)
{
    int compter_regle = 1;
    bool colonne = false;
    bool ligne = false;
    bool carre1 = false;
    bool carre2 = false;
    bool carre3 = false;

    while(findEmptyCell(tab)){
        if(compter_regle == 6){
            break;
        }
        for(int i=0; i<NB_LONGUEUR; i++){
            if(compter_regle == 1){
                ligne = singleton_nus(tab, i, i, 0, NB_LONGUEUR-1);
                colonne = singleton_nus(tab, 0, NB_LONGUEUR-1, i, i);
                if(i%NB_CARRE == 0){
                    carre1 = singleton_nus(tab, i, NB_CARRE-1, 0, NB_CARRE-1);
                    carre2 = singleton_nus(tab, i, NB_CARRE-1, NB_CARRE, NB_CARRE+2);
                    carre3 = singleton_nus(tab, i, NB_CARRE-1, NB_CARRE*2, NB_CARRE*2-1);
                }
            }
            if(compter_regle == 2){
                ligne = paires_nus(tab, i, i, 0, NB_LONGUEUR-1);
                colonne = paires_nus(tab, 0, NB_LONGUEUR-1, i, i);
                if(i%NB_CARRE == 0){
                    carre1 = paires_nus(tab, i, NB_CARRE-1, 0, NB_CARRE-1);
                    carre2 = paires_nus(tab, i, NB_CARRE-1, NB_CARRE, NB_CARRE+2);
                    carre3 = paires_nus(tab, i, NB_CARRE-1, NB_CARRE*2, NB_CARRE*2-1);
                }
            }
            if(compter_regle == 3){
                ligne = triplets_nus(tab, i, i, 0, NB_LONGUEUR-1);
                colonne = triplets_nus(tab, 0, NB_LONGUEUR-1, i, i);
                if(i%NB_CARRE == 0){
                    carre1 = triplets_nus(tab, i, NB_CARRE-1, 0, NB_CARRE-1);
                    carre2 = triplets_nus(tab, i, NB_CARRE-1, NB_CARRE, NB_CARRE+2);
                    carre3 = triplets_nus(tab, i, NB_CARRE-1, NB_CARRE*2, NB_CARRE*2-1);
                }
            }
            if(compter_regle == 4){
                ligne = singleton_cache(tab, i, i, 0, NB_LONGUEUR-1);
                colonne = singleton_cache(tab, 0, NB_LONGUEUR-1, i, i);
                if(i%NB_CARRE == 0){
                    carre1 = singleton_cache(tab, i, NB_CARRE-1, 0, NB_CARRE-1);
                    carre2 = singleton_cache(tab, i, NB_CARRE-1, NB_CARRE, NB_CARRE+2);
                    carre3 = singleton_cache(tab, i, NB_CARRE-1, NB_CARRE*2, NB_CARRE*2-1);
                }
            }
            if(compter_regle == 5){
                ligne = paires_cache(tab, i, i, 0, NB_LONGUEUR-1);
                colonne = paires_cache(tab, 0, NB_LONGUEUR-1, i, i);
                if(i%NB_CARRE == 0){
                    carre1 = paires_cache(tab, i, NB_CARRE-1, 0, NB_CARRE-1);
                    carre2 = paires_cache(tab, i, NB_CARRE-1, NB_CARRE, NB_CARRE+2);
                    carre3 = paires_cache(tab, i, NB_CARRE-1, NB_CARRE*2, NB_CARRE*2-1);
                }
            }
            if(compter_regle == 6){
                ligne = triplets_cache(tab, i, i, 0, NB_LONGUEUR-1);
                colonne = triplets_cache(tab, 0, NB_LONGUEUR-1, i, i);
                if(i%NB_CARRE == 0){
                    carre1 = triplets_cache(tab, i, NB_CARRE-1, 0, NB_CARRE-1);
                    carre2 = triplets_cache(tab, i, NB_CARRE-1, NB_CARRE, NB_CARRE+2);
                    carre3 = triplets_cache(tab, i, NB_CARRE-1, NB_CARRE*2, NB_CARRE*2-1);
                }
            }

            if(colonne || ligne || carre1 || carre2 || carre3){
                compter_regle=1;
                break;
            }

            if(i == NB_LONGUEUR-1){
                compter_regle++;
            }
        }
    }
}

/// pointante
bool pointante(StructSudoku tab){
    for(int zonei=0; zonei < NB_LONGUEUR; zonei = zonei+3) {                            //Zonei 
        for(int zonej=0; zonej < NB_LONGUEUR; zonej = zonej+3) {                        //Zonej Pour obtenir les 9 zones carrées du Sudoku
            for(int x=0; x < NB_LONGUEUR; x++) {                                        //Pour x de 0 à 8
                for(int ligne_colonne=0; ligne_colonne < NB_CARRE; ligne_colonne++) {   //Pour les 3 lignes colonnes intersectant la zone carrée courante
                    int cptl = 0;                                                       //Compteur pour les lignes 
                    int cptc = 0;                                                       //Compteur pour les colonnes
                    for (int c=0; c < NB_CARRE; c++) {                                  //Pour les 3 cases c d'intersection (exemple : (0,0) (0,1) (0,2) ligne et (0,0) (1,0) (2,0) colonne)
                        if (get_note(tab,ligne_colonne+zonei,c+zonej,x) == 0)           //Verifie si la case c contient x en ligne alors cptl++
                            cptl++;
                        if (get_note(tab,c+zonei,ligne_colonne+zonej,x) == 0)           //Verifie si la case c contient x en colonne alors cptc++
                            cptc++;
                    }
                    bool pointe = true;                                                 
                    bool boxl = true;
                    bool boxc = true;
                    bool colon = false;
                    bool ligne = false;

                    //********LIGNE********
                    if (cptl>=2) {
                        if (zonej == 0) {                                               //Si zonej==0 alors on doit parcourir la ligne de 
                            for (int y=3; y<NB_LONGUEUR; y++) {                         //3 à 8
                                if (get_note(tab,zonei+ligne_colonne,y,x) == 0)         //Verifie si la case contient x alors boxl=false 
                                    boxl = false;                                       //Signifie que sur la ligne il y a une autre note donc les notes ne peuvent
                            }                                                           //pas etre elimine de la zone carre
                        } 
                        if (zonej == 3){                                                //Si zonej==3 on doit parcourir la ligne de
                            for (int y=0; y<NB_CARRE; y++) {                            //0 à 2
                                if (get_note(tab,zonei+ligne_colonne,y,x) == 0)         //Idem zonej==0
                                    boxl = false;
                            }
                            for (int y=NB_CARRE*2; y<NB_LONGUEUR; y++) {                //6 à 8
                                if (get_note(tab,zonei+ligne_colonne,y,x) == 0)         //Idem zonej==0
                                    boxl = false;
                            }
                        }
                        if (zonej == 6){                                                //Si zonej==6 on doit parcourir la ligne de
                            for (int y=0; y<NB_LONGUEUR-NB_CARRE; y++) {                //0 à 5
                                if (get_note(tab,zonei+ligne_colonne,y,x) == 0)         //Idem zonej==0
                                    boxl = false;
                            }
                        }
                        
                        //***CARRE LIGNE***
                        if (ligne_colonne ==  0) {                                      //Si ligne_colonne==0 on doit parcourir le carre en
                            for(int i=zonei+1; i < zonei+NB_CARRE; i++) {               //i de zonei+1 à zonei+3
                                for (int j=zonej; j < zonej+NB_CARRE; j++) {            //j de zonej à zonej+3        (exemple : zonei=0 et zonej=0 alors (0,1) (1,1) (2,1) (0,2) (1,2) (2,2))
                                    if (get_note(tab,i,j,x) == 0 ){                     //Verifie si la case contient x alors pointe=false
                                        pointe = false;                                 //Signifie que dans le carre il y a une autre note donc les notes ne peuvent 
                                    }                                                   //pas etre elimine de la ligne
                                }
                            }
                            if (pointe == true){
                                ligne = true;                                           //Utile en fin de code pour savoir qu'on doit elimine les notes de la ligne
                            }
                        } 
                        if (ligne_colonne ==  1) {                                      //Si la ligne_colonne==1 on doit parcourir le carre en
                            for (int j=zonej; j < zonej+NB_CARRE; j++) {                //j de zonej à zonej+3
                                if (get_note(tab,zonei,j,x) == 0 ){                     //i = zonei
                                    pointe = false;                                     //Idem ligne_colonne==0
                                }
                            }
                            for (int j=zonej; j < zonej+NB_CARRE; j++) {                //j de zonej à zonej+3
                                if (get_note(tab,zonei+2,j,x) == 0 ){                   //i = zonei+2               
                                    pointe = false;                                     //Idem ligne_colonne==0
                                }
                            }
                            if (pointe == true){                                        //Idem ligne_colonne==0
                                ligne = true;
                            }
                        } 
                        if (ligne_colonne ==  2) {                                      //Si la ligne_colonne==2 on doit parcourir le carre en
                            for(int i=zonei; i < zonei+NB_CARRE-1; i++) {               //i de zonei à zonei+2
                                for (int j=zonej; j < zonej+NB_CARRE; j++) {            //j de zonej à zonej+3
                                    if (get_note(tab,i,j,x) == 0 ){                     //Idem ligne_colonne==0
                                        pointe = false;
                                    }
                                }
                            }
                            if (pointe == true){                                        //Idem ligne_colonne==0
                                ligne = true;
                            }
                        }
                    }
                    else
                        boxl = false;                                                   //Sinon cptl<2 alors pas une pointante

                    //********COLONNE********
                    if (cptc>=2) {
                        if (zonei == 0) {                                               //Si zonei==0 alors on doit parcourir la colonne de
                            for (int y=3; y<NB_LONGUEUR; y++) {                         //3 à 8
                                if (get_note(tab,y,zonej+ligne_colonne,x) == 0)         //Verifie si la case contient x alors boxc=false
                                    boxc = false;                                       //Signifie que sur la ligne il y a une autre note donc les notes ne peuvent
                            }                                                           //pas etre elimine de la zone carre
                        } 
                        if (zonei == 3){                                                //Si zonej==3 on doit parcourir la colonne de
                           for (int y=0; y<NB_CARRE; y++) {                             //0 à 2
                                if (get_note(tab,y,zonej+ligne_colonne,x) == 0)         //Idem zonej==0
                                    boxc = false;
                            }
                            for (int y=NB_CARRE*2; y<NB_LONGUEUR; y++) {                
                                if (get_note(tab,y,zonej+ligne_colonne,x) == 0)         //6 à 8
                                    boxc = false;                                       //Idem zonej==0
                            }
                        }
                        if (zonei == 6){                                                //Si zonej==6 on doit parcourir la colonne de
                            for (int y=0; y<NB_LONGUEUR-NB_CARRE; y++) {                //0 à 5
                                if (get_note(tab,y,zonej+ligne_colonne,x) == 0)         //Idem zonej==0
                                    boxc = false;
                            }
                        }


                        if (ligne_colonne == 0) {                                       //Si ligne_colonne==0 on doit parcourir le carre en 
                            for(int i=zonei; i < zonei+NB_CARRE; i++) {                 //i de zonei à zonei+NB_CARRE 
                                for (int j=zonej+1; j < zonej+NB_CARRE; j++) {          //j de zonej+1 à zonej+NB_CARRE
                                    if (get_note(tab,i,j,x) == 0)                       //Verifie si la case contient x alors pointe = false 
                                        pointe = false;                                 //Signifie que dans le carre il y a une autre note donc les notes ne peuvent 
                                }                                                       //pas etre elimine de la colonne
                            }
                            if (pointe == true){
                                colon = true;                                           //Utile en fin de code pour savoir qu'on doit elimine les notes de la colonne 
                            }
                        } 
                        if (ligne_colonne == 1){                                        //Si ligne_colonne==1 on doit parcourir le carre en  
                            for(int i=zonei; i < zonei+NB_CARRE; i++) {                 //i de zonei à zonei+NB_CARRE
                                if (get_note(tab,i,zonej,x) == 0)                       //j = zonej
                                    pointe = false;                                     //Idem ligne_colonne==0
                            }
                            for(int i=zonei; i < zonei+NB_CARRE; i++) {                 //i de zonei à zonei+NB_CARRE
                                 if (get_note(tab,i,zonej+2,x) == 0)                    //j = zonej+2
                                    pointe = false;                                     //Idem ligne_colonne==0
                            }
                            if (pointe == true){
                                colon = true;                                           //Idem ligne_colonne==0
                            }
                        }
                        if (ligne_colonne == 2){                                        //Si ligne_colonne==1 on doit parcourir le carre en
                            for(int i=zonei; i < zonei+NB_CARRE; i++) {                 //i de zonei à zonei+NB_CARRE
                                for (int j=zonej; j < zonej+NB_CARRE-1; j++) {          //j de zonej à zonej+NB_CARRE-1
                                    if (get_note(tab,i,j,x) == 0)
                                        pointe = false;                                 //Idem ligne_colonne==0
                                }
                            }
                            if (pointe == true){
                                colon = true;                                           //Idem ligne_colonne==0
                            }
                        }     
                    } 
                    else
                        boxc = false;                                                   //Sinon cptc<2 alors pas une pointante

                    if (pointe) {                                                       //Si pointe==true alors on peut elimine les notes de la ligne ou de la colonne avec le meme code que ci-dessus
                        if(ligne) {                                                     //Modifie la ligne
                            if (zonej == 0) {
                                for (int y=3; y<NB_LONGUEUR; y++) {                     //j de 3 à 8 et i = zonei+ligne_colonne
                                    set_note(&tab,zonei+ligne_colonne,y,x,1);           //modifie la note des coordonne i j de la note x
                                    printf("Regle : pointante, Position : (%d, %d), Modif note : %d \n",zonei+ligne_colonne,y,x);
                                } 
                            }
                            if (zonej == 3){
                                for (int y=0; y<NB_CARRE; y++) {                        //j de 0 à 2 et de 6 à 8 et i = zoni+ligne_colonne
                                    set_note(&tab,zonei+ligne_colonne,y,x,1);
                                    printf("Regle : pointante, Position : (%d, %d), Modif note : %d \n",zonei+ligne_colonne,y,x);
                                }
                                for (int y=NB_CARRE*2; y<NB_LONGUEUR; y++) {
                                    set_note(&tab,zonei+ligne_colonne,y,x,1);
                                    printf("Regle : pointante, Position : (%d, %d), Modif note : %d \n",zonei+ligne_colonne,y,x);
                                }
                            }      
                            if (zonej == 6){
                                for (int y=0; y<NB_LONGUEUR-NB_CARRE; y++) {            //j de 0 à 5 et i = zonei+ligne_colonne
                                    set_note(&tab,zonei+ligne_colonne,y,x,1);
                                    printf("Regle : pointante, Position : (%d, %d), Modif note : %d \n",zonei+ligne_colonne,y,x);
                                }
                            }
                        }
                        if(colon) {                                                     //Modifie la colonne
                            if (zonei == 0) {
                                for (int y=3; y<NB_LONGUEUR; y++) {                     //i de 3 à 8 et j = zonej+ligne_colonne
                                    set_note(&tab,y,zonej+ligne_colonne,x,1);
                                    printf("Regle : pointante, Position : (%d, %d), Modif note : %d \n",y,zonej+ligne_colonne,x);
                                    return true;
                                }
                            } 
                            if (zonei == 3){
                                for (int y=0; y<NB_CARRE; y++) {                        //i de 0 à 2 et de 6 à 8 et j = zonej+ligne_colonne
                                    set_note(&tab,y,zonej+ligne_colonne,x,1);
                                    printf("Regle : pointante, Position : (%d, %d), Modif note : %d \n",y,zonej+ligne_colonne,x);
                                }
                                for (int y=NB_CARRE*2; y<NB_LONGUEUR; y++) {
                                    set_note(&tab,y,zonej+ligne_colonne,x,1);
                                    printf("Regle : pointante, Position : (%d, %d), Modif note : %d \n",y,zonej+ligne_colonne,x);
                                }
                            }
                            if (zonei == 6){
                                for (int y=0; y<NB_LONGUEUR-NB_CARRE; y++) {            //i de 0 à 5 et j = zonej+ligne_colonne
                                    set_note(&tab,y,zonej+ligne_colonne,x,1);
                                    printf("Regle : pointante, Position : (%d, %d), Modif note : %d \n",y,zonej+ligne_colonne,x);
                                }
                            }
            
                        }
                    }
                    if (boxl){
                        if (ligne_colonne ==  0) {                                      //Si ligne_colonne==0 on doit parcourir le carre en
                            for(int i=zonei+1; i < zonei+NB_CARRE; i++) {               //i de zonei+1 à zonei+3
                                for (int j=zonej; j < zonej+NB_CARRE; j++) {            //j de zonej à zonej+3        (exemple : zonei=0 et zonej=0 alors (0,1) (1,1) (2,1) (0,2) (1,2) (2,2))
                                    set_note(&tab,i,j,x,1);
                                    printf("Regle : pointante, Position : (%d, %d), Modif note : %d \n",i,j,x);
                                }
                            }
                        } 
                        if (ligne_colonne ==  1) {                                      //Si la ligne_colonne==1 on doit parcourir le carre en
                            for (int j=zonej; j < zonej+NB_CARRE; j++) {                //j de zonej à zonej+3
                                set_note(&tab,zonei,j,x,1);
                                printf("Regle : pointante, Position : (%d, %d), Modif note : %d \n",zonei,j,x);
                            }
                            for (int j=zonej; j < zonej+NB_CARRE; j++) {                //j de zonej à zonej+3
                                set_note(&tab,zonei+2,j,x,1);
                                printf("Regle : pointante, Position : (%d, %d), Modif note : %d \n",zonei+2,j,x);
                            }
                        } 
                        if (ligne_colonne ==  2) {                                      //Si la ligne_colonne==2 on doit parcourir le carre en
                            for(int i=zonei; i < zonei+NB_CARRE-1; i++) {               //i de zonei à zonei+2
                                for (int j=zonej; j < zonej+NB_CARRE; j++) {            //j de zonej à zonej+3
                                    set_note(&tab,i,j,x,1);
                                    printf("Regle : pointante, Position : (%d, %d), Modif note : %d \n",i,j,x);
                                }
                            }
                        }
                    }
                    if (boxc){
                        if (ligne_colonne == 0) {                                       //Si ligne_colonne==0 on doit parcourir le carre en 
                            for(int i=zonei; i < zonei+NB_CARRE; i++) {                 //i de zonei à zonei+NB_CARRE 
                                for (int j=zonej+1; j < zonej+NB_CARRE; j++) {          //j de zonej+1 à zonej+NB_CARRE
                                    set_note(&tab,i,j,x,1);        
                                    printf("Regle : pointante, Position : (%d, %d), Modif note : %d \n",i,j,x);                       
                                }                                                     
                            }
                        } 
                        if (ligne_colonne == 1){                                        //Si ligne_colonne==1 on doit parcourir le carre en  
                            for(int i=zonei; i < zonei+NB_CARRE; i++) {                 //i de zonei à zonei+NB_CARRE
                                set_note(&tab,i,zonej,x,1);
                                printf("Regle : pointante, Position : (%d, %d), Modif note : %d \n",i,zonej,x);
                            }
                            for(int i=zonei; i < zonei+NB_CARRE; i++) {                 //i de zonei à zonei+NB_CARRE
                                 set_note(&tab,i,zonej+2,x,1);     
                                 printf("Regle : pointante, Position : (%d, %d), Modif note : %d \n",i,zonej+2,x);            
                            }
                        }
                        if (ligne_colonne == 2){                                        //Si ligne_colonne==1 on doit parcourir le carre en
                            for(int i=zonei; i < zonei+NB_CARRE; i++) {                 //i de zonei à zonei+NB_CARRE
                                for (int j=zonej; j < zonej+NB_CARRE-1; j++) {          //j de zonej à zonej+NB_CARRE-1
                                    set_note(&tab,i,j,x,1);
                                    printf("Regle : pointante, Position : (%d, %d), Modif note : %d \n",i,j,x);
                                }
                            }  
                        }
                    }
                    if (pointe || boxl || boxc){
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

//Regle X-Wing
bool X_wing(StructSudoku tab){
    int i1;
    int i2;
    int x1; 
    int x2;
    int counterligne = 0;
    
    int y1;
    int y2;
    int j1;
    int j2;
    int countercolonne = 0;

    bool modifc, modifl;
    
    for(int c=0; c < NB_LONGUEUR; c++){    
        counterligne = 0;
        for(int i=0; i < NB_LONGUEUR; i++){
            if(counterligne==2){
                if( (get_note(tab,i,x1,c)==0) && (get_note(tab,i,x2,c)==0) && (nb_note_ligne(tab,i,c)==2)){
                    i2 = i;
                    for(int x=0; x<NB_LONGUEUR; x++){
                        if (x != i1) {
                            if (x != i2){
                                set_note(&tab,x,x1,c,1);
                                set_note(&tab,x,x2,c,1);
                                printf("Regle : x wing, Position : (%d, %d), Modif note : %d \n",x,x1,c);
                                printf("Regle : x wing, Position : (%d, %d), Modif note : %d \n",x,x2,c);
                                modifl = true;
                            }
                        }
                    }
                    i = NB_LONGUEUR;
                }
                if(i == NB_LONGUEUR-1){
                    counterligne = 0;
                    i = i1;
                }
            }
            else if (nb_note_ligne(tab,i,c) == 2){
                for(int j=0; j < NB_LONGUEUR; j++){
                    if (get_note(tab,i,j,c) == 0){
                        if(counterligne == 0){
                            counterligne++;
                            x1=j;
                        }
                        else if(counterligne == 1){
                            counterligne++;
                            x2=j;
                            j = NB_LONGUEUR;
                            i1 = i;
                        }
                    }
                }
            }
        }
        countercolonne = 0;
        for(int i=0; i < NB_LONGUEUR; i++){
            if(countercolonne==2){
                if( (get_note(tab,y1,i,c)==0) && (get_note(tab,y2,i,c)==0) && (nb_note_colonne(tab,i,c)==2)){
                    j2 = i;
                    for(int y=0; y<NB_LONGUEUR; y++){
                        if (y != j1) {
                            if (y != j2){
                                set_note(&tab,y1,y,c,1);
                                set_note(&tab,y2,y,c,1);
                                printf("Regle : x wing, Position : (%d, %d), Modif note : %d \n",y1,y,c);
                                printf("Regle : x wing, Position : (%d, %d), Modif note : %d \n",y2,y,c);
                                modifc = true;
                            }
                        }
                    }
                    i = NB_LONGUEUR;
                }
                if(i == NB_LONGUEUR-1){
                    countercolonne = 0;
                    i = j1;
                }
            }
            else if (nb_note_colonne(tab,i,c) == 2){
                for(int j=0; j < NB_LONGUEUR; j++){
                    if (get_note(tab,j,i,c) == 0){
                        if(countercolonne == 0){
                            countercolonne++;
                            y1=j;
                        }
                        else if(countercolonne == 1){
                            countercolonne++;
                            y2=j;
                            j = NB_LONGUEUR;
                            j1 = i;
                        }
                    }
                }
            }
        }
    }
    if (modifc || modifl )
        return true;
    return false;
}

/// Backtracking
bool Backtracking(StructSudoku sudoku, int x, int y) {
    if (x == NB_LONGUEUR && y == 0) {                                    // Vérifie si on a atteint la fin de la grille
        return true;                                                     // La grille est fini
    }
    if (get_value(sudoku, x, y) != 0) {                                  // Passe à la prochaine case si la case actuelle est déjà remplie
        if (y == NB_LONGUEUR-1) {                                        // Si nous sommes à la dernière colonne on passe à la ligne suivante
            return Backtracking(sudoku, x + 1, 0);
        } else {
            return Backtracking(sudoku, x, y + 1);
        }
    }
    for (int valeur = 1; valeur <= NB_LONGUEUR; valeur++) {              //Essaye de placer les valeurs de 1 à 9 dans la case
        if (sudoku_valid(sudoku)) {
            add_value(sudoku, x, y, valeur);
            if (Backtracking(sudoku, x, y) && sudoku_valid(sudoku)) {    // Si la grille est résolue, retourner true
                return true;
            }
            rem_value(sudoku, x, y);                                     // Si la solution échoue, retirer la valeur de la cellule
        }
    }
    return false;                                                        // Aucune solution trouvée pour cette configuration
}