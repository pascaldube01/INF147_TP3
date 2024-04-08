/*****************************************************************************************/
/*  GRILLE_ECHECS.C                                                                      */
/*  Auteurs: Victor Poulin, Pascal Dube et Simon Des-Alliers                             */
/*  Date: 14 février 2024                                                                */
/*                                                                                       */
/* Ce module s'occuppe de la gestion de la grille de jeu et de l'etat du jeu.            */
/* Il offre des fonctions permettant d'initialiser le jeu, generer la liste des coups    */
/* valides du jeu et d'effectuer la mise-a-jour de la grille suite a un coup jouee.      */
/*                                                                                       */
/*Liste des fonctions: static int verifier_position_plateau_jeu_valide(int col, int ran) */
/*                     static int ajouter_coup_si_valide(t_etat_jeu *etat_jeu,           */
/*                     t_liste_coups *liste_coups,int lig, int col, int lig_dest,        */
/*					     int col_dest, int pion)                                         */
/*                     static int sens_du_jeu(t_etat_jeu* jeu)                           */
/*                     static int vider_VIDE_EP(t_etat_jeu* jeu)                         */
/*                     static int POS_TOUR(const t_coup* coup)                           */
/*                     void init_jeu(t_etat_jeu* grille_jeu, int joueur_dep)             */
/*                     int  get_joueur(const t_etat_jeu* jeu)                            */
/*                     void set_joueur(t_etat_jeu* jeu, int joueur)                      */
/*                     int** get_grille_jeu(const t_etat_jeu* jeu)                       */
/*                     t_piece get_piece_case(const t_etat_jeu* jeu, int col, int ran)   */
/*                     int set_piece_case(t_etat_jeu* jeu, t_piece piece, int col,       */
/*                       int ran)                                                        */
/*                     int generer_liste_coups(t_etat_jeu* jeu,                          */
/*					      t_liste_coups* liste_coups, int check_roq)                     */
/*                     void initialiser_grille(t_grille grille_jeu)                      */
/*                     void ajouter_coup_pion(t_liste_coups* liste_coups,                */
/*					      t_etat_jeu* etat_jeu, int col, int lig)                        */
/*                     void ajouter_coup_tour(t_liste_coups* liste_coups,                */
/*					      t_etat_jeu* etat_jeu, int col, int lig)                        */
/*                     void ajouter_coup_cavalier(t_liste_coups* liste_coups,            */
/*					      t_etat_jeu* etat_jeu, int col, int lig)                        */
/*                     void ajouter_coup_fou(t_liste_coups* liste_coups,                 */
/*					      t_etat_jeu* etat_jeu, int col, int lig)                        */
/*                     void ajouter_coup_dame(t_liste_coups* liste_coups,                */
/*					      t_etat_jeu* etat_jeu, int col, int lig)                        */
/*                     void ajouter_coup_roi(t_liste_coups* liste_coups,                 */
/*					      t_etat_jeu* etat_jeu, int col, int lig, int check_roq)         */
/*                     void roque_du_roi(t_etat_jeu* jeu, t_liste_coups* liste,          */
/*					      int check_roq)                                                 */
/*                     t_piece jouer_coup(t_etat_jeu* jeu, const t_coup* coup)           */
/*                     int verif_roque(t_etat_jeu* jeu)                                  */
/*                     t_grille creer_grille(void)                                       */
/*                     void detruire_grille(t_grille jeu)                                */
/*                     int verifier_alloc_grille(t_grille jeu)                           */
/*****************************************************************************************/

/*=========================================================*/
/*                  LES CONSTANTES                         */
/*=========================================================*/

#define TESTER_ROI  0		//Permet de tester la pièce du roi seulement
#define TESTER_PION 0		//Permet de tester la pièce du pion seulement
#define TESTER_CAVALIER 0	//Permet de tester la pièce du cavalier seulement
#define TESTER_TOUR 0		//Permet de tester la pièce de la tour seulement
#define TESTER_FOU 0		//Permet de tester la pièce du fou seulement
#define TESTER_ROQUE 0		//Permet de tester la condition du roque du roi
#define NORMAL 1			//Fonctionnement du jeu normal normal (avec toutes les pièces)

const int PTS_PIECES[16] = { 0,  1,  5,  5,  3,  3,  9,  100,   //NOIRS  = points positifs
				             0, -1, -5, -5, -3, -3, -9, -100 }; //BLANCS = points négatifs

/*=========================================================*/
/*                 LES LIBRAIRIES                          */
/*=========================================================*/

#include "test_generer_liste.h"
#include"grille_echecs.h"

/*=========================================================*/
/*                  LES FONCTIONS                          */
/*=========================================================*/

/*************************************************************************************************
	OBJECTIF : Fonction qui verifie si la position (ran, col) est bien sur le plateau,
			   et pas a l'exterieur on retourne true seulement si toutes les valeurs 
			   de positions sont valides. Ce code se repetait souvent dans plusieurs 
			   fonctions, il est maintenant a part dans une fonction static.

	PARAMETRES : col : position colonne a verifier
			   : ran : position rangee a verifier

	SORTIES :	retourne 1 si la position n'est pas valide et 0 si elle l'est et pas l'inverse,
				car elle sert surtout dans les branches et boucles

	ecrit par Pascal Dube, Victor Poulin et Simon Des-Alliers
*************************************************************************************************/
static int verifier_position_plateau_jeu_valide(int col, int ran)
{
	if (col < 0 || col > (TAILLE-1) || ran < 0 || ran > (TAILLE-1))
		return 0;
	return 1;
}

