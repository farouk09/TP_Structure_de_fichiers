#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
//#define _WIN32_WINNT 0x502
#include <windows.h>
/*****************************************PART 1*****************************************************************/
/*-------Déclaration des structures-------*/
typedef struct etablissement
{
    char etab[100];
} etablissement ;

etablissement etabl[109];

typedef struct sp
{
    char specialite[30];
} sp ;

sp spe[40];

typedef struct wilaya
{
    char wila[15];
} wilaya ;

wilaya wi[49];

typedef struct Maillon {
    int matricule ;
    int num_bloc;
    int deplacement ;
    struct Maillon *next;
    } Maillon;
typedef struct Maillon2 {
    int val;
    struct Maillon2 *nextdr;
    struct Maillon *nexth;
    } Maillon2;
Maillon *tip,*tie,*tis,*tia;
typedef struct MaillonIndex {
     int ancienter ;
     char string[100];
     struct MaillonIndex *next;
     struct Maillon *tete;
     } MaillonIndex;
MaillonIndex *ttie,*ttis,*ttia;

Maillon *t ;
Maillon2 *t2;
MaillonIndex *ts;
MaillonIndex *te;
MaillonIndex *ta;

int nb_ens=0;

void allouer(Maillon **nouveau)
{ *nouveau=(Maillon*)malloc(sizeof(Maillon));}

void aff_adr(Maillon *p,Maillon *q)
{p->next=q;}

void aff_val(Maillon *p, int matricule ,int deplacement,int num_bloc)
{p->matricule=matricule;
p->deplacement=deplacement;
p->num_bloc=num_bloc;}

Maillon *suivant(Maillon *p)
{return p->next;}

int valeur(Maillon *p)
{return p->matricule;}
void liberer(Maillon**ancien)
{free(*ancien); *ancien=NULL;}
/****************************************skiplist******************************************************************************/
void allouer2(Maillon2 **nouveau)
{
    *nouveau=(Maillon2*)malloc(sizeof(Maillon2));
}
void aff_val2_1(Maillon2 *p, int valeur)
{
    p->val=valeur;
}
Maillon2 *suivant_droite2(Maillon2 *p)
{
    return p->nextdr;
}
void aff_adr_droite2(Maillon2 *p,Maillon2 *q)
{
    p->nextdr=q;
}
int valeur2(Maillon2 *p)
{
    return p->val;
}
void aff_val2(Maillon2 *p, int valeur)
{
    p->val=valeur;
}
void aff_adr_bas2(Maillon2 *p, Maillon *q)
{
    p->nexth=q;
}
Maillon *suivant_bas2(Maillon2 *p)
{
return p->nexth ;
}
Maillon2 *sembalable(Maillon *t2 )
{
    Maillon2 *p,*u,*q=NULL;
    int cpt=1,o=1;
    while (t2!=NULL)
    {
        t2=suivant(t2);
        cpt++;
        if (cpt==(1000*o))
        {
            //printf("efzfze");
            allouer2(&p);
            //if (o!=999) o++;
            o++;
            aff_val2_1(p,valeur(t2));
            if (q!=NULL)
            {
                aff_adr_droite2(q,p);

            }
            else
            {
                u=p;
            }
            aff_adr_bas2(p,t2);
            q=p;
        }
        if (t2==NULL)
        {
            aff_adr_droite2(q,NULL);
        }
    }
    return u;
}
int ancienter(char dat[10])
{
    time_t t = time(NULL);
    struct tm tm =*localtime(&t);
   char annee[3];
   int i,an,difan;
   for(i=0;i<=3;i++)
   {
       annee[i]=dat[i] ;
   }

   an=atoi(annee) ;

   difan=tm.tm_year+1900;

   return difan-an;


}

void rech_LS2(int v , Maillon *t,Maillon2 *h , Maillon **p,Maillon **q  , int *trouv)
{
    *p=NULL ;
    *trouv=0;
    int stop=0;
    Maillon *l,*m ;
    l=t;
    m=suivant_bas2(h);
    while (h!=NULL && valeur2(h)<=v ) // cette boucle pour parcourir la list LS1 et obtenir la born inf et sup de recherch
    {
        l=m;
        h=suivant_droite2(h);
        if (h==NULL)
        {
            m=NULL;
        }
        else
        {
            m=suivant_bas2(h);
        }
    }
    while (l!=m && (*trouv)!=1 && !stop ) // parcourt sequentielle de l a m ie: de la borne inf a la borne sup obtenue de la boucle precedente
    {
        if (valeur(l)==v)
        {
            *p=l;
            *trouv=1 ;
        }
        else
        {
            if (valeur(l)>v)
            {
                stop=1;
                *p=l;
            }
            else
            {
                *q=l;
            }

        }
    l=suivant(l);
    }
}
/****************************************skiplist******************************************************************************/

                                    /*fin def list*/
void allouerIndex(MaillonIndex **nouveau)
{ *nouveau=(MaillonIndex*)malloc(sizeof(MaillonIndex));}

void aff_adrIndex(MaillonIndex *p,MaillonIndex *q)
{p->next=q;}

void aff_valIndex(MaillonIndex *p, int ancienter,char string[100])
{p->ancienter=ancienter;
strcpy(p->string,string);}

MaillonIndex *suivantIndex(MaillonIndex *p)
{return (p->next);}

int valeurIndexA(MaillonIndex *p)
{return p->ancienter;}

void libererIndex(MaillonIndex**ancien)
{free(*ancien); *ancien=NULL;}

Maillon *tete(MaillonIndex *p)
{return p->tete;}

/*000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000*/
/****************************************declaration des structure***********************************/
typedef struct Tenreg
{
char specialite[30];
int matricule;
char nom[30];
char *sexe;
char wilaya_naissance[20];
char *groupe_sanguin;
char date_recrutement[10];//par ex :"0000/00/00"
char *grade;
char date_Naissance[10];//par ex : "0000/00/00"
char *dernier_diplome;
char etablissement_univ[100];
} Tenreg;
typedef struct Tbloc
{
Tenreg T[1000];
int Nb;
} Tbloc;
Tbloc buf;
typedef struct TenregIndex
{
int matricule;
int num_bloc;
int deplacement;
} TenregIndex;
typedef struct TenregIndex2
{
char string[100];
int matricule;
int ancienter;
int num_bloc;
int deplacement;
} TenregIndex2;
typedef struct TblocIndex
{
TenregIndex T[1000];
int Nb;
} TblocIndex;
TblocIndex buff;
typedef struct TblocIndex2
{
TenregIndex2 T[1000];
int Nb;
} TblocIndex2;

TblocIndex2 bufff;

