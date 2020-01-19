#include"includes.h"




//////////////////////////////////////////////////////////////////////////////////////////////
node* ajouter_noeuds(node* liste,node noeud,int* len)
{
	int n;
	n=(*len)+1;
	if(liste==NULL)
	{
		liste=(node*)malloc(sizeof(node));
		liste[0]=noeud;
		(*len)=(*len)+1;
		return liste;
	}
	liste=realloc(liste,n*sizeof(node));
	liste[n-1]=noeud;
	(*len)=n;
	return liste;
}

//////////////////////////////////////////////////////////////////////////////////////////////
int existe(node* liste,int len,node noeud)
{
	int i;
	for(i=0;i<len;i++)
	{
		if(liste[i].x==noeud.x && liste[i].y==noeud.y)
		{
			return 1;
		}
	}
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////
way* ajouter_pas(way* chemin,int x ,int y,int cout,int k)
{
	way* new=malloc(sizeof(way));
	new->x=x;
	new->y=y;
	new->coust=cout;
	new->nb_pas=k;
	new->suivant=chemin;
	return new;
}
//////////////////////////////////////////////////////////////////////////////////////////////
node** ini_liste(int** map, int n,int m)
{
	int x,y,i;
	node** noeuds=(node**)malloc(n*sizeof(node*));
	for(i=0;i<n;i++)
	{noeuds[i]=(node*)malloc(m*sizeof(node));}
	for(x=0;x<n;x++)
	{
		for(y=0;y<m;y++)
		{
			noeuds[x][y].x=x;
			noeuds[x][y].y=y;
			noeuds[x][y].etat=map[x][y];
			noeuds[x][y].g= 0;
			noeuds[x][y].h= 0;
			noeuds[x][y].f= 0;
			noeuds[x][y].parent=NULL;
		}
	}
	return noeuds;

}
////////////////////////////////////////////////////////////////////////////////////////////////
node* supprimer_noeuds(node* liste,node noeud,int* len)
{
	int n,i,j=0,m;
	node* temp;
	n=(*len);
	m=n-1;
	temp=malloc(m*sizeof(node));
	for(i=0;i<n;i++)
	{
		if(liste[i].x==noeud.x && liste[i].y==noeud.y)
		{
			continue;
		}
		temp[j]=liste[i];
		j++;
		//printf("don2");
	}
	(*len)=m;
	return temp;
}
////////////////////////////////////////////////////////////////////////////////////////////////
way*  findpath(int** map,int n ,int m ,int startx, int starty, int endx, int endy)
{
	node* liste_ouverte=NULL;
	node* liste_fermee=NULL;
	node** noeuds;
	way* chemin=NULL;
	node* temp;
	int k,comp;
	int count=0;
	int len_O=0,len_F=0;
	int x=0,y=0; 
	int dx,dy;
	node current; 
	int minf=10000; 
	noeuds=ini_liste(map,n,m);
	current.x=startx;
	current.y=starty;
	current.g=0;
	current.h=0;
	current.f=0;
	current.parent=NULL;
	liste_fermee=ajouter_noeuds(liste_ouverte,noeuds[startx][starty],&len_F);
	while(current.x!=endx || current.y!=endy)
	{
		minf=10000;
		for(dx=-1;dx<=1;dx++)
		{	if ((current.x+dx)<0 || (current.x+dx)>=n)
			{
				continue;
			}
			for(dy=-1;dy<=1;dy++)
			{				
				if ((current.y+dy)<0 || (current.y+dy)>=m)
				{
					continue;
				}
				if(noeuds[current.x+dx][current.y+dy].etat==3 || noeuds[current.x+dx][current.y+dy].etat==2)
				{
					continue;
				}
				if(existe(liste_fermee,len_F,noeuds[current.x+dx][current.y+dy]))
				{
					continue;
				}
				if(existe(liste_ouverte,len_O,noeuds[current.x+dx][current.y+dy])==0)
				{
					noeuds[current.x+dx][current.y+dy].parent=&noeuds[current.x][current.y];
					if(dx!=0 && dy!=0) 
					{
						noeuds[current.x+dx][current.y+dy].g=14+noeuds[current.x][current.y].g ; // diagonals cost 2
					}
					else 
					{
						noeuds[current.x+dx][current.y+dy].g =10+noeuds[current.x][current.y].g ;
					}
					noeuds[current.x+dx][current.y+dy].h=(abs(endx-(current.x+dx))+abs(endy-(current.y+dy)))*10;
					noeuds[current.x+dx][current.y+dy].f=noeuds[current.x+dx][current.y+dy].g+noeuds[current.x+dx][current.y+dy].h;
					liste_ouverte=ajouter_noeuds(liste_ouverte,noeuds[current.x+dx][current.y+dy],&len_O);
				}
				else
				{
					if(dx!=0 && dy!=0) 
					{
						comp=14+noeuds[current.x][current.y].g ; // diagonals cost 2
					}
					else 
					{
						comp=10+noeuds[current.x][current.y].g ;
					}
					if(noeuds[current.x+dx][current.y+dy].g>comp)
					{
						noeuds[current.x+dx][current.y+dy].g=comp;
					    noeuds[current.x+dx][current.y+dy].parent=&noeuds[current.x][current.y];
						noeuds[current.x+dx][current.y+dy].f=noeuds[current.x+dx][current.y+dy].g+noeuds[current.x+dx][current.y+dy].h;

					}					
				}

			}
		}
	for(k=0;k<len_O;k++)
		{
			if(liste_ouverte[k].f<minf && existe(liste_fermee,len_F,liste_ouverte[k])==0 )
			{
				minf=liste_ouverte[k].f;
				current=liste_ouverte[k];
			}

		}
	liste_fermee=ajouter_noeuds(liste_fermee,noeuds[current.x][current.y],&len_F);
	liste_ouverte=supprimer_noeuds(liste_ouverte,noeuds[current.x][current.y],&len_O);
	}
	temp=malloc(sizeof(node));
	free(liste_ouverte);
	(*temp)=liste_fermee[len_F-1];
	k=0;
	while((*temp).x!=startx || (*temp).y!=starty)
	{
		k++;
		chemin=ajouter_pas(chemin,(*temp).x,(*temp).y,(*temp).f,k);
		(*temp)=(*(temp->parent));
	}
	return chemin;

}
void afficher_chemin(way* chemin)
{
	int i;
	while(chemin!=NULL)
	{
		printf("(%d,%d)->",chemin->x,chemin->y);
		chemin=chemin->suivant;
	}

}

feu* chercher_feu(SDL_Renderer** plan,SDL_Rect** Cases,int*** carte, int n,int m,feu* liste_feu,int* nb_feux,oel*** liste_robots,int* rnb)
 {
 //le drone commence par la source S(0,0)//
 	int i,j,k=0;
 	int xf,yf,deg;
	SDL_Texture* temp;
	 oel* robot;
 	for(i=0;i<n;i++)
 	{
 		if(i%2==0)
 		{for(j=0;j<m;j++)
 		{   (*carte)[i][j]=4+(*carte)[i][j]*10;
                        temp=SDL_CreateTextureFromSurface((*plan),charger_image((*carte)[i][j]));
      			SDL_RenderCopy((*plan),temp,NULL,&Cases[i][j]);
			SDL_RenderPresent((*plan));
			SDL_Delay(5);
 			if ((*carte)[i][j]>=114)
 			{
 				deg=(*carte)[i][j]/100;
 				liste_feu=ajouter_feu(liste_feu,i,j,deg,nb_feux);
 			}
 			(*carte)[i][j]=((*carte)[i][j]-4)/10;
			temp=SDL_CreateTextureFromSurface((*plan),charger_image((*carte)[i][j]));
      			SDL_RenderCopy((*plan),temp,NULL,&Cases[i][j]);
                       	if((*carte)[i][j]==2)
			{
			robot=(oel*)malloc(sizeof(oel));
			robot->ID=0;
			robot->emplacement_courant[0]=i;
			robot->emplacement_courant[1]=j;
			robot->etat=0;
			robot->reservoir=100;
			robot->coordonnees_direction[0]=i;
			robot->coordonnees_direction[1]=j;
			k=(*rnb);
			(*liste_robots)=realloc((*liste_robots),(k+1)*sizeof(oel*));
			(*liste_robots)[k]=robot;
			(*rnb)=k+1;
	 		}
 		}}
 		if(i%2==1)
 		{for(j=m-1;j>=0;j--)
 		{       (*carte)[i][j]=4+(*carte)[i][j]*10;
                        temp=SDL_CreateTextureFromSurface((*plan),charger_image((*carte)[i][j]));
      			SDL_RenderCopy((*plan),temp,NULL,&Cases[i][j]);
			SDL_RenderPresent((*plan));
			SDL_Delay(5);
 			if ((*carte)[i][j]>=114)
 			{
 				deg=(*carte)[i][j]/100;
 				liste_feu=ajouter_feu(liste_feu,i,j,deg,nb_feux);
 			}
 			(*carte)[i][j]=((*carte)[i][j]-4)/10;
			temp=SDL_CreateTextureFromSurface((*plan),charger_image((*carte)[i][j]));
      			SDL_RenderCopy((*plan),temp,NULL,&Cases[i][j]);
                       	if((*carte)[i][j]==2)
			{
			robot=(oel*)malloc(sizeof(oel));
			robot->ID=0;
			robot->emplacement_courant[0]=i;
			robot->emplacement_courant[1]=j;
			robot->etat=0;
			robot->reservoir=100;
			robot->coordonnees_direction[0]=i;
			robot->coordonnees_direction[1]=j;
			k=(*rnb);
			(*liste_robots)=realloc((*liste_robots),(k+1)*sizeof(oel*));
			(*liste_robots)[k]=robot;
			(*rnb)=k+1;
	 		}
 		}}

 	}
 	tri_feu(liste_feu,*(nb_feux));
 	return liste_feu;

 }
 feu* ajouter_feu(feu* liste_feu,int i,int j,int deg,int* nb_feux)
 {

 	feu fire;
 	int n;
 	n=(*nb_feux);
 	n=n+1;
 	if(liste_feu==NULL)
 	{
 		liste_feu=malloc(sizeof(feu));
 	}
	else
	{
		liste_feu=realloc(liste_feu,n*sizeof(feu));
	}
 	fire.emplacement_feu[0]=i;
 	fire.emplacement_feu[1]=j;
 	fire.degre_feu=deg;
	fire.nb_affectation=0;
	liste_feu[n-1]=fire;
	(*nb_feux)=n;
 	return liste_feu;
 }
feu* tri_feu(feu* liste_feu,int nb_feu)
{
	int test=0,i;
	feu temp;
	while(test==0)
	{
		test=1;
		for(i=0;i<nb_feu-1;i++)
		{
			if(liste_feu[i].degre_feu<liste_feu[i+1].degre_feu)
			{
				temp=liste_feu[i];
				liste_feu[i]=liste_feu[i+1];
				liste_feu[i+1]=temp;
				test==0;
			}
		}
	}
	return liste_feu;
}


feu* liste_feu=NULL;
oel** liste_robots=NULL;
//µµµµµµµµµµµµµµµµµµµµµµµµµµµµµµµµµµµµµµµµµµµµµµµµµµµµµ//
SDL_Window* fenetre(int*** carte,int n,int m)
{
  // initialisation des pointeurs//
  /*************************************************************************/
  int rnb=0;
  int fnb=0;
  int i,j,Casex,Casey,fL=1200,fl=600,fermer=0,onclic=0,debut=0;
  int contour_mapL=750,contour_mapl=560;
  SDL_Window* fenetre;
  SDL_Renderer* plan;
  SDL_Surface* fond;
  SDL_Texture* fondt;
  SDL_Event evenement;
  SDL_Rect** Cases;
  SDL_Surface* sf;
  SDL_Point mousePosition;
  SDL_Texture* sft;SDL_Texture* menu;

fenetre= SDL_CreateWindow("simulateur oel", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,fL,fl, SDL_WINDOW_SHOWN);
plan=SDL_CreateRenderer(fenetre,-1,SDL_RENDERER_ACCELERATED);
fond=IMG_Load("ressources/fond.jpg");
fondt=SDL_CreateTextureFromSurface(plan,fond);
SDL_Rect cadre0={0,0,fL,fl};
SDL_RenderCopy(plan,fondt,NULL,&cadre0);

/***************************************************************************/

/**************************************************************************/
SDL_Rect contour_map={20,20,contour_mapL,contour_mapl};
SDL_SetRenderDrawColor(plan,160,160,160,250);
SDL_RenderDrawRect(plan,&contour_map);
Casex=contour_mapL/n;
Casey=contour_mapl/m;
Cases=malloc(n*sizeof(SDL_Rect*));
for(i=0;i<n;i++)
{
      Cases[i]=malloc(m*sizeof(SDL_Rect));
}
for(i=0;i<n;i++)
{
  for(j=0;j<m;j++)
  {
    SDL_Rect Case={i*Casex+20,j*Casey+20,Casex,Casey};
    Cases[i][j]=Case;
    SDL_RenderDrawRect(plan,&Case);
  }}
for(i=0;i<n;i++)
{
  for(j=0;j<m;j++)
  {
    sf=charger_image(0);
    sft=SDL_CreateTextureFromSurface(plan,sf);
    SDL_RenderCopy(plan,sft,NULL,&Cases[i][j]);
    SDL_DestroyTexture(sft);
  }


}
/***************************************************************************/
SDL_Rect contour_menu={800,20,380,560};
SDL_RenderDrawRect(plan,&contour_menu);
menu=SDL_CreateTexture(plan, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,380,560);
SDL_SetTextureBlendMode(menu,SDL_BLENDMODE_BLEND);
SDL_SetRenderDrawColor(plan,23,101,125,50);
SDL_SetRenderTarget(plan,menu);
SDL_RenderClear(plan);
SDL_SetRenderTarget(plan,NULL);
SDL_RenderCopy(plan,menu,NULL,&contour_menu);
SDL_DestroyTexture(menu);
/////////////////////////////////////////////
SDL_Texture* menucase=SDL_CreateTexture(plan, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,340,200);
SDL_SetTextureBlendMode(menucase,SDL_BLENDMODE_BLEND);
SDL_SetRenderDrawColor(plan,255,255,255,50);
SDL_Rect cmenu={820,40,340,200};
SDL_SetRenderTarget(plan,menucase);
SDL_RenderClear(plan);
SDL_SetRenderTarget(plan,NULL);
SDL_RenderCopy(plan,menucase,NULL,&cmenu);
///////////////////////////////////////////////
SDL_Rect cmenu1={820,260,340,200};
SDL_RenderCopy(plan,menucase,NULL,&cmenu1);
/////////////////////////////////////////////////////////////////////////////
SDL_Surface* EO=IMG_Load("ressources/obstacle2.png");
SDL_Rect    R1={(cmenu1.x)+40,(cmenu1.y)+60,100,100};
SDL_Texture* EOt=SDL_CreateTextureFromSurface(plan,EO);
SDL_RenderCopy(plan,EOt,NULL,&R1);
////////////////////////////////////////////////////////////////////////////
SDL_Surface* ER=IMG_Load("ressources/2init.bmp");
SDL_Rect    R2={(R1.x)+(R1.w)+60,(cmenu1.y)+60,100,100};
SDL_Texture* ERt=SDL_CreateTextureFromSurface(plan,ER);
SDL_RenderCopy(plan,ERt,NULL,&R2);
//////////////////////////////////////////////////////////////////////////////////////
SDL_Surface* EF1=IMG_Load("ressources/11.bmp");
SDL_Rect    R3={(cmenu.x)+20,(cmenu.y)+10,85,85};
SDL_Texture* EFt1=SDL_CreateTextureFromSurface(plan,EF1);
SDL_RenderCopy(plan,EFt1,NULL,&R3);

SDL_Surface* EF2=IMG_Load("ressources/21.bmp");
SDL_Rect    R4={(R3.x)+(R3.w)+20,(cmenu.y)+10,85,85};
SDL_Texture* EFt2=SDL_CreateTextureFromSurface(plan,EF2);
SDL_RenderCopy(plan,EFt2,NULL,&R4);

SDL_Surface* EF3=IMG_Load("ressources/31.bmp");
SDL_Rect    R5={(R4.x)+(R4.w)+20,(cmenu.y)+10,85,85};
SDL_Texture* EFt3=SDL_CreateTextureFromSurface(plan,EF3);
SDL_RenderCopy(plan,EFt3,NULL,&R5);

SDL_Surface* EF4=IMG_Load("ressources/41.bmp");
SDL_Rect    R6={(cmenu.x)+42,(cmenu.y)+105,85,85};
SDL_Texture* EFt4=SDL_CreateTextureFromSurface(plan,EF4);
SDL_RenderCopy(plan,EFt4,NULL,&R6);

SDL_Surface* EF5=IMG_Load("ressources/51.bmp");
SDL_Rect    R7={(cmenu.x)+209,(cmenu.y)+105,85,85};
SDL_Texture* EFt5=SDL_CreateTextureFromSurface(plan,EF5);
SDL_RenderCopy(plan,EFt5,NULL,&R7);
/////////////////////////////////////////////////////////////////////////////////////
SDL_Surface* startS=IMG_Load("ressources/firefighter.png");
SDL_Rect    start={(cmenu1.x)+(cmenu1.w)/2-50,(cmenu1.y)+(cmenu1.h)+10,100,100};
SDL_Texture* startT=SDL_CreateTextureFromSurface(plan,startS);
SDL_RenderCopy(plan,startT,NULL,&start);


/**************************************************************************/

SDL_RenderPresent(plan);
//fermeture de la fenetre
while (fermer == 0 && debut==0 ) {
    while (SDL_PollEvent(&evenement) != 0)
    {
        if (evenement.type == SDL_QUIT)
        {
            fermer = 1;
        }
        SDL_Delay(1);
    }
    if (SDL_GetMouseState(&mousePosition.x, &mousePosition.y) && SDL_BUTTON(SDL_BUTTON_RIGHT))
    {
      if(labelOnHover(cmenu1,mousePosition)==1)
      {
        if(labelOnHover(R1,mousePosition)==1)
        {
          onclic=3;
        }
        if(labelOnHover(R2,mousePosition)==1)
        {
          onclic=2;
        }
      }
      if(labelOnHover(cmenu,mousePosition)==1)
      {
        if(labelOnHover(R3,mousePosition)==1)
        {
          onclic=11;
        }
        if(labelOnHover(R4,mousePosition)==1)
        {
          onclic=21;
        }
        if(labelOnHover(R5,mousePosition)==1)
        {
          onclic=31;
        }
        if(labelOnHover(R6,mousePosition)==1)
        {
          onclic=41;
        }
        if(labelOnHover(R7,mousePosition)==1)
        {
          onclic=51;
        }

      }
      if(labelOnHover(start,mousePosition)==1)
      {
        debut=1;
      }
      if(labelOnHover(contour_map,mousePosition)==1)
      {
        SDL_Texture* tempt;
        SDL_Rect temp=get_case(carte,n,m,Cases,mousePosition,onclic);
        tempt=SDL_CreateTextureFromSurface(plan,charger_image(onclic));
        SDL_RenderCopy(plan,tempt,NULL,&temp);
      }
	
    }

    SDL_RenderPresent(plan);
  }

liste_feu=chercher_feu(&plan,Cases,carte,n,m,liste_feu,&fnb,&liste_robots,&rnb);
division_tache(&plan,Cases,&liste_robots,liste_feu,carte,rnb,n,m,&fnb);
while (fermer == 0) {
    while (SDL_PollEvent(&evenement) != 0)
    {
        if (evenement.type == SDL_QUIT)
        {
            fermer = 1;
        }
        SDL_Delay(1);
    }} 
SDL_DestroyRenderer(plan);
SDL_Quit();

return EXIT_SUCCESS;
}

feu* envoyer_coordonnees(int** carte,int n,int m,oel*** robot,feu* liste_feu,int rnb,int* fnb)
{
	int i,k=0,j;
	oel* robotA;
	int dis;
	int min;
	way* chemin;
	oel* robot_dispo[rnb];
	int fire;
	for(i=0;i<rnb;i++)
	{
		if ((*robot)[i]->etat==0)
		{
			robot_dispo[k]=(*robot)[i];
			k++;
		}
	}

	if(k!=0)
	{robotA=robot_dispo[0];
	min=10000;
	i=0;
	while(i<k && liste_feu!=NULL)
	{
 		fire=feu_proche(carte,n,m,robot_dispo[i],liste_feu,(*fnb));
		robot_dispo[i]->etat=1;
		robot_dispo[i]->coordonnees_direction[0]=liste_feu[fire].emplacement_feu[0];
		robot_dispo[i]->coordonnees_direction[1]=liste_feu[fire].emplacement_feu[1];
		liste_feu[fire].nb_affectation=(liste_feu[fire].nb_affectation)+1;
		liste_feu=depiler(liste_feu,fnb);
		i++;
	}
	}
	return liste_feu;
}
void division_tache(SDL_Renderer** plan,SDL_Rect** Cases, oel*** robot,feu* liste_feu,int*** carte,int rnb,int n,int m,int* fnb)
{
	while(liste_feu!=NULL)
	{
		liste_feu=envoyer_coordonnees((*carte),n,m,robot,liste_feu,rnb,fnb);
		envoyer_robot(plan,Cases,carte,robot,rnb,n,m);
	}
}
feu* depiler(feu* liste_feu,int* fnb)
{
	int i=0,j,n,test=0;
	n=(*fnb);
	while(i<n)
	{
	if(n==0)					//si la liste est vide;
		{ return NULL;}
	if(liste_feu[i].nb_affectation<liste_feu[i].degre_feu) // si le nombre de robots affecter n'est pas suffisant
	{

		i++;
	}
	if(liste_feu[i].nb_affectation==liste_feu[i].degre_feu)
	{
		if(n==1)
		{
			(*fnb)=0;
			return NULL;
		}
		for(j=i;j<n-1;j++)			
		{
			liste_feu[j]=liste_feu[j+1];
		}
		n=n-1;
		liste_feu=realloc(liste_feu,n*sizeof(feu));
		(*fnb)=n;
	}

	}
	return liste_feu;
}

int** creer_carte(int n, int m)
{
	int** carte;
	int i,j;
	carte=(int**)malloc(n*sizeof(int*));
	for(i=0;i<n;i++)
	{carte[i]=(int*)malloc(m*sizeof(int));}
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		  {carte[i][j]=0;}
	}
	return carte;
}
int labelOnHover(SDL_Rect zone,SDL_Point mousePosition) {
    int xLabel = zone.x,
        yLabel = zone.y,
        wLabel = zone.w, hLabel = zone.h,
        xMouse = mousePosition.x, yMouse = mousePosition.y;

    if(xMouse >= xLabel && xMouse <= xLabel + wLabel
         && yMouse >= yLabel && yMouse <= yLabel + hLabel)
         {return 1;}
    return 0;
}
SDL_Rect get_case(int*** carte,int n,int m ,SDL_Rect** Cases,SDL_Point mousePosition,int onclic)
{int i,j,k;

  for(i=0;i<n;i++)
  {
    for(j=0;j<m;j++)
    {
      if(labelOnHover(Cases[i][j],mousePosition)==1)
      {
	(*carte)[i][j]=onclic;
        return Cases[i][j];
      }
    }}
}
SDL_Surface* charger_image(int  x)
{SDL_Surface* temp;
  switch(x)
  {
    case 0:
           temp=IMG_Load("ressources/0.jpg");
           return temp;
	   break;
    case 2:
          temp=IMG_Load("ressources/robot.png");
          return temp;
	  break;
    case 3:
          temp=IMG_Load("ressources/obstacle.png");
          return temp;
	  break;
    case 4:
          temp=IMG_Load("ressources/drone.png");
          return temp;
	  break;
    case 24:
          temp=IMG_Load("ressources/drone.png");
          return temp;
	  break;
    case 34:
          temp=IMG_Load("ressources/drone.png");
          return temp;
	  break;
    case 114:
          temp=IMG_Load("ressources/drone.png");
          return temp;
	  break;
    case 214:
          temp=IMG_Load("ressources/drone.png");
          return temp;
	  break;
    case 314:
          temp=IMG_Load("ressources/drone.png");
          return temp;
	  break;
    case 414:
          temp=IMG_Load("ressources/drone.png");
          return temp;
	  break;
    case 514:
          temp=IMG_Load("ressources/drone.png");
          return temp;
	  break;
    case 11:
          temp=IMG_Load("ressources/1.png");
          return temp;
          break;
    case 21:
          temp=IMG_Load("ressources/2.png");
          return temp;
          break;
    case 31:
          temp=IMG_Load("ressources/3.png");
          return temp;
          break;
    case 41:
          temp=IMG_Load("ressources/4.png");
          return temp;
          break;
    case 51:
          temp=IMG_Load("ressources/5.png");
          return temp;
          break;
  }

}
void afficher_map(SDL_Renderer** plan,SDL_Rect** Cases,int*** carte,int n,int m)
{SDL_Texture* temp;
int i,j;
  for(i=0;i<n;i++ )
  {
    for(j=0;j<m;j++)
    {
      temp=SDL_CreateTextureFromSurface((*plan),charger_image((*carte)[i][j]));
      SDL_RenderCopy((*plan),temp,NULL,&Cases[i][j]);
      SDL_DestroyTexture(temp);
    }
  }
  SDL_RenderPresent((*plan));
}


