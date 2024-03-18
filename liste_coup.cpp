/******************************************************************************************/
/*  LISTE_COUP.CPP                                                                        */
/*  Auteurs: Victor Poulin, Pascal Dube et Simon Des-Alliers                              */
/*  Date: 14 février 2024                                                                 */
/*                                                                                        */
/* Ce module gere la liste de coups au niveau de l'affichage, de la validite, etc.        */
/*                                                                                        */
/*Liste des fonctions:                                                                    */
/******************************************************************************************/

#define _CRT_SECURE_NO_WARNINGS

/*=========================================================*/
/*                 LES LIBRAIRIES                          */
/*=========================================================*/

#include "liste_coup.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/*=========================================================*/
/*                  LES FONCTIONS                          */
/*=========================================================*/

void init_liste_coups(t_liste_coups* liste_coups)
{
	liste_coups->fin = NULL;
	liste_coups->p_courant = NULL;
	liste_coups->tete = NULL;
	liste_coups->nb_noeuds = 0;
}

/*****************************************************************************/

t_coup get_coup_pc(const t_liste_coups* liste_coups)
{
	return liste_coups->p_courant->coup;
}

/*****************************************************************************/

int get_nb_coups(const t_liste_coups* liste_coups)
{
	return liste_coups->nb_noeuds;
}

/*****************************************************************************/

int valider_coup(t_liste_coups* liste_coups, char* texte_coup, t_coup* coup)
{
	//On initialise le pointeur courant au début de la liste
	liste_coups->p_courant = liste_coups->tete;

	//Tant qu'on est pas à la fin de la liste
	while (liste_coups->p_courant != NULL)
	{
		//On compare le pointeur_courant avec le texte_coup
		if (strcmp(liste_coups->p_courant->coup.texte_coup, texte_coup) == 0)
		{
			strcpy(coup->texte_coup, liste_coups->p_courant->coup.texte_coup);

			return 1;
		}
	}

	return 0;
}

/*****************************************************************************/

int valider_case_dest(t_liste_coups* liste_coups, int col, int lig)
{
	//On initialise le pointeur courant au début de la liste
	liste_coups->p_courant = liste_coups->tete;

	//Tant qu'on est pas à la fin de la liste
	while (liste_coups->p_courant != NULL)
	{

	}

	return 0;
}

/*****************************************************************************/

int ajouter_coup(t_liste_coups* liste_coups, const t_coup* coup)
{
	t_lien element; //On crée un nouvel élément à ajouter

	element = (t_lien)malloc(sizeof(t_lien));

	assert(element);

	element->coup = coup;
	element->suivant = NULL; //Dernier élement

	if (liste_est_vide(liste_coups))
	{
		//On retourne l'élément, car dans tous les cas il y a juste lui
		return element;
	}

	t_lien tmp; //C'est pas une copie, c'est vraiment la même chose
	tmp = li;         //tmp est un pointeur qui pointe à la même place que li

	while (tmp->suivant != NULL)
	{
		tmp = tmp->suivant;
	}

	//On ajoute le nouvel élément à li
	tmp->suivant = element;

	//tmp est une référence à li donc en modifiant tmp, on modifie li
	return li;
}

/*****************************************************************************/

t_lien new_list(void)
{
	return NULL;
}

/*****************************************************************************/

Bool is_empty_list(t_lien liste)
{
	if (liste == NULL)
	{
		return vrai;
	}
	else
	{
		return faux;
	}
}