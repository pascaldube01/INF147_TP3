/********************************************************************/
/* Par       : Eric Thé       								        */
/* Fichier   : SOURISLIB.CPP	(fichier donné aux élèves)          */
/*															   		*/
/* Ce module implante des fonctions de gestion de souris de base.   */
/* Utilise des commandes de la librairie standard <winuser.h>.		*/
/********************************************************************/
#include "sourislib.h"
#include "winbgim.h"   //contient les fonctions de souris

/********************************************************************/
/*  Les constantes suivantes peuvent etre utilisées dans ce code:   */ 
/*                                                                  */ 
/*  WM_LBUTTONDOWN - indique que le bouton de gauche est pesé       */
/*  WM_MBUTTONDOWN - indique que le bouton du milieu est pesé       */
/*  WM_RBUTTONDOWN - indique que le bouton de droite est pesé       */
/*  WM_LBUTTONUP   - indique que le bouton de gauche est relevé     */
/*  WM_MBUTTONUP   - indique que le bouton du milieu est relevé     */
/*  WM_RBUTTONUP   - indique que le bouton de droite est relevé     */
/*  WM_LBUTTONDBLCLK - indique un double-clic sur le bouton gauche  */
/*  WM_MBUTTONDBLCLK - indique un double-clic sur le bouton milieu  */
/*  WM_RBUTTONDBLCLK - indique un double-clic sur le bouton droite  */
/********************************************************************/

//-------------------------------------------------------------------
/* Permet de positionner la souris a la position-écran (x, y). */
void  positionne_souris (int x, int y )
{  SetCursorPos(x, y); }

//-------------------------------------------------------------------
/* Permet d'obtenir la position actuelle (x, y) de la souris. */
void  obtient_souris (int *x, int *y)
{  clearmouseclick(WM_LBUTTONDOWN);
   *x = mousex();  
   *y = mousey();  
}

//-------------------------------------------------------------------
/* Permet d'obtenir la coordonnée "x" de la position actuelle */ 
int  sourisX (void)
{ int x,y;
  
  obtient_souris(&x,&y);
  return (x);
}

//-------------------------------------------------------------------
/* Permet d'obtenir la coordonnée "y" de la position actuelle */
int  sourisY (void)
{ int x,y;
  
  obtient_souris(&x,&y);
  return(y);
}

//-------------------------------------------------------------------
/* Permet de désactiver le bouton de gauche de la souris */
void eteindre_bouton_souris()  //int code_bouton)
{
    clearmouseclick(WM_LBUTTONDOWN);
}

//-------------------------------------------------------------------
/* Permet de savoir si le bouton de gauche de la souris à été pesé */
int  bouton_pese(void)
{ if (ismouseclick(WM_LBUTTONDOWN)) {   
	clearmouseclick(WM_LBUTTONDOWN);
    return 1;
  }
  return (0);
}

//-------------------------------------------------------------------
/* Permet de savoir si le bouton de gauche à été cliqué deux fois */
int  double_clic_pese(void)
{
    return (ismouseclick(WM_LBUTTONDBLCLK));   //utiliser WM_LBUTTONDBLCLK pour un double-clic
}

//-------------------------------------------------------------------
/* Permet de savoir si le bouton de gauche de la souris à été relaché */
int  bouton_releve(void)
{ if (ismouseclick(WM_LBUTTONUP)) { 
	clearmouseclick(WM_LBUTTONUP);
    return 1;
  }
  return (0);
}

//-------------------------------------------------------------------
/* Permet de savoir si la souris à bougée à l'écran */
int  souris_bouge(void)
{ if (ismouseclick(WM_MOUSEMOVE)) { 
	clearmouseclick(WM_MOUSEMOVE);
    return 1;
  }
  return (0);
}

//-------------------------------------------------------------------
/* Cette fonction va attendre que le bouton gauche soit pesé */
void attend_bouton_pese(void)
{ clearmouseclick(WM_LBUTTONUP);
  
  while (!ismouseclick(WM_LBUTTONDOWN)) 
     delay_graph(10);    //délai necéssaire pour permettre de capturer un évenement-souris
}

//-------------------------------------------------------------------
/* Cette fonction va attendre que le bouton gauche soit relevé */
void attend_bouton_releve(void)
{  while (!ismouseclick(WM_LBUTTONUP)) 
     delay_graph(10);    //délai necéssaire pour permettre de capturer un évenement-souris
}

//-------------------------------------------------------------------
/* Fonction qui test si la position actuelle de la souris est dans 
   les limites données par (x1, y1) (x2, y2) */
int test_region_souris(int x1, int y1, int x2, int y2)
{ int x,y;

  obtient_souris(&x,&y);
  if ((x < x1) || (x > x2) || (y < y1) || (y > y2))  return (0);  //hors-limites

  return (1);    //ok, dans les limites
}

//-------------------------------------------------------------------