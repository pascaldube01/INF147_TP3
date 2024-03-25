/********************************************************************/
/* Fichier   : SOURISLIB.H  (fichier donné aux élèves)           	*/
/* Par       : Eric Thé       								        */
/*															   		*/
/* Ce module implante des fonctions de gestion de souris de base.   */
/* Utilise des commandes de la librairie standard <winuser.h>.		*/
/********************************************************************/

/* IMPORTANT :                                                         */
/* Toutes les positions-écran utilisées ici sont absolues, donc on     */
/* ne tiens pas compte de l'existence d'un "viewport" d'affichage :    */
/*   avec (0, 0) au coin sup. gauche de l'écran en tout temps.         */

/* Permet de positionner la souris a la position-écran absolue (x, y). */
void  positionne_souris(int x, int y);

/* Permet d'obtenir la position absolue actuelle (x, y) de la souris.  */
void  obtient_souris(int *x, int *y);

/* Permet d'obtenir la coordonnée absolue "x" de la position actuelle. */ 
int  sourisX(void);

/* Permet d'obtenir la coordonnée absolue "y" de la position actuelle. */
int  sourisY(void);

/* Permet de désactiver le bouton-gauche de la souris.                 */
void eteindre_bouton_souris(); 

/* Permet de savoir si le bouton-gauche de la souris à été pesé (0/1). */
int  bouton_pese(void);

/* Permet de savoir si le bouton-gauche à été cliqué deux fois (0/1).  */
int  double_clic_pese(void);

/* Pour savoir si le bouton-gauche de la souris à été relaché (0/1).   */
int  bouton_releve(void);

/* Permet de savoir si la souris à bougée à l'écran (0 ou 1).    */
int  souris_bouge(void);

/* Cette fonction va attendre que le bouton-gauche soit pesé.    */
void attend_bouton_pese(void);

/* Cette fonction va attendre que le bouton-gauche soit relaché. */
void attend_bouton_releve(void);

/* Fonction qui teste si la position actuelle de la souris est  
   dans les limites (rectangle) données par (x1, y1) (x2, y2).   */
int test_region_souris(int x1, int y1, int x2, int y2);

//-------------------------------------------------------------------
//-------------------------------------------------------------------