typedef struct Entete
{
int adrDerBloc;
int nb;
int date_creation[6];
int date_modification[6];
char *nom ;
char *type;
char etab[100];
char specia[30];
int taille;
} Entete;
typedef struct TObF
{
FILE *fichier;
Entete entete;
} TObF;
TObF *f,*g,*d,*e,*b,*o,*af;
void affich( Maillon *p )
{
 // pour l'afichage de la liste
   while ( p != NULL ) {
	printf( "%d ", valeur(p) );
	p = p->next;
   }
   printf( "#\n" );

}
 void rechval( int v , Maillon *t , Maillon **p,Maillon **q , int *trouv )
 {
     // poure rechercher ue valeur dans un list
     *trouv = 0 ;
     *q = NULL ;
     *p = t;
     while ((*p) != NULL && (*trouv)==0 )
     {
         if ( (*p)->matricule== v )
         {
             *trouv = 1 ;
         }
         else
         {
             *q=*p ;
             *p=(*p)->next;
         }
     }
 }
  void rechvalORD( int v , Maillon *t , Maillon **p,Maillon **q , int *trouv )
 {
     // poure rechercher ue valeur dans un list
     *trouv = 0 ;
     *q = NULL ;
     *p = t;
     while ((*p) != NULL && (*trouv)==0 && (*p)->matricule <v)
     {
         if ( (*p)->matricule== v )
         {
             *trouv = 1 ;
         }
         else
         {
             *q=*p ;
             *p=(*p)->next;
         }
     }
 }
 void supval(int g , Maillon **t)
{
    Maillon *r,*a,*inter ;
    int tr=0,j=5;
    j=(*t)->matricule;
    if (j == g)
    {
        inter=(*t);
        (*t)=suivant(*t);
        liberer(&inter);
    }
    else
    {
    rechval(g , *t , &r , &a , &tr );
    if(tr==1)
    {
    a->next=r->next;
    liberer(&r);
    }
    }
}
/**************************************************model des fichier *************************************/
int ouvrir(TObF **f,char *chemin,char mode)
{
*f = malloc(sizeof(TObF));
char s[3];
if((mode == 'A') || (mode == 'a')) sprintf(s,"rb+");
else if ((mode == 'N') || (mode == 'n')) sprintf(s,"wb+");
else return 0;
(*f)->fichier = fopen(chemin, s);
if((*f)->fichier == NULL) return 0;
if((mode == 'A') || (mode == 'a'))
{
fread(&((*f)->entete), sizeof(Entete), 1, (*f)->fichier);
}
else if ((mode == 'N') || (mode == 'n'))
{
(*f)->entete.adrDerBloc = 0;
}
return 1;
}
void fermer(TObF *f)
{
//Sauvegarde de l'entête
rewind(f->fichier);
fwrite(&(f->entete), sizeof(Entete), 1, f->fichier);
fclose(f->fichier);
free(f);
}
void lireDir(TObF *f,int N_Bloc,Tbloc *buffer)
{
if(N_Bloc <= (f->entete).adrDerBloc)
{
fseek(f->fichier, sizeof(Entete) + (N_Bloc-1) * sizeof(Tbloc),SEEK_SET);
fread(buffer, 1, sizeof(Tbloc), f->fichier);
}
}
void lireDirIndex(TObF *f,int N_Bloc,TblocIndex *buffer)
{
if(N_Bloc <= (f->entete).adrDerBloc)
{
fseek(f->fichier, sizeof(Entete) + (N_Bloc-1) * sizeof(TblocIndex),SEEK_SET);
fread(buffer, 1, sizeof(TblocIndex), f->fichier);
}
}
void lireDirIndex2(TObF *f,int N_Bloc,TblocIndex2 *buffer)
{
if(N_Bloc <= (f->entete).adrDerBloc)
{
fseek(f->fichier, sizeof(Entete) + (N_Bloc-1) * sizeof(TblocIndex2),SEEK_SET);
fread(buffer, 1, sizeof(TblocIndex2), f->fichier);
}
}
void ecrireDirIndex(TObF *f,int N_Bloc,TblocIndex *buffer)
{
if(N_Bloc <= (f->entete).adrDerBloc)
{
fseek(f->fichier, sizeof(Entete) + (N_Bloc-1) * sizeof(TblocIndex),SEEK_SET);
fwrite(buffer, 1, sizeof(TblocIndex), f->fichier);
}
}
void ecrireDirIndex2(TObF *f,int N_Bloc,TblocIndex2 *buffer)
{
if(N_Bloc <= (f->entete).adrDerBloc)
{
fseek(f->fichier, sizeof(Entete) + (N_Bloc-1) * sizeof(TblocIndex2),SEEK_SET);
fwrite(buffer, 1, sizeof(TblocIndex2), f->fichier);
}
}
void ecrireDir(TObF *f,int N_Bloc,Tbloc *buffer)
{
if(N_Bloc <= (f->entete).adrDerBloc)
{
fseek(f->fichier, sizeof(Entete) + (N_Bloc-1) * sizeof(Tbloc),SEEK_SET);
fwrite(buffer, 1, sizeof(Tbloc), f->fichier);
}
}
int entete(TObF *f,int i)
{
if(i == 1) return (f->entete).adrDerBloc;
else return -1;
}
void aff_entete(TObF *f, int i, int val)
{
if(i == 1) (f->entete).adrDerBloc = val;
}
int alloc_bloc(TObF *f)
{
aff_entete(f,1,entete(f,1)+1);
return entete(f,1);
}
/*******************************************************************/
void chargementIndex(Maillon **t)
{
    TObF *zf;
int i=1,j=0;
ouvrir(&zf,"index.bin",'a');
Maillon *p,*q;
*t=NULL;
allouer(&p);
while (i<=entete(zf,1))
    {
        lireDirIndex(zf,i,&buff);
            while (j<buff.Nb)
            {
               (p)->matricule=buff.T[j].matricule;
               (p)->deplacement=buff.T[j].deplacement;
               (p)->num_bloc=buff.T[j].num_bloc;
               allouer(&q);
               if ( (j==(buff.Nb-1)) && (i==entete(zf,1)) )
               {
                   p->next=NULL;
               }
               else
               {
                 p->next=q;
               }
               if (j==0 && i==1) *t=p;
               p=q;
               j++;
            }
        j=0;
        i++;
    }
    fermer(zf);
}
void saveIndex(Maillon *p)
{
    Maillon *p1;
    ouvrir(&af,"index.bin",'n');
    int i,j=0;
    p1=p;
    i=alloc_bloc(af);
    while (p1!=NULL)
    {
        buff.T[j].deplacement=p1->deplacement;
        buff.T[j].matricule=p1->matricule;
        buff.T[j].num_bloc=p1->num_bloc;
        p1=p1->next;
        if ((j==999) || (p1==NULL))
        {
            buff.Nb=j+1;
            ecrireDirIndex(af,i,&buff);
            if (p1!=NULL)
            {
                i=alloc_bloc(af);
            }
            j=0;
        }
        j++;
    }
fermer(af);
}
void chargementIndex2(char filename[],MaillonIndex **tep)
{
TObF *of;
Maillon *p,*q;
int i=1,j=0;
MaillonIndex *t1,*qe;
ouvrir(&of,filename,'a');
allouerIndex(&t1);
lireDirIndex2(of,i,&bufff);
strcpy(t1->string,bufff.T[j].string);
allouer(&p);
t1->tete=p;
if (entete(of,1)>0) *tep=t1;
    while (i<=entete(of,1))
    {
        lireDirIndex2(of,i,&bufff);
        while (j<bufff.Nb)
        {
            p->num_bloc=bufff.T[j].num_bloc;
            p->deplacement=bufff.T[j].deplacement;
            p->matricule=bufff.T[j].matricule;
            if (strcasecmp(t1->string,bufff.T[j].string)==0)
            {
            if (((j)==bufff.Nb-1) && (i==entete(of,1)))
            {
                q->next=p;
                p->next=NULL;
                t1->next=NULL;
            }
            else
            {
                q=p;
                allouer(&p);
                q->next=p;
            }
            }
            else
            {
                    allouerIndex(&qe);
                    strcpy(qe->string,bufff.T[j].string);
                    t1->next=qe;
                    q->next=NULL;
                    qe->tete=p;
                    t1=qe;
                if (((j)==bufff.Nb-1) && (i==entete(of,1)))
                {
                    p->next=NULL;
                }
                else
                {
                q=p;
                allouer(&p);
                q->next=p;
                }
            }
            j++;
        }
        i++;
        j=0;
    }
fermer(of);
}
void chargementIndexA(char filename[],MaillonIndex **tep)
{
TObF *sf;
Maillon *p,*q;
int i=1,j=0;
MaillonIndex *t1,*qe;
ouvrir(&sf,"indexa.bin",'a');
allouerIndex(&t1);
lireDirIndex2(sf,i,&bufff);
t1->ancienter=bufff.T[0].ancienter;
allouer(&p);
t1->tete=p;
if (entete(sf,1)>0) *tep=t1;
    while (i<=entete(sf,1))
    {
        lireDirIndex2(sf,i,&bufff);
        while (j<bufff.Nb)
        {
            p->num_bloc=bufff.T[j].num_bloc;
            p->deplacement=bufff.T[j].deplacement;
            p->matricule=bufff.T[j].matricule;
            if (t1->ancienter==bufff.T[j].ancienter)
            {
            if (((j)==bufff.Nb-1) && (i==entete(sf,1)))
            {
                q->next=p;
                p->next=NULL;
                t1->next=NULL;
            }
            else
            {
                q=p;
                allouer(&p);
                q->next=p;
            }
            }
            else
            {
                    allouerIndex(&qe);
                    qe->ancienter=bufff.T[j].ancienter;
                    t1->next=qe;
                    q->next=NULL;
                    qe->tete=p;
                    t1=qe;
                if (((j)==bufff.Nb-1) && (i==entete(sf,1)))
                {
                    p->next=NULL;
                }
                else
                {
                q=p;
                allouer(&p);
                q->next=p;
                }
            }
            j++;
        }
        i++;
        j=0;
    }
fermer(sf);
}
void saveIndex2(char fichierIndex[],MaillonIndex *tf)
{
Maillon *p;
int i=1,j=0;
TblocIndex2 bif;
ouvrir(&af,fichierIndex,'a');
i=alloc_bloc(af);
while (tf!=NULL)
{
    p=tf->tete;
    while(p!=NULL)
    {
        bif.T[j].deplacement=p->deplacement;
        bif.T[j].num_bloc=p->num_bloc;
        bif.T[j].matricule=p->matricule;
        strcpy(bif.T[j].string,tf->string);
        j++;
        if (j==1000)
        {
            bif.Nb=j;
            ecrireDirIndex2(af,i,&bif);
            if (!(suivantIndex(tf)==NULL && suivant(p)==NULL)) i=alloc_bloc(af);
            j=0 ;
        }
        p=p->next;
    }
    if ( j>0 && tf->next==NULL)
    {
        bif.Nb=j;
        ecrireDirIndex2(af,i,&bif);
    }
    tf=suivantIndex(tf);
}
fermer(af);
}
void saveIndexA(char nomfich[],MaillonIndex *tf)
{
Maillon *p;
int i=1,j=0;
TblocIndex2 bif;
ouvrir(&f,nomfich,'n');
i=alloc_bloc(f);
while (tf!=NULL)
{
    p=tf->tete;
    while(p!=NULL)
    {
        bif.T[j].deplacement=p->deplacement;
        bif.T[j].num_bloc=p->num_bloc;
        bif.T[j].matricule=p->matricule;
        bif.T[j].ancienter=tf->ancienter;
        j++;
        if ((j==1000))
        {
            bif.Nb=j;
            ecrireDirIndex2(f,i,&bif);
            if (!( suivantIndex(tf)==NULL  &&  suivant(p)==NULL )) i=alloc_bloc(f);
            j=0;
        }
        p=p->next;
    }
    if ( j>0 && tf->next==NULL)
    {
        bif.Nb=j;
        ecrireDirIndex2(f,i,&bif);
    }
    tf=tf->next;
}
fermer(f);
}
void ins(int v , Maillon **t,int deplacement,int num_bloc)
{
    /* inserer une valeur dans un list non ordoné ie at the end of the list */
    Maillon *p,*d,*n ;
    int tr ;
    rechval(v,*t,&p,&d,&tr);
    if (!tr)
    {
        allouer(&n);
        aff_val(n,v,deplacement,num_bloc);
        aff_adr(n,NULL);
        if ( d==NULL )
        {
            *t=n ;
        }
        else
        {
            aff_adr(d,n);
        }
    }
}

