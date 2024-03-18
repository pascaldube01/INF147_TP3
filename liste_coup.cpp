/******************************************************************************************/
/*  LISTE_COUP.C                                                                          */
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

#define _CRT_SECURE_NO_WARNINGS

/*=========================================================*/
/*                 LES LIBRAIRIES                          */
/*=========================================================*/

#include "liste_coup.hpp"

/*=========================================================*/
/*                  LES FONCTIONS                          */
/*=========================================================*/

/***********************************************************************************************/
t_coup* init_liste_coups(t_liste_coups* liste_coups)
{
	/*On alloue un espace de 80 t_coup pour le tableau dynamique qui contiendra les coups
	possibles*/
	liste_coups->tab_coups = (t_coup*)calloc(TAILLE_MAX, sizeof(t_coup));
	/*Si l'allocation dynamique c'est bien déroulé*/
	if (liste_coups->tab_coups != NULL)
	{
		//initialisation des compteurs de coups
		liste_coups->taille_liste = TAILLE_MAX;
		liste_coups->nb_coups = 0;
	}
	/*Si l'allocation dynamique ne c'est pas bien déroulé*/
	else
	{
		/*On affiche une mention d'erreur s'il y a eu un problème lors de l'allocation dynamique*/
		clrscr();
		printf("Erreur dans l'allocation dynamique de la liste de coups");
	}
	return liste_coups->tab_coups;
}

/************************************************************************************************/
void vider_liste_coups(t_liste_coups* liste_coups)
{
	liste_coups->nb_coups = 0;
}

/************************************************************************************************/
int get_nb_coups(const t_liste_coups* liste_coups)
{
	return liste_coups->nb_coups;
}

/***********************************************************************************************/
int valider_coup(const t_liste_coups* liste_coups, char* texte_coup, t_coup* coup)
{
	/*on parcoure la liste au complet et on recherche un coup qui existe dedans. si on trouve, on en
	fait une copie dans le pointeur coup recu en parametre puis on retourne 1, sinon on retourne 0*/
	for (int i = 0; i < liste_coups->taille_liste; i++)
	{
		
		if (strcmp((liste_coups->tab_coups[i].texte_coup), texte_coup) == 0)
		{
			strcpy(coup->texte_coup, liste_coups->tab_coups[i].texte_coup);
			coup->col = liste_coups->tab_coups[i].col;
			coup->lig = liste_coups->tab_coups[i].lig;
			coup->col_dest = liste_coups->tab_coups[i].col_dest;
			coup->lig_dest = liste_coups->tab_coups[i].lig_dest;
			coup->col_case2 = liste_coups->tab_coups[i].col_case2;
			coup->lig_case2 = liste_coups->tab_coups[i].lig_case2;
			return 1;
		}
	}
	return 0;
}

/************************************************************************************************/
int valider_case_dest(const t_liste_coups* liste_coups, int col, int lig)
{
	//Si un coup possede les memes coordonnees, on retourne 1, sinon 0
	for (int i = 0; i < liste_coups->taille_liste; i++)
	{
		if ((col == liste_coups->tab_coups[i].col_dest) &&
			(lig == liste_coups->tab_coups[i].lig_dest))
		{
			return 1;
		}
	}

	return 0;
}

/***********************************************************************************************/
void detruire_liste_coups(t_liste_coups* liste_coups)
{
	/*Permet de liberer l'espace du tableau dynamique, de mettre la taille et le nombre de
	coups de la liste a 0 */
	free(liste_coups->tab_coups);

	/*on doit aussi mettre le pointeur a NULL, car l'addresse vers laquelle in pointe n'est
	plus valide*/
	liste_coups->tab_coups = NULL;

	/*on met aussi a 0 les variables de position de la liste puisqu'elles n'existe plus*/
	liste_coups->taille_liste = 0;
	liste_coups->nb_coups = 0;
}