/************************************************************************************************
	OBJECTIF : La fonction ajouter_coup est seulement une fonction accesseur
	qui sert a acceder a la liste. Nous avons besoin d'une autre fonction 
	pour la logique de jeu qui verifie s'il y a une piece a la destination, 
	de quelle couleur elle est et seulement ensuite, l'ajouter a la liste.

	PARAMETRES : etat_jeu   :le pointeur de la variable qui contient la grille de jeu et le
							 joueur courrant
				 liste_coup :la liste de coup a modifier (si elle doit l'etre)
				 lig		:ligne d'origine de la piece a entrer dans la liste de coups
				 col		:colonne d'origine de la piece a entrer dans la liste de coups
				 lig_dest	:ligne de destination de la piece a entrer dans la liste de coups
				 col_Dest	:colonne de destination de la piece a entrer dans la liste de coups
				 pion		:Sert à savoir si on est une piece pion, donc si on peut juste aller
							 de l'avant sans considérer le cas où on peut manger en diagonale 
							 une case VIDE_EP ou/et une piêce adverse
	SORTIES : Retourne 1 si la fonction a rencontre une piece (la fonction appelante doit sortir
			  de la boucle), retourne 0 sinon. La liste de coup est egalement modifiee.

	ecrit par Pascal Dube, Victor Poulin et Simon Des-Alliers
************************************************************************************************/
static int ajouter_coup_si_valide(t_etat_jeu *etat_jeu, t_liste_coups *liste_coups,int lig,
	                              int col, int lig_dest, int col_dest, int pion)
{
	/*pour obtenir le joueur adverse, on utilise la fonction get_joueur (qui retourne 0 ou 8
	(NOIRS ou BLANCS)) puis on inverse avec l'operateur "!" ce qui donne 0 si l'adversaire est
	NOIR et 1 si l'adversaire est BLANC, reste a mutiplier par BLANCS (8) pour obtenir le
	joueur inverse*/
	int joueur_adverse = INVERSER_JOUEUR(get_joueur(etat_jeu));
	/*avant d'ajouter le coup,  il faut verifier s'il y a une piece a la destination*/
	t_piece piece_destination = get_piece_case(etat_jeu, col_dest, lig_dest);
	/*coup temporaire a ajouter a la liste*/
	t_coup coup;

	/*si la case de destination est vide, on peut ajouter le coup et on continue*/
	if (piece_destination == VIDE || piece_destination == VIDE_EP) 
	{
		set_coup(&coup, col, lig, col_dest, lig_dest, POS_VIDE, POS_VIDE);
		ajouter_coup(liste_coups, &coup);
	}
	/*si la piece est autre chose, on verifie de quelle piece il s'agit (un joueur peut
	en manger un autre, mais ne peut pas se manger lui-meme).On peut acceder seulement
	a cette partie si ce n'est pas un pion, car le pion ne peut manger qu'en diagonale seulement */
	else if (!pion)
	{
		/*pour verifier si on doit ajouter le coup, il faut tester si la piece destination est
		de meme type que le joueur adverse*/
		if (COMPARER_TYPE(piece_destination, joueur_adverse))
		{
			set_coup(&coup, col, lig, col_dest, lig_dest, POS_VIDE, POS_VIDE);
			ajouter_coup(liste_coups, &coup);
		}
		/*On retourne 1 car on veut activer les break_flag de la tour et du fou,
		car ils ne peuvent pas passer par dessus une autre piece*/
		return 1;
	}
	/*Si on est tombé sur une case vide, on retourne 0 pour que les boucles du fou et de la tour 
	continue*/
	return 0;
}

/*************************************************************************************************
OBJECTIF :La fonction privée sens_du_jeu est une fonction accesseur determinant dans quel sens
aller sur la grille. Cette fonction est essentiel pour l'algorithme de la fonction ajouter_pions,
car les pions sont les seules pièces du jeu qui peuvent seulement aller de l'avant. "avant" dépend
de leur référentiel (de quel couleur qu'ils sont).  

	PARAMETRES : etat_jeu : le pointeur de la variable qui contient la grille de jeu et le
							joueur courrant

	SORTIES	   : Retourne -1 si on est les blancs, retourne 1 si on est les noirs 

	Spécifications: Si on est les blancs, on veut monter sur la grille, si on est les noirs on
					veut descendre sur la grille 

*************************************************************************************************/
static int sens_du_jeu(t_etat_jeu* jeu)
{
		return get_joueur(jeu) ? -1 : 1;
}

