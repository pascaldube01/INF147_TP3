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

void set_coup(t_coup* coup, int col, int lig, int col_dest, int lig_dest, int col2, int lig2)
{
	/*On assigne les valeurs mis ne paramètre dans les paramètres du coup envoyé en paramètre*/
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

	t_lien tmp; //C'est pas une copie, c'est vraiment la même chose
	tmp = li;   //tmp est un pointeur qui pointe à la même place que li

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

int ajouter_coup_debut(t_liste_coups* liste_coups, const t_coup* coup) {
	return 1; 
}

/*****************************************************************************/

void vider_liste_coups(t_liste_coups* liste_coups) {

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
	if (liste_coups->p_courant->suivant) {
		liste_coups->p_courant = liste_coups->p_courant->suivant;
		return 1;
	}
	return 0;
}

/*****************************************************************************/

t_coup choix_coup_ordi(t_liste_coups* liste_coups) 
{
	int coup_choisi; //Variable pour prendre le nombre aléatoire est généré
	/*On doit replacer le pc au début de la liste car on a changer de joueur*/
	/*Cette ligne va être enlever pour la mettre dans le main */
	replacer_pc_debut(liste_coups);
	/*On s'assure que la liste n'est pas vide */
	if (!liste_est_vide(liste_coups))
	{
		/*On génère le nombre aléatoire*/
		coup_choisi = mt_randU(liste_coups->nb_noeuds);
		/*On retourne le coup qui est à la liste aléatoire*/
		for (int i = 0; i <= coup_choisi; i++)
		{
			avancer_pc(liste_coups);
		}
		return get_coup_pc(liste_coups);
	}
	/*Sinon on renvoie un coup vide*/
	return t_coup({ 0 });
}

/*****************************************************************************/

t_lien nouvelle_liste(void)
{
	return NULL;
}

/*****************************************************************************/

Bool liste_est_vide(t_liste_coups* liste_coups)
{
	/*Si le nombre de noeud est à zéro la liste est vide*/
	if (!get_nb_coups(liste_coups))
	{
		return vrai;
	}
	return faux;
}