void afficher_fichier()
{
  int i,j;
   ouvrir(&f , "ENSEIGNANT-MESRS.bin" ,'a');
   printf("%d \n",entete(f,1));
   for(j=1;j<=entete(f,1);j++)
   {
   lireDir(f,j,&buf) ;
   for(i=0;i<buf.Nb;i++)
   {
printf("wilaya_naissance : %s\n",buf.T[i].wilaya_naissance);
printf("date_Naissance : %s\n",buf.T[i].date_Naissance);
printf("date_recrutement : %s\n",buf.T[i].date_recrutement);
printf("dernier_diplome : %s\n",buf.T[i].dernier_diplome);
printf("etablissement_univ : %s\n",buf.T[i].etablissement_univ);
printf("groupe_sanguin : %s\n",buf.T[i].groupe_sanguin);
printf("nom_prenom : %s\n",buf.T[i].nom);
printf("grade : %s\n",buf.T[i].grade);
printf("sexe : %s\n",buf.T[i].sexe);
printf("specialite : %s \n",buf.T[i].specialite);
printf("matricule= %i  \n",buf.T[i].matricule);
printf("****************************************\n");
   }

   }
   fermer(f);
}
/*void afficher_fichier_parbloc(int k )
{
  int i,j;
   ouvrir(&f , "ENSEIGNANT-MESRS.bin" ,'a');
   printf("%d \n",entete(f,1));
   for(j=1;j<=entete(f,1);j++)
   {


   lireDir(f,j,&buf) ;
   for(i=0;i<buf.Nb;i++)
   {
printf("wilaya_naissance : %s\n",buf.T[i].wilaya_naissance);
printf("date_Naissance : %s\n",buf.T[i].date_Naissance);
printf("date_recrutement : %s\n",buf.T[i].date_recrutement);
printf("dernier_diplome : %s\n",buf.T[i].dernier_diplome);
printf("etablissement_univ : %s\n",buf.T[i].etablissement_univ);
printf("groupe_sanguin : %s\n",buf.T[i].groupe_sanguin);
printf("nom_prenom : %s\n",buf.T[i].nom);
printf("grade : %s\n",buf.T[i].grade);
printf("sexe : %s\n",buf.T[i].sexe);
printf("specialite : %s \n",buf.T[i].specialite);
printf("matricule= %i  \n",buf.T[i].matricule);
printf("****************************************\n");
   }

   }
   fermer(f);
}
*/
/*****************************************PART 2*****************************************************************/

int dep(Maillon *p)
{return p->deplacement ;}

int nbloc(Maillon *p)
{return p->num_bloc;}

void aff_adrIndex_droite(MaillonIndex *p,MaillonIndex *q)
{p->next=q ;}

void aff_adrIndex_haut(MaillonIndex *p,Maillon *q)
{p->tete=q;}

MaillonIndex *suivantIndex_droite(MaillonIndex *p)
{return p->next;}

Maillon *suivantIndex_haut(MaillonIndex *p)
{return (p->tete);}


char *valeurIndex(MaillonIndex *p)
{return p->string;}
/*//////////////////////////////////////////////*/
void rech_LS1(int v ,int nbloc , int dep , Maillon **t,Maillon2 **t2, int *trouv )
{

Maillon *q,*p,*r;
Maillon2 *h,*g,*s;
*trouv=0;
q=*t;
p=NULL;
h=*t2;
g=NULL;
int cond=0;
    while (h!=NULL && cond!=1)
    {

    if (v<valeur2(h) ) {cond=1 ;}
    else
    {g=h;
    h=suivant_droite2(h);}
    }

    cond=0;
    if(h!=NULL)
    {

        if(g!=NULL) {q=suivant_bas2(g);}
        else {q=*t;}
        r=suivant_bas2(h);

        while(q!=r && *trouv!=1 && cond!=1)
        {
            if(valeur(q)==v)  {*trouv=1;}
            else
            {
                if(valeur(q)>v)
                {
                    cond=1;


                }
                else{p=q;
                   q=suivant(q);
                }

            }
        }


    }
    else
    {

              if (g==NULL ) { q=*t;}
              else {q=suivant_bas2(g);}
              cond=0;
              while(q!=NULL && *trouv!=1 && cond!=1)
              {
                  if (valeur(q)==v){*trouv=1;}
                  else
                  {
                      if (valeur(q)>v)
                      {
                          cond=1;
                      }
                      else {p=q;
                      q=suivant(q);
                      }
                  }

              }
      }


    if (*trouv ==0)
    {


        allouer(&r) ;
        aff_val(r,v,dep,nbloc);
        aff_adr(r,q);
        if (q==*t)  *t=r ;
        else   aff_adr(p,r);




       if (v%50==0 && v!=0)
       {
           allouer2(&s);
           aff_val2(s,v);
           aff_adr_bas2(s,r) ;
           aff_adr_droite2(s,h) ;
           if(g==NULL)
           {
               *t2=s;
           }
           else{aff_adr_droite2(g,s);}


       }

}
}
void afficher_liste(Maillon *p)
{
    printf("votre liste est : \n");
   while ( p != NULL )
    {
	printf( "%ld  et %d et %d \n", valeur(p),nbloc(p),p->deplacement );
	p = suivant(p);
    }
   printf( "#\n" );
}

void afficher_listeindex(MaillonIndex *p)
{
   {
    Maillon *g;
    printf("votre liste est : \n");
   while ( p != NULL )
    {
    g=p->tete;
	if (g!=NULL) printf( "%s \n", p->string );
	while (g!=NULL)
    {
        printf("   matricule  %d  num_bloc %d  deplacement %d \n",g->matricule,g->num_bloc,g->deplacement);
        g=g->next;
    }
	p = p->next;
    }
   printf( "#\n" );
}
}
void afficher_listeindexA(MaillonIndex *p)
{
    Maillon *g;
    printf("votre liste est : \n");
   while ( p != NULL )
    {
    g=p->tete;
	if (g!=NULL) printf( "%d \n", p->ancienter );
	while (g!=NULL)
    {
        printf("  matricule  %d  num_bloc %d  deplacement %d \n",g->matricule,g->num_bloc,g->deplacement);
        g=g->next;
    }
	p = suivantIndex_droite(p);
    }
   printf( "#\n" );
}

int matricule()
{
    int x;
    x=(rand()*rand())%888888 + 111111 ;
    return x;
}
char *date_naissance()
{
    int x,y,z;
    char jour[4];
    char mois[2];
    static char annee[22];
    x=rand()%39+1953 ;
    y=rand()%11 +2 ;
    if(x%4==0 && y==2) { z=rand()%29+1 ;  }
    else
    {
        if (y==1 || y==3 || y==5 || y==7 || y==8 || y==10 || y==12) {z=rand()%31 +1 ;}
        else
        {
            if (y==2) {z=rand()%28+1 ;}
            else {z=rand()%30 +1;}
        }
    }

    itoa(x,annee,10);

     strcat(annee,"/") ;
     itoa(y,mois,10) ;
     strcat(annee,mois) ;

     strcat(annee,"/");

     itoa(z,jour,10) ;
     strcat(annee,jour);

     return annee;
}

int ver_date_naissance(int annee,int mois,int jour)
{
int v=1;

    if ((mois<=12 && mois >=1) && (jour<=31 && jour>=1) && (annee<=2000 && annee>=1900))
    {

    if(mois==2 && jour==29)
    {

        if((annee%4)==0)
        {
            if(annee%100==0) {
                if(annee%400!=0) {
                {printf(" veuillez rentrer votre date de naissance correcetement SVP car l'annee %i n'est pas bissextille !\n",annee);
                v=0;
                }
            }

        }
        }
        else {
                printf(" veuillez rentrer votre date de naissance correcetement SVP car l'annee %i n'est pas bissextille !\n",annee);
        v=0;
        }
    }


     if ((mois==4 || mois==6 || mois==9 || mois==11) && jour==31 ) { printf ("veuillez rentrer votre date de naissance correcetement SVP car ce mois contient  30 jours seulement !\n");
     v=0;
     }
     if(mois==2 && jour>29) {printf("veuillez rentrer votre date de naissance correcetement SVP car fevrier a au plus 29 jours ! \n");
     v=0;
     }
    }
    else {printf("veuillez rentrer votre date de naissance correcetement SVP  \n");
    v=0;
    }

    return v;
}

int ver_date_recrutement(int annee_naissance,int annee,int mois,int jour)
{
int v=1;


    if(annee-annee_naissance<20) { v=0;
    printf("veuillez rentrer votre date de recrutement correcetement SVP car l'age reglementaire d'un enseignant est plus de 20 ans ! \n");
      }
    else
    {
    if ((mois<=12 && mois >=1) && (jour<=31 && jour>=1) && (annee<=2000 && annee>=1900))
    {

    if(mois==2 && jour==29)
    {

        if((annee%4)==0)
        {
            if(annee%100==0) {
                if(annee%400!=0) {
                {printf(" veuillez rentrer votre date de recrutement correcetement SVP car l'annee %i n'est pas bissextille !\n",annee);
                v=0;
                }
            }

        }
        }
        else {
                printf(" veuillez rentrer votre date de recrutement correcetement SVP car l'annee %i n'est pas bissextille !\n",annee);
        v=0;
        }
    }


     if ((mois==4 || mois==6 || mois==9 || mois==11) && jour==31 ) { printf ("veuillez rentrer votre date de recrutement correcetement SVP car ce mois contient 30 jours seulment ! ! \n");
     v=0;
     }
     if(mois==2 && jour>29) {printf("veuillez rentrer votre date de recrutement correcetement SVP car fevrier a au plus 29 jours ! \n");
     v=0;
     }
    }
    else {printf("veuillez rentrer votre date de recrutement correcetement SVP  \n");
    v=0;
    }
    }
    return v;
}


char *wilaya_naissance()
{


int x;
x=rand()%48 +1;
return wi[x].wila;

}


int ver_wilaya(char *wilaya)
{
    int stop=0,x=1;
    while( x<=48 && stop!=1)
    {
        if (strcasecmp(wi[x].wila,wilaya)==0) { stop=1 ;}
        else {x++;}
    }
    if(stop==0 ) {return 0;
    printf("veuillez rentrer votre wilaya de naissance correctement SVP !\n");
    }
    else return 1;

}




char *sexe()
{
    int x;
    x=rand()%2+1 ;
    if (x==1) {return "masculin" ;}
    else {return "feminin" ;}
}

int ver_sexe(char *sexe)
{
    int a=strcasecmp("masculin",sexe),b=strcasecmp("feminin",sexe);

    if(a==0 || b==0 ) {return 1;}
    else {
    printf("veuillez rentrer votre sexe correctement SVP !\n");
    return 0;
    }


}


