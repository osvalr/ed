    
void hallar_circuito_cualquiera(v,Ady){
     int 
     }
     
void es_euleriano(Circuito, int Ady){
     }
     
void eliminar_circuito(Circuito, int Ady, int Ady_sinCirc){
     }
     
void ComponenteConexas(int Ady_sinCirc,int n,int p,int C){
     }
     
void hallar_vertice_Circuito_CompConexa(int Circuito, int C, int p, int VertC){
     }
     
void almacenar_circuito(int Circuito, int j, int vertC[i], int C[i], int Ady_sinCirc,int CirEule){
     }
     
void construirAdy_d_CompConex(int Ady, int n, int C[i], int Ady_CompConex){
     }

void cardinalidad(int C[i]){
     }
     
void CircuitoEuleriano(int Ady_CompConex, int n_CompConex, int C[i], int CirEule, int j){
     }
 
void vertices_son_grado_par(Grados,n){
     }
     
void Componentes conexa(Ady,n,p,C){
     }
     
    
int CircuitoEuleriano(Ady:Mady, int n, CompConex:conjunto, char CircEule: arreglo[N] de vertice, int j){
Ady:matrizAdy
int n;
CompConex: conjunto;
int CircEule [N] de vertice;
int j;

//INICIO
int i;
int n_CompConex;
int C [N] de vertice;
Ady_sinCirc, Ady_CompConex: matrizAdy;
int vertC [N] de vertice;
v vertice;

v=vertice_mayor_grado(Ady);
Circuito=hallar_circuito_cualquiera(v,Ady);

if(es_euleriano(Circuito,Ady)){
    CircEule=Circuito;
    }else{
                eliminar_circuito(Circuito,Ady,Ady_sinCirc);
                ComponenteConexas(Ady_sinCirc,n,p,C);
                hallar_vertice_Circuito_CompConexa(Circuito,C,p,VertC);
                    for(i=0;i<p;i++){
                        if(cardinalidad(C[i])==1 o cardinalidad(C[i])==3){
                            almacenar_circuito(Circuito,j,vertC[i],C[i],Ady_sinCirc,CirEule);
                            }else{
                                construirAdy_d_CompConex(Ady,n,C[i],Ady_CompConex);
                                n_CompConex=cardinalidad(C[i]);
                                CircuitoEuleriano(Ady_CompConex, n_CompConex, C[i], CirEule, j);
                            }
                        }
        }
}

int matrizAdy [N][N];
int vertice;

ady: matrizAdy;
int grados [N];
int C [N];
int circeule [N];
int n,p,j;

//INICIO
//Lecturas Iniciales, n ady (lee el numero de verticesdel grafo: n y lee los arcos)
//calcular_grados_vertices (Ady,n,Grados) determina los grados del vertice y los almacena en grados
if(vertices son grado par(Grados,n)){
    Componentes conexa(Ady,n,p,C)// Determina las componentes conexas
   if(p==1){
       j=0;
       CircuitoEuleriano(Ady,n,C,CircEule,j);
       printf("El Circuito Euleriano es: ",CircEule,j);
       }else{
            printf("El Grafo no es conexo y posee estas componentes conexas",C,n);
       }
    printf("Hay vertices de grado impar, y son los siguientes: ",Grados,n);
    }

}
