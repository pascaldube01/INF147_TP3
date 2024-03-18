/*==========================================================*/
/* 
	Une courte pr�sentation francaise suit l'introduction en anglais des auteurs
	et donne le caract�re g�n�ral de chaque  fonction

   Les auteurs n'offrant que des distributions uniformes qui peuvent parfois 
   paraitre redondantes.
   J'ai ajout� des fonctions standardis�es pour obtenir des �v�nements  
   dans une distribution :
		uniforme g�n�rale( avec  ou  sans  bornes ) enti�re ou r�elle.
		normale avec Z(0,1) ou normale � moyenne et �cart-type d�finis
	
	Je n'ai ajout� qu'une pr�sentation minimale en francais aux fonctions originales
	offertes sans rien  y changer + quelques observations pour nos �tudiants

	Le commentaire en pr�sentation des d�clarations originales de fonctions 
	ne suit pas le mod�le donn� dans le cours....
	il est vraiment 'limit�' mais c'est souvent ainsi qu'on offre
	du code....  mal emball�.

	hs

*/
/*==========================================================*/

/*==========================================================*/
// DES AUTEURS
/* 
   A C-program for MT19937, with initialization improved 2002/1/26.
   Coded by Takuji Nishimura and Makoto Matsumoto.

   Before using, initialize the state by using init_genrand(seed)  
   or init_by_array(init_key, key_length).

   Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
   All rights reserved.                          

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:

     1. Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.

     2. Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.

     3. The names of its contributors may not be used to endorse or promote 
        products derived from this software without specific prior written 
        permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


   Any feedback is very welcome.
   http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html
   email: m-mat @ math.sci.hiroshima-u.ac.jp (remove space)
*/

/*==========================================================*/

#ifndef _MT19937AR_H_
#define _MT19937AR_H_
/*==========================================================*/

//permet de d�sactiver certains warnings de stdio
#define _CRT_SECURE_NO_WARNINGS   
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

/*==========================================================*/
/*==========================================================*/

/* VOICI UNE INTERFACE MODULAIRE STANDARD POUR MES �TUDIANT�E�S */

/*==========================================================*/
/*  D'abord l'offre de deux fonctions d'initialisation du
     g�n�rateur. Un g�n�rateur non-initialis� s'initialise 
     en fait � 0 et �met la m�me s�quence ce qui ferait douter
	 un n�ophite du caract�re al�atoire.... 
	 C'est au client d'initialiser un g�n�rateur
	 MAIS JUSTE UNE FOIS dans tout le programme qui l'utilise
*/

/*==========================================================*/
/* La fonction mt_srand 
 la forme d'initialisation la plus classique d'un g�n�rateur  
 � partir d'un entier quelconque en parametre, la s�quence pseudo al�atoire 
 � venir est totalement d�termin�e par la valeur donn�e 

PARAMETRE(s): s, un entier quelconque

SORTIE: aucune

SPECS: aucune
*/
void mt_srand(unsigned int s);

/*==========================================================*/


/*==========================================================*/
/* la fonction mt_srandSys 
 une forme alternative d'initialisation du g�n�rateur � partir 
 de l'horloge interne de la machine,  l'horloge donne un entier
 qui sert de param�tre � la fonction pr�c�dente. 
 Cette valeur est retourn�e pour des motifs de possible reproduction
 des conditions initiales d'une simulation num�rique.

PARAMETRE(s): Aucun

SORTIE: l'entier qui a v�ritablement initialis� le g�n�rateur

SPECS: aucune
*/
unsigned int mt_srandSys(void);
/*==========================================================*/

/* LES CINQ FONCTIONS D'�MISSION DANS DES DISTRIBUTIONS SP�CIFI�ES */

/*==========================================================*/
/* La fonction mt_rand   
L'�mission d'un nombre r�el dans la distribution uniforme 0,1 

PARAMETRE(s): Aucun

SORTIE : la valeur �mise par le g�n�rateur

SPECS : aucune
*/
double mt_rand(void);
/*==========================================================*/

/*==========================================================*/
/* La fonction mt_randf, issue de la pr�c�dente

L'�mission selon une distribution uniforme dans intervalle [b1, b2] 

PARAMETRE(s): deux valeurs r�elles quelconques qui serviront 
               de bornes � l'intervalle

SORTIE : la valeur �mise par le g�n�rateur

SPECS : l'ordre des param�tres n'a aucune importance
*/
double mt_randf(double b1, double b2);
/*==========================================================*/

/*==========================================================*/
/* La fonction mt_randi

L'�mission d'un nombre entier positif dans une uniforme [1, borne]

PARAMETRE(s): une valeur enti�re quelconque

SORTIE : la valeur enti�re �mise par le g�n�rateur

SPECS :  si le param�tre effectif < 0 , c'est la valeur absolue 
			du param�tre  qui sera consid�r�e
         recevant 0 elle retourne automatiquement 0 et 
			c'est le seul 0 possible
*/
int mt_randi(int borne);
/*==========================================================*/
/*==========================================================*/
/* La fonction mt_randU

L'�mission d'un nombre entier positif dans une uniforme [0, borne-1]

PARAMETRE(s): un unsigned

SORTIE : la valeur enti�re �mise par le g�n�rateur

SPECS :   recevant 0 elle retourne automatiquement 0 
*/
unsigned int mt_randU(unsigned int borne);
/*==========================================================*/