char *nom_prenom()
{
  int x,i;
  x=rand()%26+4 ;
  static char np[30] ;
  unsigned char y;
  for(i=0; i<=x+1 ; i++)
  {
      y=rand()%26 +1 ;
      if(i==0) {y=y+64;}
      else
      {
          if (i==x/2 +1) {y=y+64;}
          else {y=y+96 ;}
      }

      if (i==x/2) {np[i]=32  ;}
      else {np[i]=y ;}
  }
  return np;
}
char *date_recrutement()
{
    int x,y,z;
    char jour[4];
    char mois[2];
    static char annee[22];
    x=rand()%39+1979 ;
    y=rand()%11 +2 ;
    if(x%4==0 && y==2) { z=rand()%29+1 ;  }
    else
    {
        if (y==1 || y==3 || y==5 || y==7 || y==8 || y==10 || y==12) {z=rand()%31 +1 ;}
        else
        {
            if (y==2) {z=rand()%28+1 ;}
            else {z=rand()%30 +1;}
        }
    }



    itoa(x,annee,10);


     strcat(annee,"/") ;
     itoa(y,mois,10) ;
     strcat(annee,mois) ;

     strcat(annee,"/");

     itoa(z,jour,10) ;
     strcat(annee,jour);


     return annee;
}
char *grade()
{
    int x;
    x=rand()%6 +1;
    if (x==1){return "professeur(e)" ;}
    if (x==2){return "maitre de conferences rang a" ;}
    if (x==3){return "maitre de conferences Rang b" ;}
    if (x==4){return "maitre assistant(e) rang a" ;}
    if (x==5){return "maitre assistant(e) rang b" ;}
    if (x==6){return "assistant(e)" ;}
}

int ver_grade(char *grade)
{
    int a=strcasecmp("professeure",grade),g=strcasecmp("professeur",grade),b=strcasecmp("maitre de conferences rang a",grade),c=strcasecmp("maitre de conferences Rang b",grade),d=strcasecmp("maitre assistant rang a",grade),h=strcasecmp("maitre assistante rang a",grade),e=strcasecmp("maitre assistante rang b",grade),i=strcasecmp("maitre assistant rang b",grade),f=strcasecmp("assistante",grade),j=strcasecmp("assistant",grade);

    if(a==0 || b==0 || c==0 || d==0 || e==0 || f==0 || g==0 || h==0 || i==0 || j==0) {return 1;}
    else {
       printf("veuillez rentrer votre grade correctement SVP !\n");
       return 0;
    }
}

char *groupe_sanguin()
{
    int x;
    x=rand()%8 +1;

    if (x==1){return "O+" ;}
    if (x==2){return "A+" ;}
    if (x==3){return "B+" ;}
    if (x==4){return "O-" ;}
    if (x==5){return "A-" ;}
    if (x==6){return "AB+" ;}
    if (x==7){return "B-" ;}
    if (x==8){return "AB-" ;}
}

int ver_groupe_sanguin(char *groupe)
{
    int a=strcasecmp("O+",groupe),b=strcasecmp("A+",groupe),c=strcasecmp("B+",groupe),d=strcasecmp("O-",groupe),e=strcasecmp("A-",groupe),f=strcasecmp("AB+",groupe),g=strcasecmp("B-",groupe),h=strcasecmp("AB-",groupe);

    if(a==0 || b==0 || c==0 || d==0 || e==0 || f==0 ||g==0||h==0) {return 1;}
    else {
       printf("veuillez rentrer votre groupe sanguin correctement SVP !\n");
       return 0;
    }


}




char *specialite()
{
int x;
x=rand()%38+1;
return spe[x].specialite;
}

int ver_specia(char specia[20])
{
int i=0,stop=1;

while (stop!=0 && i<strlen(specia))
{
    if((specia[i]>'z' || specia[i]<'a' ) && (specia[i]<'A' || specia[i]>'Z') ) {stop=0;

    }
    if(specia[i]==' ') { stop=1;}

    i++;
}
if(stop==0){  printf("veuillez rentrer votre specialite  correctement SVP ! \n");}
return stop;
}

int ver_nom(char specia[20])
{
int i=0,stop=1;

while (stop!=0 && i<strlen(specia))
{
    if((specia[i]>'z' || specia[i]<'a' ) && (specia[i]<'A' || specia[i]>'Z') ) {stop=0;

    }
    if(specia[i]==' ') { stop=1;}

    i++;
}
if (stop==0) {printf("veuillez rentrer votre nom  correctement SVP ! \n");}
return stop;
}
int ver_specialite(char specia[20])
{
    int stop=0;
    int j=1;
    while( j<=38 && stop!=1)
    {
        if (strcasecmp(spe[j].specialite,specia)==0) { stop=1 ;}
        else {j++;}
    }
    if(stop==1) return 1;

    else {

        return ver_specia(specia);
    }
return stop ;
}





char *dernier_diplome()
{
    int x;
    x=rand()%5 +1;
    if (x==1){return "Doctorat d'Etat" ;}
    if (x==2){return "Doctorat en sciences" ;}
    if (x==3){return "PhD" ;}
    if (x==4){return "HDR" ;}
    if (x==5){return "Magistere" ;}

}

int ver_dernier_diplome(char *dernier_diplome)
{
    int a=strcasecmp("Doctorat d'Etat",dernier_diplome),b=strcasecmp("Doctorat en sciences",dernier_diplome),c=strcasecmp("PhD",dernier_diplome),d=strcasecmp("HDR",dernier_diplome),e=strcasecmp("Magistere",dernier_diplome);

    if(a==0 || b==0 || c==0 || d==0 || e==0) {return 1;}
    else {
       printf("veuillez rentrer votre dernier diplome correctement SVP !\n");
       return 0;
    }
}

char *etablissement_Univ()
{
int x;
x=rand()%108+1;
return etabl[x].etab;

}





int ver_etablissement(char eta[100])
{
    int stop=0;
    int j=1;
    while( j<=108 && stop!=1)
    {
        if (strcasecmp(etabl[j].etab,eta)==0) { stop=1 ;}
        else {j++;}
    }
  if(stop==0){ printf("veuillez rentrer votre etablissement correctement SVP !\n");}
return stop ;

}
int longliste( Maillon *t )
/* retourne avec la longueur de la liste */
{
    int cpt=0;
    Maillon *p=t;
    while ( p !=NULL)
    {
        p=suivant(p);
        cpt+=1 ;
    }
    return cpt;
}
char *max_specialite()
{
    MaillonIndex *q,*p;
    q=ts;
    int max=0;
    while(q!=NULL)
    {

        if(longliste(suivantIndex_haut(q))>=max) {max=longliste(suivantIndex_haut(q)) ;
        p=q;
        }
         q=suivantIndex(q) ;
    }
    return valeurIndex(p);
}

char *max_etab()
{
    MaillonIndex *q,*p;
    q=te;
    int max=0;
    while(q!=NULL)
    {

        if(longliste(suivantIndex_haut(q))>=max) {max=longliste(suivantIndex_haut(q)) ;
        p=q;
        }
         q=suivantIndex(q) ;
    }
    return valeurIndex(p);
}

