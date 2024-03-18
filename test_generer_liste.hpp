/***************************************************************************************/
/*  TEST_GENERER_LISTE.H                                                               */
/*  Auteurs: Victor Poulin, Pascal Dube et Simon Des-Alliers                           */
/*  Date: 1 mars 2024                                                                  */
/*                                                                                     */
/* Ce module permet d'effectuer les tests de toutes les pieces avec des fonctions      */
/* indépendantes pour chaque pièce.                                                    */
/*                                                                                     */
/*Liste des fonctions:  void initialiser_grille_test_pion(t_grille grille_jeu)         */
/*                      void initialiser_grille_test_tour(t_grille grille_jeu)         */
/*                      void initialiser_grille_test_fou(t_grille grille_jeu)          */
/*                      void initialiser_grille_test_cavalier(t_grille grille_jeu)     */
/*                      void initialiser_grille_test_roi(t_grille grille_jeu)          */
/*                      void initialiser_grille_test_roque_roi(t_grille grille_jeu)    */
/***************************************************************************************/

#ifndef TEST_GENERER_LISTE
#define TEST_GENERER_LISTE 0

/*=========================================================*/
/*                 LES LIBRAIRIES                          */
/*=========================================================*/

#include <stdio.h>
#include <stdlib.h>
#include"grille_echecs.hpp"

/*=========================================================*/
/*                  LES PROTOTYPES                         */
/*=========================================================*/

/************************************************************************************************
    OBJECTIF : Cette fonction initialise la grille de jeu avec une certaine configuration pour
	           tester la fonction qui genere les coups possibles pour le pion

	PARAMETRES : grille_jeu :  la grille de jeu qui doit être initialisée
								(c'est un tableau donc un pointeur)
	SORTIES :	grille de jeu initialisee 

	écrit par Pascal Dubé, Victor Poulin et Simon Des-Alliers
**************************************************************************************************/
void initialiser_grille_test_pion(t_grille grille_jeu);

/************************************************************************************************
    OBJECTIF : Cette fonction initialise la grille de jeu avec une certaine configuration pour 
	           tester la fonction qui genere les coups possibles pour la tour

	PARAMETRES : grille_jeu :  la grille de jeu qui doit être initialisée
								(c'est un tableau donc un pointeur)
	SORTIES :	grille de jeu initialisee

	SPEC :Est utilisé pour tester la dame, car la tour fait partie du code de la dame donc pas
		  besoin de la tester separement

	écrit par Pascal Dubé, Victor Poulin et Simon Des-Alliers
*************************************************************************************************/
void initialiser_grille_test_tour(t_grille grille_jeu);

/*************************************************************************************************
    OBJECTIF : Cette fonction initialise la grille de jeu avec une certaine configuration pour
	           tester la fonction qui genere les coups possibles pour le fou

	PARAMETRES : grille_jeu :  la grille de jeu qui doit être initialisée
								(c'est un tableau donc un pointeur)
	SORTIES :	grille de jeu initialisee

	SPEC : Est utilisé pour tester la dame, car le fou fait partie du code de la dame
	       donc pas besoin de la tester separement

	écrit par Pascal Dubé, Victor Poulin et Simon Des-Alliers
*************************************************************************************************/
void initialiser_grille_test_fou(t_grille grille_jeu);

/************************************************************************************************
    OBJECTIF :Cette fonction initialise la grille de jeu avec une certaine configuration pour
	          tester la fonction qui genere les coups possibles pour le cavalier

	PARAMETRES : grille_jeu :  la grille de jeu qui doit être initialisée
								(c'est un tableau donc un pointeur)
	SORTIES :	grille de jeu initialisee

	écrit par Pascal Dubé, Victor Poulin et Simon Des-Alliers
*************************************************************************************************/
void initialiser_grille_test_cavalier(t_grille grille_jeu);

/*************************************************************************************************
   OBJECTIF :Cette fonction initialise la grille de jeu avec une certaine configuration pour 
             tester la fonction qui genere les coups possibles pour le roi

	PARAMETRES : grille_jeu :  la grille de jeu qui doit être initialisée
								(c'est un tableau donc un pointeur)
	SORTIES :	grille de jeu initialisee

	écrit par Pascal Dubé, Victor Poulin et Simon Des-Alliers
*************************************************************************************************/
void initialiser_grille_test_roi(t_grille grille_jeu);

/************************************************************************************************
    OBJECTIF : Cette fonction initialise la grille de jeu avec une certaine configuration pour 
	           tester le roque

	PARAMETRES : grille_jeu :  la grille de jeu qui doit être initialisée
								(c'est un tableau donc un pointeur)
	SORTIES :	grille de jeu initialisee

	écrit par Pascal Dubé, Victor Poulin et Simon Des-Alliers
**************************************************************************************************/
void initialiser_grille_test_roque_roi(t_grille grille_jeu);

#endif