/*===========================================================*/
/* 	INF147 - Travail Pratique #3                             */
/*===========================================================*/
//Par: Simon Des-Alliers, Victor Poulin et Pascal Dubé
//Date de création : 11 mars 2024
//Groupe : 01
//Description: Programme principal permettant de simuler un 
//             jeu d'échec intelligent entre l'ordinateur
//             et l'humain pour le projet 3 dans le cadre du 
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
#include <assert.h>

#include "affichage.h"
#include "continuation_principale.h"

/*=========================================================*/
/*                           prototypes                    */
/*=========================================================*/

t_saisie saisir_coup(t_etat_jeu* jeu, t_liste_coups* liste_coups, t_coup* coup);
int min_max(t_etat_jeu* jeu0, t_coup* coup, int niveau, int max_niveau, t_table_CP tab_CP);
void copier_etat_jeu(t_etat_jeu *jeu0, t_etat_jeu *jeu1);

/*=========================================================*/
/*                  LES CONSTANTES                         */
/*=========================================================*/

//Le fichier contenant les images
#define FICHIER_IMAGES "imagesBMP.bin"

/*activation du main de test pour verifier le bon fonctionnement de toutes les fonctions du module
liste_coup.c*/
#define TEST_MODULE_LISTE_COUP 0

#define TAILLE_MAX_TEST 80

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


/*=========================================================*/
/*                  PROGRAMME PRINCIPAL                    */
/*=========================================================*/
 
#if JOUER_UNE_PARTIE_BGI == 1
void faire_un_reset(t_liste_coups* liste_coups, t_etat_jeu* jeu);
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
	/*contiens la selection du joueur (boutons ou plateau de jeu)*/
	t_saisie bouton_clique = POS_VALIDE;
	/*indique le succes de la lecture du fichier contenant les bitmaps des pieces*/
	int succes_lire_images = 1;
	/*flag indiquant qu'il faut remettre le jeu a 0 (joueur a clique sur reset)*/
	int flag_reset = 0;
	/*la liste de coup, etant une structure, elle doit etre initialisee dans la fonction
	init_liste_coup*/
	t_liste_coups liste_coups;
	/*Le score de la grille*/
	int score = 0;
	//Le niveau maximal qu'on souhaite atteindre (4 = intermédiaire; 6 = expert)
	int max_niveau = 0; 
	/*variable qui servira a afficher les coups que l'ordinateur a calcule dans la console*/
	t_table_CP tab_CP = creer_table_CP(6);

	/*on demande le niveaux de difficulte voulu au joueur dans la console*/
	printf("niveaux de difficulte : \n\n 2 - facile\n\n 4 - moyen\n\n 6 - difficile\n\n choix :");
	scanf("%d", &max_niveau);


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

	
	/*pour debug*/
	printf("\ninit du jeu");

	/*initialisation de l'etat du jeu (aux echecs le joueur blanc est toujours le premier a
	jouer)*/
	init_jeu(&etat_jeu, BLANCS);

	//initialisation de la liste de coup (mise a 0 et allocation du pointeur)
	init_liste_coups(&liste_coups);

	/*affichage de la grille actuelle*/
	afficher_grille(&etat_jeu);

	//On initialise l'affichage du score à 0
	afficher_score(score);

	do
	{
		/*generation de la liste de coups en partant de la grille actuelle*/
		
		generer_liste_coups(&etat_jeu, &liste_coups, verif_roque(&etat_jeu));

		/*affichage du nombre de coups possible*/
		afficher_info("%d coups generes", get_nb_coups(&liste_coups));

		if (get_joueur(&etat_jeu))
		{
			/*le message changera une fois la premiere case selectionnee et reviendera si le coup n'est pas valide*/
			afficher_message("BLANCS: Veuillez cliquer sur la case-source");
			/*demande de l'input du joueur*/
			bouton_clique = saisir_coup(&etat_jeu, &liste_coups, &coup);

			/*evaluation de la condition de sortie du jeu par les boutons*/
			if (bouton_clique == RESET)
			{
				/*On fait un reset*/
				faire_un_reset(&liste_coups, &etat_jeu);
				/*generation de la liste de coups en partant de la grille actuelle*/
				generer_liste_coups(&etat_jeu, &liste_coups, verif_roque(&etat_jeu));
				/*affichage du nombre de coups possible*/
				afficher_info("%d coups generes", get_nb_coups(&liste_coups));
				/*demande de l'input du joueur*/
				bouton_clique = saisir_coup(&etat_jeu, &liste_coups, &coup);
			}
			if (bouton_clique == QUITTER)
				capture = ROI_N;
		}
		else //tour de l'ordi
		{
			/*si c'est le tour de l'ordi, il joue un coup au hasard, on l'affiche et on le joue*/
			afficher_message("Attendez SVP, je réfléchis...");
			//coup = choix_coup_ordi(&liste_coups);
			min_max(&etat_jeu, &coup, 2, max_niveau, tab_CP);
			imprimer_table_CP(tab_CP, max_niveau);
		}
		if (capture != ROI_N + INVERSER_JOUEUR(get_joueur(&etat_jeu)))
		{
			/*on affiche et on joue le coup*/
			afficher_coup(get_piece_case(&etat_jeu, coup.col, coup.lig),
				coup.col, coup.lig,
				get_piece_case(&etat_jeu, coup.col_dest, coup.lig_dest),
				coup.col_dest, coup.lig_dest);

			capture = jouer_coup(&etat_jeu, &coup);

			//On met a jour le score de la grille de jeu
			mise_a_jour_score(&etat_jeu, capture);

			//On appel la fonction accesseur pour obtenir le score de la grille mis à jour
			score = get_score_grille(&etat_jeu);

			//On affiche le score sur l'écran
			afficher_score(score);

			/*Si la capture est un roi de l'équipe adverse, alors la partie est terminée*/
			if (capture == ROI_N + INVERSER_JOUEUR(get_joueur(&etat_jeu)))
				afficher_gagnant(get_joueur(&etat_jeu));
			else
			{
				/*apres avoir affiche le mouvement de la piece (avec afficher_coup()), on doit
			re-afficher la grille au complet pour pouvoir voir les coups plus complexes
			(roque, promotion et en passant)*/
				afficher_grille(&etat_jeu);

				/*si tout s'est bien passe (le coup est joué) on change de joueur*/
				set_joueur(&etat_jeu, INVERSER_JOUEUR(get_joueur(&etat_jeu)));
				vider_liste_coups(&liste_coups);
			}
		}
		
	} while (capture != ROI_B && capture != ROI_N);

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