/*==========================================================*/
/* La fonction mt_randn

L'�mission d'un nombre r�el dans la distribution normale Z, 
la plus classique  de moyenne 0 et d'�cart type 1

PARAMETRE(s) : Aucun

SORTIE : la valeur r�elle �mise par le g�n�rateur

SPECS : celle-ci a une parit� dans l'�mission
ce qui peut d�concerter si on r�initialise le g�n�rateur
en cours d'ex�cution ( ce qui en r�alit� ne doit PAS �tre fait)
*/
double mt_randn(void);
/*==========================================================*/

/*==========================================================*/
/* La fonction mt_randnormal

L'�mission d'un nombre r�el dans une distribution normale quelconque, 
  de moyenne mu  et d'�cart-type sigma donn�s

PARAMETRE(s) : mu d�finit la moyenne voulue et sigma l'�cart-type

SORTIE : la valeur r�elle �mise par le g�n�rateur

SPECS : le signe de sigma n'a pas d'importance.
*/
double mt_randnormal(double mu, double sigma);

/*==========================================================*/






/*==========================================================*/
/* SUIT L'INTERFACE ORIGINALE DES DEUX CR�ATEURS */
/*==========================================================*/
/* 
   l'utilisation du type long par les auteurs avait une importance
   historique lorsque les entiers de base(int) pouvaient encore avoir une 
   repr�sentation � 16 bits, le long nous assurait de 32 bits (ce 
   que les auteurs consid�rent normal, puisque c'est le format 
   qu'ils d�crivent partout) et c'est 32 bits qu'on obtient maintenant 
   sur tout compilateur moderne avec un int.

   l'utilisation du modificateur unsigned  par les auteurs 
   fait partie des choixs offerts au client. Les auteurs auraient bien
   pu passer sous silence et tout dans l'interface serait en int.
   
	Encore par souci d'�largir l'interface, les auteurs offrent toutes 
	les 4 formes d'uniformes r�elles entre 0 et 1 :
		(0,1) intervalle ouvert --sans 0 ni 1 --
		[0,1) intervalle ouvert � droite -- avec 0 mais sans 1 --
		(0,1] intervalle ouvert � gauche -- sans 0 mais avec 1 --
		[0,1] intervalle ferm�  -- avec 0 et avec 1 --

  */
/*==========================================================*/
/*	Deux formes d'init possibles.
	Vous pouvez ne pas vous pr�occuper du unsigned long 
	en param�tre formel et donner un int ou un tableau 
	de int (En assumant alors le warning possible)
*/
/*==========================================================*/

/* initializes mersenne twister 
   pseudo-random number generator with a seed */
/* initialisation � partir d'un entier quelconque */
/* la s�quence pseudo al�atoire sera totalement d�termin�e*/

void mt_init_genrand(unsigned long s);
/*==========================================================*/


/*	initialize by an array with array-length
	init_key is the array for initializing keys
	key_length is its length
	slight change for C++, 2004/2/26
	idem in ANSI C
*/
/* variante de la pr�c�dente mais ici,
  donnez- lui un tableau  d'entiers et la taille du tableau */

void mt_init_by_array(const unsigned long init_key[], int key_length);
/*==========================================================*/

/* generates a random number on [0,0xffffffff]-interval*/
/* Pour obtenir un entier sur 32 bits pseudo-al�atoires */
unsigned long mt_genrand_int32(void);

/*==========================================================*/
/* generates a random number on [0,0x7fffffff]-interval*/
/* Pour obtenir un entier sur 31 bits pseudo-al�atoires */
/* Vous �tes simplement assur� qu'il ne sera pas n�gatif */
/* si on r�cup�re dans un int � 32 bits*/
long mt_genrand_int31(void);

/*==========================================================*/

/*==========================================================*/

/* These real versions are due to Isaku Wada, 2002/01/09 added */

/* et les quatre uniformes dans l'intervalle 0,1 */
/* simplement diff�renci�es par le suffixe 1,2,3,53*/
/* PAS tr�s fort comme repr�sentativit� ...... */
/* mais l'�me japonaise souffre surement des m�mes maux que la notre!*/

/* generates a random number on [0,1]-real-interval*/
double mt_genrand_real1(void);

/* generates a random number on [0,1)-real-interval*/
double mt_genrand_real2(void);

/* generates a random number on (0,1)-real-interval*/
double mt_genrand_real3(void);

/* generates a random number on [0,1) with 53-bit resolution*/
double mt_genrand_res53(void);
/*==========================================================*/

/*==========================================================*/
#endif	
/*==========================================================*/

