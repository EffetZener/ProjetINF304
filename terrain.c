
#include "terrain.h"
#include "robot.h"
#include <stdio.h>
#include <string.h>

erreur_terrain lire_terrain(char * nom_fichier, Terrain * t, int * x, int * y) {
  FILE * f;
  int l, h; // Dimensions du terrain
  int rx, ry; // Coordonnées initiales du robot
  char c;
  // Ouverture du fichier en lecture
  f = fopen(nom_fichier, "r");
  if (f == NULL) {
    return ERREUR_FICHIER;
  }
  
  if (feof(f)){
    return ERREUR_FICHIER;
  }

  // Lecture de la largeur
  // À compléter
  fscanf(f,"%d\n",&l);
  t->largeur=l;
  // Lecture de la hauteur
  // À compléter
  fscanf(f,"%d\n",&h);
  t->hauteur=h;
  // Lecture du terrain
  // À compléter
  
  
  fscanf(f,"%c",&c);
  for (int i=0;i<h;i++){
	for (int j=0; j<l;j++){
		switch (c) {
			case '#': t->tab[i][j]=ROCHER;
				break;
			case '~': t->tab[i][j]=EAU;
				break;
			case '.':t->tab[i][j]=LIBRE;
				break;
			case 'C': t->tab[i][j]=LIBRE;
				rx=i;
				ry=j;
				break;
		}
		
		fscanf(f,"%c",&c);
	}
	fscanf(f,"%c",&c);
  }
  // Initialisation de la position du robot
  // À compléter

  // Fermeture du fichier
  fclose(f);
  *x=rx;
  *y=ry;
  return OK;
}

int largeur(Terrain t){
	return t.largeur;
}

int hauteur(Terrain t){
	return t.hauteur;
}

int est_case_libre(Terrain t, int x, int y){
	if ( (x>(t.largeur)) || (y>(t.hauteur)) ) {
		return 0;
	}
	else if (x<0 || y <0){
		return 0;
	}
	
	return (t.tab[x][y]==LIBRE);

}

void afficher_terrain(Terrain * t){
	for (int i=0;i<t->hauteur;i++){
		for (int j=0; j<t->largeur;j++){
			switch (t->tab[i][j]){
				case LIBRE : printf(".");break;
				case EAU : printf("~");break;
				case ROCHER: printf("#");break;
			}
			
		}
		printf("\n");
	}
}	
		

/* À compléter */

