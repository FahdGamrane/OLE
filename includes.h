#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>



//////////////////////////////////////////////////////////////////////////////////////////////
typedef struct node{
	int x;
	int y;
	int g;
	int h;
	int f;
	int etat;
	struct node* parent;
}node;


typedef struct feu{
	int emplacement_feu[2];
	int degre_feu;
	int nb_affectation;
} feu;
typedef struct way{
	int x;
	int y;
	int coust;
	int nb_pas;
	struct way* suivant;

}way;
typedef struct oel{
	int ID;
	int emplacement_courant[2];
	int reservoir;
	int	etat;
	int coordonnees_direction[2];
	way* chemin;
} oel;


int** creer_carte(int n, int m);
int labelOnHover(SDL_Rect zone,SDL_Point mousePosition);
SDL_Rect get_case(int*** carte,int n,int m ,SDL_Rect** Cases,SDL_Point mousePosition,int onclic);
SDL_Surface* charger_image(int  x);
void afficher_map(SDL_Renderer** plan,SDL_Rect** Cases,int*** carte,int n,int m);
feu* envoyer_coordonnees(int** carte,int n,int m,oel*** robot,feu* liste_feu,int rnb,int* fnb);
void division_tache(SDL_Renderer** plan,SDL_Rect** Cases, oel*** robot,feu* liste_feu,int*** carte,int rnb,int n,int m,int* fnb);
feu* depiler(feu* liste_feu,int* fnb);
void envoyer_robot(SDL_Renderer** plan,SDL_Rect** Cases,int*** carte,oel*** liste_robots,int rnb,int n,int m);
void eteindre_feu(int*** carte,oel* robot);
void deplacement_robot(oel* robot,SDL_Renderer** plan,SDL_Rect** Cases,int*** carte,int n,int m);
int feu_proche(int** carte,int n,int m,oel* robot,feu* liste_feu,int fnb);
node* ajouter_noeud(node* liste,node noeud,int* len);
int existe(node* liste,int len,node noeud);
way* ajouter_pas(way* chemin,int x ,int y,int cout,int k);
node** ini_liste(int** map, int n,int m);
way*  findpath(int** map,int n ,int m ,int startx, int starty, int endx, int endy);
node* supprimer_noeuds(node* liste,node noeud,int* len);
void afficher_chemin(way* chemin);
feu* chercher_feu(SDL_Renderer** plan,SDL_Rect** Cases,int*** carte, int n,int m,feu* liste_feu,int* nb_feux,oel*** liste_robots,int* rnb);
feu* ajouter_feu(feu* liste_feu,int i,int j,int deg,int* nb_feux);
feu* tri_feu(feu* liste_feu,int nb_feu);
SDL_Window* fenetre(int*** carte,int n,int m);