int i=0;
void chargement_initial()
{
    int n,k,val,ver=0;
    FILE *h;
    t=NULL;
    t2=NULL;
    char term;
    Maillon *p=NULL,*r=NULL,*y=NULL,*a=NULL,*z=NULL;
    MaillonIndex *q,*s,*c,*d;
    while(ver!=1)
    {
    printf("entrez le nombre d'enseignats que vous voudrez l'inserer  :\n") ;
                    if(scanf("%d%c", &n, &term) != 2 || term != '\n')
                {
                   printf("veuillez entrer un entier SVP \n");
                   n=0;
                   fflush(stdin);

                }
                 else {if(n<=0) {printf("veuillez entrer un nombre positif SVP ! \n"); }
    else {
    ver=1;
    nb_ens=n;
    ouvrir(&f,"ENSEIGNANT-MESRS.bin",'n');
    ouvrir(&g,"index.bin",'n') ;
    ouvrir(&o,"indexa.bin",'n') ;
    ouvrir(&e,"indexs.bin",'n') ;
    ouvrir(&b,"indexe.bin",'n') ;
    int j=1,i=0,trouv=1,v,trouuv=0,troouv=0,troouuv=0;
     char wilaya[20];
    h=fopen("wilaya.txt","r");
/**** lecture des wilaya du fichier texte wilaya.txt**/
for(j=1;j<=48;j++)
{
    fgets(wilaya,20,h);
    wilaya[strlen(wilaya)-1]='\0';
    strcpy(wi[j].wila,wilaya) ;
}
fclose(h);


  for(j=0;j<=40;j++)
   {

    allouerIndex(&c);
    aff_adrIndex_haut(c,NULL);
    if(j!=0) {aff_adrIndex_droite(s,c);}
    else {ta=c;}
    s=c;
    aff_valIndex(c,j,"") ;
   }
    aff_adrIndex_droite(c,NULL);

    d=ta;
    char eta[100];
    /**** lecture des etablissements du fichier texte etablissement.txt ****/
    h=fopen("Etablissement.txt","r");

    for(j=1;j<=108;j++)
   {
    fgets(eta,100,h) ;
    eta[strlen(eta)-1]='\0';
    strcpy(etabl[j].etab,eta) ;
    allouerIndex(&c);

    aff_adrIndex_haut(c,NULL);
    if(j!=1) {aff_adrIndex_droite(s,c);}
    else {te=c;}
    s=c;
    aff_valIndex(c,1,eta) ;
   }
    aff_adrIndex_droite(c,NULL);

    c=te;
    fclose(h);



    char specia[30] ;
    h=fopen("specialite.txt","r");

    for(k=1;k<=39;k++)
    {
    fgets(specia,30,h) ;
    specia[strlen(specia)-1]='\0';
    strcpy(spe[k].specialite,specia);
    allouerIndex(&q);
    aff_adrIndex_haut(q,NULL);
    if(k!=1) {aff_adrIndex_droite(s,q);}
    else {ts=q;}
    s=q;
    aff_valIndex(q,1,specia) ;
    }
    aff_adrIndex_droite(q,NULL);
    q=ts;

    fclose(h);
j=0;
    for(k=0;k<n;k++)
    {

        // chargement des champs
        strcpy(buf.T[i].etablissement_univ,etablissement_Univ());
        strcpy(buf.T[i].wilaya_naissance,wilaya_naissance()) ;
        strcpy(buf.T[i].date_Naissance,date_naissance()) ;
        strcpy(buf.T[i].date_recrutement,date_recrutement());
        val=ancienter(buf.T[i].date_recrutement) ;
        buf.T[i].dernier_diplome=dernier_diplome();
        strcpy(buf.T[i].date_Naissance,date_naissance()) ;
        buf.T[i].groupe_sanguin=groupe_sanguin() ;
        strcpy(buf.T[i].nom,nom_prenom()) ;
        buf.T[i].grade=grade() ;
        buf.T[i].sexe=sexe() ;
       strcpy(buf.T[i].specialite,specialite()) ;
       while(trouv!=0)
        {
        v=matricule();
        rech_LS1(v,j+1,i,&t,&t2,&trouv) ; /*** chargement liste d'index primaire en utilisant la SKIP LISTE***/
        }
        trouv=1;
        buf.T[i].matricule=v;
           while(q!=NULL && trouuv!=1) /****chargement liste d'index des specialites***/
           {
            if(strcasecmp(buf.T[i].specialite,valeurIndex(q))==0)
            {
                if(suivantIndex_haut(q)!=NULL){r=suivantIndex_haut(q);}
                else {r=NULL;}
                allouer(&a);
                aff_val(a,buf.T[i].matricule,i,j+1) ;
                aff_adrIndex_haut(q,a);
                aff_adr(a,r);
                trouuv=1;
            }
            else{q=suivantIndex_droite(q);}
            }
            q=ts;
            trouuv=0;


            while(c!=NULL && troouv!=1) /**** chargement liste d'index des etablissements***/
           {

            if(strcasecmp(buf.T[i].etablissement_univ,valeurIndex(c))==0)
            {
                if(suivantIndex_haut(c)!=NULL){y=suivantIndex_haut(c);}
                else {y=NULL;}
                allouer(&p);
                aff_val(p,buf.T[i].matricule,i,j+1) ;
                aff_adrIndex_haut(c,p);
                aff_adr(p,y);
                troouv=1;
            }
            else{c=suivantIndex_droite(c);}
            }
            troouv=0;
            c=te;


            while(d!=NULL && troouuv!=1) /****chargement liste d'index des ancienters***/
           {

            if(val==valeurIndexA(d))
            {
                if(suivantIndex_haut(d)!=NULL){z=suivantIndex_haut(d);}
                else {z=NULL;}
                allouer(&a);
                aff_val(a,buf.T[i].matricule,i,j+1) ;
                aff_adrIndex_haut(d,a);
                aff_adr(a,z);
                troouuv=1;
            }
            else{d=suivantIndex_droite(d);}
            }
            d=ta;
            troouuv=0;


        i++;
        if(i==1000)
        {
            buf.Nb=1000;
            j=alloc_bloc(f);
            ecrireDir(f,j,&buf) ;
            i=0;

        }

    }
    if (n%1000!=0 && n!=1000)
    {
        buf.Nb=i;
        j=alloc_bloc(f);
        ecrireDir(f,j,&buf) ;
    }


       i=0;
        p=t;
        while(p!=NULL)  /****enregistrement liste d'index primaire dans le fichier***/
        {

         buff.T[i].matricule=valeur(p);
         buff.T[i].deplacement=dep(p);
         buff.T[i].num_bloc=nbloc(p);
         i++;




        p=suivant(p);
        if(i==1000)
        {
            buff.Nb=1000;
            j=alloc_bloc(g);
            ecrireDirIndex(g,j,&buff) ;
            i=0;
        }
        }
            if (n%1000!=0 && n!=1000)
          {
           buff.Nb=i;
        j=alloc_bloc(g);
        ecrireDirIndex(g,j,&buff) ;
        }




        i=0;
        q=ts;


            while(q!=NULL) /***** enregistrement liste d'index des specialites***/
            {
                p=suivantIndex_haut(q);
            while(p!=NULL)
            {
         bufff.T[i].deplacement=dep(p);
         bufff.T[i].matricule=valeur(p);
         bufff.T[i].num_bloc=nbloc(p);
         strcpy(bufff.T[i].string,q->string);
        i++;

        p=suivant(p);
        if(i==1000)
        {
            bufff.Nb=1000;
            j=alloc_bloc(e);
            ecrireDirIndex2(e,j,&bufff) ;
            i=0;
        }
        }
        q=suivantIndex_droite(q);
}

            if (n%1000!=0 && n!=1000)
          {
           bufff.Nb=i;
        j=alloc_bloc(e);
        ecrireDirIndex2(e,j,&bufff) ;
        }


     i=0;
        q=te;

            while(q!=NULL) /*****enregistrement liste d'index des etablisssement****/
            {
                p=suivantIndex_haut(q);

            while(p!=NULL)
            {
         bufff.T[i].deplacement=dep(p);
         bufff.T[i].matricule=valeur(p);
         bufff.T[i].num_bloc=nbloc(p);
         strcpy(bufff.T[i].string,q->string);

        i++;

        p=suivant(p);
        if(i==1000)
        {
            bufff.Nb=1000;
            j=alloc_bloc(b);
            ecrireDirIndex2(b,j,&bufff) ;
            i=0;
        }
        }
        q=suivantIndex_droite(q);
}

            if (n%1000!=0 && n!=1000)
          {
           bufff.Nb=i;
        j=alloc_bloc(b);
        ecrireDirIndex2(b,j,&bufff) ;
        }




             i=0;
             q=ta;

            while(q!=NULL) /***** enregistrement liste d'index des ancienters dans le fichier***/
            {
                p=suivantIndex_haut(q);
            while(p!=NULL)
            {
         bufff.T[i].deplacement=dep(p);
         bufff.T[i].matricule=valeur(p);
         bufff.T[i].num_bloc=nbloc(p);
         bufff.T[i].ancienter=q->ancienter;

        i++;

        p=suivant(p);
        if(i==1000)
        {
            bufff.Nb=1000;
            j=alloc_bloc(o);
            ecrireDirIndex2(o,j,&bufff) ;
            i=0;
        }
        }
        q=suivantIndex_droite(q);
}

            if (n%1000!=0 && n!=1000)
          {
           bufff.Nb=i;
        j=alloc_bloc(o);
        ecrireDirIndex2(o,j,&bufff) ;
        }


            time_t t = time(NULL);
            struct tm tm =*localtime(&t);                /***** la date de creation du fichier********/
            (f->entete).date_creation[0]=tm.tm_mday ;
            (f->entete).date_creation[1]=tm.tm_mon+1 ;
            (f->entete).date_creation[2]=tm.tm_year+1900 ;
            (f->entete).date_creation[3]=tm.tm_hour ;
            (f->entete).date_creation[4]=tm.tm_min ;
            (f->entete).date_creation[5]=tm.tm_sec ;

            (f->entete).date_modification[0]=tm.tm_mday ;  /****la date de modification du fichier****/
            (f->entete).date_modification[1]=tm.tm_mon+1 ;
            (f->entete).date_modification[2]=tm.tm_year+1900 ;
            (f->entete).date_modification[3]=tm.tm_hour ;
            (f->entete).date_modification[4]=tm.tm_min ;
            (f->entete).date_modification[5]=tm.tm_sec ;


            (f->entete).nom="ENSEIGNANT-MESRS.bin \0" ;
            (f->entete).type="Fichier BIN \0" ;
            (f->entete).nb=nb_ens; /***** nombre d'enseignats dans le fichier****/
             long size;
            fseek(f->fichier,0,SEEK_END); /**** taille du fichier****/
              size=ftell(f->fichier) ;
              f->entete.taille=(size/1024)+1;
                strcpy((f->entete).specia,max_specialite());
            strcpy((f->entete).etab,max_etab());



fermer(o);
fermer(b);
fermer(e);
fermer(g);
fermer(f);
    }
    }
    }
}


