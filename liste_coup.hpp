/******************************************************************************************/
/*  LISTE_COUP.H                                                                          */
/*  Auteurs: Victor Poulin, Pascal Dube et Simon Des-Alliers                              */
/*  Date: 14 février 2024                                                                 */
/*                                                                                        */
/* Ce module gere la liste de coups au niveau de l'affichage, de la validite, etc.        */
/*                                                                                        */
/*Liste des fonctions:  t_coup* init_liste_coups(t_liste_coups* liste_coups)              */
/*                      void set_coup(	t_coup* coup, int col, int lig, int col_dest,     */
/*                         int lig_dest, int col2, int lig2);                             */
/*                      int ajouter_coup(t_liste_coups* liste_coups, const t_coup* coup)  */
/*                      void vider_liste_coups(t_liste_coups* liste_coups)                */
/*                      int get_nb_coups(const t_liste_coups* liste_coups)                */
/*                      int valider_coup(const t_liste_coups* liste_coups,                */
/*                         char* texte_coup, t_coup* coup)                                */
/*                      int valider_case_dest(const t_liste_coups* liste_coups, int col,  */
/*                         int lig);                                                      */
/*                      void afficher_liste_coups(const t_liste_coups* liste_coups);      */
/*                      void detruire_liste_coups(t_liste_coups* liste_coups)             */
/******************************************************************************************/

#ifndef LISTE_COUP
#define LISTE_COUP 0

#define _CRT_SECURE_NO_WARNINGS

/*=========================================================*/
/*                 LES LIBRAIRIES                          */
/*=========================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef WINCONSOLE
#define WINCONSOLE 0
#include "WinConsole.hpp"
#endif

/*=========================================================*/
/*                  LES CONSTANTES                         */
/*=========================================================*/

#define TAILLE_GR    8                //taille carree de la grille de jeu
#define TAILLE_MAX  80                //taille maximale de la liste des coups
#define POS_VIDE    -1                //indique une position non-valide ou non-utilisee

/*constantes concernant l'affichage*/
#define DECALAGE_AFFICHAGE_X 2       //Valeur de decalage pour l'affichage en x
#define DECALAGE_AFFICHAGE_Y 40      //Valeur de decalage pour l'affichage en y 
#define TAILLE_COLONNE_AFFICHAGE 15  //Taille de colonne 
#define DISTANCE_ENTRE_COLONNES 13   //Distance entre les colonnes

/*=========================================================*/
/*                  LES MACROFONCTIONS                     */
/*=========================================================*/

/*convertis une position colonne a sa lettre correspondante.Eg. 0 a 'a'. comme nous utilisons
des codes ascii, et que les valeurs dans le tableau vont de 0 a TAILLE, il suffit d'ajouter le
nombre en entree a la valeur ascii de la lettre 'a'*/
#define COL_A_CH(c) ((c) + 'a')

/*convertis une position rangee en numero de ligne.Eg. 0 a 8  et 7 a 1. comme les numeros de
rangee sont a l'ordre inverse de ceux des indexes du tableau, il faut soustraire la valeur
en entree a la taille de celui-ci ajoutee a la valeur de '0' en ascii*/
#define RAN_A_NO(r) ((TAILLE_GR - r) + '0')

/***************************************************************************************/
/*                              DECLARATIONS DES TYPES                                 */
/***************************************************************************************/
typedef struct
{
	char texte_coup[6];         //le coup en texte. Ex. "a1-b2"
	int  col, lig;              //position-depart du coup
	int  col_dest, lig_dest;    //position-arrivee du coup
	int  col_case2, lig_case2;  //la case secondaire concernee (en-passant, roque)
} t_coup;

/*cette structure a besoinde t_coup, lle doit donc etre apres*/
typedef struct
{
	t_coup* tab_coups;          //tableau dynamique de la liste de coups
	int taille_liste;           //la taille totale (maximale) de la liste
	int nb_coups;               //le nombre de coups valides dans la liste
} t_liste_coups;

/***************************************************************************************/
/*                       DECLARATIONS DES FONCTIONS PUBLIQUES                          */
/***************************************************************************************/

/*************************************************************************************************
    OBJECTIF :Initialiser la liste de coups. On alloue le tableau dynamique avec TAILLE_MAX cases
	          et on met le nombre de coups valides a zero. Le champ "taille_liste" doit contenir la
			  taille totale du tableau

	PARAMETRE : liste_coup : la liste des coups a initialiser

	SORTIE :retourne l'addresse du pointeur liste_coup->tab_coup (sera NULL s'il y a erreur)
			liste de coup initialis�e (changements directement au pointeur)

	ecrit par Pascal Dube, Victor Poulin et Simon Des-Alliers
******************************************************************************/
t_coup* init_liste_coups(t_liste_coups* liste_coups);

