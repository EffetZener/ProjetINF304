#include "environnement.h"
#include "programme.h"
#include "interprete.h"
#include "generation_terrains.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define lgMax 1000
void gestion_erreur_terrain(erreur_terrain e) {
  switch(e) {
  case OK: break;
  case ERREUR_FICHIER:
    printf("Erreur lecture du terrain : erreur d'ouverture du fichier\n");
    exit(1);
  case ERREUR_LECTURE_LARGEUR:
    printf("Erreur lecture du terrain : erreur de lecture de la largeur\n");
    exit(1);
  case ERREUR_LECTURE_HAUTEUR:
    printf("Erreur lecture du terrain : erreur de lecture de la hauteur\n");
    exit(1);
  case ERREUR_LARGEUR_INCORRECTE:
    printf("Erreur lecture du terrain : largeur incorrecte\n");
    exit(1);
  case ERREUR_HAUTEUR_INCORRECTE:
    printf("Erreur lecture du terrain : hauteur incorrecte\n");
    exit(1);
  case ERREUR_CARACTERE_INCORRECT:
    printf("Erreur lecture du terrain : caractère incorrect\n");
    exit(1);
  case ERREUR_LIGNE_TROP_LONGUE:
    printf("Erreur lecture du terrain : ligne trop longue\n");
    exit(1);
  case ERREUR_LIGNE_TROP_COURTE:
    printf("Erreur lecture du terrain : ligne trop courte\n");
    exit(1);
  case ERREUR_LIGNES_MANQUANTES:
    printf("Erreur lecture du terrain : lignes manquantes\n");
    exit(1);
  case ERREUR_POSITION_ROBOT_MANQUANTE:
    printf("Erreur lecture du terrain : position initiale du robot manquante\n");
    exit(1);
  }
}

void affichage_position_programme(erreur_programme e) {
  int i;
  printf("Ligne %d, colonne %d :\n", e.num_ligne, e.num_colonne);
  printf("%s\n", e.ligne);
  /* Impression de e.num_colonne-1 espaces */
  for(i = 1; i < e.num_colonne; i++) {
    printf(" ");
  }
  /* Impression d'un curseur de position */
  printf("^\n");
}

void gestion_erreur_programme(erreur_programme e) {
  switch(e.type_err) {
  case OK_PROGRAMME: break;
  case ERREUR_FICHIER_PROGRAMME:
    printf("Erreur lecture du programme : erreur d'ouverture du fichier\n");
    exit(2);
  case ERREUR_BLOC_NON_FERME:
    printf("Erreur lecture du programme : bloc non fermé\n");
    exit(2);
  case ERREUR_FERMETURE_BLOC_EXCEDENTAIRE:
    printf("Erreur lecture du programme : fermeture de bloc excédentaire\n");
    affichage_position_programme(e);
    exit(2);
  case ERREUR_COMMANDE_INCORRECTE:
    printf("Erreur lecture du programme : commande incorrecte\n");
    affichage_position_programme(e);
    exit(2);
  }
}

int main(int argc, char ** argv){
	if (argc < 8) {
    		printf("Utilisation: %s <programme> <nbTerrains> <largeur> <hauteur> <densite> <nb_step_max> <fichier_res>\n", argv[0]);
    		return EXIT_FAILURE;
	}
	int nbTerrain, largeur, hauteur, nb_step_max = 0;
	char prog[lgMax];
	char progRes[lgMax];
	strcpy(prog,argv[1]);
	strcpy(progRes,argv[7]);
	printf("%s ; %s; %s %s\n",argv[2], argv[3], argv[4], argv[6]);
	nbTerrain=atoi(argv[2]); printf("Nb terrains : %d\n", nbTerrain);
	largeur=atoi(argv[3]); 	
	hauteur=atoi(argv[4]);
	float densite=strtof(argv[5], NULL); 	 printf("Largeur : %d, Hauteur : %d, densite : %f\n", largeur, hauteur, densite);
	nb_step_max=atoi(argv[6]);

	Terrain T;
	T.largeur=largeur;
	T.hauteur=hauteur;

	int nbEchecs = 0;

	FILE * fProg;
	FILE * fRes;
	fProg=fopen(prog, "r");
	fRes= fopen(progRes,"w");
	Programme prog1;
	Environnement environnement;
	etat_inter etatI;

	
	if( fProg == NULL ){
  		printf("Probleme lecture fichier\n");
   		return EXIT_FAILURE;
	}
	
	if( fRes == NULL ){
  		printf("Probleme louverture fichier reception\n");
   		return EXIT_FAILURE;
	}
	//copie les caracteristiques des terrains dans le fichier reception 
	fprintf(fRes,"%d\n",nbTerrain);//nbr terrain tester
	//fprintf(fRes,"%d\n",largeur);
	//fprintf(fRes,"%d\n",hauteur);
	
	for (int i=0; i<nbTerrain;i++){
		generation_aleatoire(&T, largeur, hauteur, densite);
		while (!existe_chemin_vers_sortie(T)){
			generation_aleatoire(&T, largeur, hauteur, densite);
			nbEchecs++;
			printf("Terrain invalide, nb d'échec : %d\n", nbEchecs);
		}
		environnement.t = T;
    		environnement.r.x = largeur/2;
    		environnement.r.y = hauteur/2;
    		environnement.r.o = Ouest;

		erreur_programme erreur = lire_programme(&prog1,prog);
		gestion_erreur_programme(erreur);

		int nbPas = 0;
		resultat_inter result = OK_ROBOT;
		init_etat(&etatI);
		while (result == OK_ROBOT && nbPas <= nb_step_max){
			result = exec_pas(&prog1, &environnement, &etatI);
			nbPas++;
		}
		switch(result){
			case SORTIE_ROBOT:fprintf(fRes, "Nb de pas : %d\n", nbPas);break;
			case OK_ROBOT : fprintf(fRes, "-1\n");break;
			case PLOUF_ROBOT : fprintf (fRes, "-2\n");break;
			case CRASH_ROBOT : fprintf( fRes, "-3\n");break;
			default:break;
		}
	
	}
	
	
	return EXIT_SUCCESS;
  }	