void supprimer_enregistrement(int matricule)
{
char etablisssement_univ[100],specialite[30];
Tbloc buf2;
int trouv=0,i=0,j,stop=0,ancientee;
Maillon *res,*pre  ;
MaillonIndex *r,*e ;
ouvrir(&f,"ENSEIGNANT-MESRS.bin",'a');
rechval(matricule,t,&res,&pre,&trouv);
if (trouv)
{
    matricule=res->matricule;
    j=res->deplacement;
    i=res->num_bloc;
    lireDir(f,i,&buf);
    strcpy(etablisssement_univ,buf.T[j].etablissement_univ);
    strcpy(specialite,buf.T[j].specialite);
    ancientee=ancienter(buf.T[j].date_recrutement);
    lireDir(f,entete(f,1),&buf2);
    buf2.Nb--;
    buf.T[j].matricule=buf2.T[buf2.Nb].matricule;
    strcpy(buf.T[j].date_Naissance,buf2.T[buf2.Nb].date_Naissance);
    strcpy(buf.T[j].date_recrutement,buf2.T[buf2.Nb].date_recrutement);
    buf.T[j].dernier_diplome=buf2.T[buf2.Nb].dernier_diplome;
    strcpy(buf.T[j].etablissement_univ,buf2.T[buf2.Nb].etablissement_univ);
    buf.T[j].grade=buf2.T[buf2.Nb].grade;
    buf.T[j].groupe_sanguin=buf2.T[buf2.Nb].groupe_sanguin;
    strcpy(buf.T[j].nom,buf2.T[buf2.Nb].nom);
    buf.T[j].sexe=buf2.T[buf2.Nb].sexe;
    strcpy(buf.T[j].specialite,buf2.T[buf2.Nb].specialite);
    strcpy(buf.T[j].wilaya_naissance,buf2.T[buf2.Nb].wilaya_naissance);
    if (i==entete(f,1))
    {
        buf.Nb--;
        ecrireDir(f,i,&buf);
    }
    else
    {
        ecrireDir(f,i,&buf);
        ecrireDir(f,entete(f,1),&buf2);
    }
    if (buf2.Nb==0)
    if (buf2.Nb==0) aff_entete(f,1,entete(f,1)-1);
    Maillon *inter;
    if (t==res)
    {
        inter=t;
        t=t->next;
        liberer(&inter);
    }
    else
    {
        pre->next=res->next;
        liberer(&res);
    }
    /***********************suppresion de l'index des etablissement*******************/
    stop=0;
    r=te;
    Maillon *p;
    while (r!=NULL && !stop)
        {
        if(!(strcasecmp(r->string,etablisssement_univ)))
            {
            p=r->tete;
            supval(matricule,&(r->tete));
            stop=1;
            }
        if (!stop)
            {
            e=r;
            r=suivantIndex(r);
            }
        }
        if (p==NULL)
        {
            e->next=r->next;
            libererIndex(&r);
        }
        /***********************suppresion de l'index des specialite*******************/
    stop=0;
    r=ts;
    while (r!=NULL && !stop)
        {
        if((strcasecmp(r->string,specialite))==0)
            {
            p=r->tete;
            supval(matricule,&(r->tete));
            stop=1;
            }
        if (!stop)
        {
        e=r;
        r=suivantIndex(r);
        }
        }
        if ((r->tete)==NULL)
        {
            e->next=r->next;
            libererIndex(&r);
        }
        /***********************suppresion de l'index des ancientee*******************/
    stop=0;
    r=ta;
    while (r!=NULL && !stop)
        {
        if(r->ancienter==ancientee)
            {
            supval(matricule,&(r->tete));
            stop=1;
            }
        if (!stop)
        {
        e=r;
        r=suivantIndex(r);
        }
        }
        if (p==NULL)
        {
            e->next=r->next;
            libererIndex(&r);
        }

                    time_t t = time(NULL);
            struct tm tm =*localtime(&t);
            (f->entete).date_modification[0]=tm.tm_mday ;
            (f->entete).date_modification[1]=tm.tm_mon+1 ;
            (f->entete).date_modification[2]=tm.tm_year+1900 ;
            (f->entete).date_modification[3]=tm.tm_hour ;
            (f->entete).date_modification[4]=tm.tm_min ;
            (f->entete).date_modification[5]=tm.tm_sec ;
            strcpy((f->entete).specia,max_specialite());
            strcpy((f->entete).etab,max_etab());
            (f->entete).nb --;


}
fermer(f);
}
void modification_etab(int matricule)
{
char etablisssement_univ[100];
char etablissement_univ[100];
Tbloc buf5;
int trouv=0,i=0,j,stop=0,ver=0;
Maillon *res,*pre,*p;
MaillonIndex *r,*e;
ouvrir(&f,"ENSEIGNANT-MESRS.bin",'a');
rechval(matricule,t,&res,&pre,&trouv); //recherch pour trouver si le matricule exist et pour trouver le num de bloc
if (trouv) //si le matricule exist
{
    i=res->num_bloc;
    j=res->deplacement;
    lireDir(f,i,&buf5);
    strcpy(etablissement_univ,buf5.T[j].etablissement_univ);
    printf("entrer le nouvau etablissemnt \n");
    while(ver!=1) //lecture de nouveau etablissement et controle d'erreur
    {
    scanf(" %[^\t\n]s",&etablisssement_univ);
    ver=ver_etablissement(etablisssement_univ);
    }
    strcpy(buf5.T[j].etablissement_univ,etablisssement_univ); //remplacement dans le fichier
    ecrireDir(f,i,&buf5);
    //             remplacement dans l'index d'etablissement
    r=te;
    while (r!=NULL && !stop)
    {
    if(!(strcasecmp(r->string,etablissement_univ)))
    {
        supval(matricule,&(r->tete));
        stop=1;
    }
    e=r;
    r=suivantIndex(r);
    }
    stop=0;
    r=te;
    while (r!=NULL && !stop)
        {
        if(!(strcasecmp(r->string,etablisssement_univ)))
            {
            ins(matricule,&(r->tete),j,i); //insertion dans la list de nouveau etablissement
            stop=1;
            }
        e=r;
        r=suivantIndex(r);
        }
    if (!stop)
    {
        // si le vouveau etablissement n'exit pas
    allouerIndex(&r);
    strcpy(r->string,etablisssement_univ);
    r->next=NULL;
    allouer(&p);
    p->matricule=matricule;
    p->deplacement=j;
    p->num_bloc=i;
    p->next=NULL;
    r->tete=p;
   if (te==NULL)
   {
       te=r;
   }
   else
   {
    e->next=r;
   }
   }

            time_t t = time(NULL);
            struct tm tm =*localtime(&t);
            (f->entete).date_modification[0]=tm.tm_mday ;
            (f->entete).date_modification[1]=tm.tm_mon+1 ;
            (f->entete).date_modification[2]=tm.tm_year+1900 ;
            (f->entete).date_modification[3]=tm.tm_hour ;
            (f->entete).date_modification[4]=tm.tm_min ;
            (f->entete).date_modification[5]=tm.tm_sec ;
            strcpy((f->entete).specia,max_specialite());
            strcpy((f->entete).etab,max_etab());

}
else
{
    printf("cette ens n'est pas enregistrer , veuillez vous l'ajouter");
}
fermer(f);
}

void supprimer_specialite()
{
    // recherche de la specialite dans la list d'index des specialtes et suppresion un par un
    Maillon *e,*afr;
    MaillonIndex *r;
    int stop=0,k,ver=0;
    char specialite[100];
    printf("entrer la specialiter a supprimer \n");
    while(ver!=1) // controle d'erreur
    {
    scanf(" %[^\t\n]s",&specialite);
    ver=ver_specialite(specialite);
    }
    r=ts;
    while (r!=NULL && !stop)
        {
        if((strcasecmp(r->string,specialite)==0))
            {
            e=r->tete;
            stop=1;
            }
            else
            {
        r=suivantIndex(r);
            }
        }
    while (e!=NULL && stop==1)
    {
        afr=e->next;
        k=e->matricule;
        supprimer_enregistrement(k);
        ;
        e=afr;



    }

    if(stop==0) {printf("le specialiter n'exit pas");}
                            strcpy((f->entete).specia,max_specialite());
            strcpy((f->entete).etab,max_etab());
(f->entete).nb --;

}
void requetteAintervale()
{
char etablissement_univ[100];
Tbloc buf;
ouvrir(&f,"ENSEIGNANT-MESRS.bin",'a');
int trouv=0,i=-1,j,stop=0,ancienteemax,ancienteemin,ver=0;
Maillon *res,*pre,*p,*e;
MaillonIndex *r;
while(ver!=1) // controle d'erreur
{
printf("entrer l'etablissement universitaire : \n");
scanf(" %[^\t\n]s",&etablissement_univ);
ver=ver_etablissement(etablissement_univ);
}

printf("entrer l'ancienter min:");
scanf("%d",&ancienteemin);
printf("entrer l'ancienter max:");
scanf("%d",&ancienteemax);
// recherch de l'etablissement entree
    r=te;
    while (r!=NULL && !stop)
        {
        if(!(strcasecmp(r->string,etablissement_univ)))
            {
            e=r->tete;
            stop=1;
            }
        r=suivantIndex(r);
        }

    if (stop && e!=NULL) // si on a trouver l'etablissement on parcour les ancientee et on affiche celle qui sont demender
        {
        r=ta;
        while (r!=NULL )
        {
            if ((r->ancienter<=ancienteemax) && (r->ancienter>=ancienteemin))
            {
                p=r->tete;
                while (p!=NULL)
                {
                    rechval(p->matricule,e,&res,&pre,&trouv);
                    if (trouv)
                    {
                        j=p->deplacement;
                        if (i!=p->num_bloc)
                        {
                            i=p->num_bloc;
                            lireDir(f,i,&buf);
                        }
                        lireDir(f,i,&buf);
                        printf("wilaya_naissance : %s\n",buf.T[j].wilaya_naissance);
                        printf("date_Naissance : %s\n",buf.T[j].date_Naissance);
                        printf("date_recrutement : %s\n",buf.T[j].date_recrutement);
                        printf("dernier_diplome : %s\n",buf.T[j].dernier_diplome);
                        printf("etablissement_univ : %s\n",buf.T[j].etablissement_univ);
                        printf("groupe_sanguin : %s\n",buf.T[j].groupe_sanguin);
                        printf("nom_prenom : %s\n",buf.T[j].nom);
                        printf("grade : %s\n",buf.T[j].grade);
                        printf("sexe : %s\n",buf.T[j].sexe);
                        printf("specialite : %s \n",buf.T[j].specialite);
                        printf("matricule= %i  \n",buf.T[j].matricule);
                        printf("****************************************\n");
                    }
                    trouv=0;
                    p=suivant(p);
                }
            }
            r=r->next;
        }
    }
    else
    {
        printf("la liste est vide (peut etre que l'etablissemnt n'exist pas) \n");
    }
}

