/********************************************************************/
/* Fichier   : SOURISLIB.H  (fichier donn� aux �l�ves)           	*/
/* Par       : Eric Th�       								        */
/*															   		*/
/* Ce module implante des fonctions de gestion de souris de base.   */
/* Utilise des commandes de la librairie standard <winuser.h>.		*/
/********************************************************************/

/* IMPORTANT :                                                         */
/* Toutes les positions-�cran utilis�es ici sont absolues, donc on     */
/* ne tiens pas compte de l'existence d'un "viewport" d'affichage :    */
/*   avec (0, 0) au coin sup. gauche de l'�cran en tout temps.         */

/* Permet de positionner la souris a la position-�cran absolue (x, y). */
void  positionne_souris(int x, int y);

/* Permet d'obtenir la position absolue actuelle (x, y) de la souris.  */
void  obtient_souris(int *x, int *y);

/* Permet d'obtenir la coordonn�e absolue "x" de la position actuelle. */ 
int  sourisX(void);

/* Permet d'obtenir la coordonn�e absolue "y" de la position actuelle. */
int  sourisY(void);

/* Permet de d�sactiver le bouton-gauche de la souris.                 */
void eteindre_bouton_souris(); 

/* Permet de savoir si le bouton-gauche de la souris � �t� pes� (0/1). */
int  bouton_pese(void);

/* Permet de savoir si le bouton-gauche � �t� cliqu� deux fois (0/1).  */
int  double_clic_pese(void);

/* Pour savoir si le bouton-gauche de la souris � �t� relach� (0/1).   */
int  bouton_releve(void);

/* Permet de savoir si la souris � boug�e � l'�cran (0 ou 1).    */
int  souris_bouge(void);

/* Cette fonction va attendre que le bouton-gauche soit pes�.    */
void attend_bouton_pese(void);

/* Cette fonction va attendre que le bouton-gauche soit relach�. */
void attend_bouton_releve(void);

/* Fonction qui teste si la position actuelle de la souris est  
   dans les limites (rectangle) donn�es par (x1, y1) (x2, y2).   */
int test_region_souris(int x1, int y1, int x2, int y2);

//-------------------------------------------------------------------
//-------------------------------------------------------------------