/************************************************************************************************/
void init_jeu(t_etat_jeu* grille_jeu, int joueur_dep)
{
	/*initialisation de la grille de jeu avec les valeurs de departs en utilisant la fonction
	appropriee. On va egalement chercher le pointeur pour la grille elle-meme*/
	grille_jeu->grille_jeu = creer_grille();

	/*Ici, une verification de l'allocation dynamique serait inutile,
	car la vérification se fait déjà dans creer_grille avec la fonction assert
	pour chaque allocation dynamique fait.*/
	
	/*pour activer les grilles de test, modifier les #define au debut du fichier*/
#if TESTER_ROI == 1
		initialiser_grille_test_roi(get_grille_jeu(grille_jeu));
#endif
#if TESTER_PION == 1
		initialiser_grille_test_pion(get_grille_jeu(grille_jeu));
#endif
#if TESTER_CAVALIER == 1
		initialiser_grille_test_cavalier(get_grille_jeu(grille_jeu));
#endif
#if TESTER_TOUR == 1
		initialiser_grille_test_tour(get_grille_jeu(grille_jeu));
#endif
#if TESTER_FOU == 1
		initialiser_grille_test_fou(get_grille_jeu(grille_jeu));
#endif
#if TESTER_ROQUE == 1
		initialiser_grille_test_roque_roi(get_grille_jeu(grille_jeu));
#endif
		/*grille du programme normal*/
#if NORMAL == 1
		initialiser_grille(get_grille_jeu(grille_jeu));
#endif

	//On initialise le joueur a blanc au depart (les blancs commencent toujours aux echecs)
	grille_jeu->joueur = joueur_dep;

	/*activation des permissions pour le roque*/
	grille_jeu->roque_permis[0] = 1;
	grille_jeu->roque_permis[1] = 1;

	//On initialise le score à 0
	grille_jeu->score_grille = 0;
}

/************************************************************************************************/
int  get_joueur(const t_etat_jeu* jeu)
{
	return jeu->joueur;
}

/************************************************************************************************/
void set_joueur(t_etat_jeu* jeu, int joueur)
{
	jeu->joueur = joueur;
}

/***********************************************************************************************/
int** get_grille_jeu(const t_etat_jeu* jeu)
{
	return (jeu->grille_jeu);
}

/************************************************************************************************/
t_piece get_piece_case(const t_etat_jeu* jeu, int col, int ran)
{
	return (t_piece)jeu->grille_jeu[ran][col];
}

/************************************************************************************************/
int set_piece_case(t_etat_jeu* jeu, t_piece piece, int col, int ran)
{
	/*Si la position envoyé en paramètre (col et ran) est sur la grille*/
	if (verifier_position_plateau_jeu_valide(col,ran))
	{
		/*On met la pièce envoyé en paramètre sur la grille de jeu*/
		jeu->grille_jeu[ran][col] = piece;
		/*On retourne 1 pour confirmer que la pièce c'est bien envoyé*/
		return 1;
	}
	/*si la mise en place de la grille ne s'est pas fait, on retourne 0*/
	return 0;
}

/************************************************************************************************/
int generer_liste_coups(t_etat_jeu* jeu, t_liste_coups* liste_coups, int check_roq)
{
	/*il faut faire tous les coups possibles pour toutes les pieces, on parcout la grille au
	complet et, dependament de quelle piece il s'agit, on ajoute les coups possible a la grille*/
	for (int rangee = 0; rangee < TAILLE; rangee++)
	{
		for (int colonne = 0; colonne < TAILLE; colonne++)
		{
			/*comme les pieces noires et blanches ont les memes mouvements, on verifie seulement
			pour les noirs*/
			switch (CHOIX_PIECE(get_piece_case(jeu, colonne, rangee), get_joueur(jeu)))
			{
				case VIDE_EP :
				case VIDE:
					//la ligne est vide, pas de coup a ajouter
					break;
				case PION_N :
					//ajouter coup pion
					ajouter_coup_pion(liste_coups, jeu, colonne, rangee);
					break;
				case TOUR_N :
				case TOURI_N:
					//ajouter coup tour
					ajouter_coup_tour(liste_coups, jeu, colonne, rangee);
					break;
				case CAV_N:
					//ajouter coup cavalier
					ajouter_coup_cavalier(liste_coups, jeu, colonne, rangee);
					break;
				case FOU_N:
					//ajouter coup fou
					ajouter_coup_fou(liste_coups, jeu, colonne, rangee);
					break;
				case DAME_N:
					//ajouter coup dame (tour + fou)
					ajouter_coup_dame(liste_coups, jeu, colonne, rangee);
					break;
				case ROI_N:
					//ajouter coup roi
					ajouter_coup_roi(liste_coups, jeu, colonne, rangee, check_roq);
					break;
			}
		}
	}

	/*On retourne le nombre de coup. On aurait aimé le faire avec un accesseur, 
	  mais on peut pas include la liste_coup selon les règles */
	return liste_coups->nb_noeuds;
}

/***********************************************************************************************/
void initialiser_grille(t_grille grille_jeu)
{
	/*l'ordre des pieces sur la premiere et derniere ligne est cree comme suit il sera copie dans
	les lignes directement. Comme se sont les pieces noires il faudra ajouter 8 a chaque valeurs
	pour les changer en blanches lors de la copie*/
	t_piece lignes_de_pieces[8] = { TOURI_N, CAV_N, FOU_N, DAME_N, ROI_N, FOU_N, CAV_N, TOURI_N };

	/*initialisation de la grille de jeu rangee par rangee. il est important de noter que le cote
	noir est a 0-1 et le cote blanc a 6-7*/
	for (int i = 0; i < TAILLE; i++)
	{
		/*comme l'ordre des pieces est deja etablis dans la variable ligne_de_pieces, il suffit
		de copier directement les valeurs representant ces dernieres et comme se sont les
		pieces noires, pas besoin d'ajouter 8*/
		grille_jeu[0][i] = lignes_de_pieces[i];
		/*la ligne suivante est composee entierement de pions noir*/
		grille_jeu[1][i] = PION_N;

		/*les quatres lignes suivantes sont vides automatiquement en raison 
		de l'allocation mémoire de la grille à l'aide de la fonction calloc */
		
		/*la ligne suivante est composee entierement de pions blanc*/
		grille_jeu[6][i] = PION_B;
		/*comme l'ordre des pieces est deja etablis dans la variable ligne_de_pieces, il suffit
		de copier directement les valeurs représentants ces dernieres et comme se sont les pieces
		blanches, on ajoute 8 aux pieces noires de lignes_de_pieces*/
		grille_jeu[7][i] = lignes_de_pieces[i] + BLANCS;
	}
}