void deplacement_robot(oel* robot,SDL_Renderer** plan,SDL_Rect** Cases,int*** carte,int n,int m) //à revoir
{
	way* chemin;
	int x,y;
	SDL_Texture* temp;
	x=robot->emplacement_courant[0];
	y=robot->emplacement_courant[1];
	chemin=robot->chemin;
	while(chemin->suivant!=NULL)
	{
		if((*carte)[x][y]==2)
		{
			(*carte)[x][y]=0;
			temp=SDL_CreateTextureFromSurface((*plan),charger_image((*carte)[x][y]));
      			SDL_RenderCopy((*plan),temp,NULL,&Cases[x][y]);
      			SDL_RenderPresent((*plan));
			SDL_Delay(5);
		}
		if((*carte)[chemin->x][chemin->y]==2)
		{
			chemin=findpath((*carte),n,m,x,y,robot->coordonnees_direction[0],robot->coordonnees_direction[1]);
		}
		x=chemin->x;
		y=chemin->y;
		(*carte)[x][y]=2;
		temp=SDL_CreateTextureFromSurface((*plan),charger_image((*carte)[x][y]));
      		SDL_RenderCopy((*plan),temp,NULL,&Cases[x][y]);
      		SDL_RenderPresent((*plan));
		SDL_Delay(5);
		robot->emplacement_courant[0]=x;
		robot->emplacement_courant[1]=y;
		chemin=chemin->suivant;
	}
}