/************************************************************************************************/
int ajouter_coup(t_liste_coups* liste_coups, const t_coup* coup)
{
	//Si on a rempli toute l'espace du tableau
	if (get_nb_coups(liste_coups) == TAILLE_MAX){
		return 0; //On retourne 0 et on ne cree pas un autre coup
	}
	else
	{
		liste_coups->tab_coups[liste_coups->nb_coups].col = coup->col;
		liste_coups->tab_coups[liste_coups->nb_coups].lig = coup->lig;
		liste_coups->tab_coups[liste_coups->nb_coups].col_dest = coup->col_dest;
		liste_coups->tab_coups[liste_coups->nb_coups].lig_dest = coup->lig_dest;
		liste_coups->tab_coups[liste_coups->nb_coups].col_case2 = coup->col_case2;
		liste_coups->tab_coups[liste_coups->nb_coups].lig_case2 = coup->lig_case2;
		strcpy(liste_coups->tab_coups[liste_coups->nb_coups].texte_coup, coup->texte_coup);
		liste_coups->nb_coups++;
		
		return 1;
	}

}

/***********************************************************************************************/
void set_coup( t_coup* coup, int col, int lig, int col_dest,
				int lig_dest, int col2, int lig2)
{
	/*on commence par ecrire la string texte_coup a partir des entrees de la fonction, on utilise
	les macros qui convertissent les numero de ligne et colonnes en texte ascii affichable dans
	la console*/
	coup->texte_coup[0] = COL_A_CH(col);
	coup->texte_coup[1] = RAN_A_NO(lig);
	coup->texte_coup[2] = '-';
	coup->texte_coup[3] = COL_A_CH(col_dest);
	coup->texte_coup[4] = RAN_A_NO(lig_dest);
	coup->texte_coup[5] = '\0';

	/*on copie ensuite les valeurs en entree de la fonction a leur position dans
	le *t_coup reçu en parametre*/
	coup->col = col;
	coup->lig = lig;
	coup->col_dest = col_dest;
	coup->lig_dest = lig_dest;
	coup->col_case2 = col2;
	coup->lig_case2 = lig2;
}

/***********************************************************************************************/
void afficher_liste_coups(const t_liste_coups* liste_coups)
{
	/*comme on affiche la liste de coups par colonne, il faut garder le nombre total de coups
	affichees (qui persiste entre les changements de colonne) ainsi que le numero de la colonne
	courante)*/
	int total_coups_affiche = 0;
	/*Numéro de colonne*/
	int no_de_colonne = 0; 

	/*il faut commencer par placer le curseur de winconsole au bon endroit*/
	gotoxy(DECALAGE_AFFICHAGE_Y, DECALAGE_AFFICHAGE_X);
	
	/*on affiche ensuite le nombre de coup total contenu dans la liste*/
	printf("%d coups possibles", liste_coups->nb_coups);

	/*on affiche les colones de talle TAILLE_COLONNE_AFFICHAGE une a la fois et on continue
	tant qu'on a pas affiche tous les coups de la liste*/
	while (total_coups_affiche < liste_coups->nb_coups)
	{
		for (int i = 0; i < TAILLE_COLONNE_AFFICHAGE; i++)
		{
			/*si on a plus de line a afficher, on sort de la boucle for et aussi de la boucle
			while, car on est arrive a la fin de la liste et que la condition de fin pour la
			boucle while est la meme qu'ici*/
			if (total_coups_affiche >= liste_coups->nb_coups)
				break;

			/*on commence par deplacer le curseur de la console vers le debut de la prochaine
			ligne a ecrire*/
			gotoxy(	DECALAGE_AFFICHAGE_Y + 
						(DISTANCE_ENTRE_COLONNES *no_de_colonne),
					DECALAGE_AFFICHAGE_X + i + 1);
			
			/*on affiche ensuite directement la string contenue dans la liste*/
			printf("%s", liste_coups->tab_coups[total_coups_affiche].texte_coup);

			/*si la ligne de la case 2 du coup n'est pas POS_VIDE, on doit egalement l'afficher
			mais entre parentheses, il n'est necessaire de verifier qu'une seule valeur car si la
			ligne est a POS_VIDE, la colonne le sera forcement aussi*/
			if (liste_coups->tab_coups[total_coups_affiche].lig_case2 != POS_VIDE)
				printf(" (%c%c)",
					COL_A_CH(liste_coups->tab_coups[total_coups_affiche].col_case2),
					RAN_A_NO(liste_coups->tab_coups[total_coups_affiche].lig_case2));

			/*on passe ensuite au prochain coup dans la liste (ou on sort des boucles si on est
			a la fin)*/
			total_coups_affiche++;
		}
		/*une fois la colonne pleine (a une longueur de TAILLE_COLONNE_AFFICHAGE) on passe a la
		suivante*/
		no_de_colonne++;
	}
}