/************************************************************************************************/
void ajouter_coup_pion(t_liste_coups* liste_coups, t_etat_jeu* etat_jeu, int col, int lig)
{
	//Variable utiliser pour créer un nouveau coup et ajouter ce coup à la liste
	t_coup coup;    
	//Variable utiliser pour savoir si on est une piece pion
	static int pion = 1;       
	//Variable pour la ligne et la colonne destination
	int ligne = lig, colonne = col; 
	//Paramètre pour effectuer deux fois l'algorithme du mouvement en diagonale 
	int diagonale;                  

	//On a trois possibilités
	//Possibilité 1 : on avance d'une seule case
	colonne = col;
	ligne = lig;
	ligne += sens_du_jeu(etat_jeu); //On avance vers l'avant d'une seule case
	if (verifier_position_plateau_jeu_valide(colonne, ligne))
		/*On peut mettre ce cas dans la fonction ajouter_coup_si_valide,
		car col2 et lig2 sont POS_VIDE*/
		ajouter_coup_si_valide(etat_jeu, liste_coups, lig, col, ligne, colonne, pion);

	//Possibilité 2 : on avance de deux cases (si on peut)
	ligne += sens_du_jeu(etat_jeu); //On avance vers l'avant de deux cases
	/*On doit s'assurer qu'on est sur la case de départ, sinon le pion ne peut pas avancer de
	deux cases. Donc si on est les BLANCS et que le pion se situe sur la ligne 6, ou si on est les
	NOIRS et que le pions se situe sur la ligne 1*/
	if (((sens_du_jeu(etat_jeu) < 0) && lig == 6) || ((sens_du_jeu(etat_jeu) > 0) && lig == 1))
		if (verifier_position_plateau_jeu_valide(colonne, ligne))
			if (get_piece_case(etat_jeu, colonne, ligne - sens_du_jeu(etat_jeu)) == VIDE)
			{/*On ne peut pas mettre ce cas dans la fonction ajouter_coup_si_valide, 
			 car col2 et lig2 sont différents de POS_VIDE*/
				set_coup(&coup, col, lig, colonne, ligne,
					colonne, ligne - (sens_du_jeu(etat_jeu)));
				ajouter_coup(liste_coups, &coup);
			}
	/*Possibilité 3: On avance en diagonale en capturant quelqu'un ou une piece VIDE_EP
	Cela nous permet de sauver des lignes de code en effectuant 
	la diagonale de gauche et celle de droite dans la même boucle*/
	for (diagonale = 0; diagonale < 2; diagonale++)
	{
		colonne = col;
		ligne = lig;
		ligne += sens_du_jeu(etat_jeu); //On avance vers l'avant
		/*Si on est dans la premier passage dans la boucle on va vers la gauche,
		Sinon on va vers la droite*/
		colonne = (!diagonale) ? colonne - 1 : colonne + 1;
		//On s'assure qu'on est dans la grille 
		if (verifier_position_plateau_jeu_valide(colonne, ligne))
			//Si la case en diagonale n'est pas vide 
			if (get_piece_case(etat_jeu, colonne, ligne) != VIDE)
				/*Si la piece  à la case en diagonale n'est pas du même type
				(pas de la même couleur) que nous ou si elle est VIDE_EP */
				if (VALIDER_PION(get_piece_case(etat_jeu, colonne, ligne), get_joueur(etat_jeu)))
				{
					//Si elle est de type VIDE_EP
					if (get_piece_case(etat_jeu, colonne, ligne) == VIDE_EP)
					{
						/*Alors on peut aller à la case en diagonale et capturer VIDE_EP et le
						pion ennemi, qui est sur la même ligne que le pion du joueur actuel */
						set_coup(&coup, col, lig, colonne, ligne, colonne, lig);
						ajouter_coup(liste_coups, &coup);
					}
					//Sinon on capture la pièce en diagonale de la position actuelle du pion
					else
					{
						/*On ne peut pas mettre ce cas dans la fonction ajouter_coup_si_valide
						pour empêcher la possibilité 1 d'ajouter des coups errronés, 
						soit pour l'empêcher de manger une piece sur la ligne en avant du pion*/
						set_coup(&coup, col, lig, colonne, ligne, POS_VIDE, POS_VIDE);
						ajouter_coup(liste_coups, &coup);
					}
				}
	}
}

