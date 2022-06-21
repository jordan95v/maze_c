#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <curses.h>

void mazeGen(char maze[21][21], char traversed[21][21]);
void recur(char maze[21][21], char traversed[21][21], int xpos, int ypos);
void mazeTrancho();

// Création du menu
int menu()
{
    printf("===================== Trancho's Maze =====================\n");
    printf("-1 Play \n-2 Leave\n\n");
    printf("Enter your choice: ");
    int choice = 0;
    scanf("%d", &choice);
    return (choice);
}

// Menu pour restart
int restart()
{
    printf("\n\n===================== Trancho's Maze =====================\n");
    printf("Do you want restart ?\n");
    printf("-1 Yes \n-2 Leave\n\n");
    printf("Enter your choice: ");
    int choice = 0;
    scanf("%d", &choice);
    return (choice);
}

// Vérifie que l'endroit du labyrinthe est valide pour un déplacement
int is_valid(int x, int y, int hauteur, int largeur, char grille[hauteur][largeur])
{
    if (grille[y][x] != '#')
    {
        return 1;
    }
    return 0;
}

// Vérifie si nous avons résolu le labyrinthe
int is_finish(int x, int y, int hauteur, int largeur, char grille[hauteur][largeur])
{
    if (grille[y][x] == '.')
    {
        return 1;
    }
    return 0;
}

// Fonction principale
int main()
{
    int choice = 0;
    choice = menu();
    switch (choice)
    {
    case 1:
        mazeTrancho();
        break;
    case 2:
        exit(EXIT_SUCCESS);
        break;
    default:
        printf("Invalid choice");
        main();
        break;
    }
}

