/******************************************************************************************/
/*  LISTE_COUP.CPP                                                                        */
/*  Auteurs: Victor Poulin, Pascal Dube et Simon Des-Alliers                              */
/*  Date: 18 mars 2024                                                                    */
/*                                                                                        */
/*  Module qui contient les fonctions de gestion d'une liste chainée de coups.            */
/*  Ce module est indépendant et n'inclut rien.                                           */
/*                                                                                        */
/*Liste des fonctions:   t_coup get_coup_pc(const t_liste_coups* liste_coups)             */
/*                       int get_nb_coups(const t_liste_coups* liste_coups)               */
/*                       int valider_coup(t_liste_coups* liste_coups, char* texte_coup,   */
/*                             t_coup* coup)                                              */
/*                       int valider_case_dest(t_liste_coups* liste_coups, int col,       */
/*                           int lig)                                                     */
/*                       void init_liste_coups(t_liste_coups* liste_coups)                */
/*                       void set_coup(t_coup* coup, int col, int lig, int col_dest,      */
/*                           int lig_dest, int col2, int lig2)                            */
/*                       int ajouter_coup(t_liste_coups* liste_coups, const t_coup* coup) */
/*                       int ajouter_coup_debut(t_liste_coups* liste_coups,               */
/*                           const t_coup* coup)                                          */
/*                       void vider_liste_coups(t_liste_coups* liste_coups)               */
/*                       void replacer_pc_debut(t_liste_coups* liste_coups)               */
/*                       int  avancer_pc(t_liste_coups* liste_coups)                      */
/*                       t_coup choix_coup_ordi(t_liste_coups* liste_coups)               */
/*                       void afficher_liste_coups(t_liste_coups* liste_coups)            */
/*                       void detruire_liste_coups(t_liste_coups* liste_coups)            */
/*                       void detruire_un_coup(t_liste_coups* liste_coups)                */
/******************************************************************************************/

#define _CRT_SECURE_NO_WARNINGS

/*=========================================================*/
/*                 LES LIBRAIRIES                          */
/*=========================================================*/

#include "liste_coup.h"
#include "mtwister.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/*=========================================================*/
/*                  LES FONCTIONS                          */
/*=========================================================*/

void init_liste_coups(t_liste_coups* liste_coups)
{
	//On met la fin de la liste à NULL
	liste_coups->fin = NULL;

	//On met le pointeur courant à NULL
	liste_coups->p_courant = NULL;

	//On met la tete à NULL
	liste_coups->tete = NULL;

	//On initialise le nombre de noeud à 0
	liste_coups->nb_noeuds = 0;
}

/*****************************************************************************/

void set_coup(t_coup* coup, int col, int lig, int col_dest, int lig_dest, int col2, int lig2)
{
	/*on cree la sring du coup a partir des valeurs entrees et des macros qui change les positions
	sur le plateau en valeur ascii affichable dans un terminal*/
	coup->texte_coup[0] = COL_A_CH(col);
	coup->texte_coup[1] = RAN_A_NO(lig);
	coup->texte_coup[2] = '-';
	coup->texte_coup[3] = COL_A_CH(col_dest);
	coup->texte_coup[4] = RAN_A_NO(lig_dest);
	coup->texte_coup[5] = '\0';

	/*On assigne les valeurs mis en paramètre dans les paramètres du coup envoyé en paramètre*/
	coup->col = col;
	coup->lig = lig;
	coup->col_dest = col_dest;
	coup->lig_dest = lig_dest;
	coup->col_case2 = col2;
	coup->lig_case2 = lig2;
}

/*****************************************************************************/

t_coup get_coup_pc(const t_liste_coups* liste_coups)
{
	//On retourne le coup du pointeur courant
	return liste_coups->p_courant->coup;
}

/*****************************************************************************/

int get_nb_coups(const t_liste_coups* liste_coups)
{
	//On retourne le nombre de coups de la liste chaînée (nombre de noeuds)
	return liste_coups->nb_noeuds;
}

/*****************************************************************************/

int valider_coup(t_liste_coups* liste_coups, char* texte_coup, t_coup* coup)
{
	//On initialise le pointeur courant au début de la liste
	replacer_pc_debut(liste_coups);

	//Tant qu'on est pas à la fin de la liste
	while (liste_coups->p_courant != NULL)  
	{
		//On compare le pointeur_courant avec le texte_coup
		if (strcmp(liste_coups->p_courant->coup.texte_coup, texte_coup) == 0)
		{
			/*On effectue le coup*/
			*coup = liste_coups->p_courant->coup;
			return 1;
		}
		//On avance le pointeur courant
		avancer_pc(liste_coups);
	}
	//On remet le pointeur courant au début de la liste
	replacer_pc_debut(liste_coups);
	return 0;
}

/*****************************************************************************/