/*****************************************************************************/
void ajouter_coup_cavalier(t_liste_coups* liste_coups, t_etat_jeu* etat_jeu, int col, int lig)
{
	int col_dest;        //Colonne destination sur les 8 cases possibles
	int lig_dest;        //Ligne destination sur les 8 cases possibles
	static int pion = 0; //Variable utilisée pour savoir si on est une piece pion

	for (int i = 0; i < 8; i++)
	{
		//On assigne la bonne ligne de destination et colonne de destination 
		switch (i)
		{
		/********************COIN SUPERIEUR DROIT********************/
		case 0:
			//Case 7e
			col_dest = col + 1;
			lig_dest = lig - 2;
			break;
		case 1:
			//Case 6f
			col_dest = col + 2;
			lig_dest = lig - 1;
			break;
		/********************COIN INFERIEUR DROIT********************/
		case 2:
			//Case 4f
			col_dest = col + 2;
			lig_dest = lig + 1;
			break;
		case 3:
			//Case 3e
			col_dest = col + 1;
			lig_dest = lig + 2;
			break;
		/********************COIN INFERIEUR GAUCHE********************/
		case 4:
			//Case 3c
			col_dest = col - 1;
			lig_dest = lig + 2;
			break;
		case 5:
			//Case 4b
			col_dest = col - 2;
			lig_dest = lig + 1;
			break;
		/********************COIN SUPERIEUR GAUCHE********************/
		case 6:
			//Case 6b
			col_dest = col - 2;
			lig_dest = lig - 1;
			break;
		case 7:
			//Case 7c
			col_dest = col - 1;
			lig_dest = lig - 2;
			break;
		}

		//Vérifie si la case de destination est sur le plateau
		if (verifier_position_plateau_jeu_valide(col_dest, lig_dest))
		{	
			//Si le coup est valide, on l'ajoute
			ajouter_coup_si_valide(etat_jeu, liste_coups, lig, col, lig_dest, col_dest, pion);
		}
	}
}

/************************************************************************************************/
void ajouter_coup_tour(t_liste_coups* liste_coups, t_etat_jeu* etat_jeu, int col, int lig)
{                      
	int ligne = lig, colonne = col; //ligne et colonne de destination
	int break_flag = 0;             //Drapeau qui s'active à 1 ou se desactive a 0
	static int pion = 0;            //Variable utilisée pour savoir si on est une piece pion

	/*avant d'ajouter un coup a la liste, il faut s'assurer qu'il est possible en etant sur que
	la case soit dans les mouvementa possibles de la tour (elle peut bouger vers haut bas gauche
	et droite). On a donc besoin de 4 boucles pour verifier les 4 directions*/

	//Pour aller vers le haut
	ligne--;
	//tant qu'on reste sur la grille de jeu et qu'on n'est pas sur la même case qu'une autre pièce
	while (verifier_position_plateau_jeu_valide(colonne, ligne) && !break_flag) 
	{ /*S'il y avait une piece sur la case destination, le break_flag s'active 
	  et la boucle s'arrête, car une tour ne peut pas passer par dessus une autre piece*/
		break_flag = ajouter_coup_si_valide(etat_jeu, liste_coups,lig, col, ligne, colonne, pion);
		ligne--;
	}

	//Pour aller vers le bas
	ligne = lig + 1;
	break_flag = 0;
	while (verifier_position_plateau_jeu_valide(colonne, ligne) && !break_flag)
	{ //S'il y avait une piece sur la case destination, le break_flag s'active et la boucle s'arrête
		break_flag = ajouter_coup_si_valide(etat_jeu, liste_coups, lig, col, ligne, colonne, pion);
		ligne++;
	}

	//Pour aller vers la droite
	ligne = lig;
	colonne = col + 1;
	break_flag = 0;
	while (verifier_position_plateau_jeu_valide(colonne, ligne) && !break_flag)
	{//S'il y avait une piece sur la case destination, le break_flag s'active et la boucle s'arrête
		break_flag = ajouter_coup_si_valide(etat_jeu, liste_coups, lig, col, ligne, colonne, pion);
		colonne++;
	}

	//Pour aller vers la gauche
	colonne = col - 1;
	break_flag = 0;
	while (verifier_position_plateau_jeu_valide(colonne, ligne) && !break_flag)
	{//S'il y avait une piece sur la case destination, le break_flag s'active et la boucle s'arrête
		break_flag = ajouter_coup_si_valide(etat_jeu, liste_coups, lig, col, ligne, colonne, pion);
		colonne--;
	}
}

/************************************************************************************************/
int verif_roque(t_etat_jeu* jeu)
{
	return jeu->roque_permis[get_joueur(jeu) / BLANCS];
}

/************************************************************************************************/
void ajouter_coup_roi(t_liste_coups* liste_coups, t_etat_jeu* etat_jeu, int col, int lig,
					  int check_roq)
{
	static int pion = 0; //Variable utilisée pour savoir si on est une piece pion

	/*le roi ne peut bouger que d'une seule case (sauf pour le roque), on peut donc simplement
	verifier les positions autour de la piece (de -1 a +1 autour du roi)*/
	for(int lig_dest_offset = -1; lig_dest_offset <= 1; lig_dest_offset++)
		for (int col_dest_offset = -1; col_dest_offset <= 1; col_dest_offset++)
			/*on doit quand meme s'assurer que les positions autour du roi que l'on verifie reste
			sur le plateau de jeu*/
			if (verifier_position_plateau_jeu_valide(col + col_dest_offset, lig + lig_dest_offset))
				ajouter_coup_si_valide(etat_jeu, liste_coups, lig, col, (lig + lig_dest_offset), 
					                  (col + col_dest_offset), pion);
	/*On ajoute les coups de roque possibles pour le joueur à la liste de coups, par rapport à
	l'état du jeu actuel*/
	roque_du_roi(etat_jeu, liste_coups, check_roq);
	
}

