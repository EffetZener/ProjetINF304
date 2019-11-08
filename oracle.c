#include <stdio.h>
#include <stdlib.h>
#include "curiosity.h"


int main(int argc, char* argv[]){
	if(argc < 2 ) {
		printf("Erreur : fichier test requis en argument");
		return EXIT_FAILURE;	
	}
	else{
		FILE* f=fopen(argv[1], 'r');
		char* nomFichierTerrain;
		fscanf(f, nomFichierTerrain);
		Terrain* terrain = (Terrain)malloc(sizeof(Terrain));
		Robot* robot = (Robot)malloc(sizeof(Robot));
		lire_terrain(nomFichierTerrain, terrain,  robot->x, robot-> y);
		
		
		
		 
		return EXIT_SUCCESS;	
	}	
}
