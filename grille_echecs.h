/*****************************************************************************************/
/*  GRILLE_ECHECS.H                                                                      */
/*  Auteurs: Victor Poulin, Pascal Dube et Simon Des-Alliers                             */
/*  Date: 14 février 2024                                                                */
/*                                                                                       */
/* Ce module s'occuppe de la gestion de la grille de jeu et de l'etat du jeu.            */
/*  Il offre des fonctions permettant d'initialiser le jeu, generer la liste des coups   */
/*  valides du jeu et d'effectuer la mise-a-jour de la grille suite a un coup jouee.     */
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

#if !defined(TAILLE)

/*=========================================================*/
/*                 LES LIBRAIRIES                          */
/*=========================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include"liste_coup.h"    

/*=========================================================*/
/*                  LES CONSTANTES                         */
/*=========================================================*/

#define TAILLE  8       //grille de 8x8
#define NOIRS   0       //valeur pour le joueur NOIR
#define BLANCS  8       //valeur pour le joueur BLANC

/*=========================================================*/
/*                  LES MACROFONCTIONS                     */
/*=========================================================*/

/*La macrofonction COMPARER_TYPE permet de comparer le type de d'une pièces et d'un joueur (BLANCS
ou NOIRS) pour savoir s'ils sont dans la même équipe.
X est la pièce à la destination et Y le joueur.
S'ils sont de la même équipe on retourne 1, sinon 0*/
#define COMPARER_TYPE(x,y) ((((x) / BLANCS) == ((y) / BLANCS)) ? 1 : 0)

/*La macrofonction VALIDER_PION permet de comparer le type de d'une pièces et d'un joueur
(BLANCS ou NOIRS) pour savoir s'ils sont dans la même équipe.
X est la pièce à la destination et Y le joueur.
S'ils ne sont pas de la même équipe ou que la piece est de type "vide «en-passant»", on
retourne  1, sinon 0*/
#define VALIDER_PION(x,y) (!COMPARER_TYPE(x,y) || ((x) == VIDE_EP)) 

/*La macrofonction CHOIX_PIECE permet de comparer le type de d'une pièces et d'un joueur (BLANCS
ou NOIRS) pour savoir s'ils sont dans la même équipe.
X est la pièce actuelle et Y le joueur actuel.
S'ils sont de la même équipe, on retourne  la différence entre x et y, sinon 0*/

#define CHOIX_PIECE(x,y) ((COMPARER_TYPE(x,y)) ? ((x) - (y)) : VIDE)

/*La macrofonction INVERSER_JOUEUR permet d'inverser le joueur (BLANCS ou NOIRS)
X est le joueur actuel.
Si le joueurs est blanc on retourne noir, et vice-versa*/
#define INVERSER_JOUEUR(x) ((!(x)) * BLANCS)

/*La macrofonction ROQUE_ROI permet de déterminer sur quelle ligne de la grille est effectué
le roque.
X est le joueur actuel.
Si le joueur actuel est BLANCS, on retourne 7, sinon 0*/
#define ROQUE_ROI(x) ((x)? (BLANCS-1) : NOIRS)

/*La macrofonction PROMOTION permet de déterminer si la ligne de la case sur laquelle la pièce
arrivera lui permettra d'effectuer une promotion. 
X est le joueur actuel. 
Si le joueur actuel est BLANCS, on retourne 0, sinon 7.*/
#define PROMOTION(x) ((x) ? (NOIRS) : (TAILLE-1))

/*La fonction privée POS_TOUR est une fonction qui sert a savoir sur quelle colonne
placer la tour lors du roque.*/
#define POS_TOUR(col_case2) ((col_case2) < 4) ? 3 : 5

/* La macrofonction LIG_VIDE_EP est une fonction accesseur qui sert a savoir de quel
ligne vider les cases ayant des VIDE_EP datant du dernier coup du même joueur. S'il y avait un
vide ep sur la ligne 2 et que les blancs ont joués mais qu'aucun pion blanc n'a capturer un vide
ep adverse durant ce coup, alors on doit effacer ce vide ep, car les vide ep sont seulement
affichés lors du prochain tour de l'adversaire après celui où le vide ep a apparu.*/
#define LIG_VIDE_EP(joueur) ((joueur) ? 2: 5)

