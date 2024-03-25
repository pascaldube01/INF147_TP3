/*******************************************************************************
	AFFICHAGE.CPP  (version pour le TP3)
	Auteurs :

	Module qui contient les fonctions de gestion de l'affichage de la grille et
	des coups jouées avec des images Bitmap en mode graphique.
*******************************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "affichage.hpp"

/* Type definitions */
typedef unsigned int  UINT;
typedef unsigned short int USHORT;
typedef unsigned char  UCHAR;

/* Bitmap header */
typedef struct _BMP_Header
{   //Windows header values
	USHORT magicID;				/* Magic identifier: "BM" */
	UINT   file_size;			/* Size of the BMP file in bytes */
	USHORT reserved1;			/* Reserved */
	USHORT reserved2;			/* Reserved */
	UINT   data_offset;			/* Offset of image data relative to the file's start */

	//Bitmap header values
	UINT   headersize;			/* Size of the header in bytes */
	UINT   width;				/* Bitmap's width */
	UINT   height;				/* Bitmap's height */
	USHORT planes;				/* Number of color planes in the BMP */
	USHORT bits_per_pixel;		/* Number of bits per pixel */
	UINT   compression_type;	/* Compression type */
	UINT   image_data_size;		/* Size of uncompressed image's data */
	UINT   Hpixels_per_meter;	/* Horizontal resolution (pixels per meter) */
	UINT   Vpixels_per_meter;	/* Vertical resolution (pixels per meter) */
	UINT   colors_used;			/* Number of color indexes in the color table used by the BMP */
	UINT   colors_required;		/* Number of color indexes required for displaying the BMP */
} t_BMP_Header;

typedef struct _image_BMP
{
	t_BMP_Header  header;   //en-tête du fichier bitmap
	UCHAR* image_data;		//liste des pixels (3 octets par pixel)
} t_image_BMP;

//Variable-privée qui contient les 32 bitmaps de toutes les pièces de jeu possibles :
// Rangée [0]: les 16 pièces de jeu sur fond vert-pale (aux positions-paires)
// Rangée [1]: les 16 pièces de jeu sur fond vert-foncé (positions-impaires)
static t_image_BMP images[2][16];

t_saisie choix_case(int* col_case, int* lig_case)
{
	int colonne;
	int ligne;
	int validation = 0;

	//Tant qu'on a pas obtenue un choix de case valide
	while(!validation)
	{
		//On désactive les boutons de la souris 
		eteindre_bouton_souris();

		//Contient une boucle vide qui roule jusqu’à ce qu’on clique le bouton-gauche de la souris
		attend_bouton_pese();

		//On récupère les coordonnées du clic-souris
		obtient_souris(col_case, lig_case);

		//pour obtenir la position-case équivalente (entre 0 - 7)
		colonne = ((*col_case - MARGEX) / TAILLE_BMP);
		ligne = ((*lig_case - MARGEY) / TAILLE_BMP);

		//Si le clic de la souris se situe sur le grille, on valide le clic
		if(colonne >= 0 && colonne <= 7 && ligne >= 0 && ligne <= 7)
		{
			//Permet de sortir de la boucle de validation
			validation = 1;

			//On retourne 1
			return POS_VALIDE;
		}
	}

}