#include<stdio.h>
#include<string.h>
#define N 100
typedef struct{
        int n_vert;
        int Mady[N][N];
}Grafo;

typedef struct{
        char cod_vert[3];
        char nombre_vert[50];
}datos_vertices;


datos_vertices Estaciones[100];

typedef struct{
        char v[3], w[3];
}arcos;

//variables globales

	Grafo red_Trenes;
	arcos arco[N];

void union_comp_conexa(int ii,int jj,int c[][N], int n)
{
	int i,j,k;
	
	for(i=0;i<n;i++)
	{
		if(c[i][ii]==0)
		{
			k=i;
			break;
		}
	}
	
	for(j=0;j<n;j++)
	{
		c[k][ii]=c[j][jj];
		c[j][jj]=0;
		k+=1;
	}
}

void Componentes_Conexas(int c[][N], int *p, Grafo g)
{
    int i,j,existen_arcos,x,y;
    int a[N][N];
    
    for(i=0;i<g.n_vert;i++)
    {
    	for(j=0;j<g.n_vert;j++)
    	{
    		if(g.Mady[i][j]==1)
    		{
    			a[i][j]=1;
			}
    		else
    		{
    			a[i][j]=0;
			}
		}
	}
	
    for(i=0;i<g.n_vert;i++)
    { 
    	c[0][i]=i+1;
	}
	
	*p=g.n_vert;
	
	printf("Cantidad de Componentes Conexas: %d\n",*p);

	x=0;
	y=0;
	
	existen_arcos=1;
	
	while(existen_arcos==1)
	{
		existen_arcos=0;
	    existen_arcos=leer_arco(g,a,&x,&y);
		if(existen_arcos)
		{
			i=Buscar_CompConexa_del_vertice(x+1,c,g.n_vert);
			j=Buscar_CompConexa_del_vertice(y+1,c,g.n_vert);
			
			if(i!=j)
			{
				union_comp_conexa(i,j,c,(int)g.n_vert);
				*p= *p-1;
			}
		}
		else
			break;
    }

	int o,u;
	for(o=0; o<g.n_vert; o++)
	{
		for(u=0; u<g.n_vert; u++)
			printf("%d ",c[o][u]);
		printf("\n");
	}
}
void reiniciar_matriz(int g[][N], int 	n)
{
	int i,j;
	
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			g[i][j]= 0;

}
	
int leer_arco(Grafo g, int a[][N], int *ii, int *jj)
{
	int i,j;
	for(i=*ii;i<g.n_vert;i++){
		for(j=0;j<g.n_vert;j++){
			if(a[i][j]==1){
				*ii=i;
				*jj=j;
				a[i][j]=2;
				return 1;
			}
		}
	}
	return 0;
}
int Buscar_CompConexa_del_vertice(int verts,int c[][N], int n)
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(c[j][i]==verts)
			{
				return i;
			}
		}
	}
}


int main(){
	FILE *tren;
	char v[3], w[3];
	int n_arcos,i,k, pos_v, pos_w,num,encontrado,encontradoV,encontradoW;
					int c[N][N];
				int p;
	tren=fopen("viastren.in", "r");
	if(tren==NULL)
	{
		printf("El Archivo No Existe\n");
	}
    else
    {
    	// Cargar nombre de vertices
    	
    	fscanf(tren,"%d",&num);
    	printf("%d\n",num);
    	
    	while(num!=0)
    	{
			if(num!=0)
			{
				red_Trenes.n_vert=num;
				for (i=0;i<red_Trenes.n_vert;i++)
				{
					fscanf(tren,"%s %[^\n]",Estaciones[i].cod_vert, Estaciones[i].nombre_vert);
					printf("%s %s\n",Estaciones[i].cod_vert, Estaciones[i].nombre_vert);
				}
				
				// Cargar el grafo
				fscanf(tren,"%d",&n_arcos);
				printf("%d\n",n_arcos);
				
				for (i=0;i<n_arcos;i++)
				{
					fscanf(tren,"%s %s",v,w);
					
					printf("%s %s\n",v,w);
					
								
					encontradoV= 0;
					encontradoW= 0;
					
					k=0;
					while(!encontradoV || !encontradoW)
					{
						if(strcmp(Estaciones[k].cod_vert,v)==0)
						{
							pos_v=k;
							encontradoV=1;
						}
						if(strcmp(Estaciones[k].cod_vert,w)==0)
						{
							pos_w=k;
							encontradoW=1;
						}
						k++;
					}
					if(encontradoW && encontradoV)
					{
						red_Trenes.Mady[pos_v][pos_w]=1;
						red_Trenes.Mady[pos_w][pos_v]=1;
					}
				}
				

				
				Componentes_Conexas(c,&p,red_Trenes);
				///CICLOS PARA MOSTRAR LA MATRIZ DE ADYACENCIA DE UN GRAFO;	
					printf("Cantidad de Componentes Conexas: %d\n",p);

				//~ int o,u;
				//~ for(o=0; o<red_Trenes.n_vert; o++)
				//~ {
					//~ for(u=0; u<red_Trenes.n_vert; u++)
						//~ printf("%d ",red_Trenes.Mady[o][u]);
					//~ printf("\n");
				//~ }
				///Hasta aqui ya has impreso y procesado la informacion de un solo grafo, es decir que antes de este mensaje debes de hallar el(los) caminos eulerianos
				/// y generar las lineas del grafo procesado.
					
			}
			///aqui deberia de ir un procedimiento que te reinicie el grafo [ es decir, la matrices y los valores que se necesitan para procesarlo ]
			reiniciar_matriz(red_Trenes.Mady, red_Trenes.n_vert);
			reiniciar_matriz(c, red_Trenes.n_vert);
			red_Trenes.n_vert= 0;
			fscanf(tren,"%d",&num);
		}
	}
		fclose(tren);
	return 0;
}
