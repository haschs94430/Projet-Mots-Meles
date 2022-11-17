#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#define N 20

/*strcuture permettant de stocker la position des points*/

typedef struct{
	int x;
	int y;
}Point;

/*structure permettant de stocker la direction des vecteurs*/

typedef struct{
	Point p1;
	Point p2;
}Segment;

/*strcuture permettant de stocker notre tableau*/

typedef struct{
	Segment tableau[N];
	int nelement;
}Ensemble;

/*fonction permettant de calculer la longueur d'un mot*/

int longeur(char mot[]){
	int i = 0;
	for ( i = 0; mot[i] != '\0'; i++)
		;	
	return i;
}

/*fonction permettant de calculer la longueur notre grille*/

int calculLongeur(int taille){
	return (50 * 1 * (2 * taille - 3));
}

/*fonction permettant de calculer la largeur de notre grille*/

int calculLargeur(int taille){
	return (50 * 1 * (taille + 3));
}

/*fonction permettant de faire la valeur absolue de notre vecteur donc de notre direction*/

int AbsolueVecteur(int n){
	if (n == 0)
		return 1;
	if (n > 0)
		return n;
	return -n;
}

/*fonction permettant de calculer la longueur d'une chaine*/

int longeurChaine(int taille, char chaine[][N+1]){
    int i;
    for ( i = 0; chaine[i][0] != '\0' && i < taille; i++)
		;
    return i;
}

/*fonction permetant de copier les elements de tableau dans cible*/

void copieChar(char tableau[], char cible[]){
    int i;
    for( i = 0; tableau[i] != '\0'; i++)
        cible[i] = tableau[i];
    cible[i] = '\0';
}

/*fonction permettant les elements de matrice dans cible*/

void copieMatrice(int taille, char matrice[][N], char cible[][N]){
    int i;
    int j;
    for( i = 0; i < taille; i++)
        for( j = 0; j < taille; j++)
            cible[i][j] = matrice[i][j];
}

/*fonction permettant de remplir la matrice de lettre aleatoire*/

void remplirMatrice(int taille, char matrice[][N]){
    int i, j;
    for( i = 0; i < taille; i++)
        for(j = 0; j < taille ; j++)
            if(matrice[i][j] == 0)
                matrice[i][j] = 'A' + rand() % 26;
}

/*fonction permettant d'afficher une grille*/

void affiche_grille (int taille, char matrice [][N]){
	int position1;
	int position2;
	int c;
    printf("-");
	for (c = 0; c < taille; c++)
		printf("----");
	printf("\n");
	for (position1 = 0; position1 < taille; position1++){
		for (position2 = 0; position2 < taille; position2++)
			if(matrice [position1][position2] == 0)
				printf("|   ");
			else
				printf("| %c ", matrice[position1][position2] );
		printf("|\n");
        printf("-");
		for (c = 0; c < taille; c++)
			printf("----");
		printf("\n");
	}
}

/*fonction permettant de convertir un mot de minuscule en majuscule*/

int convertir_Minuscule_en_Majuscule(char mot[]){
    int i;
    for(i = 0; mot[i] != '\0'; i++){
        if(mot[i] <= 'z' && mot[i] >= 'a')
            mot[i] += 'A' - 'a';
        else if(mot[i] > 'Z' || mot[i] < 'A'){
            printf("%c",mot[i]);
            return 0;
        }
    }
    return 1;
}

/*fonction permettant de creer une grille*/

int creeGrille(int taille, char matrice[][N],char mot[], Point coordonne, Point vecteur){
    char temporaire[N][N];
    copieMatrice(taille, matrice, temporaire);
    int x, y;
    int i;
    for(i = 0; mot[i] != '\0' ; i++){
        x = coordonne.x + vecteur.x * i;
        y = coordonne.y + vecteur.y * i;
        if(x < taille && x >= 0 && y < taille && y >= 0){
            if (temporaire[y][x] == 0 || temporaire[y][x] == mot[i])
                temporaire[y][x] = mot[i];
            else
                return 0;
        }
        else
            return 0;
    }
    copieMatrice(taille, temporaire, matrice);
    return 1;
}

/*fonction permettant de savoir si la chaine de caractere est presente dans la matrice*/

int estPresent(int taille, char tableau[][N+1], char element[N+1]){
	int i, j;
	for ( i = 0; i < taille; i++ ){
		for ( j = 0; tableau[i][j] == element[j] && element[j] != '\0' && tableau[i][j] != '\0'; j++)
			;
		if ( tableau[i][j] == '\0' && element[j] == '\0' )
			return i;
	}
	return -1;	
}

/*fonction permettant d'initialiser les vecteurs en fonction des directions*/

int choixCoefficient(int choix, Point *vecteur){
    switch(choix){
        case 0: vecteur -> x = -1;
                vecteur -> y = -1;
                break;
        case 1: vecteur -> x = 0;
                vecteur -> y = -1;
                break;
        case 2: vecteur -> x = 1;
                vecteur -> y = -1;
                break;
        case 3: vecteur -> x = -1;
                vecteur -> y = 0;
                break;
        case 4: vecteur -> x = 1;
                vecteur -> y = 0;
                break;
        case 5: vecteur -> x = -1;
                vecteur -> y = 1;
                break;
        case 6: vecteur -> x = 0;
                vecteur -> y = 1;
                break;
        case 7: vecteur -> x = 1;
				vecteur -> y = 1;
                break;
        default:
            return 0;
    }
    return 1;
}

/*fonction permettant de remplir la grille en ASCII*/

