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
/*                       int liste_est_vide(t_liste_coups* liste)                         */
/*                                                                                        */
/******************************************************************************************/

#define _CRT_SECURE_NO_WARNINGS

/*=========================================================*/
/*                 LES LIBRAIRIES                          */
/*=========================================================*/

#include "liste_coup.hpp"
#include "mtwister.hpp"
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
			//On copie le texte_coup de la liste avec le texte_coup reçu
			strcpy(coup->texte_coup, liste_coups->p_courant->coup.texte_coup);

			return 1;
		}

		//On avance le poibteur courant
		avancer_pc(liste_coups);
	}

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

	}

	return 0;
}

/*****************************************************************************/

int ajouter_coup(t_liste_coups* liste_coups, const t_coup* coup)
{
	//On crée un nouvel élément à ajouter
	t_lien element = NULL;

	//On alloue de l'espace mémoire pour un nouvel élément
	element = (t_lien)malloc(sizeof(t_lien));

	//On vérifie que l'allocation dynamique s'est bien effectuée
	if (element == NULL)
		return 0;

	/*On set le coup dans element*/
	set_coup(&element->coup, coup->col, coup->lig, coup->col_dest, coup->lig_dest,
		coup->col_case2, coup->lig_case2);

	//Si la liste est vide, on débute la liste 
	if (!get_nb_coups(liste_coups))
	{
		element->suivant = NULL;
		
		liste_coups->tete = element;
		liste_coups->fin = element;
		liste_coups->p_courant = element;
	}
	else
	{
		/*On remet le pc au debut*/
		replacer_pc_debut(liste_coups);

		//On avance le pointeur courant jusqu'à la fin de la liste
		while (liste_coups->p_courant->suivant != NULL)
			avancer_pc(liste_coups);
		
		/*On fait le lien entre la liste et l'élément */
		liste_coups->p_courant->suivant = element;

		/*on met le suivant de l'élément à NULL car c'est le dernier de la liste*/
		element->suivant = NULL;

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
	element = (t_lien)malloc(sizeof(t_lien));

	//On vérifie que l'allocation dynamique s'est bien effectuée
	if (element == NULL) {
		return 0;
	}

	//On replace le pointeur courant au début de la liste
	replacer_pc_debut(liste_coups);

	set_coup(&element->coup, coup->col, coup->lig, coup->col_dest, coup->lig_dest,
		coup->col_case2, coup->lig_case2);

	/*Si la liste est vide*/
	if (liste_est_vide(liste_coups))
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

	}

	//On incrémente le nombre de noeud, car on ajoute un nouvel élément
	liste_coups->nb_noeuds++;
	return 1;

}

/*****************************************************************************/

void vider_liste_coups(t_liste_coups* liste_coups)
{
	int compteur = 0; //Compteur permettant de sortir de la boucle

	//On met le pointeur courant au debut de la liste
	replacer_pc_debut(liste_coups);

	//Tant qu'on est pas arrivé à la fin de la liste
	while (compteur != get_nb_coups(liste_coups))
	{
		//On avance le pointeur_courant
		avancer_pc(liste_coups);

		//On libère la tête
		free(liste_coups->tete);

		//On met la tête sur le pointeur courant
		liste_coups->tete = liste_coups->p_courant;

		//On incrémente le compteur
		compteur++;
	}

	//On libère les pointeurs
	liste_coups->tete = NULL;
	liste_coups->p_courant = NULL;

	//On met le nombre de noeuds à zéro, car on a vidé la liste
	liste_coups->nb_noeuds = 0;

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
	if (liste_coups->p_courant->suivant) 
	{
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
		coup_choisi = mt_randU(get_nb_coups(liste_coups));

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

int liste_est_vide(t_liste_coups* liste_coups)
{
	//Si le nombre de noeud est à zéro la liste est vide
	if (!get_nb_coups(liste_coups))
	{
		return 1;
	}
	return 0;
}

/*****************************************************************************/

void detruire_liste_coups(t_liste_coups* liste_coups)
{
	//Pour détruire la liste on doit simplement la vider (free) et mettre les pointeurs à NULL
	vider_liste_coups(liste_coups);
}