void faire_un_reset(t_liste_coups* liste_coups, t_etat_jeu* jeu)
{
	/*On doit recommencer du début*/
	vider_liste_coups(liste_coups);
	detruire_grille(jeu->grille_jeu);
	/*initialisation de l'etat du jeu (aux echecs le joueur blanc est toujours le premier a
	jouer)*/
	init_jeu(jeu, BLANCS);
	//initialisation de la liste de coup (mise a 0 et allocation du pointeur)
	init_liste_coups(liste_coups);
	/*On affiche la grille nouvellement créer*/
	afficher_grille(jeu);
	/*On affiche un messsage de reset sur le terminal*/
	printf("\nRESET du jeu");
}
#endif

/******************************************************************************/

t_saisie saisir_coup(t_etat_jeu* jeu, t_liste_coups* liste_coups, t_coup* coup)
{
	/*contiendera la string qu'il faudra chercher dans la liste pour valider le coup*/
	char coup_input_string[6] = { 0 };
	/*contiens le bouton qui sera clique par le joueur*/
	t_saisie bouton_clique = POS_VALIDE;
	/*variables qui contiendront la selection de cases de jeu faites par l'utilisateur on a besoin
	d'un tableau car la deuxieme case est la case de destination*/
	int lig_choisi[2] = { 0 }, col_choisi[2] = { 0 };
	/*indique si le coup est valide (pour sortie de la boucle et retourner dans le main)*/
	int coup_valide = 1;

	/*demande de la case a selectionnée par le joueur*/
	/*comme on a besoin de demander la case de depart et de destination ainsi que de verifier
	si on ne clique pas sur quitter ou reset entre temps, on fait une boucle et on ecrit le
	choix du joueur dans deux tableaux a 2 case (depart et arrivee)*/

	while (coup_valide)
	{
		for (int i = 0; i < 2; i++)
		{
			/*demande d'une case au joueur*/
			bouton_clique = choix_case(&col_choisi[i], &lig_choisi[i]);

			if (bouton_clique != RESET && bouton_clique != QUITTER)
			{
				//On demande la case-destination au joueur
				afficher_message("BLANCS: Veuillez cliquer sur la case-destination");
			}

			/*verification de si on a clique sur quitter ou reset, dans ces cas, pas besoin de
			demander une deuxieme case, on retourne cond immediatement dans le main qui va gerer la
			sortie ou le reset du jeu*/
			switch (bouton_clique)
			{
			case RESET:
				return RESET;
			case QUITTER: //fin du jeu
				return QUITTER;
			}

			//Affiche sur la console les cases choisies
			if (!i)
				printf("\nchoix de la case source : %d, %d", lig_choisi[i], col_choisi[i]);
			else
				printf("\nchoix de la case destination : %d, %d", lig_choisi[i], col_choisi[i]);
		}

		/*pour pouvoir chercher le coup avec valider coup, il faut construire sa string*/
		coup_input_string[0] = COL_A_CH(col_choisi[0]);
		coup_input_string[1] = RAN_A_NO(lig_choisi[0]);
		coup_input_string[2] = '-';
		coup_input_string[3] = COL_A_CH(col_choisi[1]);
		coup_input_string[4] = RAN_A_NO(lig_choisi[1]);
		coup_input_string[5] = '\0';

		/*on recherche le coup choisi par le joueur dans la liste, s'il est possible, on le
			joue, sinon, on en demande un autre en retournant en haut de la boucle*/
		if (valider_coup(liste_coups, coup_input_string, coup))
		{
			printf("\ncoup valide");
			coup_valide = 0;
			/*si le coup est valide, on affiche et joue le coup*/
		}
		else //Si le coup n'est opas valide, on affiche un message d'erreur
		{	
			afficher_message("ERREUR! Coup non-permis, recommencez..");
			delai_ecran(1000);
		}
	}

	return POS_VALIDE;
}

