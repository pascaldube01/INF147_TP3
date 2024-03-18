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
#include <string.h>

/*=========================================================*/
/*                  LES FONCTIONS                          */
/*=========================================================*/

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

