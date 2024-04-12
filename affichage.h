/*******************************************************************************
    AFFICHAGE.H 
    Auteurs :Éric Thé et modifié par Victor Poulin, Pascal Dube et Simon Des-Alliers   
    Date: 18 mars 2024

    Module qui contient les fonctions de gestion de l'affichage de la grille et
    des coups jouées avec des images Bitmap en mode graphique.
    Les outils et fonctions d'affichages utilisée proviennent du module 
    "utilitaire_affichage.h" et les fonctions de gestion de la souris sont
    importées du module "SOURISLIB.h". Ce module inclut aussi "grille_echecs.h".

    Liste des fonctions:t_saisie choix_case(int* col_case, int* lig_case)
	                    void afficher_grille(const t_etat_jeu* jeu)
	                    int lire_images(const char* nom_fich_bin)
                        void detruire_images()
                       	void afficher_coup(t_piece piece_src, int col_src, int ran_src,
	                         t_piece piece_dest, int col_dest, int ran_dest)
                        void afficher_gagnant(int joueur)
*******************************************************************************/

#ifndef _AFF_LIB_H
#define _AFF_LIB_H 1

//Librairies et modules externes nécessaires
#include"utilitaire_affichage.h"
#include"grille_echecs.h"
#include"SOURISLIB.h"

//position du bouton-Abandon
#define POSY_BOUT_QUIT   20
#define POSX_BOUT_QUIT   (20 + TAILLE_BMP)

//position du bouton-Recommencer
#define POSY_BOUT_RESET  100
#define POSX_BOUT_RESET  (20 + TAILLE_BMP)

//chaine par défaut pour un coup VIDE
#define COUP_VIDE  "xx-xx"
 
//les trois valeurs de retour d'un clic-souris. 
//QUITTER = bouton "ABANDONNER", RESET = bouton "RECOMMENCER", POS_VALIDE = une case valide
typedef enum { QUITTER = -1, RESET, POS_VALIDE } t_saisie;

/*-------------------------------------------------------------------*/
/*                       MACROFONCTION                               */
/*-------------------------------------------------------------------*/

/*La macrofonction PALE_FONCER permet de déterminer de quelle couleur de fond la case de la grille 
doit être. Retourne 1 (vert foncer) ou 0 (vert pale) dépendamment de la parité de la case*/
#define PALE_FONCER(i, j) ((((i)+(j)) % 2) ? 1:0)

/*-------------------------------------------------------------------*/
/*                       FONCTIONS PUBLIQUES                         */
/*-------------------------------------------------------------------*/

/* Permet de lire toutes les images Bitmap à partit du fichier binaire reçu en paramètre.    */
/* La fonction tente d'ouvrir le fichier avec le nom reçu en paramètre en mode binaire.      */
/* Si l’ouverture de fichier a échouée, la fonction retourne 0.  Sinon, elle lit les 32      */
/* images Bitmap se trouvant dans le fichier dans la variable privée "images" et retourne 1. */
int lire_images(const char* nom_fich_bin);

/* Permet de détruire les allocations des tableaux d'octets de chacune des 32 images Bitmap. */
void detruire_images();

/* Permet d'afficher la grille du "jeu" reçu en paramètre à l'aide des 32 images Bitmap qui  */
/* se trouvent dans le tableau privé "images". Cette fonction fera appel aux procédures      */
/* d'affichage "init_zone_grille()", "afficher_piece()" et "dessiner_grille_vide()".   */
void afficher_grille(const t_etat_jeu* jeu);

/* Permet de choisir une case de la grille (ou un bouton-commande) avec la souris. Utilise   */
/* les outils de gestion de souris offerts dans le module "SOURISLIB.h".                     */
/* Cette fonction va retourner trois informations :                                          */
/*  - le type de saisie "QUITTER", "RESET" ou "POS_VALIDE" (type t_saisie).                  */
/*  - la position-grille (*col_case, *lig_case) de la saisie si on retourne "POS_VALIDE".    */
t_saisie choix_case(int* col_case, int* lig_case);

/* Cette procédure va illustrer un coup choisi par soit l’utilisateur ou l’ordinateur.       */
/* On reçoit la pièce "piece_src" qui se trouve sur la case-source (col_src, ran_src) et la  */
/* pièce (ou case vide) "piece_dest" qui se trouve à la case-destination(col_dest, ran_dest) */
void afficher_coup(t_piece piece_src, int col_src, int ran_src,
                   t_piece piece_dest, int col_dest, int ran_dest);
/*Cette fonction permet d'afficher le gagnant du jeu sur winBGIm                             */
/*On reçoit la valeur du joueur est paramètre et on affiche un message de victoire           */
/*personnaliser en fonction du joueur reçu en paramètre.                                     */
void afficher_gagnant(int joueur);
#endif