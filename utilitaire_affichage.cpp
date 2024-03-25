/******************************************************************************/
/*  UTILITAIRE_AFFICHAGE.CPP                                                  */
/*  Module utilitaire qui permet d'afficher les cases d'une grille en mode    */
/*  graphique avec le module graphique "winBGim.h".                           */
/*                                                                            */
/*  Conception : Pierre Bélisle, Eric Thé                                     */
/******************************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utilitaire_affichage.h"
#include "winbgim.h"

//Nombre de pixels pour un caractere
#define TAILLE_CAR 24
#define TAILLE_STR 80
  
#define COULEUR_DEFAULT  RED

/* Variables privées pour retenir les dimensions de la grille */
static int dim_x;
static int dim_y;


//*********************************
//  INIT GRAPHE
//*********************************
//Crée une fenetre de la dimension voulue
void init_graphe(){  //int nb_cases_lignes, int nb_cases_colonnes) {  
	int carte, mode;

	//la fenetre principale
	initgraph(&carte, &mode, "");
	//initwindow(nb_cases_colonnes*TAILLE_CASE_X, nb_cases_lignes*TAILLE_CASE_Y);   
}

//******************************
//  INIT ZONE GRILLE
//******************************
//Dessine un cadre blanc autour de la zone d'affichage
void init_zone_grille(int dimy, int dimx) {
	//La fenetre de la grille
	setviewport(MARGEX, MARGEY,
		        (dimx + 1) * TAILLE_BMP + MARGEX + 1, (dimy + 1) * TAILLE_BMP + MARGEY + 1, 0);
	setcolor(COULEUR_DEFAULT);
	rectangle(0, 0, (dimx * TAILLE_BMP), (dimy * TAILLE_BMP));

	//retenir la taille de la grille dans les 2 variables privées
	dim_x = dimx;
	dim_y = dimy;
}

//******************************
//  DESSINER GRILLE VIDE
//******************************
//Dessine un gabarit de grille vide avec les titres des colonnes et rangées
void dessiner_grille_vide() {
	char buff[2] = { 0 };    //string-tampon de 2 char (eg. "a" ou "1")
	int px = 0, py = 0;

	setlinestyle(0, 1, 1);
	setcolor(RED);

	//contour carré
	rectangle(0, 0, 8 * TAILLE_BMP, 8 * TAILLE_BMP);

	//+7 lignes horz.
	py += TAILLE_BMP;
	for (int i = 0; i < 7; i++, py += TAILLE_BMP)
		line(px, py, px + 8 * TAILLE_BMP, py);

	//+7 lignes vert.
	py = 0;
	px += TAILLE_BMP;
	for (int i = 0; i < 7; i++, px += TAILLE_BMP)
		line(px, py, px, py + 8 * TAILLE_BMP);

	settextstyle(TRIPLEX_FONT, 0, 3);
	setcolor(LIGHTGRAY);

	//titres des colonnes 'a' - 'h'
	py = -TAILLE_CAR - 10;
	px = TAILLE_CAR;
	for (int i = 0; i < dim_x; i++, px += TAILLE_BMP) {
		buff[0] = i + 'a';			//remplacer 1ier char du tampon
		outtextxy(px, py, buff);
	}

	//titres des lignes '8' - '1'
	py = TAILLE_CAR;
	px = -TAILLE_CAR - 10;
	for (int i = 0; i < dim_y; i++, py += TAILLE_BMP) {
		buff[0] = dim_y - i + '0';	//remplacer 1ier char du tampon
		outtextxy(px, py, buff);
	}
}

//******************************
//  AFFICHER BOUTON
//******************************
//Affiche un bouton à la position fournie (lig, col) du coin supérieur-gauche du bitmap
void afficher_bouton(int lig, int col, const char* texte) {
	setfillstyle(SOLID_FILL, COULEUR_DEFAULT);
	bar(col, lig, col + TAILLEX_BOUTON, lig + TAILLEY_BOUTON);   //rectangle rouge

	settextstyle(DEFAULT_FONT, 0, 2);
	setcolor(WHITE);
	setbkcolor(COULEUR_DEFAULT);
	outtextxy(col + 12, lig + 12, texte);    //afficher le texte
	rectangle(col+2, lig+2, col + TAILLEX_BOUTON - 3, lig + TAILLEY_BOUTON - 3);
}

