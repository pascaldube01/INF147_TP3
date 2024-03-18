/*******************************************************************************
    LISTE_COUPS.HPP  (version pour le TP3)
    Auteurs : Simon Des-Alliers, PAscal Dubé et Victor Poulin

    Module qui contient les fonctions de gestion d'une liste chainée de coups.
    Ce module est indépendant et n'inclut rien.
*******************************************************************************/
#if !defined(POS_VIDE)

#define TAILLE_GR    8      //taille carrée de la grille de jeu
#define POS_VIDE    -1      //indique une position non-valide ou non-utilisée

//les deux macros de conversion de coordonnées (pour remplir un "texte_coup")
#define COL_A_CH(c)  ((c) + 'a')
#define RAN_A_NO(r)  (TAILLE_GR - (r) + '0')

/*-------------------------------------------------------------------*/
/*                    TYPES POINTEURS ET STRUCT                      */
/*-------------------------------------------------------------------*/

//NOTE: Ce type-struct n'est PAS encapsulé. Vous avez le droit d'accéder à
//      n'importe quel de ses 7 champs directement n'importe-où dans le projet.
typedef struct
{
    char texte_coup[6];         //le coup en texte. Ex. "a1-b2"
    int col, lig;               //position-départ du coup (source)
    int col_dest, lig_dest;     //position-arrivée du coup (destination)
    int col_case2, lig_case2;   //la case secondaire concernée (en-passant et roque) 
} t_coup;

/* Les types nécessaires pour la liste chainée de coups */
typedef struct noeud* t_lien;      //type-pointeur vers un neoud

/* la structure-noeud contenant un coup et le lien vers le coup suivant */
struct noeud
{
    t_coup coup;
    t_lien suivant;     //pointeur vers le noeud suivant
};

/* structure principale de gestion de la liste chainée */
typedef struct
{
    t_lien tete;        //la tête de la liste
    t_lien fin;         //la fin de la liste
    t_lien p_courant;   //le pointeur-courant (pour parcourir la liste)
    int nb_noeuds;      //le nombre d'éléments dans la liste
} t_liste_coups;


/*-------------------------------------------------------------------*/
/*                       FONCTIONS PUBLIQUES                         */
/*-------------------------------------------------------------------*/

/*-------------------------------------------------------------------*/
/*                     FONCTIONS INFORMATRICES                       */
/*-------------------------------------------------------------------*/
/* obtenir le coup du neoud pointé par le pointeur-courant */
t_coup get_coup_pc(const t_liste_coups* liste_coups);

/* Accesseur qui permet de savoir le nombre de coups valides dans la liste. */
int get_nb_coups(const t_liste_coups* liste_coups);

/* Valide si le "coup" reçu est dans la liste des coups possibles à jouer.  On reçoit  */
/* la représentation-texte du coup à retrouver.  On parcourt la liste en comparant le  */
/* texte reçu avec le champ "texte_coup" de chaque coup.  Si ce texte a été retrouvé,  */
/* on retourne une copie de ce coup via la référence "*coup" et on retourne 1.  Sinon, */
/* on retourne 0 (coup non-présent dans la liste). */
int valider_coup(t_liste_coups* liste_coups, char* texte_coup, t_coup* coup);

/* Valide si la position-destination (col, lig) reçue fait partie d'un des coups de la */
/* liste. On reçoit les coordonnées de la case "col, lig" et on parcourt la liste à la */
/* recherche d'un coup qui a la même case-destination que (col, lig). Dès qu'on trouve */
/* un coup qui atteint cette case, la fonction arrête sa recherche et retourne 1.      */
/* Sinon, elle retourne 0 (aucun coup de la liste se rends à la case [col, lig]). */
int valider_case_dest(t_liste_coups* liste_coups, int col, int lig);

/*-------------------------------------------------------------------*/
/*                         LES MUTATEURS                             */
/*-------------------------------------------------------------------*/
/* Initialiser la liste de coups. On mets les trois pointeurs de la liste à NULL et on */
/* met le nombre d'éléments de la liste à zéro. */
void init_liste_coups(t_liste_coups* liste_coups);

/* Fonction qui crée un nouveau coup. Les 6 derniers paramètres sont copiés dans leurs */
/* champs respectifs de la référence "coup".  On doit aussi former la représentation-  */
/* texte du coup à partir des valeurs "col, lig" et "col_dest, lig_dest". Eg. "a2-a4". */
void set_coup(t_coup* coup, int col, int lig, int col_dest, int lig_dest, int col2, int lig2);

/* Ajoute un nouveau coup à la fin de la liste de coups reçue en référence. On crée un */
/* nouveau noeud. On y copie le coup reçu et on l'ajoute à la FIN de la liste chainée. */
/* Si l'allocation du nouveau noeud a échoué, la fonction retourne 0. Sinon, on ajoute */
/* le coup, on place le pointeur de fin de liste sur le nouveau coup et on retourne 1. */
int ajouter_coup(t_liste_coups* liste_coups, const t_coup* coup);

/* Ajoute un coup au début de la liste de coups. On crée un nouveau noeud. On y copie  */
/* le coup reçu et on l'ajoute au DÉBUT de la liste. Si l'allocation du nouveau noeud  */
/* a échoué, la fonction retourne 0. Sinon, on ajoute le coup et on retourne 1. */
int ajouter_coup_debut(t_liste_coups* liste_coups, const t_coup* coup);

/* Vider la liste des coups en détruisant tous les noeuds de la liste et en remettant  */
/* son "nb_noeuds" à zéro. Les trois pointeurs seront mis à NULL. */
void vider_liste_coups(t_liste_coups* liste_coups);

/* Replacer le pointeur-courant sur le noeud de tête. */
void replacer_pc_debut(t_liste_coups* liste_coups);

/* Si le pointeur-courant est non-NULL et qu'il ne pointe pas sur le dernier noeud, on */
/* l'avance au noeud suivant et on retourne 1. Sinon on le bouge pas et on retourne 0. */
int  avancer_pc(t_liste_coups* liste_coups);

/* Effectue un choix de coup aléatoire dans la liste de coups. On génére une position  */
/* aléatoirement entre [0..nb_noeuds-1] et on parcours la liste à partir du début en   */
/* faisant "pos_alea" déplacements (avec le "p_courant").  On retourne le coup qui se  */
/* trouve dans le noeud suite aux "pos_alea" déplacements (utilisée pour le MANDAT 1). */
t_coup choix_coup_ordi(t_liste_coups* liste_coups);

/* Affiche le contenu de la liste dans la console-texte (SANS le "Winconsole" pour la  */
/* version finale du projet).  Sera utile pour les débuggages seulement. */
void afficher_liste_coups(t_liste_coups* liste_coups);

/* Détruire la liste de coups. Faites simplement un appel à "vider_liste_coups()" ici. */
void detruire_liste_coups(t_liste_coups* liste_coups);

#endif