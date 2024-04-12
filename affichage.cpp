/*******************************************************************************
	AFFICHAGE.CPP  (version pour le TP3)
	Auteurs : Victor Poulin, Pascal Dube et Simon Des-Alliers
	Date: 18 mars 2024

	Module qui contient les fonctions de gestion de l'affichage de la grille et
	des coups jouées avec des images Bitmap en mode graphique.

	Liste des fonctions:t_saisie choix_case(int* col_case, int* lig_case)
	                    void afficher_grille(const t_etat_jeu* jeu)
	                    int lire_images(const char* nom_fich_bin)
                        void detruire_images()
                       	void afficher_coup(t_piece piece_src, int col_src, int ran_src,
	                         t_piece piece_dest, int col_dest, int ran_dest)
                        void afficher_gagnant(int joueur)
*******************************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "affichage.h"

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
	int validation = 0;

	//Tant qu'on a pas obtenue un choix de case valide
	do
	{
		//On désactive les boutons de la souris 
		eteindre_bouton_souris();

		//Contient une boucle vide qui roule jusqu’à ce qu’on clique le bouton-gauche de la souris
		attend_bouton_pese();

		//On récupère les coordonnées du clic-souris
		obtient_souris(col_case, lig_case);

		//Si on a cliqué sur QUITTER
		if ((*col_case >= POSX_BOUT_QUIT) && (*col_case <= POSX_BOUT_QUIT + TAILLEX_BOUTON) &&
			(*lig_case >= POSY_BOUT_QUIT) && (*lig_case <= POSY_BOUT_QUIT + TAILLEY_BOUTON))
		{
			//On met -1 dans la colonne et la ligne
			*col_case = POS_VIDE;
			*lig_case = POS_VIDE;

			//On retourne -1
			return QUITTER;
		}

		//Si on a cliqué sur RESET
		if ((*col_case >= POSX_BOUT_RESET) && (*col_case <= POSX_BOUT_RESET + TAILLEX_BOUTON) &&
			(*lig_case >= POSY_BOUT_RESET) && (*lig_case <= POSY_BOUT_RESET + TAILLEY_BOUTON))
		{
			//On met -1 dans la colonne et la ligne
			*col_case = POS_VIDE;
			*lig_case = POS_VIDE;

			//On retourne 0
			return RESET;
		}

		//À partir d'ici, on n'a pas souhaité quitter ou recommencer, donc on vérifie la validité
		//du clic

		//pour obtenir la position-case équivalente (entre 0 - 7)
		*col_case = ((*col_case - MARGEX) / TAILLE_BMP);
		*lig_case = ((*lig_case - MARGEY) / TAILLE_BMP);

		//Si le clic de la souris se situe sur le grille, on valide le clic
		if(*col_case >= 0 && *col_case <= 7 && *lig_case >= 0 && *lig_case <= 7)
		{
			//Permet de sortir de la boucle de validation
			validation = 1;
		}

	} while (!validation);

	//On retourne 1
	return POS_VALIDE;

}

void afficher_grille(const t_etat_jeu* jeu)
{
	int piece; //Contient la pièce à la colonne et la rangée choisit

	//On dessinne le cadre de la grille de jeu
	init_zone_grille(TAILLE, TAILLE);

	//On parcourt toute la grille
	for (int i = 0; i < TAILLE; i++)
	{
		for (int j = 0; j < TAILLE; j++)
		{
			//On va chercher la pièce à la case voulue
			piece = (int)get_piece_case(jeu, j, i);

			//On affiche la pièce sur la grille
			afficher_piece(i * TAILLE_BMP, j * TAILLE_BMP, 
			images[PALE_FONCER(i, j)][piece].header.height,
			images[PALE_FONCER(i, j)][piece].header.width,
			images[PALE_FONCER(i, j)][piece].image_data);
		}
	}

	//On crée un gabarit de la grille initialisée
	dessiner_grille_vide();
}

int lire_images(const char* nom_fich_bin)
{
	/*ouverture du fichier et test de l'ouverture*/
	FILE* fichier_images = fopen(nom_fich_bin, "rb");
	if (fichier_images == NULL)
		return 0;

	/*parcourt du fichier .bin pour lire les 32 images qui s'y trouve. on utilise deux boucles for
	pour remplir les deux dimensions du tableaux images[][]*/
	for (int i=0; i<2; i++)
		for (int j=0; j<16; j++)
		{
			/*lecture du header du fichier*/
			fread(&images[i][j].header, sizeof(t_BMP_Header), 1, fichier_images);

			/*allocation du tableau pour lire les données de l'image*/
			images[i][j].image_data = (UCHAR*) malloc(images[i][j].header.image_data_size);
			assert(images[i][j].image_data);

			/*lecture des donnes de l'image*/
			fread(images[i][j].image_data,
				  images[i][j].header.image_data_size,
				  1,
				  fichier_images);
		}

	//On ferme le fichier
	fclose(fichier_images);

	//On retourne 1 pour confirmer qu'on a ouvert le fichier correctement
	return 1;
}


/*******************************************************************************/

void detruire_images()
{
	/*Destruction des pointeurs des donnees des images*/
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 16; j++)
			free(images[i][j].image_data);
}

/*******************************************************************************/

void afficher_coup(t_piece piece_src, int col_src, int ran_src,
	t_piece piece_dest, int col_dest, int ran_dest)
{
	/*on se sert de pointeurs vers les fichiers images en memoire pour simplifier la lecture*/
	t_image_BMP * origine_origine = &images[PALE_FONCER(ran_src, col_src)][piece_src];
	t_image_BMP * origine_destination = &images[PALE_FONCER(ran_dest, col_dest)][piece_dest];
	t_image_BMP * piece_a_destination = &images[PALE_FONCER(ran_dest, col_dest)][piece_src];
	t_image_BMP * vide_origine = &images[PALE_FONCER(ran_src, col_src)][VIDE];

	/*on clignote le coup de son etat present a son etat futur*/
	for (int i = 0; i < 3; i++)
	{
		/*remise de la piece source a la source*/
		afficher_piece(ran_src * TAILLE_BMP, col_src * TAILLE_BMP,
			origine_origine->header.height,
			origine_origine->header.width,
			origine_origine->image_data);

		/*remise de la piece destination a la destination*/
		afficher_piece(ran_dest * TAILLE_BMP, col_dest * TAILLE_BMP,
			origine_destination->header.height,
			origine_destination->header.width,
			origine_destination->image_data);


		delai_ecran(200);


		/*affichage de la piece a la destination*/
		afficher_piece(ran_dest * TAILLE_BMP, col_dest * TAILLE_BMP,
			piece_a_destination->header.height,
			piece_a_destination->header.width,
			piece_a_destination->image_data);

		/*mise a vide de la case source*/
		afficher_piece(ran_src * TAILLE_BMP, col_src * TAILLE_BMP,
			vide_origine->header.height,
			vide_origine->header.width,
			vide_origine->image_data);

		delai_ecran(200);
	}
}

void afficher_gagnant(int joueur)
{/*Avec afficher_info pour afficher le gagnant en haut du message de fin*/
	/*Si le joueur est blanc*/
	if (joueur)
	{ 
		afficher_info("Le gagnant est le joueur blanc!", joueur);
	}
	else
	{
		/*Si le joueur est noir*/
		afficher_info("Le gagnant est le joueur noir!", joueur);
	}
}