/**************************************************************************************************/
void ajouter_coup_fou(t_liste_coups* liste_coups, t_etat_jeu* etat_jeu, int col, int lig)
{
	int ligne;           //ligne de la case destination
	int colonne;         //colonne de la case destination
	static int pion = 0; //Variable utilisée pour savoir si on est une piece pion
	int break_flag = 0;  //Drapeau qui s'active ou bien se desactive

	//Pour aller vers nord-est
	ligne = lig - 1;  //On veut aller vers le haut de la grille
	colonne = col + 1;//On veut aller vers la droite de la grille
	while (verifier_position_plateau_jeu_valide(colonne, ligne) && !break_flag)
	{ /*S'il y avait une piece sur la case destination, le break_flag s'active et la boucle
	  s'arrête, car un fou ne peut pas passer par dessus une autre piece*/
		break_flag = ajouter_coup_si_valide(etat_jeu, liste_coups, lig, col, ligne, colonne, pion);
		ligne--;   //On veut aller vers le haut de la grille
		colonne++; //On veut aller vers la droite de la grille
	}

	//Pour aller vers le nord-ouest
	ligne = lig - 1;   //On remet la ligne à la ligne à droite de celle actuelle
	colonne = col - 1; //On remet la colonne à la colonne à gauche de celle actuelle
	break_flag = 0;
	while (verifier_position_plateau_jeu_valide(colonne, ligne) && !break_flag)
	{//S'il y avait une piece sur la case destination, le break_flag s'active et la boucle s'arrête
		break_flag = ajouter_coup_si_valide(etat_jeu, liste_coups, lig, col, ligne, colonne, pion);
		ligne--;   //On veut aller vers le haut de la grille
		colonne--; //On veut aller vers la gauche de la grille 
	}

	//Pour aller vers le sud-ouest 
	ligne = lig + 1;   //On remet la ligne à la ligne à droite de celle actuelle
	colonne = col - 1; //On remet la colonne à la colonne à gauche de celle actuelle
	break_flag = 0;
	while (verifier_position_plateau_jeu_valide(colonne, ligne) && !break_flag)
	{//S'il y avait une piece sur la case destination, le break_flag s'active et la boucle s'arrête
		break_flag = ajouter_coup_si_valide(etat_jeu, liste_coups, lig, col, ligne, colonne, pion);
		ligne++;   //On veut aller vers le bas de la grille
		colonne--; //On veut aller vers la gauche de la grille
	}

	//Pour aller vers le sud-est
	ligne = lig + 1;   //On remet la ligne à la ligne à droite de celle actuelle
	colonne = col + 1; //On remet la colonne à la colonne à droite de celle actuelle
	break_flag = 0;
	while (verifier_position_plateau_jeu_valide(colonne, ligne) && !break_flag)
	{//S'il y avait une piece sur la case destination, le break_flag s'active et la boucle s'arrête 
		break_flag = ajouter_coup_si_valide(etat_jeu, liste_coups, lig, col, ligne, colonne, pion);
		ligne++;   //On veut aller vers le bas de la grille 
		colonne++; //On veut aller vers la droite de la grille 
	}
}

/**************************************************************************************************/
void ajouter_coup_dame(t_liste_coups* liste_coups, t_etat_jeu* etat_jeu, int col, int lig)
{
	/*La dame est un combinaison du fou et du roi,
	car elle fait les diagonales, les haut/bas et droite/gauche*/
	ajouter_coup_fou(liste_coups, etat_jeu, col, lig);
	ajouter_coup_tour(liste_coups, etat_jeu, col, lig);
}

