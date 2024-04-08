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
    t_table_CP tab_CP = (t_table_CP) malloc(sizeof(taille));
    for (int i = taille; i != 0; i--)
    {
        tab_CP[taille - i] = (t_texte_coup * ) malloc(sizeof(t_texte_coup) * i);
    }
    return tab_CP;
}

/******************************************************************************/
void detruire_table_CP(t_table_CP tab_2d, int taille)
{

}

/******************************************************************************/
void mise_a_jour_CP(t_table_CP tab_CP, int niv, int max_niv,
    t_texte_coup texte_coup)
{

}

/******************************************************************************/
void imprimer_table_CP(t_table_CP tab_CP, int max_niveau)
{

}