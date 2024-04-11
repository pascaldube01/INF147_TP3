/*****************************************************************************************/
/*  CONTINUATION_PRINCIPALE.C                                                            */
/*  Auteurs: Victor Poulin, Pascal Dube et Simon Des-Alliers                             */
/*  Date: 8 avril 2024                                                                   */
/*                                                                                       */
/* Ce module s'occupe de la gestion de la continuation principale                        */
/*                                                                                       */
/*Liste des fonctions: t_table_CP creer_table_CP(int taille)                             */
/*                     void detruire_table_CP(t_table_CP tab_2d, int taille)             */
/*                     void mise_a_jour_CP(t_table_CP tab_CP, int niv, int max_niv,      */
/*                          t_texte_coup texte_coup)                                     */
/*                     void imprimer_table_CP(t_table_CP tab_CP, int max_niveau)         */
/*****************************************************************************************/

/*=========================================================*/
/*                 LES LIBRAIRIES                          */
/*=========================================================*/

#include "continuation_principale.h"

/*=========================================================*/
/*                  LES FONCTIONS                          */
/*=========================================================*/

/******************************************************************************/
t_table_CP creer_table_CP(int taille)
{
    t_table_CP tab_CP = (t_table_CP)calloc(taille, sizeof(t_table_CP));
	assert(tab_CP);
    for (int i = taille; i != 0; i--)
    {
        tab_CP[taille - i] = (t_texte_coup*)calloc(i, sizeof(t_texte_coup));
		assert(tab_CP[taille - i]);
    }
	
    return tab_CP;
}

/******************************************************************************/
void detruire_table_CP(t_table_CP tab_2d, int taille)
{
	//On detruit chaque tableau de colonne de chaque ligne qui été alloué
	for (int i = 0; (i < taille) && tab_2d[i] != NULL; i++)
	{
		free(tab_2d[i]);
		tab_2d[i] = NULL;
	}

	//On detruit le tableau de pointeurs des lignes
	free(tab_2d);
	tab_2d = NULL;
}

/******************************************************************************/
void mise_a_jour_CP(t_table_CP tab_CP, int niv, int max_niv,
    t_texte_coup texte_coup)
{
	int diag_sec = (max_niv - 1) - niv;
	int col = diag_sec -1;

	strcpy(tab_CP[niv][diag_sec], texte_coup);

	while (col >= 0)
	{
		strcpy(tab_CP[niv][col], tab_CP[niv +1][col]);
		col--;
	}
}

/******************************************************************************/
void imprimer_table_CP(t_table_CP tab_CP, int max_niveau, FILE* log_file)
{
	printf("\n");
	fprintf(log_file, "\n");
	for (int i = 0; i < max_niveau; i++)
	{
		printf("%s->", tab_CP[0][i]);
		fprintf(log_file, "%s->", tab_CP[0][i]);
	}
}