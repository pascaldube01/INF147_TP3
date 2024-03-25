/*******************************************************************************/
/*  UTILITAIRE_AFFICHAGE.H                                                     */
/*  Module utilitaire qui permet d'ouvrir le mode graphique, d'afficher les    */
/*  cases d'une grille, des messages et des boutons en mode graphique avec le  */
/*  module d'interface graphique "winBGim.h".                                  */
/*                                                                             */
/*  Conception : Pierre Bélisle, Eric Thé                                      */
/*                                                                             */
/*  *** NOTE IMPORTANTE POUR LA COMPILATION AVEC VISUAL_STUDIO ***             */
/*                                                                             */
/*  Afin de compiler ce fichier correctement dans Visual-Studio effectuez les  */
/*  étapes suivantes :                                                         */
/*  - aller dans le menu "Projet", commande "Propriétés de projetTP3" (Alt-F7) */
/*                                          (selon VOTRE nom actuel de projet) */
/*  - dans le menu de gauche de la boite de dialogue, choisir l'option         */
/*    "Propriétés de configuration/Paramètres avancés"                         */
/*  - dans la liste de paramètres affichée à droite, choisir la catégorie      */
/*    "Jeu de caratères"                                                       */
/*  - choisir l'option "Utiliser le jeu de caractères multioctet (MBCS)"       */
/*  - cliquer sur "Appliquer", ensuite "OK", et re-générer la solution.        */
/*******************************************************************************/

#ifndef _UTIL_AFF_H
#define _UTIL_AFF_H  1

//La longueur des côtés des pièces en pixels
#define TAILLE_BMP  75 

//la taille d'un bouton-commande
#define TAILLEX_BOUTON  200
#define TAILLEY_BOUTON   40

//décalage pour la zone d'affichage de la grille (coin sup. gauche)
#define MARGEX 400
#define MARGEY 50


/*******************************************************************************/
/*                        DÉCLARATION DES FONCTIONS                            */
/*******************************************************************************/
//Permet de créer une fenêtre graphique.
void init_graphe();  

//Permet de dessiner un cadre autour de la zone d'affichage (reçoit les dimensions de la grille)
void init_zone_grille(int dimy, int dimx);

//Permet de dessiner le gabarit vide de la grille avec les titres des colonnes et des rangées
//NOTE: Cette fonction doit toujours être appelée APRÈS l'affichage des 64 cases de la grille
void dessiner_grille_vide();

//Affiche le message reçu au bas de la zone d'affichage (à la ligne 1)
void afficher_message(const char* mess);

//Affiche le score du jeu à droite de la zone d'affichage 
void afficher_score(int val);

//Affiche le texte et la valeur reçue au bas de la zone d'affichage (à la ligne 2).
//Exemple d'appels :  afficher_info("Le nombre de cases est: %d", 64);
void afficher_info(const char * texte, int valeur);    

//Affiche un bouton à la position fournie (lig, col) du coin supérieur-gauche du bouton-commande
void afficher_bouton(int lig, int col, const char* texte);

//Affiche une piece (un bitmap) à la position fournie (lig, col) du coin supérieur-gauche du bitmap
void afficher_piece(int lig, int col, int hauteur, int largeur, unsigned char * image_data);

//Permet d'effacer la zone d'affichage au complet
void effacer_zone_environnement(int dimy, int dimx);

//Permet de faire une pause de "msec" millisecondes à l'écran
void delai_ecran(int msec);

//Retourne 1 si une touche a été pesée, 0 sinon.
int  touche_pesee();

//Pour récupérer un caractère saisi dans la console graphique (ou pour faire une pause-écran).
int  obtenir_touche();

//Permet de fermer la fenêtre graphique
void fermer_mode_graphique();

#endif