//******************************
//  AFFICHER PIECE
//******************************
//Affiche une piece (un bitmap) à la position fournie (lig, col) du coin supérieur-gauche du bitmap
void afficher_piece(int lig, int col, int hauteur, int largeur, unsigned char* image_data) {
	BGIimage bi = { largeur, hauteur, image_data }; 

	putimage(col, lig, (void*)&bi, COPY_PUT);
}

//******************************
//  AFFICHER MESSAGE
//******************************
//Affiche le message reçu au bas de la zone d'affichage (à la ligne 1)
void afficher_message(const char* mess) {
	int debuty = MARGEY / 2 + dim_y * TAILLE_BMP + TAILLE_CAR + 10;
	int debutx = -50;

	//Faire un grand rectangle noir pour EFFACER
	setbkcolor(BLACK);
	setfillstyle(SOLID_FILL, BLACK);
	bar(debutx, debuty, 990, debuty + TAILLE_CAR);   //rectangle noir

	settextstyle(TRIPLEX_FONT, 0, 3);
	setcolor(LIGHTGRAY);
	outtextxy(debutx, debuty, mess);    //afficher le message
}

//******************************
//  AFFICHER INFO
//******************************
//Affiche le texte et la valeur reçue au bas de la zone d'affichage (ligne 2)
void afficher_info(const char* texte, int valeur) {
	char txt[TAILLE_STR];
	int debuty = MARGEY / 2 + dim_y * TAILLE_BMP;
	int debutx = 150;

	//Faire un grand rectangle noir pour EFFACER
	setbkcolor(BLACK);
	setfillstyle(SOLID_FILL, BLACK);
	bar(debutx, debuty, 990, debuty + TAILLE_CAR);   //rectangle noir
	settextstyle(TRIPLEX_FONT,0,3);
	setcolor(LIGHTGRAY);

	//afficher le texte & valeur
	sprintf(txt, texte, valeur);
	outtextxy(debutx, debuty, txt);
}                         

//******************************
//  AFFICHER SCORE
//******************************
//Affiche le score du jeu à droite de la zone d'affichage 
void afficher_score(int val) {
	int debuty = 0;
	int debutx = 9 * TAILLE_BMP;
	char buff[30];

	//Faire un grand rectangle noir pour EFFACER
	setbkcolor(BLACK);
	setfillstyle(SOLID_FILL, BLACK);
	bar(debutx, debuty, 990, debuty + TAILLE_CAR);   //rectangle noir

	settextstyle(TRIPLEX_FONT, 0, 3);
	setcolor(LIGHTGRAY);
	sprintf(buff, "Score: %d", val);
	outtextxy(debutx, debuty, buff);    //afficher le score
}

//******************************
//  EFFACER ZONE ENVIRONNEMENT
//******************************
//Permet d'effacer la zone d'affichage au complet
void effacer_zone_environnement(int dimy, int dimx) {
   setviewport(MARGEX, MARGEY,
	           (dimx+1)* TAILLE_BMP +MARGEX+1, (dimy+1)* TAILLE_BMP +MARGEY+1, 1);
   clearviewport();
}

//******************************
//  DELAI ÉCRAN
//******************************
//Permet de faire une pause de "msec" millisecondes à l'écran
void delai_ecran(int msec) {
   delay_graph(msec);
}

//******************************
//  TOUCHE PESEE
//******************************
//Retourne 1 si une touche a été pesée, 0 sinon.
int  touche_pesee() {  
   return kbhit_graph();
}

//******************************
//  OBTENIR TOUCHE
//******************************
//Pour récupérer un caractère saisi dans la console graphique.
int  obtenir_touche() {
   return getch_graph();
}

//******************************
//  FERMER MODE GRAPHIQUE
//******************************
void fermer_mode_graphique() {
	closegraph();
}