/************************************************************************************************/
void roque_du_roi(t_etat_jeu* jeu, t_liste_coups* liste, int check_roq)
{
	t_liste_coups coups_tmp;        //Liste de coups temporaire
	t_coup coup_roi;                //Coup du roi a ajoute si les conditions sont valides
	int flag_grand_roque = 1;		//Drapeau pour le grand roque 
	int flag_petit_roque = 1;		//Drapeau pour le petit roque 
	int non_validation_case = 0;	//Variable pour voir si les cases sont en danger
	int joueur = get_joueur(jeu);   //Variable pour le joueur actuel

	/*check_roq a 1 veut dire qu'on doit verifier le roque car, pour ce joueur, c'est encore
	possible*/
	if (check_roq)
	{
		/*on doit également verifier si les positions sur le plateau de jeu sont vides pour
		pouvoir roquer*/
		/***************GRAND ROQUE*************/
		for (int colonne = 1; (colonne < 4) && (flag_grand_roque); colonne++)
			if (get_piece_case(jeu, colonne, ROQUE_ROI(joueur)) != VIDE)
				flag_grand_roque = 0;
		
		/**************PETIT ROQUE**************/
		for (int colonne = 5; (colonne < 7) && (flag_petit_roque); colonne++)
			if (get_piece_case(jeu, colonne, ROQUE_ROI(joueur)) != VIDE)
				flag_petit_roque = 0;

		//Si on peut faire le petit roque
		if (flag_petit_roque)
		{
			/*Verification si les tours ont bougés*/
			if (get_piece_case(jeu, TAILLE - 1, ROQUE_ROI(joueur)) == TOURI_N + joueur)
			{
				//on doit creer une liste de coups temporaire
				init_liste_coups(&coups_tmp);
				
				//On inverse le joueur
					
				set_joueur(jeu, INVERSER_JOUEUR(joueur));

				/*On doit s'assurer que le roi n'est pas en danger lorsqu'il se déplace
				on met donc temporairement des rois sur les cases que le roi va se déplacer*/
				set_piece_case(jeu, (t_piece)(ROI_N + joueur), 5, ROQUE_ROI(joueur));
				set_piece_case(jeu, (t_piece)(ROI_N + joueur), 6, ROQUE_ROI(joueur));
					
				//On génère la liste de coups de l'ennemi
				generer_liste_coups(jeu, &coups_tmp, 0);
				/*On doit vider les cases où nous avions
				temporairement placé des rois sur les cases que le roi va se déplacer*/
					
				set_piece_case(jeu, VIDE, 5, ROQUE_ROI(joueur));
				set_piece_case(jeu, VIDE, 6, ROQUE_ROI(joueur));
				/*On doit vérifier que les coups possibles de l'ennemi ne mange pas le roi
					
				sur ces 3 cases de déplacements*/
				for (int col_dest = 4; col_dest <= 6; col_dest++)
					if (!valider_case_dest(&coups_tmp, col_dest, ROQUE_ROI(joueur)))
						non_validation_case++;
					
				//Si le roi ne sera pas en danger avant, pendant et après son déplacement
				if (non_validation_case == 3)
				{
					//On veut ajouter le coup à notre vrai liste 
					set_coup(&coup_roi, 4, ROQUE_ROI(joueur), 6, ROQUE_ROI(joueur),
					7, ROQUE_ROI(joueur));
					ajouter_coup(liste, &coup_roi);
				}
					
				//on réinverse le joueur 
				set_joueur(jeu, joueur);
				detruire_liste_coups(&coups_tmp);
				
			}
		}
		non_validation_case = 0;
		//Si on peut faire le grand roque
		if (flag_grand_roque)
		{
			/*verification si les tours ont bougés*/
			if (get_piece_case(jeu, 0, ROQUE_ROI(joueur)) == TOURI_N + joueur)
			{	
				/*on doit creer une liste de coups temporaire*/
				init_liste_coups(&coups_tmp);
				
				//On inverse le joueur
				set_joueur(jeu, INVERSER_JOUEUR(joueur));
					
				/*On doit s'assurer que le roi n'est pas en danger lorsqu'il se déplace
				on met donc temporairement des rois sur les cases que le roi va se déplacer*/
				set_piece_case(jeu, (t_piece)(ROI_N + joueur), 2, ROQUE_ROI(joueur));
				set_piece_case(jeu, (t_piece)(ROI_N + joueur), 3, ROQUE_ROI(joueur));
					
				//On génère la liste de coups de l'ennemi
				generer_liste_coups(jeu, &coups_tmp, 0);
					
				/*On doit vider les cases où nous avions
				temporairement placer des rois sur les cases que le roi va se déplacer*/
				set_piece_case(jeu, VIDE, 2, ROQUE_ROI(joueur));
				set_piece_case(jeu, VIDE, 3, ROQUE_ROI(joueur));
					
				//On doit vérifier que les coups possible de l'ennemi ne mange pas le roi
				//sur ces 3 cases de déplacements
				for (int col_dest = 4; col_dest >= 2; col_dest--)
					if (!valider_case_dest(&coups_tmp, col_dest, ROQUE_ROI(joueur)))
						non_validation_case++;
					
				//Si le roi ne sera pas en danger avant, pendant et après son déplacement
				if (non_validation_case == 3)
				{
					//On veut ajouter le coup à notre vrai liste 
					set_coup(&coup_roi, 4, ROQUE_ROI(joueur), 2, ROQUE_ROI(joueur),
					0, ROQUE_ROI(joueur));
					ajouter_coup(liste, &coup_roi);
				}
					
				//on réinverse le joueur 
				set_joueur(jeu, joueur);
				detruire_liste_coups(&coups_tmp);
				
				
			}
		}
	}
}