/***************************************************************************************/
/*                              DECLARATIONS DES TYPES                                 */
/***************************************************************************************/

/* pieces du jeu : case VIDE et NOIRS = 0 a 7 */
typedef enum { VIDE,    PION_N, TOURI_N, TOUR_N, CAV_N, FOU_N, DAME_N, ROI_N, 
    /* case vide-en-passant et BLANCS = 8 a 15 */
               VIDE_EP, PION_B, TOURI_B, TOUR_B, CAV_B, FOU_B, DAME_B, ROI_B } t_piece;

typedef int** t_grille;   //type-tableau de la grille de jeu

typedef struct
{
    t_grille grille_jeu;   //la grille 8x8 du jeu
    int roque_permis[2];   //indique si le roque est permis: [0] = NOIRS, [1] = BLANCS
    int joueur;            //le joueur, NOIRS ou BLANCS, a jouer
	int score_grille;       //Score de la grille
} t_etat_jeu;

/***************************************************************************************/
/*                       DECLARATIONS DES FONCTIONS PUBLIQUES                          */
/***************************************************************************************/

/*************************************************************************************************
    OBJECTIF : Initialisation de la grille de jeu avec la position de depart.

	PARAMETRES : grille_jeu : grille du jeu 
				joueur de départ (toujours blanc)

	SORTIES :	aucune (void)

	écrit par Pascal Dubé, Victor Poulin et Simon Des-Alliers
**************************************************************************************************/
void init_jeu(t_etat_jeu* grille_jeu, int joueur_dep);

/*************************************************************************************************
    OBJECTIF : Accesseur pour savoir qui est le prochain joueur a jouer.

	PARAMETRES : jeu : etat actuel du jeu

	SORTIES :	la valeur du champ "joueur" (NOIRS ou BLANCS)

	écrit par Pascal Dubé, Victor Poulin et Simon Des-Alliers
************************************************************************************************/
int  get_joueur(const t_etat_jeu* jeu);

/************************************************************************************************
    OBJECTIF : Fonction-mutatrice pour modifier le "joueur" a jouer le prochain coup.

	PARAMETRES : jeu : etat du jeu
				 joueur : nouveau joueur courrant

	SORTIES :	aucune (void)

	écrit par Pascal Dubé, Victor Poulin et Simon Des-Alliers
***********************************************************************************************/
void set_joueur(t_etat_jeu* jeu, int joueur);

/***********************************************************************************************
    OBJECTIF : Accesseur pour obtenir une reference a la grille de jeu.

	PARAMETRES : jeu : etat du jeu

	SORTIES :	un pointeur a la grille de jeu.

	écrit par Pascal Dubé, Victor Poulin et Simon Des-Alliers
**************************************************************************************************/
int** get_grille_jeu(const t_etat_jeu* jeu);

/*************************************************************************************************
    OBJECTIF : Accesseur pour obtenir la valeur de la piece du jeu a la case (col, ran).

	PARAMETRES : jeu : etat du jeu (et donc la grille)
			   : la colonne et la ligne : position sur la grille

	SORTIES :	une des constantes-pieces du type-enum "t_piece".

	écrit par Pascal Dubé, Victor Poulin et Simon Des-Alliers
**************************************************************************************************/
t_piece get_piece_case(const t_etat_jeu* jeu, int col, int ran);


/*************************************************************************************************
    OBJECTIF : Fonction-mutatrice qui remplace la case (col, ran) de la grille avec la "piece"
	           reçue. Si on reçoit la piece "VIDE", on vide la case du jeu. On doit valider si
			   la position (col, ran) est une position-grille valide.

	PARAMETRES : jeu etat actuel (inclus la grille)
				 colonne et ligne : position a changer sur la grille
				 piece : piece a changer sur la position donne dans la grille

	SORTIES :	1 si la coordonnee est valide et que la case a ete mise-a-jour,
                0 sinon (coordonnee non-valide).

	écrit par Pascal Dubé, Victor Poulin et Simon Des-Alliers
**********************************************************************************************/
int set_piece_case(t_etat_jeu* jeu, t_piece piece, int col, int ran);

