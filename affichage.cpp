/***************************************************************************************/
/*  AFFICHAGE.C                                                                        */
/*  Auteurs: Victor Poulin, Pascal Dube et Simon Des-Alliers                           */
/*  Date: 14 février 2024                                                              */
/*                                                                                     */
/* Ce module gère l'affichage de la grille d'échec (pièces, couleurs, etc.)            */
/*                                                                                     */
/*Liste des fonctions:  void afficher_jeu(const t_grille grille_jeu, int joueur)       */
/*                      void afficher_piece(int piece_a_afficher)                      */
/*                      void changer_couleur_arriere_plan(int pair_impair)             */
/*                      void afficher_joueur(int joueur)                               */
/*                      t_coup lire_coup_joueur(const t_liste_coups* liste_coups)      */
/*                      void afficher_coup(const t_etat_jeu* jeu, const t_coup* coup)  */
/*                      t_coup  choix_coup_ordi(const t_liste_coups liste)             */
/*                      void gagnant_jeu(const t_etat_jeu* jeu)                        */
/***************************************************************************************/

#define _CRT_SECURE_NO_WARNINGS

/*=========================================================*/
/*                 LES LIBRAIRIES                          */
/*=========================================================*/

#include "affichage.hpp"

/*=========================================================*/
/*                  LES CONSTANTES                         */
/*=========================================================*/

#define VALEUR_DEPART 0  //Valeur permettant d'initialiser le générateur
#define FIN_PARTIE  "xx" //String qui signifie que le joueur souhaite abandonner

//constantes ascii pour passer des pièces de la grille à des codes ascii
/*les valeurs à afficher pour les pièces données dans l'énoncé présume que le terminal utilisé
supporte les codes ANSI par défaut, ce qui semble faux dans notre cas (peu importe la raison).
pour assurer une compatibilité maximale, nous avons décidé d'utiliser des symboles alphabétiques.
P = pion, R = tour, C = cavalier, B = fou, Q = dame et K = roi */
const unsigned char CH_PIECES[9] = { ' ', 'P', '.', 'R', 'C', 'B', 'Q', 'K', '_'};

/*=========================================================*/
/*                  LES FONCTIONS                          */
/*=========================================================*/

void afficher_jeu(const t_grille grille_jeu, int joueur)
{
	/*pour s'assurer que le jeu s'affiche correctement, on efface toute la console*/
	clrscr();

	gotoxy(DECALAGE_X, DECALAGE_Y + 17);
	printf("(tapez 'xx' pour quitter le jeu)");

	/*on commence par afficher le texte "grille de jeu" au bon endroit par rapport au décalage de
	la grille de jeu*/
	gotoxy(DECALAGE_X + 1, DECALAGE_Y - 3);
	printf("grille de jeu");

	/*on affiche ensuite le nom des colonnes juste en dessous*/
	gotoxy(DECALAGE_X + 1, DECALAGE_Y - 1);
	printf("A B C D E F G H");

	/*on affiche ensuite toutes les cases et leurs pieces respectives. La premiere boucle for
	compte les rangees et la deuxième compte les colonnes*/
	for (int rangee = 0; rangee < TAILLE; rangee++)
	{
		/*pour chaque rangee, on affiche d'abord son numero de rangee juste avant celle-ci*/
		gotoxy(DECALAGE_X - 2, DECALAGE_Y + rangee);
		printf("%d", TAILLE - rangee);

		/*on affiche ensuite chaque colonne de la rangee*/
		for (int colonne = 0; colonne < TAILLE; colonne++)
		{
			/*la couleur de la case plan dépend uniquement de la paritee du numero de celle ci. On
			peut trouver cette information en effectuant un modulo 2 sur la somme du numero de
			colonne et de rangee*/
			changer_couleur_arriere_plan((colonne + rangee) % 2);

			/*on va ensuite à la position de la piece (le no de colonne est multiplie par deux, car
			on ecrit deux caracteres lors du printf pour que la grille de jeu ait un aspect carre)
			et on affiche le caractere ASCII de la piece*/
			gotoxy((colonne * 2) + DECALAGE_X, rangee + DECALAGE_Y);
			afficher_piece(grille_jeu[rangee][colonne]);
			
		}
		/*on remet ensuite la couleur d'arriere plan à BLACK et la couleur du texte à WHITE pour
		ecrire le numéro de rangee (si on refait un tour de boucle) et pour que le reste du
		texte ailleurs dans l'écran de jeu s'affiche normalement (si la boucle est finie)*/
		textcolor(WHITE);
		textbackground(BLACK);
	}

	/*une fois l'affichage de la grille de jeu termine, on affiche quel joueur doit jouer le
	prochain tour*/
	afficher_joueur(joueur);
}