int valider_case_dest(t_liste_coups* liste_coups, int col, int lig)
{
	//On initialise le pointeur courant au début de la liste
	replacer_pc_debut(liste_coups);

	//Tant qu'on est pas à la fin de la liste
	while (liste_coups->p_courant != NULL)
	{
		if (liste_coups->p_courant->coup.lig_dest == lig &&
			liste_coups->p_courant->coup.col_dest == col)
			return 1;
		avancer_pc(liste_coups);
	}
	//On replace le p_courant au début de la liste 
	replacer_pc_debut(liste_coups);
	return 0;
}

/*****************************************************************************/

int ajouter_coup(t_liste_coups* liste_coups, const t_coup* coup)
{
	//On crée un nouvel élément à ajouter
	t_lien element = NULL;

	//On alloue de l'espace mémoire pour un nouvel élément
	element = (t_lien) malloc(sizeof(t_noeud));

	//On vérifie que l'allocation dynamique s'est bien effectuée
	if (element == NULL)
		return 0;

	/*On transfert le coup dans element*/
	element->coup = *coup;
	/*on met le suivant de l'élément à NULL car c'est le dernier de la liste*/
	element->suivant = NULL;

	//Si la liste est vide, on débute la liste 
	if (!get_nb_coups(liste_coups))
	{	
		liste_coups->tete = element;
		liste_coups->fin = element;
		liste_coups->p_courant = element;
	}
	else
	{
		liste_coups->fin->suivant = element;
		liste_coups->p_courant = element;
		/*on met la fin à l'élément*/
		liste_coups->fin = element;
	}

	//On incrémente le nombre de noeud, car on ajoute un nouvel élément
	liste_coups->nb_noeuds++;

	return 1;
}

/*****************************************************************************/

int ajouter_coup_debut(t_liste_coups* liste_coups, const t_coup* coup) 
{
	t_lien element; //Variable représentant un nouvel élément dans la liste

	//On alloue de l'espace mémoire pour une nouvel élément
	element = (t_lien)malloc(sizeof(t_noeud));

	//On vérifie que l'allocation dynamique s'est bien effectuée
	if (element == NULL)
	{
		return 0;
	}

	//On replace le pointeur courant au début de la liste
	replacer_pc_debut(liste_coups);

	/*On transfert le coup appelé en paramètre*/
	element->coup = *coup;
	/*Si la liste est vide*/
	if (!get_nb_coups(liste_coups))
	{
		element->suivant = NULL;
		
		liste_coups->tete = element;
		liste_coups->fin = element;
		liste_coups->p_courant = element;
	}
	else
	{
		/*On fait le lien entre la fin de l'élément et le début de la file*/
		element->suivant = liste_coups->tete;

		/*On pointe la tete sur l'élément*/
		liste_coups->tete = element;
		liste_coups->p_courant = element;
	}

	//On incrémente le nombre de noeud, car on ajoute un nouvel élément
	liste_coups->nb_noeuds++;
	return 1;
}

/*****************************************************************************/

void vider_liste_coups(t_liste_coups* liste_coups)
{
	/*On s'assure que la liste est vide*/
	replacer_pc_debut(liste_coups);
	if (liste_coups->tete != NULL) 
	{
		//Tant qu'on est pas arrivé à la fin de la liste
		while (get_nb_coups(liste_coups))
		{
			//On détruit le coup
			detruire_un_coup(liste_coups);
			//On décrémente le nombre de coup
			liste_coups->nb_noeuds--;
		}

		//On libère les pointeurs
		liste_coups->tete = NULL;
		liste_coups->p_courant = NULL;
		liste_coups->fin = NULL;
	}
}

/*****************************************************************************/

void replacer_pc_debut(t_liste_coups* liste_coups) 
{
	/*On fait pointer p_courant sur le même noeud que le noeud
	que pointe la tête pour le replacer au début de la liste*/
	liste_coups->p_courant = liste_coups->tete;
}

/*****************************************************************************/

int  avancer_pc(t_liste_coups* liste_coups) 
{
	/*Si on n'est pas à la fin de la liste*/
	if (liste_coups->p_courant != NULL) 
	{
		liste_coups->p_courant = liste_coups->p_courant->suivant;
		return 1;
	}
	/*Sinon on remet le pc au début pour ne pas prendre de risque*/
	replacer_pc_debut(liste_coups);
	return 0;
}

/*****************************************************************************/

void detruire_liste_coups(t_liste_coups* liste_coups)
{
	//Pour détruire la liste on doit simplement la vider (free) et mettre les pointeurs à NULL
	vider_liste_coups(liste_coups);
}

/******************************************************************************/

void detruire_un_coup(t_liste_coups* liste_coups)
{
	t_lien ptr_debut; //Pointeur sur le coup à supprimer

	/*On le met au début de la liste*/
	ptr_debut = liste_coups->tete;

	/*On met la tete sur le noeud suivant*/
	liste_coups->tete = liste_coups->tete->suivant;  

	/*On replace le pointeur courant au début*/
	replacer_pc_debut(liste_coups);

	//On libère la tête
	free(ptr_debut);

	ptr_debut = NULL;
}
