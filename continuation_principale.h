#ifndef CP_H
#define CP_H 1

#define _CRT_SECURE_NO_WARNINGS 

/*on en a besoin pour malloc et free*/
#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include<string.h>

typedef char t_texte_coup[6];       //pour retenir un titre de coup (eg. "a2-a3")
typedef t_texte_coup** t_table_CP;  //tableau 2D dynamique de la cont. principale

/*=========================================================*/
/*                  LES PROTOTYPES                         */
/*=========================================================*/

/************************************************************************************************
    OBJECTIF :  Crée et retourne un tableau dynamique triangulaire inversé de dimension
                ("taille" x "taille")/2

    PARAMETRES : La taille de la ligne de la matrice

    SORTIES :	 tableau 2D dynamique de la cont. principale

    écrit par Pascal Dubé, Victor Poulin et Simon Des-Alliers
***********************************************************************************************/
t_table_CP creer_table_CP(int taille);

/************************************************************************************************
    OBJECTIF : Libère (free) le tableau dynamique de la continuation principale.
               Le nombre de lignes à détruire est donné par la "taille" reçue.

    PARAMETRES : La taille correspond aux nombres de lignes à détruire,
                 le tableau dynamique de la continuation principale.

    SORTIES :	 void (Ne retourne rien)

    écrit par Pascal Dubé, Victor Poulin et Simon Des-Alliers
***********************************************************************************************/
void detruire_table_CP(t_table_CP tab_2d, int taille);

/************************************************************************************************
    OBJECTIF : Ajoute un nouvel élément "texte_coup" à la continuation principale.
               Si nécessaire, les valeurs des niveaux suivants seront copiées au même 
               niveau "niv" que l'ajout.

    PARAMETRES : tab_CP  - tableau triangulaire de la continuation principale.
                 niv     - niveau actuel (la ligne) de l'ajout.
                 max_niv - la taille maximale du tableau.
                 texte_coup - le texte du coup à ajouter au tableau.

    SORTIES :	 void (Ne retourne rien)

    écrit par Pascal Dubé, Victor Poulin et Simon Des-Alliers
***********************************************************************************************/
void mise_a_jour_CP(t_table_CP tab_CP, int niv, int max_niv,
    t_texte_coup texte_coup);

/************************************************************************************************
    OBJECTIF : Imprime la première ligne du tableau "tab_CP" de droite à gauche dans la
               console texte. La largeur de la ligne est donnée avec « max_niveau ».

    PARAMETRES : le tableau tab_CP et la largeur de la ligne

    SORTIES :	 void (Ne retourne rien)

    écrit par Pascal Dubé, Victor Poulin et Simon Des-Alliers
***********************************************************************************************/
void imprimer_table_CP(t_table_CP tab_CP, int max_niveau, FILE * log_file);

#endif