void envoyer_robot(SDL_Renderer** plan,SDL_Rect** Cases,int*** carte,oel*** liste_robots,int rnb,int n,int m)
{
	int x,y,i,j;
	SDL_Texture* temp;
	for(i=0;i<rnb;i++)
	{
		if((*liste_robots)[i]->etat==1)
		{deplacement_robot((*liste_robots)[i],plan,Cases,carte,n,m);}
	}
	for(i=0;i<rnb;i++)
	{
		if((*liste_robots)[i]->etat==1)
		{
		eteindre_feu(carte,(*liste_robots)[i]);
		x=(*liste_robots)[i]->coordonnees_direction[0];
		y=(*liste_robots)[i]->coordonnees_direction[1];
		temp=SDL_CreateTextureFromSurface((*plan),charger_image((*carte)[x][y]));
    SDL_RenderCopy((*plan),temp,NULL,&Cases[x][y]);
    SDL_RenderPresent((*plan));
		SDL_Delay(5);
		}
	}
}
void eteindre_feu(int*** carte,oel* robot)
{
	if((*carte)[robot->coordonnees_direction[0]][robot->coordonnees_direction[1]]/10==1)
	{(*carte)[robot->coordonnees_direction[0]][robot->coordonnees_direction[1]]=0;}
	else{
		(*carte)[robot->coordonnees_direction[0]][robot->coordonnees_direction[1]]=(*carte)[robot->coordonnees_direction[0]][robot->coordonnees_direction[1]]-10;
	}
	robot->etat=0;

}