/**********************************************************************************************
    OBJECTIF : Genere la liste de tous les coups possibles a jouer pour le joueur actuel du jeu a partir de
               l'etat du jeu actuel.

	PARAMETRES : jeu : etat actuel du jeu
				 liste_coups : liste de coups possible pour le joueur actuel
				 le check_roq : possibilite de faire le roque pour le joueur actuel

	SORTIES : le nombre de coups generes.

	écrit par Pascal Dubé, Victor Poulin et Simon Des-Alliers
***********************************************************************************************/
int generer_liste_coups(t_etat_jeu* jeu, t_liste_coups* liste_coups, int check_roq);

/************************************************************************************************
    OBJECTIF : Cette fonction initialise la grille de jeu avec les positions de départ de toutes 
	           les pièces

	PARAMETRES : grille_jeu :  la grille de jeu qui doit être initialisée
								(c'est un tableau donc un pointeur)
	SORTIES :	aucune (entre des valeurs dans un tableau, donc sa sortie est
						un pointeur)

	SPEC :

	écrit par Pascal Dubé, Victor Poulin et Simon Des-Alliers
**************************************************************************************************/
void initialiser_grille(t_grille grille_jeu);

/*************************************************************************************************
    OBJECTIF : Ajoute les coups possibles a la liste dans le cas ou la piece est un pion

	PARAMETRE : liste_coup : la liste des coups possible
				etat_jeu : grille, info sur le roque et joueur courrant
				col et lig : position de la piece verifier

	SORTIE :	ajout dans la liste de coups

	ecrit par Pascal Dube, Victor Poulin et Simon Des-Alliers

***********************************************************************************************/
void ajouter_coup_pion(t_liste_coups* liste_coups, t_etat_jeu* etat_jeu, int col, int lig);

/***********************************************************************************************
    OBJECTIF : ajoute les coups possibles a la liste dans le cas ou la piece est une tour

	PARAMETRE : liste_coup : la liste des coups possible
				etat_jeu : grille, info sur le roque et joueur courrant
				col et lig : position de la piece verifier

	SORTIE :	ajout dans la liste de coups

	ecrit par Pascal Dube, Victor Poulin et Simon Des-Alliers

*************************************************************************************************/
void ajouter_coup_tour(t_liste_coups* liste_coups, t_etat_jeu* etat_jeu, int col, int lig);

/************************************************************************************************
    OBJECTIF : Ajoute les coups possibles a la liste dans le cas ou la piece est un roi

	PARAMETRE : liste_coup : la liste des coups possible
				etat_jeu : grille, info sur le roque et joueur courrant
				col et lig : position de la piece verifier
				check_roq : flag de la possibilite du roque

	SORTIE :	ajout dans la liste de coups

	ecrit par Pascal Dube, Victor Poulin et Simon Des-Alliers

*************************************************************************************************/
void ajouter_coup_roi(t_liste_coups* liste_coups, t_etat_jeu* etat_jeu,
					  int col, int lig, int check_roq);

/************************************************************************************************
    OBJECTIF : Ajoute les coups possibles a la liste dans le cas ou la piece est un cavalier

	PARAMETRE : liste_coup : la liste des coups possible
				etat_jeu : grille, info sur le roque et joueur courrant
				col et lig : position de la piece verifier

	SORTIE :	ajout dans la liste de coups

	ecrit par Pascal Dube, Victor Poulin et Simon Des-Alliers

**************************************************************************************************/
void ajouter_coup_cavalier(t_liste_coups* liste_coups, t_etat_jeu* etat_jeu, int col, int lig);

