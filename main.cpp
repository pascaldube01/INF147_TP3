/*===========================================================*/
/* 	INF147 - Travail Pratique #2                             */
/*===========================================================*/
//Par: Simon Des-Alliers, Victor Poulin et Pascal Dubé
//Date de création : 12 février 2024
//Groupe : 01
//Description: Programme principal permettant de simuler un 
//             jeu d'échec non-intelligent entre l'ordinateur
//             et l'humain pour le projet 2 dans le cadre du 
//             cours INF147.
// 
//Présenté à: Éric Thé
/*=========================================================*/

#define _CRT_SECURE_NO_WARNINGS 

/*=========================================================*/
/*                 LES LIBRAIRIES                          */
/*=========================================================*/

#include <stdio.h>
#include <stdlib.h>
#include "liste_coup.hpp"
#include "grille_echecs.hpp"
#include "affichage.hpp"
#include <assert.h>
#include "SOURISLIB.h"
#include "utilitaire_affichage.h"
#include "winBGIm.h"

/*=========================================================*/
/*                  LES CONSTANTES                         */
/*=========================================================*/

#define FICHIER_IMAGES "imagesBMP.bin"


/*activation du main de test pour verifier le bon fonctionnement de toutes les fonctions du module
liste_coup.c*/
#define TEST_MODULE_LISTE_COUP 0

#define TAILLE_MAX_TEST 80

/*test pour la fonction jouer_coup et l'affichage*/
#define TEST_JOUER_COUP 0

/*test pour les fonctions de l'affichage graphique*/
#define TEST_AFFICHAGE_GRAPH 1

/*activation du main pour faire rouler le programme principal en mode console */
#define JOUER_UNE_PARTIE_TERMINAL 0

/*=========================================================*/
/*                  PROGRAMME DE TESTS                     */
/*=========================================================*/

#if TEST_AFFICHAGE_GRAPH == 1
int main()
{
	t_saisie succes_choix_case = RESET;
	int succes_lire_images = 0;
	int lig_recu = 0;
	int col_recu = 0;

	t_etat_jeu etat_jeu;

	init_graphe();

	/*initialisation de l'etat du jeu (aux echecs le joueur blanc est toujours le premier a
	jouer)*/
	init_jeu(&etat_jeu, BLANCS);
		
	succes_lire_images = lire_images(FICHIER_IMAGES);
	if (succes_lire_images == 0)
	{
		printf("erreur lors de l'ouverture du fichier images");
		return EXIT_FAILURE;
	}
	printf("fichier images ouvert avec succes\n\n");

	afficher_grille(&etat_jeu);

	/*test de choix_case*/
	printf("choisisez une case sur le plateau de jeu avec la souris");
	
	succes_choix_case =  choix_case(&col_recu, &lig_recu);
	printf("\ncase choisie : %d, %d, ", lig_recu, col_recu);




	detruire_images();
	detruire_grille(etat_jeu.grille_jeu);

	printf("\n\nle programme de test s'est execute correctement");
	system("pause");
	return EXIT_SUCCESS;
}
#endif


