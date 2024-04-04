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

//Le fichier contenant les images
#define FICHIER_IMAGES "imagesBMP.bin"

/*activation du main de test pour verifier le bon fonctionnement de toutes les fonctions du module
liste_coup.c*/
#define TEST_MODULE_LISTE_COUP 0

#define TAILLE_MAX_TEST 80

/*test pour la fonction jouer_coup et l'affichage*/
#define TEST_JOUER_COUP 0

/*test pour les fonctions de l'affichage graphique*/
#define TEST_AFFICHAGE_GRAPH 0

/*activation du main pour faire rouler le programme principal en mode console */
#define JOUER_UNE_PARTIE_TERMINAL 0

/*activation du main pour faire rouler le programme principal en mode graphique */
#define JOUER_UNE_PARTIE_BGI 1

/*=========================================================*/
/*                  PROGRAMME DE TESTS                     */
/*=========================================================*/

#if TEST_AFFICHAGE_GRAPH == 1
int main()
{
	t_saisie succes_choix_case = RESET; //Variable montrant que la fonction choix_case fonctionne
	int succes_lire_images = 0;         //Variable montrant que la fonxtion lire_image fonctionne
	int lig_recu = 0;                   //Ligne envoyée en paramètre de choix_case
	int col_recu = 0;                   //Colonnne envoyée en paramètre de choix_case

	t_etat_jeu etat_jeu;

	init_graphe();

	/*initialisation de l'etat du jeu (aux echecs le joueur blanc est toujours le premier a
	jouer)*/
	init_jeu(&etat_jeu, BLANCS);
		
	succes_lire_images = lire_images(FICHIER_IMAGES);

	//S'il y a une erreur dans la lecture de l'image, on affiche un message d'erreur
	if (succes_lire_images == 0)
	{
		printf("erreur lors de l'ouverture du fichier images");

		//On quitte
		return EXIT_FAILURE;
	}

	//Sinon, on affiche un message de succès pour l'ouverture de l'image
	printf("fichier images ouvert avec succes\n\n");

	/*affichage des boutons*/
	afficher_bouton(POSY_BOUT_QUIT, POSX_BOUT_QUIT, "ABANDONNER");
	afficher_bouton(POSY_BOUT_RESET, POSX_BOUT_RESET, "RECOMMENCER");

	//On affiche la grille
	afficher_grille(&etat_jeu);
	
	/*test de choix_case*/
	printf("choisisez une case sur le plateau de jeu avec la souris");
	
	//On récupère le succès ou bien l'échec de la fonction choix_case
	succes_choix_case =  choix_case(&col_recu, &lig_recu);
	


	switch (succes_choix_case)
	{
	case POS_VALIDE:
		printf("\ncase choisie : %d, %d, ", lig_recu, col_recu);
		break;
	case RESET:
		printf("\n le joueur a clique sur RESET");
		break;
	case QUITTER:
		printf("\n le joueur a clique sur QUITTER");
		break;
	}


	//On détruit les images
	detruire_images();

	//On détruit la grille de jeu
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

#if JOUER_UNE_PARTIE_BGI == 1
int main()
{
	/*piece qui a ete capturee (s'il y en a une), utilise pour terminer le jeu si on capture
	un roi*/
	t_piece capture = VIDE;
	/*coup (complet) qui sera retourne par valider_coup()*/
	t_coup coup;
	/*la variable etat_jeu sert a contenir l'etat du jeu courant (permission pour le roque,
	grille de jeu et joueur courant)*/
	t_etat_jeu etat_jeu;
	/*variables qui contiendront la selection de cases de jeu faites par l'utilisateur on a besoin
	d'un tableau car la deuxieme case est la case de destination*/
	int lig_choisi[2] = { 0 }, col_choisi[2] = { 0 };
	/*contiens la string qui sera genere a partir des selections du joueur afin de pouvoir la
	chercher avec valider_coup()*/
	char coup_input_string[6] = { 0 };
	/*contiens la selection du joueur (boutons ou plateau de jeu)*/
	t_saisie bouton_clique = POS_VALIDE;
	/*indique le succes de la lecture du fichier contenant les bitmaps des pieces*/
	int succes_lire_images = 1;
	/*flag indiquant qu'il faut remettre le jeu a 0 (joueur a clique sur reset)*/
	int flag_reset = 0;
	/*la liste de coup, etant une structure, elle doit etre initialisee dans la fonction
	init_liste_coup*/
	t_liste_coups liste_coups;

	/*ouverture de la fenetre graphique*/
	init_graphe();

	succes_lire_images = lire_images(FICHIER_IMAGES);

	//S'il y a une erreur dans la lecture de l'image, on affiche un message d'erreur
	if (succes_lire_images == 0)
	{
		printf("erreur lors de l'ouverture du fichier images");

		//On quitte
		return EXIT_FAILURE;
	}

	/*affichage des boutons pour reset et quitter*/
	afficher_bouton(POSY_BOUT_QUIT, POSX_BOUT_QUIT, "ABANDONNER");
	afficher_bouton(POSY_BOUT_RESET, POSX_BOUT_RESET, "RECOMMENCER");

	/*boucle de jeu incluant initialisation (si on clique reset, on recommence ici)*/
	do
	{
		/*pour debug*/
		printf("\ninit du jeu");

		/*initialisation de l'etat du jeu (aux echecs le joueur blanc est toujours le premier a
		jouer)*/
		init_jeu(&etat_jeu, BLANCS);

		//initialisation de la liste de coup (mise a 0 et allocation du pointeur)
		init_liste_coups(&liste_coups);

		/*affichage de la grille actuelle*/
		afficher_grille(&etat_jeu);

		do
		{

			/*generation de la liste de coups en partant de la grille actuelle*/
			vider_liste_coups(&liste_coups);
			generer_liste_coups(&etat_jeu, &liste_coups, verif_roque(&etat_jeu));




			/*affichage du joueur courant*/
			if (get_joueur(&etat_jeu) == BLANCS)
			{
				//On demande la case-source au joueur
				afficher_message("BLANCS: Veuillez cliquer sur la case-source");
			}
			else
			{
				afficher_message("Attendez SVP, je réfléchis...");
			}

			/*affichage du nombre de coups possible*/
			afficher_info("%d coups generes", get_nb_coups(&liste_coups));

			if (get_joueur(&etat_jeu))
			{
				/*demande de la case a selectionnée par le joueur*/
				/*comme on a besoin de demander la case de depart et de destination ainsi que de verifier
				si on ne clique pas sur quitter ou reset entre temps, on fait une boucle et on ecrit le
				choix du joueur dans deux tableaux a 2 case (depart et arrivee)*/
				for (int i = 0; i < 2; i++)
				{
					/*demande d'une action du joueur*/
					bouton_clique = choix_case(&col_choisi[i], &lig_choisi[i]);

					if (bouton_clique != RESET && bouton_clique != QUITTER)
					{
						//On demande la case-destination au joueur
						afficher_message("BLANCS: Veuillez cliquer sur la case-destination");
					}

					/*verification de si on a clique sur quitter ou reset*/
					switch (bouton_clique)
					{
						break;
					case RESET: /*remise du jeu a son etat initial*/
						/*on sort de la boucle, comme on ne peut pas utiliser un break pour sortir
						d'une boucle dans un switch case, on met i (la variable du for) a 2 pour
						s'assurer qu'il n'y aura pas unn autre tour*/

						i = 2;

						break;
					case QUITTER: //fin du jeu
						goto fin_du_jeu;
					}

					//Affiche sur la console les cases choisies
					if (!i)
					{
						printf("\nchoix de la case source : %d, %d", lig_choisi[i], col_choisi[i]);
					}
					else
					{
						printf("\nchoix de la case destination : %d, %d", lig_choisi[i], col_choisi[i]);
					}
					
				}


				/*si le bouton clique est RESET, on sort de la boucle et on refait l'init du jeu*/
				if (bouton_clique == RESET)
					break;

				/*pour pouvoir chercher (et valider) le coup entree par l'utilisateur, on doit creer sa string*/
				coup_input_string[0] = COL_A_CH(col_choisi[0]);
				coup_input_string[1] = RAN_A_NO(lig_choisi[0]);
				coup_input_string[2] = '-';
				coup_input_string[3] = COL_A_CH(col_choisi[1]);
				coup_input_string[4] = RAN_A_NO(lig_choisi[1]);
				coup_input_string[5] = '\0';

				/*pour debug*/
				printf("\nstring de coup %s", coup_input_string);

				/*on recherche le coup choisi par le joueur dans la liste, s'il est possible, on le
				joue, sinon, on en demande un autre en retournant en haut de la boucle*/
				if (valider_coup(&liste_coups, coup_input_string, &coup))
				{
					printf("\ncoup valide");
					/*si le coup est valide, on affiche et joue le coup*/
					afficher_coup(get_piece_case(&etat_jeu, col_choisi[0], lig_choisi[0]),
						col_choisi[0], lig_choisi[0],
						get_piece_case(&etat_jeu, col_choisi[1], lig_choisi[1]),
						col_choisi[1], lig_choisi[1]);

					capture = jouer_coup(&etat_jeu, &coup);
				}
				else
				{
					//Si le coup n'est opas valide, on affiche un message d'erreur
					afficher_message("ERREUR! Coup non-permis, recommencez..");

					//On attend 2 secondes avant de re-demander un coup
					delai_ecran(2000);

					//On revient au début de la boucle (sans changer de joueur)
					continue;
				}
			}
			else //tour de l'ordi
			{
				/*si c'est le tour de l'ordi, il joue un coup au hasard, on l'affiche et on le joue*/
				coup = choix_coup_ordi(&liste_coups);
				afficher_coup(get_piece_case(&etat_jeu, coup.col, coup.lig),
					coup.col, coup.lig,
					get_piece_case(&etat_jeu, coup.col_dest, coup.lig_dest),
					coup.col_dest, coup.lig_dest);
				capture = jouer_coup(&etat_jeu, &coup);
			}
			
			/*apres avoir affiche le mouvement de la piece (avec afficher_coup()), on doit
			re-afficher la grille au complet pour pouvoir voir les coups plus complexes
			(roque, promotion et en passant)*/
			afficher_grille(&etat_jeu);

			/*si tout s'est bien passe (le coup est joué) on change de joueur*/
			set_joueur(&etat_jeu, INVERSER_JOUEUR(etat_jeu.joueur));

		} while (capture != ROI_B && capture != ROI_N);

		//Si la pièce capturée est le roi blanc, le joueur noir gagne la partie 
		if (capture == ROI_B)
			afficher_message("le joueur noir gagne, quitter ou reset");
		//Sinon, c'est le joueur blanc qui gagne
		else if (capture == ROI_N)
			afficher_message("le joueur blanc gagne quitter ou reset");
		//Sinon, le joueur blanc abandonne ou bien quitte
		else
			afficher_message("le joueur blanc abandonne quitter ou reset");

		while (bouton_clique != QUITTER && bouton_clique != RESET)
			bouton_clique = choix_case(&col_choisi[0], &lig_choisi[0]);
		if (bouton_clique == QUITTER)
			goto fin_du_jeu;

	} while (1);
	/*cette boucle est infinie mais on peut quand meme sortir en cliquant sur le bouton reset*/

	/*comme il faut sortir de plusieurs boucles en meme temps et qu'on peut pas juste faire un
	return (il faut liberer la memoire), on envoie toutes les condition causant la fin du jeu
	a la fin de la fonction main*/
	fin_du_jeu:

	//Si le joueur souhaite quitter, on lui demande d'appuyer sur une touche avant
	afficher_message("Au revoir :-( Appuyer sur une touche pour quitter.");
	printf("\nabandon");
	while (!touche_pesee()){}

	//On détruit les allocations et on ferme le mode graphique
	detruire_liste_coups(&liste_coups);
	detruire_grille(etat_jeu.grille_jeu);
	detruire_images();
	fermer_mode_graphique();
	
	return EXIT_SUCCESS;
}

#endif

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

