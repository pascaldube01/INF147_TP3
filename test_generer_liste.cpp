/***************************************************************************************/
/*  TEST_GENERER_LISTE.C                                                               */
/*  Auteurs: Victor Poulin, Pascal Dube et Simon Des-Alliers                           */
/*  Date: 1 mars 2024                                                                  */
/*                                                                                     */
/* Ce module permet d'effectuer les tests de toutes les pieces avec des fonctions      */
/* indépendantes pour chaque pièce.                                                    */
/*                                                                                     */
/*Liste des fonctions:  void initialiser_grille_test_pion(t_grille grille_jeu)         */
/*                      void initialiser_grille_test_tour(t_grille grille_jeu)         */
/*                      void initialiser_grille_test_fou(t_grille grille_jeu)          */
/*                      void initialiser_grille_test_cavalier(t_grille grille_jeu)     */
/*                      void initialiser_grille_test_roi(t_grille grille_jeu)          */
/*                      void initialiser_grille_test_roque_roi(t_grille grille_jeu)    */
/***************************************************************************************/

/*=========================================================*/
/*                 LES LIBRAIRIES                          */
/*=========================================================*/

#include"test_generer_liste.hpp"

/*=========================================================*/
/*                  LES FONCTIONS                          */
/*=========================================================*/

void initialiser_grille_test_pion(t_grille grille_jeu)
{
	/*Au départ la grille est déjà vide en raison de calloc*/
	int test_jeu_pion = 2;

	switch (test_jeu_pion) 
	{
		//on test avancer une fois et deux fois si ces coups sont bloqués quand il y a une piece
		//sur la case à l'avant du pion
		case 0: 
			grille_jeu[1][0] = PION_B;
			grille_jeu[7][0] = PION_B;
			grille_jeu[6][1] = PION_B;
			grille_jeu[5][4] = PION_B;
			grille_jeu[6][7] = PION_B;
			grille_jeu[5][7] = PION_N;
			break;
		//on test si on capture un pion adverse en diagonale ou si on capture un VIDE_EP et pion
		//adverse
		case 1: 		
			grille_jeu[2][1] = VIDE_EP;
			grille_jeu[3][1] = PION_N;
			grille_jeu[3][0] = PION_B;
			grille_jeu[3][2] = PION_B;
			grille_jeu[2][2] = PION_N;
			grille_jeu[4][2] = PION_B;
			grille_jeu[2][0] = TOUR_B;
			break;
		/*On test qu'on peut capturer un pion en mangeant un vide en passant d'un pion ennemi*/
		case 2: 
			grille_jeu[1][2] = PION_N;
			grille_jeu[3][3] = PION_B;
			grille_jeu[6][1] = PION_B;
			grille_jeu[5][7] = PION_N;
			break;
			/*On test qu'on peut se faire capturer un pion ennemi par notre vide en passant*/
		case 3: 
			grille_jeu[4][3] = PION_N;
			grille_jeu[4][1] = PION_B;
			grille_jeu[6][2] = PION_B;
			break;
	}

}

/*****************************************************************************/
void initialiser_grille_test_tour(t_grille grille_jeu)
{
	/*Au départ la grille est déjà vide en raison de calloc*/

	grille_jeu[4][4] = TOUR_B;
	grille_jeu[4][2] = PION_B;
	grille_jeu[4][6] = PION_N;
}

/*****************************************************************************/
void initialiser_grille_test_fou(t_grille grille_jeu)
{
	/*Au départ la grille est déjà vide en raison de calloc*/

	grille_jeu[4][4] = FOU_B;
	grille_jeu[2][6] = PION_N;
	grille_jeu[2][2] = PION_B;
}

/*****************************************************************************/
void initialiser_grille_test_cavalier(t_grille grille_jeu)
{
	int test_jeu_cavalier = 3; //Variable qui sert à tester differentes configurations

	/*Au départ la grille est déjà vide en raison de calloc*/

	switch (test_jeu_cavalier)
	{
		//on test tous les coins
		case 0:
			grille_jeu[0][0] = CAV_B; 
			grille_jeu[0][7] = CAV_B;
			grille_jeu[7][0] = CAV_B;
			grille_jeu[7][7] = CAV_B;
			break;
		//on test pour un saut par dessus un pion
		case 1:
			grille_jeu[3][3] = CAV_B;
			grille_jeu[3][2] = PION_N;
			break;
	    //on veut s'assurer qu'il ne mange pas un pion de sa couleur
		case 2:
			grille_jeu[3][3] = CAV_B;
			grille_jeu[1][2] = PION_B;
			break;
		//on veut s'assurer qu'il mange un pion de couleur différente
		case 3:
			grille_jeu[3][3] = CAV_B;
			grille_jeu[1][2] = PION_N;
			break;
	}
}

/*****************************************************************************/
void initialiser_grille_test_roi(t_grille grille_jeu)
{
	/*Au départ la grille est déjà vide en raison de calloc*/

	/*mise des pieces sur le jeu pour le test */
	grille_jeu[4][4] = ROI_B;
	grille_jeu[4][3] = PION_N;
	grille_jeu[6][1] = PION_N;
	grille_jeu[5][4] = PION_B; 
	//grille_jeu[3][4] = VIDE_EP;
}

/*****************************************************************************/
void initialiser_grille_test_roque_roi(t_grille grille_jeu)
{
	int test_jeu_roque = 0; //Variable qui sert à tester differentes configurations

	/*Au départ la grille est déjà vide en raison de calloc*/
	switch (test_jeu_roque)
	{
		/*Test pour les blancs*/
		case 0:
			grille_jeu[7][4] = ROI_B;
			grille_jeu[1][6] = PION_N;
			grille_jeu[7][0] = TOURI_B;
			grille_jeu[7][7] = TOURI_B;
			grille_jeu[2][7] = PION_N;
			break;
		/*Test pour les noirs, marche si l'ordinateur prend le bon coup */
		case 1:
			grille_jeu[0][4] = ROI_N;
			grille_jeu[3][6] = PION_B;
			grille_jeu[7][4] = ROI_B;
			grille_jeu[0][0] = TOURI_N;
			grille_jeu[0][7] = TOURI_N;
	}
}