/************************************************************************************************/
t_piece jouer_coup(t_etat_jeu* jeu, const t_coup* coup)
{
	//La pièce qui sera retournée, c'est la piece étant à la case_destination
	t_piece capture = VIDE;  
	//Variable contenant la piece qu'on veut déplacer
	t_piece piece_a_deplacer = get_piece_case(jeu, coup->col, coup->lig);     
	//Variable à la case_destination
	t_piece piece_case_destination = get_piece_case(jeu, coup->col_dest, coup->lig_dest);  
	//Variable représentant la pièce à la case secondaire
	t_piece piece_case_secondaire = VIDE; 
	int joueur = get_joueur(jeu); //Joueur actuel

	if(coup->col_case2 != POS_VIDE && coup->lig_case2 != POS_VIDE)
		piece_case_secondaire = get_piece_case(jeu, coup->col_case2, coup->lig_case2);

	//Si la piece présente à la case à laquelle on veut aller n'est pas vide,
	//alors on va capturer cette piece ultimement
	if (piece_case_destination != VIDE && piece_case_destination != VIDE_EP)
		capture = piece_case_destination; 

	//Si la case secondaire est rempli, alors on doit effectuer certaine manipulation
	if (coup->col_case2 != POS_VIDE && coup->lig_case2 != POS_VIDE)
	{
		/*Si la piece à la case secondaire est vide, c'est un pion qui avance de deux cases*/
		//On met donc le type VIDE_EP à cette case
		if (piece_case_secondaire == VIDE)
			set_piece_case(jeu, VIDE_EP, coup->col_case2, coup->lig_case2);
		/*Si la pièce à la case destination est de type VIDE_EP*/
		else if (piece_case_destination == VIDE_EP)
		{
			//On capture le pion du vide-en passant
			capture = piece_case_secondaire;
			//On vide la case secondaire
			set_piece_case(jeu, VIDE, coup->col_case2, coup->lig_case2);
		}
		//Si la case est une TOUR_I
		else if (piece_case_secondaire == TOURI_N + joueur)
		{
			//Calcul de la colonne qu'on met la tour 
			//Si on est les blancs (ou les noirs) on va à la ligne 7 (ou 0), colonne 3 (ou 5)
			set_piece_case(jeu, (t_piece)(TOUR_N + joueur), POS_TOUR(coup->col_case2), ROQUE_ROI(joueur));
			//On vide la case où il y avait la tour avant le roque 
			set_piece_case(jeu, VIDE, coup->col_case2, coup->lig_case2);
			//On désactive la permission de faire le roque pour le joueur
			jeu->roque_permis[joueur / 8] = 0;
		}
	}

	//Si on veut déplacer une tour qui n'a pas encore été déplacée on doit modifier la valeur
	if (piece_a_deplacer == TOURI_N + joueur)
		set_piece_case(jeu, (t_piece)(TOUR_N + joueur), coup->col_dest, coup->lig_dest);
	//Sinon, si on veut déplacer un pion qui est à l'extrémité de la grille 
	else if (piece_a_deplacer == PION_N + joueur)
	{
		//Si le joueur désire mettre le pion sur la ligne 0 ou 7, 
		//on effectue une promotion et le pion devient une dame 
		if (coup->lig_dest == PROMOTION(joueur))
		{
			set_piece_case(jeu, (t_piece)(DAME_N + joueur), coup->col_dest, coup->lig_dest);

			//Si on fait une promotion et que le joueur est noir, on fait +8 au score
			if (joueur == NOIRS)
			{
				jeu->score_grille += 8;
			}
			//Sinon on fait -8 
			else
			{
				jeu->score_grille -= 8;
			}
		}
		//Sinon, on peut placer la pièce à déplacer dans la case destination
		else
			set_piece_case(jeu, piece_a_deplacer, coup->col_dest, coup->lig_dest);
	}
	//Si on est pas un cas spécial, on place la pièce à déplacer dans la case destination
	if((piece_a_deplacer != TOURI_N + joueur) && (piece_a_deplacer != PION_N + joueur))
		set_piece_case(jeu, piece_a_deplacer, coup->col_dest, coup->lig_dest);
	
	//Si un roi a été déplacer, on doit désactiver l'option roque_permis
	if (piece_a_deplacer == ROI_N + joueur)
		jeu->roque_permis[joueur / 8] = 0;

	/*On vide les cases du coup précedent qui était de type VIDE_EP On doit savoir quelle est
	l'équipe du joueur adverse pour savoir quelle ligne regarder. De plus, on ne veut pas modifier
	l'état des cases de la ligne de l'équipe actuelle */
	for (int colonne = 0; colonne < TAILLE; colonne++)
		if (get_piece_case(jeu, colonne, LIG_VIDE_EP(get_joueur(jeu))) == VIDE_EP)
			set_piece_case(jeu, VIDE, colonne, LIG_VIDE_EP(get_joueur(jeu)));
	
	//On vide la case de la piece à déplacer
	set_piece_case(jeu, VIDE, coup->col, coup->lig);

	return capture;
}

/************************************************************************************************/
t_grille creer_grille(void)
{
	t_grille grille; //La grille de jeu (**)
	
	//On alloue de la mémoire pour le tableau de pointeurs (les lignes)
	grille = (int**)calloc(TAILLE_GR, sizeof(int*));
	assert(grille);

	/*Si l'allocation mémoire du tableau des lignes s'est fait correctement*/

		//On alloue de la mémoire pour chaque pointeur du tableau de pointeurs (les colonnes)
		for (int i = 0; i < TAILLE_GR; i++)
		{
			grille[i] = (int*)calloc(TAILLE_GR, sizeof(int));
			assert(grille[i]);
		}
		/*Tout c'est bien déroulé alors on retourne la grille*/
		return grille;
}

/***********************************************************************************************/
void detruire_grille(t_grille grille_jeu)
{
	//On detruit chaque tableau de colonne de chaque ligne qui été alloué
	for (int i = 0; (i < TAILLE_GR) && grille_jeu[i] != NULL; i++)
	{
		free(grille_jeu[i]);
		grille_jeu[i] = NULL;
	}

	//On detruit le tableau de pointeurs des lignes
	free(grille_jeu);
	grille_jeu = NULL;
}

/***********************************************************************************************/
void mise_a_jour_score(t_etat_jeu* jeu, int capture)
{
	//On soustrait la valeur associée à la pièce capturée au score actuel de la grille
	jeu->score_grille -= PTS_PIECES[capture];
}

/***********************************************************************************************/
int get_score_grille(const t_etat_jeu* jeu)
{
	//On retourne le score de la grille
	return jeu->score_grille;
}