/************************************************************************************************
    OBJECTIF : Fonction qui cree un nouveau coup. Les 6 derniers parametres sont copies dans leurs
	           champs respectifs de la reference *coup.  On doit aussi former la 
			   representation-texte du coup a partir des valeurs "col, lig" et "col_dest,
			   lig_dest". Eg. "a2-a4".

	PARAMETRES : coup :		pointeur qui renvoie vers le coup a modifier
				 col :		colonne d'origine de la piece
				 lig :		ligne d'origine de la piece
				 col_dest :	colonne de destination de la piece
				 lig_dest : ligne de destination de la piece
				 col2 :		position de colonne necesaire pour certains coups
				 lig2 :		position de ligne necessaire pour certains coups

	SORTIES : Ne retourne rien (void)

ecrit par Pascal Dube, Victor Poulin et Simon Des-Alliers
*******************************************************************************/
void set_coup(	t_coup* coup, int col, int lig, int col_dest, int lig_dest,
				int col2, int lig2);

/************************************************************************************************
    OBJECTIF : Ajoute un nouveau coup a la liste de coups reçue en reference. On doit verifier si il reste encore
               de la place dans le tableau dynamique des coups. 

	PARAMETRES : liste-coup : la liste de coup
				 coup : le coup a ajouter

	SORTIES : retourne soit 1 (succes) ou 0 (erreur)
			  ajoute le coup a la liste de coup directement

ecrit par Pascal Dube, Victor Poulin et Simon Des-Alliers

*************************************************************************************************/
int ajouter_coup(t_liste_coups* liste_coups, const t_coup* coup);

/************************************************************************************************
    OBJECTIF : Vide la liste des coups en remettant le "nb_coups" a zero.

	PARAMETRE : liste_coup : la liste des coups a vider

	SORTIE :	liste de coup videe (changements directement au pointeur)

	ecrit par Pascal Dube, Victor Poulin et Simon Des-Alliers
*************************************************************************************************/
void vider_liste_coups(t_liste_coups* liste_coups);

/************************************************************************************************
    OBJECTIF : Accesseur qui permet de savoir le nombre de coups valides dans la liste.

	PARAMETRE : liste_coup : la liste des coups a compter

	SORTIE :	retourne le nombre d'entree de la liste de coup

	ecrit par Pascal Dube, Victor Poulin et Simon Des-Alliers
*************************************************************************************************/
 int get_nb_coups(const t_liste_coups* liste_coups);

/*************************************************************************************************
    OBJECTIF : Valide si le coup reçu est dans la liste des coups possibles a jouer. On re�oit la
	           representation texte du coup a retrouver. On parcourt la liste en comparant le texte
			   recu avec le champ texte_coup de chaque coup. Si ce texte a ete retrouve, on
			   retourne une copie de ce coup via la reference "*coup" et on retourne 1. Sinon, on
			   retourne 0 (coup non-present dans la liste).

	PARAMETRE : liste_coup : la liste des coups a compter
			  :	texte_coup : le texte recu a comparer avec les strings des differentes coups
			  : coup :		 le pointeur de retour pour le coup

	SORTIE : retourne 1 si le coup est dans la liste de coups valide sinon on retourne 0
			 le coup extrait de la liste retournee via le pointeur coup

	ecrit par Pascal Dube, Victor Poulin et Simon Des-Alliers
*************************************************************************************************/
int valider_coup(const t_liste_coups* liste_coups, char* texte_coup, t_coup* coup);

/*************************************************************************************************
    OBJECTIF : Valide si la position-destination (col, lig) recue fait partie d'un des coups de
	           la liste. On recoit les coordonnees de la case "col, lig" et on parcourt la liste a
			   la recherche d'un coup qui a la meme case-destination que (col, lig). Des qu'on
			   trouve un coup qui atteint cette case, la fonction arrete sa recherche et retourne
			   1. Sinon, elle retourne 0 (aucun coup de la liste n'atterri sur la case [col, lig]).

	PARAMETRE : liste_coup : la liste des coups possibles a jouer
				col : colonne de destination du coup a verifier
				lig : ligne de destination du coup a verifier

	SORTIE :	retourne 1 si le coup est possible et 0 sinon

	ecrit par Pascal Dube, Victor Poulin et Simon Des-Alliers
*************************************************************************************************/
int valider_case_dest(const t_liste_coups* liste_coups, int col, int lig);

/**********************************************************************************************
    OBJECTIF : Affiche le contenu de la liste dans la moitie-droite de la console-texte.

	PARAMETRE : liste_coup : la liste des coups a afficher

	SORTIE :	affichage a l'ecran seulement

	ecrit par Pascal Dube, Victor Poulin et Simon Des-Alliers

************************************************************************************************/
void afficher_liste_coups(const t_liste_coups* liste_coups);

/**********************************************************************************************
    OBJECTIF : Detruit la liste de coups (libere le tableau dynamique des coups et remet les
	           compteurs a zero)

	PARAMETRE : liste_coup : la liste des coups a detruire

	SORTIE :	liste de coup vide (incluant les 'free' pour les coups eux meme)

	ecrit par Pascal Dube, Victor Poulin et Simon Des-Alliers
******************************************************************************/
void detruire_liste_coups(t_liste_coups* liste_coups);

#endif