void saisieGrilleTerminal(int taille, char matrice[][N], char tableau_mot[][N+1]){
	Point coordonne, vecteur;
    int saisie;
    int compteur = 0;
    char mot[taille];
	do{
        affiche_grille(taille, matrice);
        printf("Entrez les coordonnee de la premiere lettre x, y :\n");
        scanf("%d %d", &(coordonne.x), &(coordonne.y));
        printf("Entrez la direction souhaite parmi \n 0 = Nord-Ouest,\n 1 = Nord,\n 2 = Nord-Est,\n 3 = Ouest,\n 4 = Est,\n 5 = Sud-Ouest,\n 6 = Sud,\n 7 = Sud-Est : ");
        scanf("%d", &saisie);
        if(choixCoefficient(saisie, &vecteur)){
            printf("Entrez la chaine de caractere :\n");
            scanf("%s",mot);
            if(convertir_Minuscule_en_Majuscule(mot)){
                if(!creeGrille(taille, matrice, mot, coordonne, vecteur))
                    printf("Une erreur est survenue\n");
                else{
                    copieChar(mot, tableau_mot[compteur]);
                    compteur ++;
                }
            }
            else{
                printf("Fin de saisie \n");
                break;
            }
        }
        else{
            printf("direction incorrect\n");
        }
    }while(compteur > 0);
    remplirMatrice(taille, matrice);
    affiche_grille(taille, matrice);
}

/*fonction permettant d'ecrire dans un fichier la matrice*/

void ecrit_fichier(int taille, char matrice[][N], char tableau_mot[][N+1], FILE*fichier){
    int i, j;
    fprintf(fichier, "%d\n", taille);
    fprintf(fichier, "%d\n", longeurChaine(taille, tableau_mot));
    for ( i = 0; tableau_mot[i][0] != '\0' && i < taille; i++)
        fprintf(fichier, "%s ", tableau_mot[i]);
    fprintf(fichier, "\n");
    
    for (i = 0; i < taille; i++)
        for (j = 0; j < taille; j++)
            fprintf(fichier, "%c", matrice[i][j]);
}

/*fonction permettant de lire la matrice depuis un fichier*/

void lire_fichier(int *taille, FILE* fichier, char matrice[][N], char mot[][N+1]){
    int i;
    int j;
    int nombre_mot;
    fscanf(fichier, "%d\n" , taille);
    fscanf(fichier, "%d\n" , &nombre_mot);
	for( i = 0; i < nombre_mot; i++)
        fscanf(fichier, "%s " , mot[i]);
	for( i = 0; i < (*taille); i++ )
        for( j = 0; j < (*taille); j++)
			matrice[i][j] = fgetc(fichier);
}

/*fonction permettant de jouer aux jeu en version ASCII*/

void joueTerminal(int taille, char matrice[][N], char tableau_mot[][N+1]){
	int mot_restant = 0;
	Point coordonne, vecteur;
	int saisie = 0;
	char mot[N+1];
	int position = 0;
	int i = 0;
	mot_restant = longeurChaine(taille, tableau_mot);
	do{        
        affiche_grille(taille, matrice);
        printf("Mot restant : %d \n", mot_restant);
        for ( i = 0; i < N; i ++)
            if ( tableau_mot[i][0] != '\0')
				printf("%s \n", tableau_mot[i]);
        printf("Entrez les coordonnee de la premiere lettre x, y: \n");
        scanf("%d %d", &(coordonne.x), &(coordonne.y));
        printf("Entrez la direction souhaite parmi \n 0 = Nord-Ouest,\n 1 = Nord,\n 2 = Nord-Est,\n 3 = Ouest,\n 4 = Est,\n 5 = Sud-Ouest,\n 6 = Sud,\n 7 = Sud-Est : ");
        scanf("%d", &saisie);
        if(choixCoefficient(saisie, &vecteur)){
            printf("Entrez la chaine de caractere :\n");
            scanf("%s", mot);
            if(convertir_Minuscule_en_Majuscule(mot)){
                position = estPresent(taille, tableau_mot, mot);
                if(!creeGrille(taille, matrice, mot, coordonne, vecteur) || position == -1)
                    printf("Une erreur est survenue\n");
                else{
					tableau_mot[position][0] = '\0';
                    mot_restant--;
                }
            }
            else{
                printf("Felicitation vous avez complete la grille");
                break;
            }
        }
        else
            printf("direction incorrect\n");
    }while(mot_restant);
    printf("Vous avez gagnez\n");
}

int main(int argc, char *argv[]){	
    char matrice[N][N] = {{0}}; 
    char tableau_mot[N][N+1] = {{"\0"}};
    int taille = 0;
    FILE* fichier = NULL;
	if (argc < 3)
		return 1;
    if(argv[1][0] == '-'){
        if(argv[1][1] == 'c' && argv[1][2] == 'a'){
            printf("Taille de la grille ?\n");
            scanf("%d", &taille);
            if(taille > 20)
				taille = 20;
			else if(taille < 5)
				taille = 5;
            fichier = fopen(argv[2], "w");
            saisieGrilleTerminal(taille, matrice, tableau_mot);
            ecrit_fichier(taille, matrice, tableau_mot, fichier);
        }
        else{
            fichier = fopen(argv[2],"r");
            if (fichier == NULL){
				printf("Le fichier n'existe pas \n");
				return 2;
			}
			else{
				lire_fichier(&taille, fichier, matrice, tableau_mot);
				if (taille == 0){
					printf("Le fichier est vide\n");
					return 2;
				}
				if(argv[1][1] == 'a'){
					joueTerminal(taille, matrice, tableau_mot);
				}
			}	
        }
    }
    else{
        printf("erreur commande\n");
		return 2;
	}
	return 0;
}