void ajout(int matricule)
{
Tbloc buf;
int trouv=0,i=0,j,stop=0,mn=0,jr,an,mn1,ver,verr=0;
Maillon *res,*pre,*n,*p;
char mnc[4],anc[20],jrc[2],date,mncr[4],ancr[20],jrcr[2];
MaillonIndex *r,*e;
rechvalORD(matricule,t,&res,&pre,&trouv);
if (!trouv) //si le matricule n'exist pas
{
ouvrir(&f,"ENSEIGNANT-MESRS.bin",'a');
/**************************lecture des donnee*************************/
char nom[20],term;
printf("entrer le nom et le prenom de l'enseignant :\n");
ver=0;
while(ver!=1)
{
scanf(" %[^\t\n]s",&nom); // %[^\t\n]s est pour lire une chaine de plusieur mots
ver=ver_nom(nom);
}
ver=0;
char date_Naissance[10];//par ex : "0000/00/00"
while(ver!=1)// verification si la date entree est correct
{
printf("entrer la date de naissance de l'enseignant :\n");
printf("annee:");
                verr=0;
                while(verr!=1)
                {
                if(scanf("%d%c", &an, &term) != 2 || term != '\n')
                {
                   printf("veuillez entrer un entier SVP \n");
                                      an=0;
                   fflush(stdin);
                }
                else {verr=1;}}

printf("mois:");
                verr=0;
                while(verr!=1)
                {
                if(scanf("%d%c", &mn, &term) != 2 || term != '\n')
                {
                   printf("veuillez entrer un entier SVP \n");
                                      mn=0;
                   fflush(stdin);
                }
                else {verr=1;}}
printf("jour:");
                verr=0;
                while(verr!=1)
                {
                if(scanf("%d%c", &jr, &term) != 2 || term != '\n')
                {
                   printf("veuillez entrer un entier SVP \n");
                                      jr=0;
                   fflush(stdin);
                }
                else {verr=1;}}
ver=ver_date_naissance(an,mn,jr);
}
int ancc=an;
ver=0;
// conversion de entier ver chaine
    itoa(an,anc,10);

     strcat(anc,"/") ;
     itoa(mn,mnc,10) ;
     strcat(anc,mnc) ;

     strcat(anc,"/");

     itoa(jr,jrc,10) ;
     strcat(anc,jrc);
strcpy(date_Naissance,anc);
char wilaya_naissance[15];
while(ver!=1)
{
printf("entrer la wilaya de naissance de l'enseignant :(ex : alger , annaba ...)\n");
scanf(" %[^\t\n]s",wilaya_naissance);
ver=ver_wilaya(wilaya_naissance);
}
ver=0;
char sexe[10];
printf("entrer le sexe de l'enseignant : ( masculin ou feminin ) \n");
while(ver!=1)
{
scanf("%s",&sexe);
ver=ver_sexe(sexe);
}
ver=0;
char groupe_sanguin[10];
printf("entrer le groupe sanguin de l'enseignant :(a+,b+,a-,...) \n");
while(ver!=1)
{
scanf("%s",&groupe_sanguin);
ver=ver_groupe_sanguin(groupe_sanguin);
}
ver=0;
char *date_recrutement;//par ex :"0000/00/00"
printf("entrer la date de recrutement de l'enseignant :\n");
while(ver!=1) /********************* controle d'erreur*************************/
{
printf("annee:");
                verr=0;
                while(verr!=1)
                {
                if(scanf("%d%c", &an, &term) != 2 || term != '\n')
                {
                   printf("veuillez entrer un entier SVP \n");
                                      an=0;
                   fflush(stdin);
                }
                else {verr=1;}}

printf("mois:");
                verr=0;
                while(verr!=1)
                {
                if(scanf("%d%c", &mn, &term) != 2 || term != '\n')
                {
                   printf("veuillez entrer un entier SVP \n");
                                      mn=0;
                   fflush(stdin);
                }
                else {verr=1;}}
printf("jour:");
                verr=0;
                while(verr!=1)
                {
                if(scanf("%d%c", &jr, &term) != 2 || term != '\n')
                {
                   printf("veuillez entrer un entier SVP \n");
                                      jr=0;
                   fflush(stdin);
                }
                else {verr=1;}}
ver=ver_date_recrutement(ancc,an,mn,jr);
}
ver=0;

     itoa(an,ancr,10);
     strcat(ancr,"/") ;
     itoa(mn,mncr,10) ;
     strcat(ancr,mncr) ;

     strcat(ancr,"/");

     itoa(jr,jrcr,10) ;
     strcat(ancr,jrcr);
date_recrutement=ancr;
int ancientee=ancienter(date_recrutement);



char specialite[20];
printf("entrer la specialite de l'enseignant : (ex : veterinaire , medecine ...)\n");
while(ver!=1)
{
scanf(" %[^\t\n]s",&specialite);
ver=ver_specialite(specialite);
}
ver=0;

char dernier_diplome[20];

printf("entrer le dernier diplom de l'enseignant :(ex : Doctorat d'Etat , PhD ...)\n");
while(ver!=1)
{
scanf(" %[^\t\n]s",&dernier_diplome);
ver=ver_dernier_diplome(dernier_diplome);
}
ver=0;
char etablissement_univ[100];
printf("entrer l'etablissement universitaire de l'enseignant : \n");
while(ver!=1)
{
scanf(" %[^\t\n]s",&etablissement_univ);
ver=ver_etablissement(etablissement_univ);
ver=1;
}
ver=0;
char grade[50];
printf("entrer le grade de l'enseignant : (ex : professeur(e),maitre de conferences rang a ...) \n");
while(ver!=1)
{
scanf(" %[^\t\n]s",&grade);
ver=ver_grade(grade);
}
ver=0;
/* ajout sur le dernier bloc de fichier */
lireDir(f,entete(f,1),&buf);
if (buf.Nb<1000)
{
    i=entete(f,1);
}
else
{
    i=alloc_bloc(f);
    buf.Nb=0;
}
j=buf.Nb;
strcpy(buf.T[buf.Nb].etablissement_univ,etablissement_univ);
strcpy(buf.T[buf.Nb].wilaya_naissance,wilaya_naissance);
strcpy(buf.T[buf.Nb].date_Naissance,date_Naissance);
strcpy(buf.T[buf.Nb].date_recrutement,date_recrutement);
buf.T[buf.Nb].dernier_diplome=dernier_diplome;
buf.T[buf.Nb].groupe_sanguin=groupe_sanguin;
strcpy(buf.T[buf.Nb].nom,nom);
buf.T[buf.Nb].grade=grade;
buf.T[buf.Nb].sexe=sexe;
strcpy(buf.T[buf.Nb].specialite,specialite);
buf.T[buf.Nb].matricule=matricule;

buf.Nb++;
ecrireDir(f,i,&buf);
/* ajout d'un nouveau maillon sur la list d'index primaire*/
allouer(&n);
n->matricule=matricule;
n->deplacement=j;
n->num_bloc=i;

            time_t taa = time(NULL);
            struct tm tm =*localtime(&taa);
            (f->entete).date_modification[0]=tm.tm_mday ;
            (f->entete).date_modification[1]=tm.tm_mon+1 ;
            (f->entete).date_modification[2]=tm.tm_year+1900 ;
            (f->entete).date_modification[3]=tm.tm_hour ;
            (f->entete).date_modification[4]=tm.tm_min ;
            (f->entete).date_modification[5]=tm.tm_sec ;
            (f->entete).nb ++;
            strcpy((f->entete).specia,max_specialite());
            strcpy((f->entete).etab,max_etab());
                     long size;
            fseek(f->fichier,0,SEEK_END); /**** taille du fichier****/
              size=ftell(f->fichier) ;
              f->entete.taille=(size/1024)+1;

if (t==NULL)
{
t=n;
}
else
{
    if (pre==NULL)
    {
        n->next=t;
        t=n;
    }
    else
    {
        pre->next=n;
        n->next=res;
    }
}
stop=0;
//           l'ajout sur la list d'index des specialite
r=ts;
while (r!=NULL && !stop)
{
    if(!(strcasecmp(r->string,specialite)))
    {
        ins(matricule,&(r->tete),j,i);
        stop=1;
    }
    e=r;
    r=suivantIndex(r);
}
if (!stop)
{
    /*dans le cas d'un nouveau specialite ou dans le cas ou la list d'index est vide */
    allouerIndex(&r);
    strcpy(r->string,specialite);
    r->next=NULL;
    allouer(&p);
    p->matricule=matricule;
    p->deplacement=j;
    p->num_bloc=i;
    p->next=NULL;
    r->tete=p;
   if (ts==NULL)
   {
       ts=r;
   }
   else
   {
    e->next=r;
   }
}
//           l'ajout sur la list d'index des etablissement
stop=0;
r=te;
while (r!=NULL && !stop)
{
    if(!(strcasecmp(r->string,etablissement_univ)))
    {
        ins(matricule,&(r->tete),j,i);
        stop=1;
    }
    e=r;
    r=suivantIndex(r);
}
if (!stop)
{
    /*dans le cas d'un nouveau etablissement ou dans le cas ou la list d'index est vide */
    allouerIndex(&r);
    strcpy(r->string,etablissement_univ);
    r->next=NULL;
    allouer(&p);
    p->matricule=matricule;
    p->deplacement=j;
    p->num_bloc=i;
    p->next=NULL;
    r->tete=p;
   if (te==NULL)
   {
       te=r;
   }
   else
   {
    e->next=r;
   }
}
//           l'ajout sur la list d'index des ancientee
stop=0;
r=ta;
while (r!=NULL && !stop)
{
    if(r->ancienter==ancientee)
    {
        ins(matricule,&(r->tete),j,i);
        stop=1;
    }
    e=r;
    r=suivantIndex(r);
}
if (!stop)
{
    /*dans le cas d'un nouveau ancientee ou dans le cas ou la list d'index est vide */
    allouerIndex(&r);
    r->ancienter=ancientee;
    r->next=NULL;
    allouer(&p);
    p->matricule=matricule;
    p->deplacement=j;
    p->num_bloc=i;
    p->next=NULL;
    r->tete=p;
   if (ta==NULL)
   {
       ta=r;
   }
   else
   {
    e->next=r;
   }
}
}
else
{
    printf("cette matricule exist deja dans le fichier \n");
}

fermer(f);
}

char *region_eta(char *eta)
{
    int j=1,stop=0;
    while(j<=108 && stop!=1)
    {
        if(strcmp(eta,etabl[j].etab)==0) {stop=1;}

        else {j++;}
    }
    if (j<=42) return "centre" ;
    else {
        if(j>77) return "ouest" ;
        else return "est" ;
    }

}

