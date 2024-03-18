/***************************************************************************************/
/*  AFFICHAGE.H                                                                        */
/*  Auteurs: Victor Poulin, Pascal Dube et Simon Des-Alliers                           */
/*  Date: 14 février 2024                                                              */
/*                                                                                     */
/* Ce module gère l'affichage de la grille d'échec (pièces, couleurs, etc.)            */
/*                                                                                     */
/*Liste des fonctions:  void afficher_jeu(const t_grille grille_jeu, int joueur)       */
/*                      void afficher_piece(int piece_a_afficher)                      */
/*                      void changer_couleur_arriere_plan(int pair_impair)             */
/*                      void afficher_joueur(int joueur)                               */
/*                      t_coup lire_coup_joueur(const t_liste_coups* liste_coups)      */
/*                      void afficher_coup(const t_etat_jeu* jeu, const t_coup* coup)  */
/*                      t_coup  choix_coup_ordi(const t_liste_coups liste)             */
/*                      void gagnant_jeu(const t_etat_jeu* jeu)                        */
/***************************************************************************************/

#ifndef AFFICHAGE
#define AFFICHAGE

/*=========================================================*/
/*                 LES LIBRAIRIES                          */
/*=========================================================*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "mtwister.h"
#include "grille_echecs.h"

#ifndef WINCONSOLE
#define WINCONSOLE 0
#include "WinConsole.h"
#endif

/*=========================================================*/
/*                  LES CONSTANTES                         */
/*=========================================================*/

#define DECALAGE_X 10 //Decalage en x
#define DECALAGE_Y 5  //Decalage en y 

/*=========================================================*/
/*                  LES PROTOTYPES                         */
/*=========================================================*/

/*************************************************************************************************
    OBJECTIF : cette macrofonction nettoie le buffer d'entree de scanf

	PARAMETRES : aucun
	SORTIES :	aucune

	SPEC :

	Ecrit par Pascal Dube, Victor Poulin et Simon Des-Alliers
**************************************************************************************************/
#define FFLUSH() while(getchar() != '\n') {}

/************************************************************************************************
    OBJECTIF : Cette fonction affiche le plateau de jeu ainsi que les pieces a leur position

	PARAMETRES : grille_jeu :  la position des pieces qui doit etre affichee
				joueur : le joueur courant (soit NOIRS ou BLANCS qui sont definis dans
						 grille_echecs.h)
	
	SORTIES :	aucune (affichage seulement)

	SPEC :

	ecrit par Pascal Dube, Victor Poulin et Simon Des-Alliers
***********************************************************************************************/
void afficher_jeu(const t_grille grille_jeu, int joueur);

/***********************************************************************************************
    OBJECTIF : Cette fonction affiche une piece de type t_piece, il est necessaire d'utiliser
              cette fonction, car l'affichage doit etre ascii et t_piece n'est pas ascii

	PARAMETRES : piece_a_afficher : la piece a afficher
	SORTIES : affichage seulement

	SPEC : 

	ecrit par Pascal Dube, Victor Poulin et Simon Des-Alliers
*************************************************************************************************/
void afficher_piece(int piece_a_afficher);

/************************************************************************************************
    OBJECTIF : Cette fonction sert a changer la couleur de l'arriere plan de la grille de jeu elle
	          existe principalement pour alleger la lecture de la fonction afficher_jeu()

	PARAMETRES : pair_impair :  la couleur (GEEN ou LIGHTGREEN) depend seulement de la parite
								du nombre total de cases vues jusqu'a date

	SORTIES : change la couleur de l'arriere plan avec le module WinConsole

	SPEC : 

	ecrit par Pascal Dube, Victor Poulin et Simon Des-Alliers
*************************************************************************************************/
void changer_couleur_arriere_plan(int pair_impair);

/***********************************************************************************************
    OBJECTIF : Permet d'afficher le joueur

	PARAMETRE : joueur     : le joueur actuel

	SORTIE :	void (Ne retourne rien)

	ecrit par Pascal Dube, Victor Poulin et Simon Des-Alliers
***********************************************************************************************/
void afficher_joueur(int joueur);

/*********************************************************************************************
    OBJECTIF : Permet de saisir un coup de l’utilisateur

	PARAMETRE : liste     : la liste des coups possible

	SORTIE :	Le coup de l'utilisateur

	ecrit par Pascal Dube, Victor Poulin et Simon Des-Alliers
***********************************************************************************************/
t_coup lire_coup_joueur(const t_liste_coups* liste_coups);

/**********************************************************************************************
    OBJECTIF : Affiche le coup choisi par l’un ou l’autre joueur à l’écran avec une couleur de fond
	          différente

	PARAMETRE : jeu    : État du jeu actuel
	            coup   : Le coup choisi

	SORTIE :	void (Ne retourne rien)

	ecrit par Pascal Dube, Victor Poulin et Simon Des-Alliers
*************************************************************************************************/
void afficher_coup(const t_etat_jeu* jeu, const t_coup* coup);

/*************************************************************************************************
    OBJECTIF : Va choisir et retourner le coup de l’ordinateur aléatoirement parmi tous les coups 
	          valides dans la « liste » reçue en paramètre.

	PARAMETRE : liste   : la liste des coups possible

	SORTIE :	Le coup de l'ordinateur aléatoire

	ecrit par Pascal Dube, Victor Poulin et Simon Des-Alliers
*************************************************************************************************/
t_coup  choix_coup_ordi(const t_liste_coups liste);

/***********************************************************************************************
    OBJECTIF : Va afficher à l'écran le gagnant du jeu

	PARAMETRE : jeu et état du jeu actuel

	SORTIE :	On retourne 1

	ecrit par Pascal Dube, Victor Poulin et Simon Des-Alliers
************************************************************************************************/
void gagnant_jeu(const t_etat_jeu* jeu);
#endif