#if TEST_MODULE_LISTE_COUP == 1
int main()
{
	/*pour le test, on a besoin de creer une liste de coup*/
	t_liste_coups liste_coups;
	int compteur = TAILLE_MAX_TEST;
	/*on cree des variables pour des strings car certaines fonctions requerent des pointeurs*/
	char string_test_faux[6] = "faux" ;
	char string_test_case[6] = "b7-c6";

	init_liste_coups(&liste_coups);

	/*on cree une variable test_coup pour pouvoir tester les fonctions set_coup et ajouter_coup*/
	t_coup* test_coup = (t_coup*) malloc(sizeof(t_coup));
	if (test_coup == NULL)
	{
		printf("impossible d'allouer test_coup");
		return EXIT_FAILURE;
	}

	/*affichage du message qui indique que le programme fait seulement un test ainsi que les
	instructions pour desactiver ce dernier*/
	printf("main de test pour le module liste_coup.c actif\n"
		"s'il s'agit d'une operation non desiree, verifier l'etat de la "
		"constante TEST_MODULE_LISTE_COUP dans main.c\n\n\n");

	/*test des macros qui permettent de convertir les positions dans le tableau de jeu en valeur
	de rangee et colonnes que le joueur peut comprendre et qui seront affichees a l'ecran*/
	printf("test des macros de conversion d'indexe de tableau vers texte ASCII");
	for (int i = 0; i < TAILLE; i++)
	{
		printf("\nvaleur rangee/colonne : %d ", i);
		printf("colonne %c ", COL_A_CH(i));
		printf("rangee %c", RAN_A_NO(i));
	}

	/*on fait un test de set_coup avec la variable declaree plus haut, noter que la fonction prend
	normalement un pointeur (inclus dans le type t_liste_coup) mais pour le test, nous envoyons
	simplement l'addresse de la variable declaree plus haut. nous utilisons egalement les valeurs 
	1 1 2 2 et 3 3 purement pour le test*/
	set_coup(test_coup, 1, 1, 2, 2, 3, 3);


	/*on teste maintenant la fonction ajotuer_coup en entrant test_coup dans liste_coups autant de
	fois que possible. une fois toutes les cases de coups pleines, la fonction retourne une erreur
	ce qui arrete la boucle, on teste par le fait meme get_nb_coups*/
	while (compteur) {
		ajouter_coup(&liste_coups, test_coup);
		compteur--;
	}

	printf("\n\napres avoir rempli la liste de coup, on a %d coups", get_nb_coups(&liste_coups));


	/*le premier test pour valider_coup cherche une valeur qui n'existe pas*/
	printf("\n\n\ntestde valider_coup");
	if (valider_coup(&liste_coups, string_test_faux, test_coup) == 0)
		printf("\nSUCCES : valeur inexistante introuvable");
	else
		printf("\nECHEC :  valeur inexistante trouvee");

	/*le deuxieme test recherche une valeur qui existe*/
	if (valider_coup(&liste_coups, string_test_case, test_coup))
		printf("\nSUCCES : valeur existante trouvable");
	else
		printf("\nECHEC :  valeur existante introuvable");



	printf("\n\n\ntest de valider_case_dest");
	/*le premier test pour valider_case_dest une valeur inexistante*/
	if(valider_case_dest(&liste_coups, 1, 1) == 0)
		printf("\nSUCCES : valeur inexistante introuvable");
	else
		printf("\nECHEC :  valeur inexistante trouvee");

	/*le deuxieme test pour valider_case dest est une valeur existante*/
	if (valider_case_dest(&liste_coups, 2, 2))
		printf("\nSUCCES : valeur existante trouvable\n\n");
	else
		printf("\nECHEC :  valeur existante introuvable\n\n");

	printf("test d'affichage des coups possible"
		   "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	afficher_liste_coups(&liste_coups);
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");

	/*pour vider la liste de coup, il suffit de remettre le compteur a 0*/
	vider_liste_coups(&liste_coups);
	printf("\n\napres avoir vide la liste de coup, on a %d coups, il en faut 0\n\n"
			, get_nb_coups(&liste_coups));

	/*une fois le programme termine, il faut liberer la memoire qui etait
	allouee pour la liste de coup*/
	detruire_liste_coups(&liste_coups);

	//le programme s'est termine correctement
	free(test_coup);
	return EXIT_SUCCESS;
}
#endif
#if (TEST_JOUER_COUP)
int main()
{
	printf("FONCITON DE TEST DE LA FONCTION JOUER_COUP ACTIF\n"
		"verifiez l'etat de la constante TEST_JOUER_COUP "
		"s'il s'agit d'une operation non desiree le jeu jouera "
		"seul le premier coup disponible jusqu'a arret du "
		"programme\n\n");

	system("pause");
	jouer_coup(&etat_jeu, &liste_coups.tab_coups[0]);
}
#endif

/*=========================================================*/
/*                  PROGRAMME PRINCIPAL                    */
/*=========================================================*/

#if JOUER_UNE_PARTIE_TERMINAL == 1
int main()
{
	t_piece capture = VIDE;  //Représente la variable pour sortir de la boucle
	t_coup coup;			 //Représente le coup du joueur actuel 
	/*la variable etat_jeu sert a contenir l'etat du jeu courant (permission pour le roque,
	grille de jeu et joueur courant)*/
	t_etat_jeu etat_jeu;

	/*initialisation de l'etat du jeu (aux echecs le joueur blanc est toujours le premier a
	jouer)*/
	init_jeu(&etat_jeu, BLANCS);

	/*la liste de coup, etant une structure, elle doit etre initialisee dans la fonction
	init_liste_coup (c'est fait juste apres)*/
	t_liste_coups liste_coups;

	//initialisation de la liste de coup (mise a 0 et allocation du pointeur)
	init_liste_coups(&liste_coups);

	//Boucle principale
	do {
		/*une fois initialisé, on affiche le plateau de jeu, la liste de coups et on deplace le
		curseur de WinConsole dans le bas pour pouvoir voir la liste de coup*/
		afficher_jeu(get_grille_jeu(&etat_jeu), get_joueur(&etat_jeu));
		
		/*Génération de la liste de coups possibles selon l'état du jeu*/
		generer_liste_coups(&etat_jeu, &liste_coups, verif_roque(&etat_jeu));
		
		/*On affiche la liste des coups possibles à l'écran*/
		gotoxy(0, 20);
		afficher_liste_coups(&liste_coups);

		//Si le joueur est blanc (humain), on saisit son choix de coup
		if (get_joueur(&etat_jeu) == BLANCS)
		{
			/*On conserve les données du coup entré par l'utilisateur*/
			coup = lire_coup_joueur(&liste_coups);
			//si l'utilisateur souhaite terminer la partie, alors l'utilisateur aura écrit "xx"
			if (coup.col == POS_VIDE)
			{
				//On affiche que la partie se termine sur l'écran 
				gotoxy(DECALAGE_X, DECALAGE_Y + 16);
				clreol();
				
				/*on affiche le message de fin de partie, comme le joueur blanc est le seul
				qui peut abandonner (l'ordi peut pas), on a pas besoin de verifier de quel
				joueur il s'agit*/
				
				printf("Le joueur blanc abandonne\n");

				/*On enleve le message disant de taper 'xx' pour quitter, car le joueur a
				deja quitte*/
				gotoxy(DECALAGE_X, DECALAGE_Y + 17);
				clreol();
				
				/*On détermine que la capture correspond au roi blanc pour sortir de la
				boucle et donc ne pas entrer dans le if qui suit*/
				capture = ROI_B;
			}
		}
		//Si le joueur est noir (ordi), on choisit son coup de manière aléatoire
		else
			coup = choix_coup_ordi(&liste_coups);
		
		/*Si l'utilisateur à rentré le message de fin de partie, 
		on doit sortir de la boucle et ne pas exécuter les actions suivantes*/
		if (capture != ROI_B)
		{
			afficher_coup(&etat_jeu, &coup);
			/*Exécution du coup sur la grille et assignation de la pièce capturé lors de
			l'exécution du coup*/
			capture = jouer_coup(&etat_jeu, &coup);
			/*Si la pièce capturé est le roi de l'autre joueur, alors le joueur a gagne la partie*/
			if (capture == ROI_N + INVERSER_JOUEUR(etat_jeu.joueur))
			{
				textbackground(BLACK);
				gagnant_jeu(&etat_jeu);
			}
			/*On modifie le joueur pour le prochain joueur à jouer*/
			set_joueur(&etat_jeu, INVERSER_JOUEUR(etat_jeu.joueur));
			/*On remet la liste de coups à 0 */
			liste_coups.nb_noeuds = 0;
			/*On répète la boucle jusqu'à temps que le joueur humain arrête la partie, ou qu'un
			roi est capturé*/
		}
	} while (capture != ROI_B && capture != ROI_N);
	
	/*une fois le programme termine, il faut liberer la memoire qui etait allouee pout la liste
	de coup et pour la grille*/
	detruire_liste_coups(&liste_coups);
	detruire_grille(etat_jeu.grille_jeu);

	printf("\n\n");
	
	/*On garde la console*/
	system("pause");
	
	//le programme s'est termine correctement
	return EXIT_SUCCESS;
}
#endif