int feu_proche(int** carte,int n,int m,oel* robot,feu* liste_feu,int fnb)
{
	way* liste_chemin[fnb];
	int i,dis,xstart,ystart,j,optimal=0,indice=0;
	feu temp;
	way* chemin=malloc(sizeof(way));
	for(i=0;i<fnb;i++)
	{
		xstart=robot->emplacement_courant[0];
		ystart=robot->emplacement_courant[1];
		chemin=findpath(carte,n,m,xstart,ystart,liste_feu[i].emplacement_feu[0],liste_feu[i].emplacement_feu[1]);
		liste_chemin[i]=chemin;

	}
	while(optimal==0)
	{
		optimal=1;
		for(i=0;i<fnb-1;i++)
		{
			if(liste_feu[i].degre_feu==liste_feu[i+1].degre_feu)
			{
				if((liste_chemin[i]->coust)>(liste_chemin[i+1]->coust))
					{ j=i+1;}
				else
				{	j=i;}

				if((liste_chemin[indice]->coust)>(liste_chemin[j]->coust))
				{
					indice=j;
					optimal=0;
				}
			}
		}

	}
	robot->chemin=liste_chemin[indice];
	return indice;
}



int main(int argc, char const **argv)
{int n,m;
  int** carte;
  puts("###### DONNER LES DIMENSIONS N puis M #######");
  scanf("%d",&n);
  scanf("%d",&m);
  SDL_Window* window;
  carte=creer_carte(n,m);
  window=fenetre(&carte,n,m);
}

/*gcc main.c -o RUN -lSDL2 -lSDL2_image $(sdl2-config --libs --cflags)*/
