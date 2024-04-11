/*******************************************************************************
    AFFICHAGE.H  (version pour le TP3)
    Auteurs :

    Module qui contient les fonctions de gestion de l'affichage de la grille et
    des coups jou�es avec des images Bitmap en mode graphique.
    Les outils et fonctions d'affichages utilis�e proviennent du module 
    "utilitaire_affichage.h" et les fonctions de gestion de la souris sont
    import�es du module "SOURISLIB.h". Ce module inclut aussi "grille_echecs.h".
*******************************************************************************/
#ifndef _AFF_LIB_H
#define _AFF_LIB_H 1

//Librairies et modules externes n�cessaires
#include"utilitaire_affichage.h"
#include"grille_echecs.h"
#include"SOURISLIB.h"

//position du bouton-Abandon
#define POSY_BOUT_QUIT   20
#define POSX_BOUT_QUIT   (20 + TAILLE_BMP)

//position du bouton-Recommencer
#define POSY_BOUT_RESET  100
#define POSX_BOUT_RESET  (20 + TAILLE_BMP)

//chaine par d�faut pour un coup VIDE
#define COUP_VIDE  "xx-xx"
 
//les trois valeurs de retour d'un clic-souris. 
//QUITTER = bouton "ABANDONNER", RESET = bouton "RECOMMENCER", POS_VALIDE = une case valide
typedef enum { QUITTER = -1, RESET, POS_VALIDE } t_saisie;


/*-------------------------------------------------------------------*/
/*                       FONCTIONS PUBLIQUES                         */
/*-------------------------------------------------------------------*/

/* Permet de lire toutes les images Bitmap � partit du fichier binaire re�u en param�tre.    */
/* La fonction tente d'ouvrir le fichier avec le nom re�u en param�tre en mode binaire.      */
/* Si l�ouverture de fichier a �chou�e, la fonction retourne 0.  Sinon, elle lit les 32      */
/* images Bitmap se trouvant dans le fichier dans la variable priv�e "images" et retourne 1. */
int lire_images(const char* nom_fich_bin);

/* Permet de d�truire les allocations des tableaux d'octets de chacune des 32 images Bitmap. */
void detruire_images();

/* Permet d'afficher la grille du "jeu" re�u en param�tre � l'aide des 32 images Bitmap qui  */
/* se trouvent dans le tableau priv� "images". Cette fonction fera appel aux proc�dures      */
/* d'affichage "init_zone_grille()", "afficher_piece()" et "dessiner_grille_vide()".   */
void afficher_grille(const t_etat_jeu* jeu);

/* Permet de choisir une case de la grille (ou un bouton-commande) avec la souris. Utilise   */
/* les outils de gestion de souris offerts dans le module "SOURISLIB.h".                     */
/* Cette fonction va retourner trois informations :                                          */
/*  - le type de saisie "QUITTER", "RESET" ou "POS_VALIDE" (type t_saisie).                  */
/*  - la position-grille (*col_case, *lig_case) de la saisie si on retourne "POS_VALIDE".    */
t_saisie choix_case(int* col_case, int* lig_case);

/* Cette proc�dure va illustrer un coup choisi par soit l�utilisateur ou l�ordinateur.       */
/* On re�oit la pi�ce "piece_src" qui se trouve sur la case-source (col_src, ran_src) et la  */
/* pi�ce (ou case vide) "piece_dest" qui se trouve � la case-destination(col_dest, ran_dest) */
void afficher_coup(t_piece piece_src, int col_src, int ran_src,
                   t_piece piece_dest, int col_dest, int ran_dest);
/*Cette fonction permet d'afficher le gagnant du jeu sur winBGIm                             */
/*On re�oit la valeur du joueur est param�tre et on affiche un message de victoire           */
/*personnaliser en fonction du joueur re�u en param�tre.                                      */
void afficher_gagnant(int joueur);
#endif