/******************************************************************************/

int min_max(t_etat_jeu* jeu0, t_coup* coup, int niveau, int max_niveau, t_table_CP tab_CP)
{
	t_liste_coups liste_coups_ordi;    //Liste de coups des noirs
	t_liste_coups liste_coups_joueur;  //Liste de coups des blancs

	int min;                           //Valeur minimale
	int max;                           //Valeur maximale
	int valeur_grille = 0;             //Valeur grille

	t_coup coupOrdi;                   //Coup joué par l'ordinateur
	t_coup coupJr;                     //Coup joué par l'ordinateur
	t_coup coup_max = { 0 };           //Coup maximal

	t_etat_jeu jeu1;                   //État du jeu après 1 coup
	t_etat_jeu jeu2;                   //État du jeu après 2 coup

	t_piece capture;				   //piece capturee

	/*comme les grilles de jeu sont des double pointeurs, il faut faure une allocation dynamique*/
	jeu1.grille_jeu = creer_grille();
	jeu2.grille_jeu = creer_grille();

	//On initialise les 2 listes pour les noirs et les blancs
	init_liste_coups(&liste_coups_ordi);
	init_liste_coups(&liste_coups_joueur);

	//On génère tous les coups possibles de l'ordinateur à partir de l'état de jeu0
	generer_liste_coups(jeu0, &liste_coups_ordi, verif_roque(jeu0));

	//Une valeur minimale de départ
	max = -999;

	//On remet le pc au début
	replacer_pc_debut(&liste_coups_ordi);

	//Pour tous les coups de l'ordi
	for (int i = 0; i < get_nb_coups(&liste_coups_ordi); i++)
	{
		//On fait une copie de l'état de jeu actuel
		//jeu1.grille_jeu = jeu0->grille_jeu;
		//jeu1.joueur = jeu0->joueur;
		copier_etat_jeu(jeu0, &jeu1);

		//On effectue le coup
		coupOrdi = get_coup_pc(&liste_coups_ordi);

		//On avance le pointeur courant
		avancer_pc(&liste_coups_ordi);
		/*On effectue la mise a jour du score*/
		mise_a_jour_score(&jeu1, jouer_coup(&jeu1, &coupOrdi));
		//Changer de joueur dans l'état de jeu 1
		jeu1.joueur = INVERSER_JOUEUR(jeu1.joueur);
		
		//Génération des coups du joueur à partir du jeu1
		generer_liste_coups(&jeu1, &liste_coups_joueur, verif_roque(&jeu1));


		/*NIVEAU 1: On cherche le meilleur coup possible (le MIN) du 
		joueur si l'ordi joue le coup coupOrdi. Il est à noter que
		plus la valeur est petite, plus le coup du joueur est bon*/

		//Une valeur maximale de départ
		min = 999;

		replacer_pc_debut(&liste_coups_joueur);

		//Pour tous les coups coupJr dans liste_coups_joueur
		for (int j = 0; j < get_nb_coups(&liste_coups_joueur); j++)
		{
			//On fait une copie de l'état de jeu suivant
			copier_etat_jeu(&jeu1, &jeu2);

			//On effectue le coup
			coupJr = get_coup_pc(&liste_coups_joueur);
			capture = jouer_coup(&jeu2, &coupJr);

			//On avance le pointeur courant
			avancer_pc(&liste_coups_joueur);

			//revenir au 1ier joueur dans l’état jeu2 
			jeu2.joueur = INVERSER_JOUEUR(jeu2.joueur);

			//Appel récursif
			if (niveau == max_niveau)
			{
				/* Obtenir la valeur de la grille du jeu 2*/
				mise_a_jour_score(&jeu2, capture);
				valeur_grille = get_score_grille(&jeu2);
			}
			else
			{
				//Effectuer la récursion avec une profondeur plus élevée
				valeur_grille = min_max(&jeu2, coup, niveau + 2, max_niveau, tab_CP);
			}


			if (valeur_grille < min)
			{
				min = valeur_grille;
				mise_a_jour_CP(tab_CP, niveau-1, max_niveau, coupJr.texte_coup);
			}   
		}

	   /* Si le meilleur coup du joueur quand l’ordi a joué le coupOrdi */
	   /* donne un meilleur pointage (max) que le celui du coup maximal */
	   /* jusqu'à date, alors on garde coupOrdi comme coup maximal.     */
		if (min > max)
		{
			max = min;
			coup_max = coupOrdi;
			mise_a_jour_CP(tab_CP, niveau - 2, max_niveau, coupOrdi.texte_coup);
		}

		//On vide la liste du joueur
		vider_liste_coups(&liste_coups_joueur);
	}

	//On vide la liste de l'ordi
	vider_liste_coups(&liste_coups_ordi);

	//On retourne le coup max en référence
	*coup = coup_max;

	/*on doit detruire les grilles de jeu qui ont ete allouees dynamiquement*/
	detruire_grille(jeu1.grille_jeu);
	detruire_grille(jeu2.grille_jeu);

	return max;
}

/******************************************************************************/

void copier_etat_jeu(t_etat_jeu *jeu, t_etat_jeu *jeu_copie)
{
	/*la grille de jeu est un double pointeur (8x8), on copie donc les lignes une a une*/
	for (int i = 0; i < TAILLE_GR; i++)
	{
		memcpy(jeu_copie->grille_jeu[i], jeu->grille_jeu[i], sizeof(t_piece) *8);
	}

	/*le reste sont juste des entiers, on peut les copier directement*/
	jeu_copie->joueur = jeu->joueur;
	jeu_copie->roque_permis[0] = jeu->roque_permis[0];
	jeu_copie->roque_permis[1] = jeu->roque_permis[1];
	jeu_copie->score_grille = jeu->score_grille;
}