/*****************************************************************************/
void afficher_joueur (int joueur)
{
	/*il faut se mettre en position en dessous du plateau de jeu pour faire le printf*/
	gotoxy(DECALAGE_X, DECALAGE_Y + 10);

	/*on ecrit ensuite de quel joueur il s'agit*/
	if (joueur)
		printf("joueur blanc c'est a vous");
	else
		printf("joueur noir c'est a vous");
}

/*****************************************************************************/
void changer_couleur_arriere_plan(int pair_impair)
{
	/*si le numero de la case est pair, la couleur sera GREEN au moment du
	printf (qui se trouve dans la fonction afficher_piece()), sinon, la couleur
	sera LIGHTGREEN*/
	switch (pair_impair) {
	case 0:
		textbackground(GREEN);
		break;
	case 1:
		textbackground(LIGHTGREEN);
		break;
	}
}

/*****************************************************************************/
void afficher_piece(int piece_a_afficher)
{
	/*il faut s'assurer d'afficher la bonne couleur pour la bonne piece et
	comme la seule difference entre les blancs et les noirs est que les blancs
	ont le bit 8 allume, on peut simplement verifier ce bit en verifiant si
	la piece à afficher est plus grande que 8. il faut egalement considerer que
	l'underscore de VIDE_EP est jaune. comme VIDE_EP est plus grand que 8 on
	teste cette condition avant tout le reste*/
	if (piece_a_afficher == VIDE_EP)
		textcolor(YELLOW);
	else if (piece_a_afficher >= BLANCS)
		textcolor(WHITE);
	else
		textcolor(BLACK);

	/*une fois la couleur choisie, on peut se servir de printf pour afficher
	le caractere CH_PIECE qui correspond à notre piece. Comme la couleur est
	deja selectionnee, il faut eviter de la compter sinon on risque d'avoir
	une valeur en dehors de CH_PIECE, on fait donc modulo BLANCS (modulo 8)
	pour regler ce problème (et comme c'est la seule difference entre les
	pièces BLANCS et NOIR on a pas besoin d'avoir deux fois le code ASCII dans
	CH_PIECES). il faut aussi ajouter un point si la tour n'a pas bougee
	(indication pour le roque) et comme TOURI_N est deja le caractere ascii
	d'un point (et qu'aucune autre piece n'utilise le point), on peut juste
	ajouter le R (pour rook en notation algebrique) avant le point (car
	VIDE_EP est '.' pas 'R')*/
	if (piece_a_afficher == VIDE_EP)
		printf("%c ", CH_PIECES[piece_a_afficher]);
	else if(piece_a_afficher % BLANCS != TOURI_N)
		printf("%c ", CH_PIECES[piece_a_afficher % BLANCS]);
	else
		printf("R%c", CH_PIECES[piece_a_afficher % BLANCS]);
}

/*****************************************************************************/
t_coup lire_coup_joueur(t_liste_coups* liste_coups)
{
	char coup_depart[6] = { 0 };  //Le coup de depart saisit par le joueur
	char coup_arrivee[3] = { 0 }; //Le coup d'arrivee saisit par le joueur
	t_coup coup = {0};            //On crée un nouveau coup
	int flag_coup_valide = 0;     //Flag permettant de savoir si le coup est valide
	int init = 0;                 //Compteur qui permet d'afficher un message d'erreur

	//on demande le coup au joueur et on s'assure qu'il écrit juste 5 caractères
	do {
		//On met le coup de depart a 0
		for (int i = 0; i < 6; i++)
			coup_depart[i] = 0;
		//On affiche un message d'erreur si ça fait plus d'un coup qu'on demande
		if (init)
		{
			gotoxy(DECALAGE_X, DECALAGE_Y + 16);
			clreol();
			printf("ERREUR! Coup non-permis, recommencez..");

			//On attend 2 secondes avant de re-demander un coup
			delay(2000);
		}

		//On demande la case de depart
		gotoxy(DECALAGE_X, DECALAGE_Y + 16);
		clreol();
		printf("Case de depart ? ");
		scanf("%2s", coup_depart);

		/*avant de rechercher un coup dans la liste, on verifie si le joueur veut quitter*/
		if (!strcmp(coup_depart, FIN_PARTIE))
		{
			/*On cree un coup vide pour signaler au main que le joueur veut quitter la partie*/
			set_coup(&coup, POS_VIDE, POS_VIDE, POS_VIDE, POS_VIDE, POS_VIDE, POS_VIDE);
			return coup;
		}

		//On demande la case d'arrivee
		gotoxy(DECALAGE_X, DECALAGE_Y + 16);
		clreol();
		printf("Case d'arrivee ? ");
		scanf("%2s", coup_arrivee);
	
		/*avant de rechercher un coup dans la liste, on verifie si le joueur veut quitter*/
		if (!strcmp(coup_arrivee, FIN_PARTIE))
		{
			/*On cree un coup vide pour signaler au main que le joueur veut quitter la partie*/
			set_coup(&coup, POS_VIDE, POS_VIDE, POS_VIDE, POS_VIDE, POS_VIDE, POS_VIDE);
			return coup;
		}

		//On incremente le compteur
		init++;

		//On ajoute le tiret
		coup_depart[2] = '-';

		//On concatène les deux cases
		strcat(coup_depart, coup_arrivee);

		/*si le joueur ne desire pas quitter, on verifie si son coup est possible*/
		flag_coup_valide = valider_coup(liste_coups, coup_depart, &coup);

		//On vide la mémoire tampon de scanf
		FFLUSH()
	} while (!flag_coup_valide);
	
	return coup;
}