/*************************************************************************************************
    OBJECTIF : Ajoute les coups possibles a la liste dans le cas ou la piece est un fou

	PARAMETRE : liste_coup : la liste des coups possible
				etat_jeu : grille, info sur le roque et joueur courrant
				col et lig : position de la piece verifier

	SORTIE :	ajout dans la liste de coups

	ecrit par Pascal Dube, Victor Poulin et Simon Des-Alliers

**************************************************************************************************/
void ajouter_coup_fou(t_liste_coups* liste_coups, t_etat_jeu* etat_jeu, int col, int lig);

/*************************************************************************************************
    OBJECTIF : Ajoute les coups possibles a la liste dans le cas ou la piece est une dame

	PARAMETRE : liste_coup : la liste des coups possible
				etat_jeu : grille, info sur le roque et joueur courrant
				col et lig : position de la piece verifier

	SORTIE :	ajout dans la liste de coups

	ecrit par Pascal Dube, Victor Poulin et Simon Des-Alliers

*************************************************************************************************/
void ajouter_coup_dame(t_liste_coups* liste_coups, t_etat_jeu* etat_jeu, int col, int lig);

/*************************************************************************************************
    OBJECTIF :Permet d'effectuer le grand roque et le petit roque pour joueur blanc et noir

	PARAMETRE : liste     : la liste des coups possible
				jeu       : jeu actuel
				check_roq : flag du roque du roi

	SORTIE :	void (Ne retourne rien)

	ecrit par Pascal Dube, Victor Poulin et Simon Des-Alliers

**************************************************************************************************/
void roque_du_roi(t_etat_jeu* jeu, t_liste_coups* liste, int check_roq);

/*************************************************************************************************
    OBJECTIF : Effectue la mise-à-jour de la grille du "jeu" selon le "coup" joué.

	PARAMETRE :	jeu : la liste des coups possible
				coup: pour accèder à la liste des coups

	RETOUR: Retourne la valeur de la pièce de jeu qui a été capturée si c'est le cas.
		    Retour de 0 (VIDE) si aucune pièce a été capturée.

	ecrit par Pascal Dube, Victor Poulin et Simon Des-Alliers
*************************************************************************************************/
t_piece jouer_coup(t_etat_jeu* jeu, const t_coup* coup);

/************************************************************************************************
    OBJECTIF : Effectue la vérifiction de la possibilité pour le joueur courant de faire le
	           roque du roi.

	PARAMETRE :	etat_jeu : pour le roque_permis du joueur courant	

	RETOUR: Retourne la valeur de la roque_permis pour le joueur.
		    Retourne 1 si le roque est possible, sinon 0.

	ecrit par Pascal Dube, Victor Poulin et Simon Des-Alliers
**************************************************************************************************/
int verif_roque(t_etat_jeu* jeu);

/*************************************************************************************************
    OBJECTIF : Effectue la création de la grille du "jeu".

	PARAMETRE :	rien

	RETOUR: Retourne l'addresse de la premiere case si tous c'est bien passé NULL sinon.

	ecrit par Pascal Dube, Victor Poulin et Simon Des-Alliers
**************************************************************************************************/
t_grille creer_grille(void);

/************************************************************************************************
    OBJECTIF : Destruction de la grille du "jeu".

	PARAMETRE :	jeu : pour l'état de jeu pour accèder à la grille de jeu

	RETOUR: Retourne rien (void)

	ecrit par Pascal Dube, Victor Poulin et Simon Des-Alliers
**************************************************************************************************/
void detruire_grille(t_grille jeu);


/************************************************************************************************
	OBJECTIF : Mutateur du score de la grille. On ajoute la valeur associée à la pièce
               « capture » au score actuel de la grille.

	PARAMETRE :	Le jeu et la capture

	RETOUR: Retourne rien (void)
**************************************************************************************************/
void mise_a_jour_score(t_etat_jeu* jeu, int capture);

/************************************************************************************************
	OBJECTIF : Accesseur du score de la grille

	PARAMETRE :	Le jeu 

	RETOUR: int
**************************************************************************************************/


int get_score_grille(const t_etat_jeu* jeu);

#endif