void afficher_region()
{
    ouvrir(&f,"ENSEIGNANT-MESRS.bin",'a');
    MaillonIndex *q,*p;
    Maillon *a;
    int k;
    char reg[7];
    q=te;
    printf("quelle region voulez-vous afficher : ");
    scanf("%s",&reg);
   if(strcasecmp(reg,"centre")==0 || strcasecmp(reg,"est") || strcasecmp(reg,"ouest") )
   {
    while(q!=NULL)
    {
          a=suivantIndex_haut(q);
         if(a!=NULL){
          if(strcasecmp(region_eta(valeurIndex(q)),reg)==0)
          {
          k=nbloc(a);
          lireDir(f,nbloc(a),&buf);

          while(a!=NULL)
          {
              if (nbloc(a)!=k) {lireDir(f,nbloc(a),&buf);
              k=nbloc(a);
              }

                i=dep(a);
                printf("wilaya_naissance : %s\n",buf.T[i].wilaya_naissance);
                printf("dernier_diplome : %s\n",buf.T[i].dernier_diplome);
                printf("date_Naissance : %s\n",buf.T[i].date_Naissance);
                printf("etablissement_univ : %s\n",buf.T[i].etablissement_univ);
                printf("groupe_sanguin : %s\n",buf.T[i].groupe_sanguin);
                printf("nom_prenom : %s\n",buf.T[i].nom);
                printf("grade : %s\n",buf.T[i].grade);
                printf("sexe : %s\n",buf.T[i].sexe);
                printf("date_recrutement : %s\n",buf.T[i].date_recrutement);
                printf("specialite : %s \n",buf.T[i].specialite);
                printf("matricule= %i  \n",buf.T[i].matricule);
                printf("****************************************\n");
                a=suivant(a);
          }
          }}
          q=suivantIndex(q);
    }
   }
   else {printf("veuillez entrer la region correctement < est , ouest , centre > ! \n");}

fermer(f);
}

void afficher_entete()
{
    ouvrir(&f,"ENSEIGNANT-MESRS.bin",'a');
    printf("nom : %s\n",f->entete.nom);
    printf("nombre d'esneignants enregistres dans le fichier : %i\n",f->entete.nb);
    printf("la specialite la plus choisie est : %s\n",f->entete.specia);
    printf("l'etablissement le plus frequent est : %s\n",f->entete.etab);
    printf("numero des blocs du  fichier est : %d\n",entete(f,1));
    printf("Cree le : %i/%i/%i %i:%i:%i \n",f->entete.date_creation[0],f->entete.date_creation[1],f->entete.date_creation[2],f->entete.date_creation[3],f->entete.date_creation[4],f->entete.date_creation[5]);
    printf("modifiee le : %i/%i/%i %i:%i:%i \n",f->entete.date_modification[0],f->entete.date_modification[1],f->entete.date_modification[2],f->entete.date_modification[3],f->entete.date_modification[4],f->entete.date_modification[5]);
    printf("taille : %i Ko\n",f->entete.taille);
    printf("type : %s\n",f->entete.type);
    fermer(f);
}
void afficher_fichier_index(char filename[])
{
  int i,j,k;
   ouvrir(&f,filename,'a');

   for(j=1;j<=entete(f,1);j++)
   {
   lireDirIndex2(f,j,&bufff) ;
   printf("%d\n",bufff.Nb);
   for(i=0;i<bufff.Nb;i++)
   {
       printf("%s\n",bufff.T[i].string);
       printf("                               %d\n",bufff.T[i].matricule);
       printf("                                                         %d\n",bufff.T[i].num_bloc);
       printf("                                                                                 %d\n",bufff.T[i].deplacement);
   }

   }
   fermer(f);
}
void afficher_fichier_indexP()
{
  int i,j,k;
   ouvrir(&f,"index.bin",'a');
   for(j=1;j<=entete(f,1);j++)
   {
   lireDirIndex(f,j,&buff) ;
   for(i=0;i<buff.Nb;i++)
   {
       printf("                               %d\n",buff.T[i].matricule);
       printf("                                                         %d\n",buff.T[i].num_bloc);
       printf("                                                                                 %d\n",buff.T[i].deplacement);
   }

   }
   fermer(f);
}
void afficher_fichier_indexA()
{
  int i,j,k;
   ouvrir(&f,"indexa.bin",'a');
   for(j=1;j<=entete(f,1);j++)
   {
   lireDirIndex2(f,j,&bufff) ;
   for(i=0;i<bufff.Nb;i++)
   {
       printf("%d\n",bufff.T[i].ancienter);
       printf("                               %d\n",bufff.T[i].matricule);
       printf("                                                         %d\n",bufff.T[i].num_bloc);
       printf("                                                                                 %d\n",bufff.T[i].deplacement);
   }

   }
   fermer(f);
}
void afficher_fichier_premier_element()
{
  int i,j,k;
   ouvrir(&f,"ENSEIGNANT-MESRS.bin",'a');
   for(j=1;j<=1;j++)
   {
   lireDir(f,j,&buf) ;
   for(i=0;i<1;i++)
   {
printf("wilaya_naissance : %s\n",buf.T[i].wilaya_naissance);
printf("date_Naissance : %s\n",buf.T[i].date_Naissance);
printf("date_recrutement : %s\n",buf.T[i].date_recrutement);
printf("dernier_diplome : %s\n",buf.T[i].dernier_diplome);
printf("etablissement_univ : %s\n",buf.T[i].etablissement_univ);
printf("groupe_sanguin : %s\n",buf.T[i].groupe_sanguin);
printf("nom_prenom : %s\n",buf.T[i].nom);
printf("grade : %s\n",buf.T[i].grade);
printf("sexe : %s\n",buf.T[i].sexe);
printf("specialite : %s \n",buf.T[i].specialite);
printf("matricule= %i  \n",buf.T[i].matricule);
printf("****************************************\n");
   }

   }
   fermer(f);
}
void programme()
{
FILE *h;
int j,ver=0;
    char wilaya[20],eta[100];
h=fopen("wilaya.txt","r");
for(j=1;j<=48;j++)
{
    fgets(wilaya,20,h);
    wilaya[strlen(wilaya)-1]='\0';
    strcpy(wi[j].wila,wilaya) ;
}
fclose(h);


h=fopen("Etablissement.txt","r");

    for(j=1;j<=108;j++)
   {
    fgets(eta,100,h) ;
    eta[strlen(eta)-1]='\0';
    strcpy(etabl[j].etab,eta) ;


   }
    fclose(h);

    char specia[30] ;
    h=fopen("specialite.txt","r");
    int k;
    for(k=1;k<=39;k++)
    {
    fgets(specia,30,h) ;
    specia[strlen(specia)-1]='\0';
    strcpy(spe[k].specialite,specia);
    }

    fclose(h);
    int stop=0,matricule,stop1=0;
    char rep[10];
    /*
    //                        FULL SCREEN
    COORD c;
    SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE),CONSOLE_FULLSCREEN_MODE,&c);
    getchar();
    //                        FULL SCREEN
    */
    while (!stop)
    {
printf("                chargement initial tapez 1\n");
printf("                travailler sur un fichier deja charge tapez 2 \n");
scanf("%s",&rep);
printf("                N'OUBLIEZ PAS DE SAUVEGARDER VOS CHANGEMENT A LA FIN  \n");

if (atoi(rep)==1)
{
    chargement_initial();
    stop=1;
}
if (atoi(rep)==2)
{
    chargementIndex(&t);
    chargementIndex2("indexe.bin",&te);
    chargementIndex2("indexs.bin",&ts);
    chargementIndexA("indexa.bin",&ta);
    stop=1;

}
    }
   while (strcmp(rep,"10"))
    {
            printf("................................... MENU .......................................\n ") ;
    printf("         1/ afficher le fichier  \n") ;
    printf("          2/ ajouter un enseignant \n") ;
    printf("          3/ modifier l'etablissement d'un enseignant \n") ;
    printf("          4/ supprimer un enseignant \n") ;
    printf("          5/ supprimer une specialite \n") ;
    printf("          6/ Afficher des enseignants dans un etablissement donne ayant une anciennete entre deux valeurs donnees  \n") ;
    printf("          7/ afficher par region  \n") ;
    printf("          8/ afficher l'entete \n") ;
    printf("          9/ sauvegarder les changement \n") ;
    printf("          10/ exit \n") ;
    scanf("%s",&rep);
    switch (atoi(rep))
    {
        case 1:
            {
                afficher_fichier();
                break;
            }
        case 2:
            {

                printf("entrer le matricule a inserer : \n");
                char term;

                if(scanf("%d%c", &matricule, &term) != 2 || term != '\n')
                {
                   printf("veuillez entrer un entier SVP \n");
                   matricule=0;
                   fflush(stdin);

                }
                else
                {
                    if(matricule<=0) printf("veuillez entrer votre matricule correctement ! \n");
                else{ajout(matricule);
                printf("\n FIN! \n");}
                }

                break;
            }
        case 3:
            {
                printf("entrer le matricule a modifer \n");
                char term;
                if(scanf("%d%c", &matricule, &term) != 2 || term != '\n')
                {printf("veuillez entrer un entier SVP \n");
                                   matricule=0;
                   fflush(stdin);}
                else
                {
                           if(matricule<=0) printf("veuillez entrer votre matricule correctement ! \n");
               else{ modification_etab(matricule);
                printf("\n FIN! \n"); }
                }
                break;
            }
        case 4:
            {
                printf("entrer le matricule a supprimer \n");
                char term;
                if(scanf("%d%c", &matricule, &term) != 2 || term != '\n')
                {printf("veuillez entrer un entier SVP \n");
                                   matricule=0;
                   fflush(stdin);}
                else
                {
                           if(matricule<=0) printf("veuillez entrer votre matricule correctement ! \n");
                else{supprimer_enregistrement(matricule);
                printf("\n FIN! \n");}
                }
                break;
            }
        case 5:
            {
                supprimer_specialite();
                break;
            }
        case 6:
            {
                requetteAintervale();
                break;
            }
        case 8:
            {
                afficher_entete();
                break;
            }
        case 7:
            {
                afficher_region();
                break;
            }
        case 9:
            {
                saveIndex(t);
                saveIndex2("indexs.bin",ts);
                saveIndex2("indexe.bin",te);
                saveIndexA("indexa.bin",ta);
                printf("all has been saved \n");
                break;
            }
        case 10:
            {
                saveIndex(t);
                saveIndex2("indexs.bin",ts);
                saveIndex2("indexe.bin",te);
                saveIndexA("indexa.bin",ta);
                break;
            }
    }
}
}
int main()
{
    programme();
}