/*****************************************************************************/
void afficher_coup(const t_etat_jeu* jeu, const t_coup* coup) 
{
	t_piece piece_case_source;     //Pièce de la case source
	t_piece piece_case_secondaire; //Pièce à la case secondaire
	int joueur = get_joueur(jeu);  //Joueur actuel
	
	/*On initialise la valeur de la piece secondaire à PION_B pour s'assurer de ne pas rentrer
	dans les conditions de l'affichage de tous cas sauf pour le roque*/
	piece_case_secondaire = PION_B;

	/*On initialise la valeur de la piece case_source*/
	piece_case_source = get_piece_case(jeu, coup->col, coup->lig);

	/*Si le coup possède une case secondaire, alors on met piece_case_secondaire 
	à la valeur de la case secondaire de la grille du jeu*/
	if (coup->col_case2 != POS_VIDE && coup->lig_case2 != POS_VIDE)
		piece_case_secondaire = get_piece_case(jeu, coup->col_case2, coup->lig_case2);

	/*On commence par allez en bas de la grille pour afficher le coup*/
	gotoxy(DECALAGE_X, DECALAGE_Y + 16);
	clreol();
	printf("coup choisi : %s", coup->texte_coup);

	/*On va à la case source sur l'écran*/
	gotoxy((coup->col * 2) + DECALAGE_X, coup->lig + DECALAGE_Y);
	/*Ensuite on affiche la case en bleu cyan*/
	textbackground(CYAN);
	printf("  ");

	/*Si on fait le roque du roi */
	if (piece_case_secondaire == TOURI_N + joueur)
	{
		gotoxy((coup->col_case2 * 2) + DECALAGE_X, coup->lig_case2 + DECALAGE_Y);
		printf("  ");
	}

	/*On prend un délai de 500ms*/
	delay(500);

	/*On remet la case source dans sa couleur d'origine*/
	changer_couleur_arriere_plan((coup->col + coup->lig) % 2);
	gotoxy((coup->col * 2) + DECALAGE_X, coup->lig + DECALAGE_Y);
	printf("  ");

	/*Si on fait le roque du roi, on remet l'arrière-plan de la case initiale de la TOUR
	dans sa couleur d'origine */
	if (piece_case_secondaire == TOURI_N + joueur)
	{
		changer_couleur_arriere_plan((coup->col_case2 + coup->lig_case2) % 2);
		gotoxy((coup->col_case2 * 2) + DECALAGE_X, coup->lig_case2 + DECALAGE_Y);
		printf("  ");
	}

	/*On va à la case destination sur l'écran*/
	gotoxy((coup->col_dest * 2) + DECALAGE_X, coup->lig_dest + DECALAGE_Y);

	/*On affiche la pièce avec un fond d'écran bleu cyan pendant 500 ms*/
	textbackground(CYAN);
	afficher_piece(piece_case_source);

	/*Si c'est un pion et qu'on avance de deux cases, on doit montrer la case secondaire en cyan*/
	if (piece_case_secondaire == VIDE)
	{
		gotoxy((coup->col_case2 * 2) + DECALAGE_X, coup->lig_case2 + DECALAGE_Y);
		afficher_piece(VIDE_EP);
	}

	/*Si on fait le roque du roi */
	if (piece_case_secondaire == TOURI_N + joueur)
	{
		/*Si on fait le petit roque*/
		if (coup->col_case2 > coup->col_dest)
		{
			/*TOUR est à gauche du roi*/
			gotoxy(((coup->col_dest - 1) * 2) + DECALAGE_X, coup->lig_dest + DECALAGE_Y);
			afficher_piece(TOUR_N + joueur);
		}

		/*Si on fait le grand roque*/
		if (coup->col_case2 < coup->col_dest)
		{
			/*TOUR est à droite du roi*/
			gotoxy(((coup->col_dest + 1) * 2) + DECALAGE_X, coup->lig_dest + DECALAGE_Y);
			afficher_piece(TOUR_N + joueur);
		}
	}

	/*On prend un délai de 500ms*/
	delay(500);

	/*Si le joueur est les noirs, on conserve le fond d'écran bleu pendant 3 secondes de plus*/
	if (jeu->joueur == NOIRS)
		delay(3000);

	/*Ensuite, on remet la couleur du fond d'écran de la case pièce destination dans sa couleur
	d'origine et on remet la pièce dans cette case*/
	changer_couleur_arriere_plan((coup->col_dest + coup->lig_dest) % 2);
	gotoxy((coup->col_dest * 2) + DECALAGE_X, coup->lig_dest + DECALAGE_Y);
	afficher_piece(piece_case_source);

	/*Si c'est un pion et qu'on avance de deux cases, on doit remettre la couleur du fond d'écran
	de la case intermédiaire dans sa couleur d'origine et on remet VIDE_EP dans cette case*/
	if (piece_case_secondaire == VIDE)
	{
		changer_couleur_arriere_plan((coup->col_case2 + coup->lig_case2) % 2);
		gotoxy((coup->col_case2 * 2) + DECALAGE_X, coup->lig_case2 + DECALAGE_Y);
		afficher_piece(VIDE_EP);
	}

	/*Si c'est le roque du roi, on doit remettre la couleur du fond d'écran 
	de la case destination de la tour dans sa couleur d'origine */
	if (piece_case_secondaire == TOURI_N + joueur)
	{
		/*Si on fait le petit roque*/
		if (coup->col_case2 > coup->col_dest)
		{
			/********************************TOUR est a gauche du roi***************************/
			changer_couleur_arriere_plan(((coup->col_dest - 1) + coup->lig_dest) % 2);
			gotoxy(((coup->col_dest - 1) * 2) + DECALAGE_X, coup->lig_dest + DECALAGE_Y);
			afficher_piece(TOUR_N + joueur);
		}
		/*Si on fait le grand roque*/
		if (coup->col_case2 < coup->col_dest)
		{
			/********************************TOUR est a droite du roi***************************/
			changer_couleur_arriere_plan(((coup->col_dest + 1) + (coup->lig_dest)) % 2);
			gotoxy(((coup->col_dest + 1) * 2) + DECALAGE_X, coup->lig_dest + DECALAGE_Y);
			afficher_piece(TOUR_N + joueur);
		}
	}
}

/*****************************************************************************/
t_coup  choix_coup_ordi(const t_liste_coups liste)
{
	int coup_aleatoire; //Représente la coup choisit aléatoirement par le générateur mtwister

	//On initialise le générateur pseudo-aléatoire
	mt_srand(VALEUR_DEPART);

	//On veut prendre un coup aléatoire dans la liste, 
	//Le nombre doit donc être entre 0 et le nombre de coups possible -1.
	coup_aleatoire = mt_randU(liste.nb_noeuds);

	//On retourne un coup du tableau aléatoire
	return liste.tab_coups[coup_aleatoire];
}

/*****************************************************************************/
void gagnant_jeu(const t_etat_jeu* jeu) 
{
	//On clear les deux lignes a la fin de la console
	gotoxy(DECALAGE_X, DECALAGE_Y + 16);
	clreol();
	gotoxy(DECALAGE_X, DECALAGE_Y + 17);
	clreol();

	//On affiche le gagnant (soit le blanc ou le noir)
	switch (jeu->joueur)
	{
	case NOIRS:
		printf("La partie est terminee, le gagnant est le joueur noir.");
		break;
	case BLANCS:
		printf("La partie est terminee, le gagnant est le joueur blanc.");
		break;
	}
}