// Fonction qui affiche le labyrinthe
void mazeTrancho()
{
    // Mémorise le labyrinthe
    char maze[21][21] = {
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', 'O', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}};

    // garde la trace des zones qui ont déjà été traversées et/ou qui ne seront jamais traversées.
    char traversed[21][21] =
        {{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
         {'#', 'O', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', '#'},
         {'#', 't', '#', 't', '#', 't', '#', 't', '#', 't', '#', 't', '#', 't', '#', 't', '#', 't', '#', 't', '#'},
         {'#', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', '#'},
         {'#', 't', '#', 't', '#', 't', '#', 't', '#', 't', '#', 't', '#', 't', '#', 't', '#', 't', '#', 't', '#'},
         {'#', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', '#'},
         {'#', 't', '#', 't', '#', 't', '#', 't', '#', 't', '#', 't', '#', 't', '#', 't', '#', 't', '#', 't', '#'},
         {'#', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', '#'},
         {'#', 't', '#', 't', '#', 't', '#', 't', '#', 't', '#', 't', '#', 't', '#', 't', '#', 't', '#', 't', '#'},
         {'#', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', '#'},
         {'#', 't', '#', 't', '#', 't', '#', 't', '#', 't', '#', 't', '#', 't', '#', 't', '#', 't', '#', 't', '#'},
         {'#', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', '#'},
         {'#', 't', '#', 't', '#', 't', '#', 't', '#', 't', '#', 't', '#', 't', '#', 't', '#', 't', '#', 't', '#'},
         {'#', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', '#'},
         {'#', 't', '#', 't', '#', 't', '#', 't', '#', 't', '#', 't', '#', 't', '#', 't', '#', 't', '#', 't', '#'},
         {'#', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', '#'},
         {'#', 't', '#', 't', '#', 't', '#', 't', '#', 't', '#', 't', '#', 't', '#', 't', '#', 't', '#', 't', '#'},
         {'#', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', '#'},
         {'#', 't', '#', 't', '#', 't', '#', 't', '#', 't', '#', 't', '#', 't', '#', 't', '#', 't', '#', 't', '#'},
         {'#', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', '#'},
         {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}};
    mazeGen(maze, traversed);

    initscr();
    noecho();
    cbreak();
    int x = 1;
    int y = 1;
    int move_x, move_y;

    do
    {
        clear();
        for (int i = 0; i < 21; ++i)
        {
            for (int j = 0; j < 21; j++)
            {
                mvprintw(i, j, "%c", maze[i][j]);
            }
        }
        mvprintw(y, x, "@");
        mvprintw(y, x, "");
        refresh();
        move_x = x;
        move_y = y;
        switch (getch())
        {
        case 'z':
            move_y = y - 1;
            break;
        case 's':
            move_y = y + 1;
            break;
        case 'q':
            move_x = x - 1;
            break;
        case 'd':
            move_x = x + 1;
            break;
        }
        if (is_valid(move_x, move_y, 21, 21, maze))
        {
            x = move_x;
            y = move_y;
        }
    } while (!is_finish(x, y, 21, 21, maze));
    refresh();
    clrtoeol();
    refresh();
    endwin();
    switch (restart())
    {
    case 1:
        mazeTrancho();
        break;
    case 2:
        exit(EXIT_SUCCESS);
        break;
    default:
        printf("Invalid choice");
        main();
        break;
    }
}
// Algorithme de Prim
// ajouter o à 1,1
// répéter jusqu'à ce qu'il soit reched 10,10
// Regardez autour de l'objet.
// Choisis un point au hasard
// Si le mur peut être sculpté dans les limites et que le point n'a pas déjà été traversé.
// creuser le mur
// Sinon
// chercher un nouveau mur
// ajouter 10,10

void mazeGen(char maze[21][21], char traversed[21][21])
{
    srand(time(NULL));
    int xpos = 1;
    int ypos = 1;
    // Fixe la première cellule au marqueur indiquant un point de départ.
    maze[xpos][ypos] = '@';
    // Appelle la fonction de récursion pour générer le labyrinthe.
    recur(maze, traversed, xpos, ypos);
    // Une fois la fonction de récursion terminée, marque la destination
    maze[19][19] = '.';
    // Imprime le labyrinthe terminé
    for (int n = 0; n < 21; n++)
    {
        for (int k = 0; k < 21; k++)
        {
            printf("%c", maze[n][k]);
        }
        printf("%c", '\n');
    }
}
void recur(char maze[21][21], char traversed[21][21], int xpos, int ypos)
{
    // Génère un nombre aléatoire compris entre 0 et 3 inclus.
    int randomnumber = rand() % 4;
    // Cette boucle s'exécute tant qu'il y a des espaces vides autour des coordonnées dans ledit emplacement.
    while (traversed[xpos - 1][ypos - 1] == 't' || traversed[xpos][ypos - 1] == 't' ||
           traversed[xpos + 1][ypos - 1] == 't' || traversed[xpos - 1][ypos] == 't' || traversed[xpos][ypos] == 't' ||
           traversed[xpos + 1][ypos] == 't' || traversed[xpos - 1][ypos + 1] == 't' || traversed[xpos][ypos + 1] == 't' || traversed[xpos + 1][ypos + 1] == 't')
    {
        // Détermine une direction aléatoire dans laquelle dessiner le chemin (soit vers le haut, le bas, la gauche ou la droite).
        randomnumber = rand() % 4;
        // Si le nombre aléatoire est égal à zéro, essayez de dessiner un chemin à gauche.
        if (randomnumber == 0)
        {
            if ((xpos > 1) && (traversed[xpos - 2][ypos] == 't'))
            {
                // Prendre la position x par rapport au mur
                xpos--;
                // Démolir le mur et le marquer comme visité.
                maze[xpos][ypos] = ' ';
                // Appelle la fonction de récursion pour la cellule suivante.
                traversed[xpos][ypos] = ' ';
                // Définir les coordonnées de l'intérieur de la cellule suivante
                xpos--;
                // Marquer la cellule comme visitée et comme chemin car le mur est certain d'être vide.
                traversed[xpos][ypos] = ' ';
                // Appelle cette fonction (récursion) pour la cellule suivante.
                recur(maze, traversed, xpos, ypos);
                // Réinitialise toute modification apportée à la valeur ypos dans les instructions précédentes de cette instruction if afin que la boucle puisse continuer à vérifier la même cellule jusqu'à ce que toutes les zones environnantes soient pleines.
                xpos += 2;
            }
            // Si le tracé du chemin crée une boucle (selon l'algorithme de Prim), laissez le mur et marquez la zone comme traversée.
            else if (traversed[xpos - 2][ypos] != 't')
            {
                traversed[xpos - 1][ypos] = '#';
            }
        }
        // Si le nombre aléatoire est égal à un, essayez de dessiner le chemin à droite.
        else if (randomnumber == 1)
        {
            if ((xpos < 19) && (traversed[xpos + 2][ypos] == 't'))
            {

                xpos++;
                maze[xpos][ypos] = ' ';
                traversed[xpos][ypos] = ' ';
                xpos++;
                traversed[xpos][ypos] = ' ';
                recur(maze, traversed, xpos, ypos);
                xpos -= 2;
            }
            else if (traversed[xpos + 2][ypos] != 't')
            {
                traversed[xpos + 1][ypos] = '#';
            }
        }
        else if (randomnumber == 2)
        {
            if ((ypos > 1) && (traversed[xpos][ypos - 2] == 't'))
            {
                ypos--;
                maze[xpos][ypos] = ' ';
                traversed[xpos][ypos] = ' ';
                ypos--;
                traversed[xpos][ypos] = ' ';
                recur(maze, traversed, xpos, ypos);
                ypos += 2;
            }
            else if (traversed[xpos][ypos - 2] != 't')
            {
                traversed[xpos][ypos - 1] = '#';
            }
        }
        else
        {
            if ((ypos < 19) && (traversed[xpos][ypos + 2] == 't'))
            {
                ypos++;
                maze[xpos][ypos] = ' ';
                traversed[xpos][ypos] = ' ';
                ypos++;
                traversed[xpos][ypos] = ' ';
                recur(maze, traversed, xpos, ypos);
                ypos -= 2;
            }
            // Si le tracé du chemin crée une boucle (selon l'algorithme de Prim), laissez le mur et marquez la zone comme traversée.
            else if (traversed[xpos][ypos + 2] != 't')
            {

                traversed[xpos][ypos + 1] = '#';
            }
        }
    }
}