///            FACULTAD DE CIENCIAS Y TECNOLOGIA
///                DEPARTAMENTO DE COMPUTACION
///                    ELEMENTOS DISCRETOS

///            PROYECTO COMPUTACIONAL "GAZPROM"

///            PROF. JOHANA GUERRERO
///                DESARROLLADORES:
///                            - OSVAL REYES
///                            - MANUEL PINTO
///                            - SAMANTHA BORJAS
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include<curses.h>
#define MOL 35
#define GI 0.08205
#define MAX 100
typedef struct{
    char tipo[3];
    int ind;
    char nombre[25];
}vert;
typedef struct{
	float ATM;       ///[-3,3]
	float vol;       ///[15 DM3 , 50 DM3]
	int temp;        ///[-15 °K, 45°K]
	int trans;       ///1-ES TRANSOCEÁNICA, 0-CASO CONTRARIO
	float costo;     ///VALOR REAL QUE REPRESENTA EL COSTO DE LA TUBERIA
	int est;         ///ESTABILIDAD:1-ESTABLE, 0-CASO CONTRARIO
	int exarc;       ///EXISTE ARCOS:1-EXISTE, 0-CASO CONTRARIO
}arcos;
typedef struct{
    arcos Ady[MAX][MAX];        /// Matriz de Registros
}TAdy;
typedef struct{
    vert VC[MAX][2];      /// Matriz de Vertices de Consulta
}VVC;
TAdy VAdy[20];               /// Vector de Matriz de Registro, es decir, Vector de Diseños de Sistemas de Gasoductos de GAZPROM
vert PDist[20][MAX];    /// Vector de Vectores de Vertices
int CV[20];                 /// Vector de Cantidad de Vertices por Planta Mundiales
int CPM;                     /// Cantidad de Plantas a Nivel Mundial
VVC VeCo[MAX];               /// Ve-ctor de Co-nsultas, su campo es una matriz de registro, 
                             ///     ya que las consultas son con respecto a pares de Vertices

/// MM [PROCEDIMIENTO <NINGUN PARÁMETRO> ]: RECUADRO Ó MARCO DEL PROGRAMA
mm(){
 int i;
	erase();
	mvaddstr(3,5,"Sistema de Administracion :: GAZPROM CORPORATION");
	mvaddstr(37,5,"Opciones: | [A]  Acerca de... |  [S]  Salir   |");
	mvaddstr(37,90,"Estado:");
	mvaddstr(3,113,"_");
	mvaddstr(3,115,"[]");
	mvaddch(3,118,'X');
	for(i=2;i<121;i++){
		mvaddch(2,i,ACS_HLINE);
		mvaddch(38,i,ACS_HLINE);
		if(i<38){
		   mvaddch(i,2,ACS_VLINE);
		   mvaddch(i,120,ACS_VLINE);
		}
		mvaddch(2,2,ACS_ULCORNER);
		mvaddch(2,120,ACS_URCORNER);
		mvaddch(38,2,ACS_LLCORNER);
		mvaddch(38,120,ACS_LRCORNER);
	}
	for(i=3;i<120;i++){
		mvaddch(4,i,ACS_HLINE);
		mvaddch(4,2,ACS_LTEE);
		mvaddch(4,120,ACS_RTEE);
		mvaddch(36,i,ACS_HLINE);
		mvaddch(36,2,ACS_LTEE);
		mvaddch(36,120,ACS_RTEE);
	}
	refresh();
}

/// ERROR [PROCEDIMIENTO]: CONTIENE TODAS LAS NOTIFICACIONES DEL SISTEMA QUE NECESITEN RECUADROS
ERROR(int k){
	int i,j,l;
	char ani[4]={'|','/','-','\\'};
	noecho();
	switch(k){
    	case 1:{
    	    for(i=41;i<80;i++){
    	    	mvaddch(16,i,ACS_HLINE);
    	    	mvaddch(20,i,ACS_HLINE);
    	    	if(i<44){
    	    		mvaddch(i-24,40,ACS_VLINE);
    	    		mvaddch(i-24,80,ACS_VLINE);
    	    		mvaddch(16,40,ACS_ULCORNER);
    	    		mvaddch(16,80,ACS_URCORNER);
    	    		mvaddch(20,40,ACS_LLCORNER);
    	    		mvaddch(20,80,ACS_LRCORNER);
    	    		mvaddstr(18,41,"            OPCION INCORRECTA          ");
					curs_set(0);
    	    	}
    	    }
            refresh();
            sleep(1);
        }break;
    	case 2:{
    	    for(i=17;i<23;i++){
    	        for(j=16;j<100;j++){
    	        	mvaddstr(i,j," ");
			    }
			}
    	    for(i=41;i<101;i++){
				mvaddstr(15,52,"GAZPROM CORPORATION");
				mvaddstr(19,36,"No se encontro el archivo de entrada \"gasoduc.in\"");
				mvaddstr(20,48,"Revise e Intente de Nuevo");
				refresh();
    	    	mvaddch(14,i-11,ACS_HLINE);
    	    	mvaddch(16,i-11,ACS_HLINE);
    	    	mvaddch(23,i-11,ACS_HLINE);
    	    	if(i<50){
    	    		mvaddch(i-27,30,ACS_VLINE);
    	    		mvaddch(i-27,90,ACS_VLINE);
    	    		mvaddch(14,30,ACS_ULCORNER);
    	    		mvaddch(14,90,ACS_URCORNER);
    	    		mvaddch(23,30,ACS_LLCORNER);
    	    		mvaddch(23,90,ACS_LRCORNER);
    	    	}
    	    }
    	    mvaddch(16,30,ACS_LTEE);
    	    mvaddch(16,90,ACS_RTEE);
        	curs_set(0);
            refresh();
            sleep(2);
        }break;
		case 3:{
            do{
                for(i=41;i<72;i++){
            		mvaddstr(30,42,"PRESIONE ESCAPE PARA REGRESAR");
               		refresh();
            		mvaddch(29,i,ACS_HLINE);
            		mvaddch(31,i,ACS_HLINE);
                }
                for(i=30;i<31;i++){
        			mvaddch(i,41,ACS_VLINE);
        			mvaddch(i,71,ACS_VLINE);
        			mvaddch(29,41,ACS_ULCORNER);
        			mvaddch(29,71,ACS_URCORNER);
                    mvaddch(31,41,ACS_LLCORNER);
                    mvaddch(31,71,ACS_LRCORNER);
                }
                curs_set(0);
                refresh();
            }while(getch()!='\x1B');
        }break;
        case 4:{
        	mm();
	        for(i=34;i<81;i++){
	        		mvaddch(13,i,ACS_HLINE);
	        		mvaddch(15,i,ACS_HLINE);
	        		mvaddch(19,i,ACS_HLINE);
	        }
	        mvaddstr(14,47,"GAZPROM CORPORATION");
	        mvaddstr(17,35,"La Base de Datos Solo Se Puede Cargar Una vez");
	        refresh();
	        for(i=14;i<19;i++){
	        			mvaddch(i,33,ACS_VLINE);
	        			mvaddch(i,81,ACS_VLINE);
	        			mvaddch(13,33,ACS_ULCORNER);
	        			mvaddch(13,81,ACS_URCORNER);
	        			mvaddch(19,33,ACS_LLCORNER);
	        			mvaddch(19,81,ACS_LRCORNER);
	        			mvaddch(15,33,ACS_LTEE);
	        			mvaddch(15,81,ACS_RTEE);
	        }
	        curs_set(0);
	        refresh();
	        sleep(2);
	    }break;
	    case 5:{
	    	mm();
	    	for(i=34;i<81;i++){
		    	mvaddch(13,i,ACS_HLINE);
		    	mvaddch(15,i,ACS_HLINE);
				mvaddch(19,i,ACS_HLINE);
	        }
	        mvaddstr(14,47,"GAZPROM CORPORATION");
	        mvaddstr(17,35," Antes, Debe Cargar el Archivo \"gasoduct.in\"");
	        refresh();
	        for(i=14;i<19;i++){
				mvaddch(i,33,ACS_VLINE);
				mvaddch(i,81,ACS_VLINE);
				mvaddch(13,33,ACS_ULCORNER);
				mvaddch(13,81,ACS_URCORNER);
				mvaddch(19,33,ACS_LLCORNER);
				mvaddch(19,81,ACS_LRCORNER);
				mvaddch(15,33,ACS_LTEE);
				mvaddch(15,81,ACS_RTEE);
	        }
	        curs_set(0);
	        refresh();
	        sleep(2);
		}break;
		case 6:{
			erase();
	        mm();
	        curs_set(0);
	        for(j=0;j<3;j++){
	            for(i=25;i<95;i++){
	            	mvaddch(15,i,ACS_HLINE);
	            	mvaddch(21,i,ACS_HLINE);
	            }
	            for(i=15;i<22;i++){
	            	mvaddch(i,24,ACS_VLINE);
	            	mvaddch(i,94,ACS_VLINE);
	            }
	            mvaddch(15,24,ACS_ULCORNER);
	            mvaddch(15,94,ACS_URCORNER);
	            mvaddch(21,24,ACS_LLCORNER);
	            mvaddch(21,94,ACS_LRCORNER);
	            if(j==0){
                	mvaddstr(18,26,"  [ ] Preparando Sistema...                          ");
                }
                if(j==1){
                	mvaddstr(18,26,"  [ ] Espere por Favor...                                       ");
	            }
	            if(j==2){
                	mvaddstr(18,26,"  [ ] A Continuacion, La Carga del Nuevo Diseno...    ");
                }
                refresh();
                for(i=0;i<5;i++){
                	for(l=0;l<4;l++){
                        move(18,29);
                    	printw("%c",ani[l]);
            	         refresh();
            	        system("sleep 0.06");
	        	    }
	        	}
            	
            }
            for(i=25;i<77;i++){
				mvaddch(18,i,' ');
			}
	        refresh();
        }break;
		case 7:{
			erase();
			mm();
			curs_set(0);
	        mvaddstr(15,52,"GAZPROM CORPORATION");
	        mvaddstr(19,33,"La Carga del Archivo \"gasoduc.in\" se realizo con exito!");
	        for(i=30;i<90;i++){
	            mvaddch(14,i,ACS_HLINE);
	            mvaddch(16,i,ACS_HLINE);
	            mvaddch(23,i,ACS_HLINE);
	        }
	        for(i=14;i<23;i++){
	            mvaddch(i,30,ACS_VLINE);
	        	mvaddch(i,90,ACS_VLINE);
	        }
	        mvaddch(14,30,ACS_ULCORNER);
	        mvaddch(14,90,ACS_URCORNER);
	        mvaddch(23,30,ACS_LLCORNER);
	        mvaddch(23,90,ACS_LRCORNER);
	        mvaddch(16,30,ACS_LTEE);
	        mvaddch(16,90,ACS_RTEE);
	        curs_set(0);
	        refresh();
	        sleep(2);
        }break;
	}
}

/// PRES [PROCEDIMIENTO <NINGUN PARÁMETRO> ]: ANIMACION DE LA APERTURA DEL PROGRAMA
pres(){
    int i,j,k;
    char ani[4]={'|','/','~','\\'};
    noecho();
	curs_set(0);
    do{
        for(i=35;i<75;i++){
        	mvaddch(12,i,ACS_HLINE);
        	mvaddch(20,i,ACS_HLINE);
        	if(i<42){
            	mvaddch(i-22,34,ACS_VLINE);
            	mvaddch(i-22,75,ACS_VLINE);
    	    }
    	    if(i==35){
    	        mvaddch(12,34,ACS_ULCORNER);
        	    mvaddch(12,75,ACS_URCORNER);
        	    mvaddch(20,34,ACS_LLCORNER);
        	    mvaddch(20,75,ACS_LRCORNER);
    		}
        }
        mvaddstr(14,42,"GAZPROM COMPANY, GASODUCTOS");
        mvaddstr(16,48,"- BIENVENIDOS -");
        mvaddstr(18,44,"ESPACIO PARA CONTINUAR");
        refresh();
        erase();
    }while(getchar()!=' ');
	for(i=35;i<75;i++){
		mvaddch(12,i,ACS_HLINE);
		mvaddch(20,i,ACS_HLINE);
		if(i<42){
			mvaddch(i-22,34,ACS_VLINE);
			mvaddch(i-22,75,ACS_VLINE);
		}
	    if(i==35){
		    mvaddch(12,34,ACS_ULCORNER);
		    mvaddch(12,75,ACS_URCORNER);
		    mvaddch(20,34,ACS_LLCORNER);
		    mvaddch(20,75,ACS_LRCORNER);
		}
	}
	refresh();
	for(k=0;k<10;k++){
        for(j=0;j<4;j++){
            mvaddstr(16,50,"Cargando ");
            mvaddch(16,60,ani[j]);
            refresh();
            system("sleep 0.09");
            curs_set(0);
		}
	}
refresh();
}

/// MENU [PROCEDIMIENTO]: MENU PRINCIPAL DEL SISTEMA DE ADMINISTRACION DE GAZPROM CORPORATION
menu(int *o){
	int i,y,x;
	char opc[50];
	do{
	    do{
	    	mm();
	    	mvaddstr(12,30,"1.- Cargar Database <<Gasoduct.in>> [Obligatorio]");
	    	mvaddstr(14,30,"2.- Modificar un Disenio Existente");
	    	mvaddstr(16,30,"3.- Agregar un Disenio Nuevo");
	    	mvaddstr(18,30,"4.- Determinar Estabilidad en un Disenio existente");
	    	mvaddstr(20,30,"5.- Mostrar Zonas Comunicadas y Funcionales");
	    	mvaddstr(22,30,"6.- Determinar el Costo de las Zonas Funcionales");
	    	mvaddstr(24,30,"7.- Determinar el Costo de Construccion partiendo de 2 Puntos");
	        curs_set(1);
	        move(37,98);
	    		scanw(" %[^\n]",opc);
	    	if(strlen(opc)!=1){
	    		ERROR(1);
	    		erase();
	    		echo();
			}
	    }while(strlen(opc)!=1);
		opc[0]=toupper(opc[0]);
		switch(opc[0]){
		    case '1':{
		    	x=1;
		    }break;
		    case '2':{
		    	x=2;
		    }break;
		    case '3':{
		    	x=3;
		    }break;
		    case '4':{
		    	x=4;
		    }break;
		    case '5':{
		    	x=5;
		    }break;
		    case '6':{
		    	x=6;
		    }break;
		    case '7':{
		    	x=7;
		    }break;
		    case 'A':{
		    	x=8;
		    }break;
		    case 'S':{
		    	x=9;
		    }break;
		    default:{
		    	x=-1;
			}break;
		}
		if(x==-1){
			ERROR(1);
			refresh();
			echo();
		}
	}while(x==-1);
	*o=x;
    refresh();
}

/// GASODUCIN [PROCEDIMIENTO <NINGUN PARAMETRO> ]: CARGA DEL ARCHIVO GASODUC.IN DE GAZPROM
Gasoducin(vert PDist[][MAX],TAdy VAdy[], int CV[], VVC VeCo[], int *w){
FILE *Arch;
int band=0;
int i1,i2;
int i,j,r;   ///Indices Genericos
int k,l;     ///Indices de la Matriz de Filas de Filas y Columnas
int C;        
char ID1[4],ID2[4];
int id1,id2;
    if ((Arch = fopen("gasoduc.in","r"))==NULL){
    	refresh();
    	ERROR(2);
	}
	else{
	    *w=0;
        fscanf(Arch, "%d",&C);
        while(C!=0){
        	CV[*w]=0;
    	    if(C!=0){
    	        for(r=0;r<3;r++){
    	        	if(r>0){
    	        		fscanf(Arch, "%d",&C);
					}
    	    	    for(i=CV[*w];i<CV[*w]+C;i++){
    	    		    fscanf(Arch, " %2s",PDist[*w][i].tipo);
    	    		    fscanf(Arch, "%d", &PDist[*w][i].ind);
    	    		    fscanf(Arch, " %s", PDist[*w][i].nombre);
                        if(strncmp(PDist[*w][i].nombre, "Planta",6)==0||strncmp(PDist[*w][i].nombre, "Punto",5)==0){
			                PDist[*w][i].nombre[strlen(PDist[*w][i].nombre)-1]='\0';
						}
    	    	    }
            		CV[*w]+=C;
    	        }
    	        band=0;
    	        while(band==0){
    	    		fscanf(Arch, " %2s",ID1);
    	        	if(ID1[0]!='0'){
    	    		    fscanf(Arch, "%d", &i1);
    	        	    fscanf(Arch, " %2s",ID2);
    	    		    fscanf(Arch, "%d", &i2);
    	            	for(i=0;i<CV[*w];i++){
    	            		if(strcmp(ID1,PDist[*w][i].tipo)==0&&i1==PDist[*w][i].ind){
    	            			id1=i;
            				}
    	    		    	if(strcmp(ID2,PDist[*w][i].tipo)==0&&i2==PDist[*w][i].ind){
    	            			id2=i;
    	        			}
            			}
    	                VAdy[*w].Ady[id1][id2].exarc=1;
    	                VAdy[*w].Ady[id1][id2].costo=0;
						fscanf(Arch, "%f",&VAdy[*w].Ady[id1][id2].ATM);
						fscanf(Arch, "%f",&VAdy[*w].Ady[id1][id2].vol);
						fscanf(Arch, "%d",&VAdy[*w].Ady[id1][id2].temp);
						fscanf(Arch, "%d",&VAdy[*w].Ady[id1][id2].trans);
						if(VAdy[*w].Ady[id1][id2].trans==1){
							VAdy[*w].Ady[id1][id2].costo+=20000;
						}
						if(VAdy[*w].Ady[id1][id2].temp<=0){
							VAdy[*w].Ady[id1][id2].costo+=15000;
						}
						else if(VAdy[*w].Ady[id1][id2].temp>0&&VAdy[*w].Ady[id1][id2].temp<30){
							VAdy[*w].Ady[id1][id2].costo+=10000;
						}
						else if(VAdy[*w].Ady[id1][id2].temp>=30&&VAdy[*w].Ady[id1][id2].temp<=45){
							VAdy[*w].Ady[id1][id2].costo+=20000;
						}					
    	    	    }
    	    	    else{
    	    	    	band=1;
    	    		}
    	    	}

    	    	band=0;
    	    	r=0;
    	    	while(band==0){
					fscanf(Arch, " %2s",VeCo[*w].VC[r][0].tipo);
					if(VeCo[*w].VC[r][0].tipo[0]!='0'){
					    fscanf(Arch, "%d", &VeCo[*w].VC[r][0].ind);
					    fscanf(Arch, " %2s",VeCo[*w].VC[r][1].tipo);
					    fscanf(Arch, "%d", &VeCo[*w].VC[r][1].ind);
					    r+=1;
					}
					else{
						band=1;
					}
				}
            }
            *w+=1;
            fscanf(Arch, "\n%d",&C);
        }
        if(C==0){
            fclose(Arch);
        }        	
    }
}

/// MODIFICA [PROCEDIMIENTO]: PERMITE AL USUARIO SOLAMENTE AGREGAR TUBERIAS,AGREGAR PG, DP, CT Y REGRESAR AL MENU PRINCIPAL
MODIFICA(int CPM, int CV[], vert PDist[][MAX], TAdy VAdy[]){
	int DIS,OP,i,b,pos1,pos2,p[2],vi,wi,j;
    char opc[MAX],v[20],w[20];
    double pv,nrt;
    mm();
    do{
    	echo();
    	mm();
	    for(i=30;i<88;i++){
	        mvaddch(10,i,ACS_HLINE);
	    	mvaddch(12,i,ACS_HLINE);
	    	mvaddch(28,i,ACS_HLINE);
	    	mvaddch(30,i,ACS_HLINE);
	    	if(i<50){
	        	mvaddch(i-19,87,ACS_VLINE);
	        	mvaddch(i-20,30,ACS_VLINE);
	        }
	    }
      	mvaddch(10,30,ACS_ULCORNER);
    	mvaddch(10,87,ACS_URCORNER);
    	mvaddch(30,30,ACS_LLCORNER);
    	mvaddch(30,87,ACS_LRCORNER);
    	mvaddch(28,30,ACS_LTEE);
    	mvaddch(28,87,ACS_RTEE);
    	mvaddch(12,30,ACS_LTEE);
    	mvaddch(12,87,ACS_RTEE);
    	mvaddstr(11,31," SELECCIONE EL DISENO QUE DESEA MODIFICAR ");
    	j=13;
    	i=34;
    	for(DIS=0;DIS<CPM;DIS++){
		    move(j,i);
    		printw("Disenio N° %d",DIS+1);
		    if(j>26){
		        j=13;
		        i+=16;
		    }
		    else{
		        j+=1;
			}
    	}
    	move(29,70);
    	curs_set(1);
    	printw("Opcion:");
    	    scanw(" %[^\n]",opc);
    	    curs_set(0);
        DIS=atoi(opc);
        opc[0]=toupper(opc[0]);
        if((DIS<1||DIS>CPM+1)&&opc[0]!='S'){
        	ERROR(1);
        	erase();
		}
    }while((DIS<1||DIS>CPM+1)&&opc[0]!='S');
    if(opc[0]!='S'){
        DIS-=1;
        do{
            do{
            	mm();
            	echo();
            	curs_set(1);
            	mvaddstr(14,30,"Seleccione la Operacion a realizar:");
            	mvaddstr(16,30,"1.- Agregar Tuberias");
            	mvaddstr(18,30,"2.- Agregar Plantas Gasiferas");
            	mvaddstr(20,30,"3.- Agregar Puntos de Conexion de Tuberias");
            	mvaddstr(22,30,"4.- Agregar Puntos de Distribucion de Poblados");
            	mvaddstr(24,30,"5.- Terminar con este Disenio y regresar al Menu Principal");
            	move(37,98);
            	    scanw(" %[^\n]", opc);
            	OP=atoi(opc);
	        }while(OP<1||OP>5);
	        erase();
	        mm();
	        switch(OP){
	        	case 1:{
	        		do{
	        			do{
	        				mm();
	        		        mvaddstr(10,10,"Introduzca el Punto EMISOR de Gas: ");
	        		            scanw(" %[^\n]",opc);
	        		        vi=0;
	        		        if(strlen(opc)>5){
	        		        	mvaddstr(25,3," No Puede Haber mas de 5 Caracteres en la etiqueta del Punto EMISOR de Gas");
	        		        	curs_set(0);
	        		        	refresh();
	        		        	sleep(3);
	        				}
	        				b=0;
	        			    for(i=0;i<strlen(opc);i++){
	        			    	if(i>1&&isdigit(opc[i])){
	        			    		b+=1;
	        					}
	        					else if(i<2&&isalpha(opc[i])){
	        			    		b+=1;
	        					}
	        				}
	        				if(strlen(opc)!=b){
	        		        	mvaddstr(25,3," Los Dos Primeros Caracteres de la Etiqueta deben ser: PG o CT y el Resto deben ser Números");
	        		        	curs_set(0);
	        		        	refresh();
	        		        	sleep(3);
	        				}
	        		    }while(strlen(opc)<3||strlen(opc)>5||b!=strlen(opc));
	        		        v[0]=toupper(opc[0]);
	        		        v[1]=toupper(opc[1]);
	        		        v[2]='\0';
	        		        if(isdigit(opc[2])&&isdigit(opc[3])&&isdigit(opc[4])){
	        		            opc[0]=opc[2];
	        		            opc[1]=opc[3];
	        		            opc[2]=opc[4];
	        		            opc[3]='\0';
        					    opc[4]='\0';
	        				}
	        				else if(isdigit(opc[2])&&isdigit(opc[3])&&!isdigit(opc[4])){
	          	                opc[0]=opc[2];
	    	    	            opc[1]=opc[3];
	    	    	            opc[2]='\0';
	    	    	            opc[3]='\0';
	    	    	            opc[4]='\0';
	    	    			}
	    	    			else if(isdigit(opc[2])&&!isdigit(opc[3])&&!isdigit(opc[4])){
	    	                    opc[0]=opc[2];
	    	    	            opc[1]='\0';
			    				opc[2]='\0';
	    	    	            opc[3]='\0';
	    	    	            opc[4]='\0';
	    	    	            
	    	    			}
	    	    	        vi=atoi(opc);
	    	    	        if(vi==0){
	    	    	        	mvaddstr(25,3,"Lo Indices de las Plantas Gasiferas, Distribucion de Poblados y/o Conexiones entre tuberias no tienen Indice 0");
	    	    	         	curs_set(0);
	    	    	        	refresh();
	    	    	        	sleep(3);
	    	    			}
	    	    			else if(strcmp(v,"DP")==0){
	    	    				mvaddstr(25,3,"Los Puntos de Distribucion de Poblados no pueden ser Emisores de Gas");
	    	    		     	curs_set(0);
	    	    	        	refresh();
	    	    	        	sleep(3);
	    	    			}
	    	    			else if(strcmp(v,"CT")!=0&&strcmp(v,"PG")!=0){
	    	    				mvaddstr(25,3,"Ingreso incorrectamente el Punto EMISOR de Gas");
	    	    				curs_set(0);
	    	    	        	refresh();
	    	    	        	sleep(3);
	    	    			}
	    	        }while(vi==0||strcmp(v,"DP")==0||(strcmp(v,"CT")!=0&&strcmp(v,"PG")!=0));
	    	    	do{
	    	    		do{
	    	    	        mvaddstr(12,10,"Introduzca el Punto RECEPTOR de Gas: ");
	    	    	            scanw(" %[^\n]",opc);
			    			wi=0;
			    			noecho();
	    	    	        if(strlen(opc)>5){
	    	    	        	mvaddstr(25,3," No Puede Haber mas de 5 Caracteres en la etiqueta del Punto RECEPTOR de Gas");
	    	    	        	curs_set(0);
	    	    	        	refresh();
	    	    	        	sleep(3);
	    	    			}
	    	    			b=0;
	    	    		    for(i=0;i<strlen(opc);i++){
	    	    		    	if(i>1&&opc[i]!='\0'&&isdigit(opc[i])){
	    	    		    		b+=1;
	    	    				}
	    	    				else if(i<2&&opc[i]!='\0'&&isalpha(opc[i])){
	    	    		    		b+=1;
	    	    				}
	    	    			}
	    	    			if(strlen(opc)!=b){
	    	    	        	mvaddstr(25,3,"Los Dos Primeros Caracteres de la Etiqueta deben ser: DP o CT y el Resto deben ser Números ");
	    	    	        	curs_set(0);
	    	    	        	refresh();
	    	    	        	sleep(3);
	    	    			}
	    	    	    }while(strlen(opc)<3||strlen(opc)>5||b!=strlen(opc));
	    	    	        w[0]=toupper(opc[0]);
	    	    	        w[1]=toupper(opc[1]);
	    	    	        w[2]='\0';
	    	    	        if(isdigit(opc[2])&&isdigit(opc[3])&&isdigit(opc[4])){
	    	    	            opc[0]=opc[2];
	    	    	            opc[1]=opc[3];
	    	    	            opc[2]=opc[4];
	    	    	            opc[3]='\0';
	    	    	            opc[4]='\0';
	    	    			}
	    	    			else if(isdigit(opc[2])&&isdigit(opc[3])&&!isdigit(opc[4])){
	    	                    opc[0]=opc[2];
	    	    	            opc[1]=opc[3];
			    				opc[2]='\0';
	    	    	            opc[3]='\0';
	    	    	            opc[4]='\0';
	    	    			}
	    	    			else if(isdigit(opc[2])&&!isdigit(opc[3])&&!isdigit(opc[4])){
	    	                    opc[0]=opc[2];
	    	    	            opc[1]='\0';
			    				opc[2]='\0';
	    	    	            opc[3]='\0';
	    	    	            opc[4]='\0';
	    	    			}
	    	    	        wi=atoi(opc);
	    	    	        if(wi==0){
	    	    	        	mvaddstr(25,3,"Lo Indices de las Plantas Gasiferas, Distribucion de Poblados y/o Conexiones entre tuberias no tienen Indice 0 ");
	    	    	        	curs_set(0);
	    	    	        	refresh();
	    	    	        	sleep(3);
	    	    			}
	    	    			else if(strcmp(w,"PG")==0){
	    	    				mvaddstr(25,3,"Las Plantas Gasiferas no pueden ser Receptores de Gas ");
	    	    	        	curs_set(0);
								refresh();
	    	    	        	sleep(3);
	    	    			}
	    	       			else if(strcmp(w,"CT")==0&&strcmp(w,"DP")==0){
	    		    			mvaddstr(25,3,"Ingreso incorrectamente el Punto RECEPTOR de Gas ");
	    		            	curs_set(0);
	    		            	refresh();
	    		            	sleep(3);
	    		    		}
	    		    		echo();
	    	        }while(wi==0||strcmp(w,"PG")==0||(strcmp(w,"CT")!=0&&strcmp(w,"DP")!=0));
                    b=0;
                    for(i=0;i<CV[DIS];i++){
	    		    	if(strcmp(PDist[DIS][i].tipo,v)==0&&PDist[DIS][i].ind==vi){
	    		    		pos1=i;
	    		    	    b+=1;
	    		    	}
	    		    	if(strcmp(PDist[DIS][i].tipo,w)==0&&PDist[DIS][i].ind==wi){
	    		    		pos2=i;
	    		    	    b+=1;
	    		    	}
	    		    }
	    		    noecho();
                    if(b==2&&VAdy[DIS].Ady[pos1][pos2].exarc==1){
	                   for(i=30;i<93;i++){
	                   mvaddch(14,i,ACS_HLINE);
	                   mvaddch(16,i,ACS_HLINE);
	                   mvaddch(21,i,ACS_HLINE);
    	               }
	                   for(i=15;i<22;i++){
	                   mvaddch(i,30,ACS_VLINE);
	                   mvaddch(i,92,ACS_VLINE);
	                   }
	                   curs_set(0);
      	               mvaddch(14,30,ACS_ULCORNER);
    	               mvaddch(14,92,ACS_URCORNER);
    	               mvaddch(21,30,ACS_LLCORNER);
    	               mvaddch(21,92,ACS_LRCORNER);
    	               mvaddstr(15,52,"GAZPROM CORPORATION");
    	               move(18,38);
    	               printw("Ya Existe una tuberia entre desde %s%d y %s%d",v,vi,w,wi);
                       mvaddstr(19,31,"Intente de Nuevo, e Indique Puntos donde no existan Tuberias");
                       refresh();
                       sleep(3);
                       b=0;
	    		    }
				    else if(b==0||b==1){
	                    for(i=30;i<93;i++){
	                        mvaddch(14,i,ACS_HLINE);
	                    	mvaddch(16,i,ACS_HLINE);
	                    	mvaddch(21,i,ACS_HLINE);
    	                }
	                    for(i=15;i<22;i++){
	                    	mvaddch(i,30,ACS_VLINE);
	                    	mvaddch(i,92,ACS_VLINE);
	                }
	                curs_set(0);
      	            mvaddch(14,30,ACS_ULCORNER);
    	            mvaddch(14,92,ACS_URCORNER);
    	            mvaddch(21,30,ACS_LLCORNER);
    	            mvaddch(21,92,ACS_LRCORNER);
    	            mvaddstr(15,52,"GAZPROM CORPORATION");
    	            mvaddstr(18,32,"No existe al menos uno de los dos puntos donde desea ubicar");
                    move(19,40);
                    printw("la tuberia %s%d hasta %s%d. Intente de nuevo",v,vi,w,wi);
                    refresh();
                    sleep(3);
	    			b=0;
				    }
	    		else if(b==2&&VAdy[DIS].Ady[pos1][pos2].exarc==0){
	    			echo();
///PRESION ----------------------------------------------------------------------------------------------------------------///
			        do{
			        	do{
							for(i=4;i<98;i++){
							    mvaddch(14,i,' ');
							}
							move(14,10);
							refresh();
							strcpy(opc," ");
							printw("Introduzca la Presion (ATM) para la tuberia %s%d-%s%d :",v,vi,w,wi);
							    scanw(" %[^\n]", opc);
			        		VAdy[DIS].Ady[pos1][pos2].ATM=atof(opc);
			        		if(VAdy[DIS].Ady[pos1][pos2].ATM<-3){
    			        	    mvaddstr(18,40,"La Presion no puede ser menor a -3 ATM");
				        	    curs_set(0);
				        	    refresh();
				        	    sleep(2);
				        	    for(i=40;i<110;i++){
					            	mvaddch(18,i,' ');
				        	    }
			        		}
			        		else if(VAdy[DIS].Ady[pos1][pos2].ATM>3){
			        			mvaddstr(18,40,"La Presion no puede ser mayor a 3 ATM");
				        	    curs_set(0);
				        	    refresh();
				        	    sleep(2);
				        	    for(i=40;i<110;i++){
					            	mvaddch(18,i,' ');
				        	    }
			        		}
			        	}while(VAdy[DIS].Ady[pos1][pos2].ATM<-3||VAdy[DIS].Ady[pos1][pos2].ATM>3);
			        	p[0]=0;
			        	p[1]=0;
			        	for(i=0;i<strlen(opc);i++){
			        		if(opc[i]=='.'){
			        			p[0]+=1;
			        		}
			        		else if(isdigit(opc[i])){
			        		    p[1]+=1;
			        		}
			        	}
			        	if(p[0]>1){
							mvaddstr(18,15,"La Cantidad que representa a la Presion debe contener un '.' (PUNTO DECIMAL) o ninguno");
							curs_set(0);
							refresh();
							sleep(2);
							for(i=15;i<110;i++){
								mvaddch(18,i,' ');
							}
							refresh();
			        	}
			        	if(p[0]+p[1]!=strlen(opc)){
                            mvaddstr(18,40,"No estan permitidos Caracteres Simbolicos ni Alfabéticos");
							curs_set(0);
							refresh();
							sleep(2);
							for(i=40;i<110;i++){
								mvaddch(18,i,' ');
							}
							refresh();
			        	}
						for(i=4;i<98;i++){
							mvaddch(18,i,' ');
						}
			        }while(p[0]>1||p[0]+p[1]!=strlen(opc));
///VOLUMEN -------------------------------------------------------------------------------------------------------------///
                    do{
			        	do{
			        		for(i=4;i<98;i++){
								mvaddch(16,i,' ');
				        	}
				        	curs_set(1);
			        		move(16,10);
			        		printw("Introduzca el Volumen del Gas para la tuberia %s%d-%s%d: ",v,vi,w,wi);
			        			scanw(" %[^\n]", opc);
			        		VAdy[DIS].Ady[pos1][pos2].vol=atof(opc);
			        		if(VAdy[DIS].Ady[pos1][pos2].vol<15){
			        			mvaddstr(18,40,"El Volumen del Gas no puede ser menor a 15 dm^(3)");
							    curs_set(0);
							    refresh();
							    sleep(2);
							    for(i=40;i<110;i++){
							    	mvaddch(18,i,' ');
							    	mvaddch(16,i,' ');
							    }
							    refresh();
			        		}
			        		else if(VAdy[DIS].Ady[pos1][pos2].vol>50){
			        			mvaddstr(18,40,"El Volumen del Gas no puede ser mayor a 50 dm^(3)");
							    curs_set(0);
							    refresh();
							    sleep(2);
							    for(i=40;i<110;i++){
							    	mvaddch(18,i,' ');
							    	mvaddch(16,i,' ');
							    }
							    refresh();
			        		}
			        	}while(VAdy[DIS].Ady[pos1][pos2].vol<15||VAdy[DIS].Ady[pos1][pos2].vol>50);
			        	p[0]=0;
			        	p[1]=0;
			        	for(i=0;i<strlen(opc);i++){
			        		if(opc[i]=='.'){
			        			p[0]+=1;
			        		}
			        		else if(isdigit(opc[i])){
			        		    p[1]+=1;
			        		}
			        	}
			        	if(p[0]>1){
			        		mvaddstr(18,40,"No pueden haber mas de un punto decimal en la cantidad que representa el Volumen del Gas");
							curs_set(0);
							refresh();
							sleep(2);
							for(i=40;i<79;i++){
								mvaddch(18,i,' ');
							}
							refresh();
			        	}
			        	if(p[0]+p[1]!=strlen(opc)){
			        		mvaddstr(18,15,"La Cantidad que representa el Volumen del Gas solo debe contener numeros y un punto decimal");
							curs_set(0);
							refresh();
							sleep(2);
							for(i=40;i<110;i++){
								mvaddch(18,i,' ');
							}
							refresh();
			        	}
			        }while(p[0]>1||p[0]+p[1]!=strlen(opc));
///TEMPERATURA -------------------------------------------------------------------------------------------------------------///
			        do{
						for(i=4;i<98;i++){
							mvaddch(18,i,' ');
						}
						move(18,10);
			        	printw("Introduzca la Temperatura (°K) del Gas dentro de la Tuberia %s%d-%s%d: ",v,vi,w,wi);
			        		scanw(" %[^\n]", opc);
			            VAdy[DIS].Ady[pos1][pos2].temp=atoi(opc);
			            b=0;
			            for(i=0;i<strlen(opc);i++){
			            	if(!isdigit(opc[i])){
			            		b=1;
			    			}
			    		}
			       		if(b==1){
			    			mvaddstr(20,15,"La Temperatura solo debe contener numeros");
							curs_set(0);
							refresh();
							sleep(2);
							for(i=15;i<120;i++){
								mvaddch(20,i,' ');
							}
							refresh();
							endwin();
			    		}
			    		if(VAdy[DIS].Ady[pos1][pos2].temp<-15){
			    			mvaddstr(20,15,"La Temperatura del Gas dentro de la tuberia no puede ser menor que -15 °K");
							curs_set(0);
							refresh();
							sleep(2);
							for(i=15;i<120;i++){
								mvaddch(20,i,' ');
							}
							refresh();
							endwin();
			    		}
			    		else if(VAdy[DIS].Ady[pos1][pos2].temp>45){
			    			mvaddstr(20,15,"La Temperatura del Gas dentro de la tuberia no puede ser mayor que 45 °K");
							curs_set(0);
							refresh();
							sleep(2);
							for(i=15;i<120;i++){
								mvaddch(20,i,' ');
							}
							refresh();
							endwin();
			    		}
			    	}while(b==1||VAdy[DIS].Ady[pos1][pos2].temp<-15||VAdy[DIS].Ady[pos1][pos2].temp>45);
///TRANSOCEANICA --------------------------------------------------------------------falta ncurses----------------------------///
			        do{
			        	move(20,10);
			        	printw("Indique si la Tuberia %s%d-%s%d es Transoceánica o no:",v,vi,w,wi);
			        	mvaddstr(22,15," 1.- Si, Es Transoceánica");
			        	mvaddstr(24,15," 2.- No, No es Transoceánica");
			        	move(26,30);
			        		scanw(" %[^\n]", opc);
			            p[0]=atoi(opc);
			            if(p[0]!=1&&p[0]!=2){
			            	mvaddstr(27,20,"Solo Indique si la tuberia es transoceánica o no ");
			            	refresh();
			            	sleep(2);
			            	for(i=20;i<110;i++){
								mvaddch(27,i,' ');
								mvaddch(26,i,' ');
							}
			    		}
	    	    	}while(p[0]!=1&&p[0]!=2);
	    	    	switch(p[0]){
	    	    		case 1:{
	    	    			VAdy[DIS].Ady[pos1][pos2].trans=1;
			    		}break;
			    		default:{
			    			VAdy[DIS].Ady[pos1][pos2].trans=0;
			    		}break;
			       	}
			        pv = VAdy[DIS].Ady[pos1][pos2].ATM*VAdy[DIS].Ady[pos1][pos2].vol;
			        nrt = GI * MOL * VAdy[DIS].Ady[pos1][pos2].temp;
                    pv=pv*100000;
                    nrt=nrt*100000;
                    p[0]=pv;
                    p[1]=nrt;
                    pv=p[0];
                    nrt=p[1];
                    if(pv-nrt>0.0001&&nrt<pv){
                    	nrt+=1;
					}
					else if (nrt-pv>0.0001&&nrt>pv){
                    	pv+=1;
					}
                    pv=pv/100000;
                    nrt=nrt/100000;
			        if(pv!=nrt){
			        	VAdy[DIS].Ady[pos1][pos2].est=0;
			    	}
			    	else{
			    		VAdy[DIS].Ady[pos1][pos2].est=1;
			    	}
				VAdy[DIS].Ady[pos1][pos2].exarc=1;
			    }
			}break;
			case 2:{
				b=-1;
				for(i=0;i<CV[DIS];i++){
					if(b==-1&&strcmp(PDist[DIS][i].tipo,"PG")==0){
						b=PDist[DIS][i].ind;
					}
					else if(strcmp(PDist[DIS][i].tipo,"PG")==0&&PDist[DIS][i].ind>b){
						b=PDist[DIS][i].ind;
					}
				}
				PDist[DIS][CV[DIS]].ind=b+1;
				strcpy(PDist[DIS][CV[DIS]].tipo,"PG");
				strcpy(PDist[DIS][CV[DIS]].nombre,"Planta");
				CV[DIS]+=1;
				b=0;
				move(28,30);
				printw("La Planta Gasifera <%s%d> Ha sido creada con exito!",PDist[DIS][CV[DIS]-1].nombre,PDist[DIS][CV[DIS]-1].ind);
				refresh();
				sleep(2);
				for(i=20;i<110;i++){
					mvaddch(28,i,' ');
				}
			}break;
			case 3:{
				b=-1;
				for(i=0;i<CV[DIS];i++){
					if(b==-1&&strcmp(PDist[DIS][i].tipo,"CT")==0){
						b=PDist[DIS][i].ind;
					}
					else if(strcmp(PDist[DIS][i].tipo,"CT")==0&&PDist[DIS][i].ind>b){
						b=PDist[DIS][i].ind;
					}
				}
				PDist[DIS][CV[DIS]].ind=b+1;
				strcpy(PDist[DIS][CV[DIS]].tipo,"CT");
				strcpy(PDist[DIS][CV[DIS]].nombre,"Punto");
				CV[DIS]+=1;
				b=0;
				move(28,30);
				printw("La Conexion de Tuberia <%s%d> Ha sido creado con exito!",PDist[DIS][CV[DIS]-1].nombre,PDist[DIS][CV[DIS]-1].ind);
				refresh();
				sleep(2);
				for(i=20;i<110;i++){
					mvaddch(28,i,' ');
				}
			}break;	
			case 4:{
				b=-1;
				for(i=0;i<CV[DIS];i++){
					if(b==-1&&strcmp(PDist[DIS][i].tipo,"DP")==0){
						b=PDist[DIS][i].ind;
					}
					else if(strcmp(PDist[DIS][i].tipo,"DP")==0&&PDist[DIS][i].ind>b){
						b=PDist[DIS][i].ind;
					}
				}
				do{
					move(13,30);
				    printw("Introduzca el Nombre del Punto de Distribucion de Poblado: ");
				        scanw(" %[^\n]",PDist[DIS][CV[DIS]].nombre);
				    for(i=20;i<110;i++){
				    	mvaddch(28,i,' ');
				    }
				}while(strlen(PDist[DIS][CV[DIS]].nombre)<5||strlen(PDist[DIS][CV[DIS]].nombre)>15);
				PDist[DIS][CV[DIS]].ind=b+1;
				strcpy(PDist[DIS][CV[DIS]].tipo,"DP");
				CV[DIS]+=1;
				b=0;
				move(28,30);
				printw("El Punto de Distribucion de Poblado <%s> Ha sido creado con exito!",PDist[DIS][CV[DIS]-1].nombre);
				refresh();
				sleep(2);
				for(i=20;i<110;i++){
					mvaddch(28,i,' ');
				}
			}break;
			case 5:{
				b=1;
			}break;
			default:{
				b=0;
			}break;
		}
		erase();
		mm();
	}while(b==0);
    }
}

/// NUEVO [PROCEDIMIENTO]: PERMITE AL USUARIO CREAR NUEVOS DISEÑOS PARA GAZPROM CORPORATION
NUEVO(int *CPM, int CV[], vert PDist[][MAX], TAdy VAdy[]){
	int DIS,OP,i,b,pos1,pos2,p[2],vi,wi;
    char opc[20],v[20],w[20];
    double pv,nrt;
    ERROR(6); ///###############################################################################################
///Plantas Gasíferas----------------------------------------------------------------------------------------------------------
    do{
    	erase();
    	mm();
    	move(10,10);
    	printw("Numero de Plantas Gasiferas para el Disenio No. %d: ",*CPM+1);
        	scanw(" %[^\n]",opc);
        for(i=10;i<110;i++){
        	mvaddch(10,i,' ');
		}
    	b=0;
		pos1=atoi(opc);
    	for(i=0;i<strlen(opc);i++){
    		if(isalpha(opc[i])){
    			b=1;
			}
		}
		if(b==1){
			curs_set(0);
			move(18,10);
			printw("La Cantidad de Plantas Gasiferas para el Disenio No. %d, No puede contener Letras ni Simbolos ASCII",*CPM+1);
			refresh();
			sleep(2);
		}
		else if(pos1<=0){
			move(20,30);
			curs_set(0);
			printw("El Disenio No. %d debe contener al menos 1 Planta Gasifera",*CPM+1);
			refresh();
			sleep(2);
		}
		else if(pos1>50){
			curs_set(0);
			move(18,10);
			printw("GAZPROM CORPORATION, No tiene más de 50 Plantas Gasiferas por Disenio");
			refresh();
			sleep(2);
		}
	}while(pos1<=0||b==1||pos1>50);
	CV[*CPM]=pos1;
	for(i=0;i<CV[*CPM];i++){
		PDist[*CPM][i].ind=i+1;
		strcpy(PDist[*CPM][i].tipo,"PG");
		strcpy(PDist[*CPM][i].nombre, "Planta");
	}
///NOTIFICACION DE COMPLETACION DE CREACION DE NUEVAS PLANTAS GASIFERAS PARA EL NUEVO DISEÑO-----------------------------------
	move(18,10);
	curs_set(0);
	printw("GAZPROM CORPORATION: %d Plantas Gasiferas para el Disenio No. %d, Han sido creadas con exito!",pos1,*CPM+1);
	move(19,10);
	refresh();
	sleep(3);
	for(i=9;i<120;i++){
		mvaddch(18,i,' ');
		mvaddch(10,i,' ');
	}
///Puntos Conexiones de Tuberias-----------------------------------------------------------------------------------------------
    do{
		OP=0;
		strcpy(opc," ");
    	mvaddstr(10,10,"¿ Desea Agregar Conexiones de Tuberias ?");
    	mvaddstr(12,20,"1.- Si, Deseo Agregar");
    	mvaddstr(14,20,"2.- No, Luego Agregaré Conexiones de Tuberias");
    	mvaddstr(16,10,"Opcion: ");
    	    scanw(" %[^\n]",opc);
		OP=atoi(opc);
    }while(OP<1||OP>2);
    if(OP==1){
        do{
        	move(18,10);
        	printw("Indique la cantidad de Conexiones de Tuberias para el Disenio No. %d:",*CPM+1);
        	    scanw(" %[^\n]",opc);
        	b=0;
	    	pos1=atoi(opc);
        	for(i=0;i<strlen(opc);i++){
        		if(!isdigit(opc[i])){
        			b=1;
	    		}
	    	}
	    	if(b==1){
	    		move(20,10);
	            curs_set(0);
	    		printw("La Cantidad de Conexiones de Tuberias para el Disenio No. %d, Solo deben ser numeros",*CPM+1);
	    		refresh();
	            sleep(3);
		        for(i=10;i<110;i++){
                	mvaddch(20,i,' ');
                	mvaddch(18,i,' ');
	            }
	    	}
	    	else if(pos1<=0){
		    	curs_set(0);
		    	mvaddstr(20,10,"La Cantidad de Conexiones de Tuberias no puede ser Menor o Igual a Cero");
		    	refresh();
	            sleep(3);
		        for(i=10;i<110;i++){
                	mvaddch(20,i,' ');
                	mvaddch(18,i,' ');
	            }
		    }
	    }while(pos1<=0||b==1);
    b=1;
	for(i=CV[*CPM];i<CV[*CPM]+pos1;i++){
		PDist[*CPM][i].ind=b;
		strcpy(PDist[*CPM][i].tipo,"CT");
		strcpy(PDist[*CPM][i].nombre, "Punto");
		b+=1;
	}
	    CV[*CPM]+=pos1;
///NOTIFICACION DE COMPLETACION DE CREACION DE NUEVAS CONEXIONES DE TUBERIAS PARA EL NUEVO DISEÑO------------------------------
        move(22,10);
	    printw("GAZPROM CORPORATION: %d Conexiones de Tuberias para el Disenio No. %d, Han sido creadas con exito!",pos1,*CPM+1);
	}
	else{
///NOTIFICACION DE COMPLETACION DE CREACION DE NUEVAS CONEXIONES DE TUBERIAS PARA EL NUEVO DISEÑO------------------------------
	    move(18,10);
	    curs_set(0);
	    printw("GAZPROM CORPORATION: Se Agregaron 0 Conexiones de Tuberias para el Disenio No. %d",*CPM+1);
	    refresh();
	    sleep(3);
		for(i=10;i<110;i++){
        	mvaddch(18,i,' ');
	    }
	}
///Puntos de Distribucion de Poblados------------------------------------------------------------------------------------------
	do{
		erase();
		mm();
		move(10,10);
		curs_set(1);
		strcpy(opc," ");
		printw("Indique la cantidad de Distribucion de Poblados para el Disenio No. %d: ",*CPM+1);
			scanw(" %[^\n]",opc);
	    curs_set(0);
		b=0;
		pos1=atoi(opc);
		for(i=0;i<strlen(opc);i++){
			if(!isdigit(opc[i])){
				b=1;
			}
		}
		if(b==1){
        	move(18,10);
			printw("La Cantidad de Puntos de Distribucion de Poblados para el Disenio No. %d, No puede contener Letras ni Simbolos ASCII",*CPM+1);
        	refresh();
        	sleep(3);
		}
		if(pos1<=0){
			move(18,10);
			printw("La Cantidad de Puntos de Distribucion de Poblados no puede ser Menor o Igual a Cero");
	        refresh();
	        sleep(3);
		}
	}while(pos1<=0||b==1);
	for(i=10;i<110;i++){
		mvaddch(10,i,' ');
	}
    b=1;
    p[0]=8;
    vi=0;
	for(i=CV[*CPM];i<CV[*CPM]+pos1;i++){
		PDist[*CPM][i].ind=b;
		strcpy(PDist[*CPM][i].tipo,"DP");
		do{
			if(vi==1){
			 	for(p[1]=10;p[1]<110;p[1]++){
                	mvaddch(p[0],p[1],' ');
	            }
			    move(p[0],10);
			}
			else{
				p[0]+=1;
				move(p[0],10);
			}
			curs_set(1);
		    printw("Indique el Nombre para el Punto de Distribucion de Centros Poblados <%s%d>: ",PDist[*CPM][i].tipo,PDist[*CPM][i].ind);
    		    scanw(" %[^\n]",PDist[*CPM][i].nombre);
    		refresh();
    		curs_set(0);
    		vi=0;
		    for(wi=0;wi<strlen(PDist[*CPM][i].nombre);wi++){
		    	if(!isalpha(PDist[*CPM][i].nombre[wi])){
		    		vi=1;
		    	}
		    }
		    if(vi==1){
	            move(33,20);
		    	printw("El Nombre de los Puntos de Distribucion Deben Contener Nombres con Simbolos Alfabéticos",*CPM+1);
	            refresh();
	            sleep(3);
	            for(p[1]=10;p[1]<115;p[1]++){
                	mvaddch(33,p[1],' ');
	            }
		    }
		    if(strlen(PDist[*CPM][i].nombre)<=2){
	            move(33,20);
		    	printw("El Nombre del Punto de Distribucion del Poblado <%s%d>, Debe Contener más de 2 Caracteres",PDist[*CPM][i].tipo,PDist[*CPM][i].ind,*CPM+1);
	            refresh();
	            sleep(3);
	            for(p[1]=10;p[1]<115;p[1]++){
                	mvaddch(33,p[1],' ');
	            }
		    }
		    if(strlen(PDist[*CPM][i].nombre)>20){
	            move(33,20);
		    	printw("El Nombre del Punto de Distribucion del Poblado <%s%d>, Debe Contener menos de 20 Caracteres",PDist[*CPM][i].tipo,PDist[*CPM][i].ind,*CPM+1);
	            sleep(3);
	            for(p[1]=10;p[1]<115;p[1]++){
                	mvaddch(33,p[1],' ');
	            }
		    }
		}while(vi==1||strlen(PDist[*CPM][i].nombre)<=2||strlen(PDist[*CPM][i].nombre)>20);
		b+=1;
	}
///NOTIFICACION DE COMPLETACION DE CREACION DE NUEVAS CONEXIONES DE TUBERIAS PARA EL NUEVO DISEÑO------------------------------
	move(18,10);
	curs_set(0);
	noecho();
	printw("GAZPROM CORPORATION: %d Conexiones de Tuberias para el Disenio No. %d, Han sido creadas con exito!",pos1,*CPM+1);
	refresh();
	sleep(2);
///ACUMULA LA CANTIDAD DE VERTICES PARA EL NUEVO DISEÑO------------------------------------------------------------------------
	CV[*CPM]+=pos1;
///ACUMULA LA CANTIDAD PLANTAS A NIVEL MUNDIAL PARA EL NUEVO DISEÑO------------------------------------------------------------
	*CPM+=1;
///INFORME Y ACTUALIZACION DE DATOS--------------------------------------------------------------------------------------------
        	erase();
        	mm();
        	noecho();
	        curs_set(0);
	        for(i=26;i<94;i++){
	        	mvaddch(11,i,ACS_HLINE);
	        	mvaddch(22,i,ACS_HLINE);
	        }
	        for(i=11;i<22;i++){
	        	mvaddch(i,26,ACS_VLINE);
	        	mvaddch(i,94,ACS_VLINE);
	        }
	        refresh();
			mvaddch(11,26,ACS_ULCORNER);
	        mvaddch(11,94,ACS_URCORNER);
	        mvaddch(22,26,ACS_LLCORNER);
	        mvaddch(22,94,ACS_LRCORNER);
	        refresh();
	        move(12,30);
	        printw("Espere un Momento...");
	        refresh();
	        sleep(1);
	        move(14,30);
	        printw("Actualizando Base de Datos... ");
	        refresh();
	        sleep(1);
	        printw("ok");
	        refresh();
	        move(16,30);
	        sleep(1);
	        printw("Disenios Agregados: 1 ");
	        refresh();
	        move(18,30);
	        sleep(1);
            printw("Cantidad Total de puntos agregados: %d",CV[*CPM-1]);
	        refresh();
	        sleep(1);
	        move(20,30);
	        printw("Cantidad de Plantas a Nivel Mundial[CPM]: %d",*CPM);
	        refresh();
	        sleep(3);
	        echo();
}

/// CCOMPONENTES [PROCEDIMIENTO]: REALIZA LA UNION DE LOS VERTICES QUE ESTAN EN LA MISMA COMPONENTE CONEXA
CComponentes(int comp[][MAX], int *p, int CV[], int w){
    int i,j,exist_arcos,x,y;
    int m[MAX][MAX];
    ///INICIALIZA MATRIZ M[][] EN 0 Y AGREGA LOS ARCOS A LA MATRIZ
    for(i=0;i<CV[w];i++){
    	for(j=0;j<CV[w];j++){
    		m[i][j]=0;
		}
	}
	CCAM(m,w,CV,VAdy);
    ///INICIALIZA COMP[][] PARA QUE CADA VERTICE INICIALMENTE SEA UNA COMPONENTE CONEXA
    for(i=0;i<CV[w];i++){ 
    	comp[0][i]=i+1;
	}
	*p=CV[w];
	x=0;
	y=0;
	exist_arcos=1;
	while(exist_arcos==1){
		exist_arcos=0;
	    exist_arcos=larcos(CV[w],m,&x,&y);
		i=buscar_componente(x+1,comp,CV[w]);
		j=buscar_componente(y+1,comp,CV[w]);
		if(i!=j){
	    	Union(i,j,comp,CV[w]);
			*p-=1;
	    }
    }
}

/// LARCOS [PROCEDIMIENTO]: LEE LOS ARCOS QUE EXISTEN EN LA MATRIZ PARA LUEGO SER EVALUADOS 
int larcos(int n,int m[][MAX], int *ii, int *jj){
	int i,j;
	int k=1;
	for(i=*ii;i<n;i++){
		for(j=0;j<n;j++){
			if(m[i][j]==1){
				*ii=i;
				*jj=j;
				m[i][j]=2;
				return 1;
				break;
			}
		}
	}
}

/// BUSCAR_COMPONENTE [FUNCION]: BUSCA Y RETORNA EL INDICE DE UN ARCO EN LA MATRIZ DE COMPONENTES CONEXAS
int buscar_componente(int verts,int comp[][MAX], int n){
	int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(comp[j][i]==verts){
				return i;
			}
		}
	}
}

/// UNION [PROCEDIMIENTO]: UNE DOS COMPONENTES CONEXAS DISTINTAS, ES DECIR, UNE EL CONTENIDO DE UNA COLUMNA CON OTRA EN LA MATRIZ DE LAS COMPONENTES CONEXAS
Union(int ii,int jj,int comp[][MAX],int n){
	int i,j,k;
	for(i=0;i<n;i++){
		if(comp[i][ii]==0){
			k=i;
			break;
		}
	}
	for(j=0;j<n;j++){
		comp[k][ii]=comp[j][jj];
		comp[j][jj]=0;
		k+=1;
	}
}

/// MESTABILIDAD [PROCEDIMIENTO]: DADO UN DISEÑO SEÑALADO POR EL USUARIO, MUESTRA LA ESTABILIDAD Ó EN CASO CONTRARIO, INESTABILIDAD, DE TODAS LAS TUBERÍAS QUE PERTENECEN A ESE DISEÑO
MEstabilidad(TAdy VAdy[], int CV[],int CPM, vert PDist[][MAX]){
	int w,i,j;
	int aux1[2];
	char aux[10];
	int opc;
    ///LLAMADA A ESTABILIDAD PARA ACTUALIZAR LA MATRIZ DE ADYACENCIA CON RESPECTO A LA ESTABILIDAD DE CADA TUBERÍA
    Estabilidad(VAdy,CV,CPM,PDist);
	for(i=10;i<31;i++){
		for(j=30;j<88;j++){
			mvaddch(i,j,' ');
		}
	}
    do{
    	mm();
	    for(i=30;i<88;i++){
	        mvaddch(10,i,ACS_HLINE);
	    	mvaddch(12,i,ACS_HLINE);
	    	mvaddch(28,i,ACS_HLINE);
	    	mvaddch(30,i,ACS_HLINE);
	    	if(i<50){
	        	mvaddch(i-19,87,ACS_VLINE);
	        	mvaddch(i-20,30,ACS_VLINE);
	        }
	    }
      	mvaddch(10,30,ACS_ULCORNER);
    	mvaddch(10,87,ACS_URCORNER);
    	mvaddch(30,30,ACS_LLCORNER);
    	mvaddch(30,87,ACS_LRCORNER);
    	mvaddch(28,30,ACS_LTEE);
    	mvaddch(28,87,ACS_RTEE);
    	mvaddch(12,30,ACS_LTEE);
    	mvaddch(12,87,ACS_RTEE);
    	mvaddstr(11,31," SELECCIONE EL DISENO QUE DESEA REVISAR ");
    	j=13;
    	i=34;
    	for(w=0;w<CPM;w++){
		    move(j,i);
    		printw("Disenio N° %d",w+1);
		    if(j>26){
		        j=13;
		        i+=16;
		    }
		    else{
		        j+=1;
			}
    	}
    	move(29,70);
    	curs_set(1);
    	printw("Opcion:");
    	    scanw(" %[^\n]",aux);
    	    curs_set(0);
        opc=atoi(aux);
        aux[0]=toupper(aux[0]);
        if((opc<1||opc>CPM+1)&&aux[0]!='S'){
        	ERROR(1);
        	erase();
		}
    }while((opc<1||opc>CPM)&&aux[0]!='S');
	opc-=1;
    if(aux[0]!='S'){
	    mm();
        for(i=5;i<101;i++){
	    	mvaddch(5,i+5,ACS_HLINE);
	    	mvaddch(7,i+5,ACS_HLINE);
	    	mvaddch(9,i+5,ACS_HLINE);
	    	mvaddch(35,i+5,ACS_HLINE);
	    	if(i<35){
	    		mvaddch(i,10,ACS_VLINE);
	       		mvaddch(i,105,ACS_VLINE);
		    }
	    }
	    mvaddch(5,10,ACS_ULCORNER);
	    mvaddch(5,105,ACS_URCORNER);
	    mvaddch(35,10,ACS_LLCORNER);
	    mvaddch(35,105,ACS_LRCORNER);
	    mvaddch(9,105,ACS_RTEE);
	    mvaddch(7,105,ACS_RTEE);
	    mvaddch(7,10,ACS_LTEE);
	    mvaddch(9,10,ACS_LTEE);
	    mvaddch(7,58,ACS_TTEE);
	    mvaddch(35,58,ACS_BTEE);
        for(i=8;i<35;i++){
        	mvaddch(i,58,ACS_VLINE);
	    }
        move(6,40);
        printw("Estabilidad de Tuberias para el Disenio %d",opc+1);
        curs_set(0);
	    aux1[0]=10;
	    aux1[1]=12;
        mvaddstr(8,25,"Tuberias Inestables");
	    for(i=0;i<CV[opc];i++){
	    	for(j=0;j<CV[opc];j++){
	    		if(VAdy[opc].Ady[i][j].est==0){
	    		    move(aux1[0],aux1[1]);
	    		    printw("%s [%s%d] %s [%s%d]",PDist[opc][i].nombre,PDist[opc][i].tipo,PDist[opc][i].ind,PDist[opc][j].nombre,PDist[opc][j].tipo,PDist[opc][j].ind);
	    		    aux1[0]+=1;
	    		    
	    		}
	    	}
	    }
	    aux1[0]=10;
	    aux1[1]=60;
	    mvaddstr(8,74,"Tuberias Estables");
	    for(i=0;i<CV[opc];i++){
	    	for(j=0;j<CV[opc];j++){
	    		if(VAdy[opc].Ady[i][j].est==1){
	    		    move(aux1[0],aux1[1]);
	    		    printw("%s [%s%d] %s [%s%d]",PDist[opc][i].nombre,PDist[opc][i].tipo,PDist[opc][i].ind,PDist[opc][j].nombre,PDist[opc][j].tipo,PDist[opc][j].ind);
	    		    aux1[0]+=1;
	    		}
	    	}
	    }
	    ERROR(3);
	    refresh();
    }
}    
    
/// CAMINO_FINDER [PROCEDIMIENTO]: BUSCA LOS INDICES DEL PUNTO DE PARTIDA Y LLEGADA PARA UN CAMINO ENTRE DOS PUNTOS: 1.- PG* 2.- DP*
Camino_Finder(char ID1[], char ID2[], int i1, int i2,int *sol_enc, int Cam[][MAX], int sol_parcial[], vert PDist[][MAX], int CV[], int w, int TUS){
	int i;
	int vp,vf;
	for(i=0;i<CV[w];i++){
		if(strcmp(ID1,PDist[w][i].tipo)==0&&PDist[w][i].ind==i1){
			vp=i;
		}
		if(strcmp(ID2,PDist[w][i].tipo)==0&&PDist[w][i].ind==i2){
			vf=i;
		}
	}
    sol_parcial[0]=vp;
    TUS=1;
	buscar_camino(vp, vf, Cam, sol_parcial, TUS, &*sol_enc, CV, w);
}

/// BUSCA_CAMINO [PROCEDIMIENTO]: BUSCA CAMINOS ENTRE UN PG* Y DP*, DONDE '*' ES UN ENTERO QUE REPRESENTA UN INDICE PROPIO PARA CADA VERTICE DE CADA TIPO PARA CADA DISEÑO
buscar_camino(int vp, int vf, int datos[][MAX], int sol_parcial[], int tusp, int *sol_enc, int CV[], int w){
	int k=0,i;
	while((k<CV[w])&&(*sol_enc==0)){
		k++;
		if((datos[vp][k]==1)&&(encontrar(sol_parcial, tusp, k)==0)){
			sol_parcial[tusp]=k;
			tusp+=1;
			if(vf==k){
				*sol_enc=1;
			}
			else{
				buscar_camino(k, vf, datos, sol_parcial, tusp, &*sol_enc, CV, w);
				tusp-=1;
			}
		}
	}
}

/// ENCONTRAR [FUNCION]: RETORNA UN VALOR ENTERO
int encontrar(int sol_parcial[], int tusp, int K){
	int i,bandera=0;
	for(i=0;i<tusp;i++){
		if(sol_parcial[i]==K){
			bandera=1;	
		}
	}
	if(bandera==1){
		return(1);
	}
	else{
		return(0);
	}
}

/// ESTABILIDAD [PROCEDIMIENTO]: DETERMINA LA ESTABILIDAD PARA CADA TUBERIA, CALCULANDO Y EVALUANDO LA IGUALDAD (PV=NRT)
Estabilidad(TAdy VAdy[], int CV[],int CPM, vert PDist[][MAX]){
	int w,i,j;
	int aux1[2];
	char aux[10];
	int opc;
	double pv, nrt;
	
	for(w=0;w<CPM;w++){
		for(i=0;i<CV[w];i++){
            for(j=0;j<CV[w];j++){
            	    pv=VAdy[w].Ady[i][j].ATM * VAdy[w].Ady[i][j].vol;
                    nrt=MOL * GI * VAdy[w].Ady[i][j].temp;
                    pv=pv*100000;
                    nrt=nrt*100000;
                    aux1[0]=pv;
                    aux1[1]=nrt;
                    pv=aux1[0];
                    nrt=aux1[1];
                    if(pv>nrt){
                    	nrt+=1;
					}
					else if(nrt>pv){
                    	pv+=1;
					}
                    pv=pv/100000;
                    nrt=nrt/100000;
                    if((pv==nrt)&&VAdy[w].Ady[i][j].exarc==1){
                       	VAdy[w].Ady[i][j].est=1;
		            }
		            else if(pv!=nrt&&VAdy[w].Ady[i][j].exarc==1){
                        VAdy[w].Ady[i][j].est=0;
					}
					else if(VAdy[w].Ady[i][j].exarc==0){
                        VAdy[w].Ady[i][j].est=-1;
					}
			}
		}
	}
}

/// CCAM [PROCEDIMIENTO]: COPIA LA MATRIZ DE UN DISEÑO 'w' SEGUN LA ESTABILIDAD EN OTRA
CCAM(int Cam[][MAX],int w, int CV[], TAdy VAdy[]){
	int i,j;
	for(i=0;i<CV[w];i++){
		for(j=0;j<CV[w];j++){
			if(VAdy[w].Ady[i][j].est==1){
				Cam[i][j]=1;
			}
			else{
				Cam[i][j]=0;
			}
		}
	}
}

///CONSULTAS [PROCEDIMIENTO]: DADO DOS UNA PLANTA GASÍFERA Y UN PUNTO DE DISTRIBUCION DE POBLADOS, ENCUENTRA EL CAMINO (SII EXISTE) Y CALCULA EL COSTO PARA ESA LINEA DE DISTRIBUCION Y DA UN TIEMPO ESTIMADO PARA EL REGRESO AL MENU PRINCIPAL
Consultas(vert PDist[][MAX], int sol_parcial[],int TUS, VVC VeCo[], int CV[], TAdy VAdy[], int Cam[][MAX]){
    int sol_enc,i,w,j,m,i1,i2,band,l,k,costo;
    char ID1[3],ID2[3],aux[15],aux2[3];
	do{
    	mm();
    	strcpy(aux," ");
	    for(i=30;i<88;i++){
	        mvaddch(10,i,ACS_HLINE);
	    	mvaddch(12,i,ACS_HLINE);
	    	mvaddch(28,i,ACS_HLINE);
	    	mvaddch(30,i,ACS_HLINE);
	    	if(i<50){
	        	mvaddch(i-19,87,ACS_VLINE);
	        	mvaddch(i-20,30,ACS_VLINE);
	        }
	    }
      	mvaddch(10,30,ACS_ULCORNER);
    	mvaddch(10,87,ACS_URCORNER);
    	mvaddch(30,30,ACS_LLCORNER);
    	mvaddch(30,87,ACS_LRCORNER);
    	mvaddch(28,30,ACS_LTEE);
    	mvaddch(28,87,ACS_RTEE);
    	mvaddch(12,30,ACS_LTEE);
    	mvaddch(12,87,ACS_RTEE);
    	move(11,31);
    	printw("CONSULTAS DE DISENIOS :: GAZPROM CORPORATION");
    	j=13;
    	i=34;
    	for(w=0;w<CPM;w++){
		    move(j,i);
    		printw("Disenio N° %d",w+1);
		    if(j>26){
		        j=13;
		        i+=16;
		    }
		    else{
		        j+=1;
			}
    	}
    	move(29,70);
		curs_set(1);
	    printw("Opcion:");
    	    scanw(" %[^\n]",aux);
    	    curs_set(0);
        w=atoi(aux);
        aux[0]=toupper(aux[0]);
        strcpy(aux," ");
        if((w<1||w>CPM)&&aux[0]!='S'){
        	ERROR(1);
        	erase();
		}
    }while((w<1||w>CPM)&&aux[0]!='S');
    w-=1;
    erase();
    mm();
    ///VALIDACION DEL PRIMER PUNTO -- PARTIDA
	do{
		mm();
		echo();
        curs_set(1);
        strcpy(aux," ");
        strcpy(aux2," ");
	    mvaddstr(12,10,"Introduzca una Planta Gasifera como Punto de Partida: ");
		scanw(" %[^\n]",aux);
		aux2[0]=toupper(aux[0]);
		aux2[1]=toupper(aux[1]);
		aux2[2]='\0';
		aux[0]=aux[2];
		aux[1]='\0';
		aux[2]='\0';
		///INDICE DEL PRIMER PUNTO
		i1=atoi(aux);
	}while(strcmp("PG",aux2)!=0||i1<=0||i1>99);
		///TIPO DEL PRIMER PUNTO
		strcpy(ID1,aux2);
    ///VALIDACION DEL SEGUNDO PUNTO -- LLEGADA
	do{
		for(i=10;i<125;i++){
			mvaddch(14,i,' ');
		}
		mvaddch(14,120,ACS_VLINE);
		strcpy(aux," ");
		strcpy(aux2," ");
	    mvaddstr(14,10,"Introduzca un Punto de Distribucion de Poblado como Punto de Llegada: ");
		scanw(" %[^\n]",aux);
		aux2[0]=toupper(aux[0]);
		aux2[1]=toupper(aux[1]);
		aux2[2]='\0';
		aux[0]=aux[2];
		aux[1]='\0';
		aux[2]='\0';
		///INDICE DEL SEGUNDO PUNTO
		i2=atoi(aux);
	}while(strcmp("DP",aux2)!=0||i2<=0||i2>99);
	///INDICE DEL SEGUNDO PUNTO 
	strcpy(ID2,aux2);
	for(l=0;l<CV[w];l++){
		sol_parcial[l]=-1;
	}
	CCAM(Cam,w,CV,VAdy);
	sol_enc=0;
	Camino_Finder(ID1,ID2,i1,i2,&sol_enc,Cam,sol_parcial,PDist,CV,w,TUS);
	if(sol_enc==1){
		m=0;
		TUS=0;
		costo=0;                                
		for(k=1;k<CV[w];k++){
			if(sol_parcial[k]>-1&&strcmp(PDist[w][sol_parcial[k-1]].tipo, ID2)!=0){
				if(VAdy[w].Ady[sol_parcial[k-1]][sol_parcial[k]].trans==1){
					costo+=20000;
				}
				if(VAdy[w].Ady[sol_parcial[k-1]][sol_parcial[k]].temp<=0){
					costo+=15000;
				}
				if(0<VAdy[w].Ady[sol_parcial[k-1]][sol_parcial[k]].temp&&VAdy[w].Ady[sol_parcial[k-1]][sol_parcial[k]].temp<30){
					costo+=10000;
				}
				if(30<=VAdy[w].Ady[sol_parcial[k-1]][sol_parcial[k]].temp&&VAdy[w].Ady[sol_parcial[k-1]][sol_parcial[k]].temp<=45){
					costo+=20000;
				}
			}
		}
		move(17,10);
		printw("TRAYECTO DE LA LINEA DE DISTRIBUCION SEGUN LA CADENA DE TUBERIAS DESDE %s%d HASTA %s%d",ID1,i1,ID2,i2);
		move(20,10);
		printw("PUNTOS EN ORDEN DE CONEXION:");
		band=0;
		m=22;
		move(m,15);
		for(k=0;k<CV[w];k++){
			if(sol_parcial[k]>-1&&strcmp(PDist[w][sol_parcial[k-1]].tipo, ID2)!=0){
			    if(band!=5){
			        band+=1;
				}
				else{
					m+=1;
                    move(m,15);
                    band=0;
				}
				if(strncmp(PDist[w][sol_parcial[k]].nombre, "Planta",6)==0||strncmp(PDist[w][sol_parcial[k]].nombre, "Punto",5)==0){
					printw("%s%d: %s%d",PDist[w][sol_parcial[k]].tipo,PDist[w][sol_parcial[k]].ind,PDist[w][sol_parcial[k]].nombre,PDist[w][sol_parcial[k]].ind);
				}
				if(strncmp(PDist[w][sol_parcial[k]].nombre, "Planta",6)!=0&&strncmp(PDist[w][sol_parcial[k]].nombre, "Punto",5)!=0){
					printw("%s%d: %s",PDist[w][sol_parcial[k]].tipo,PDist[w][sol_parcial[k]].ind,PDist[w][sol_parcial[k]].nombre);
				}
			}
			if(sol_parcial[k]>-1&&sol_parcial[k+1]>-1){
				printw(" - ");
			}
		}
		noecho();
		curs_set(0);
		m+=2;
		move(m,10);
		printw("COSTO DE LA LINEA DE DISTRIBUCION: %d US$",costo);
		for(i=15;i>0;i--){
			move(m+4,30);
			if(i>9){
			    printw("- En %d Segundos el programa lo guiará al Menu Principal -",i);
			}
			else{
				printw("- En 0%d Segundos el programa lo guiará al Menu Principal -",i);
			}
			refresh();
			sleep(1);
		}
		echo();
	}
	else{
		move(17,15);
		printw("ATENCION: NO ES POSIBLE QUE FLUYA GAS DESDE %s%d HASTA %s%d",ID1,i1,ID2,i2);
		noecho();
		curs_set(0);
		for(i=5;i>0;i--){
			move(20,30);
				printw("- En 0%d Segundos el programa lo guiará al Menu Principal -",i);
			refresh();
			sleep(1);
		}
		echo();
	}
	i+=1;
}

///ZONA_FUNCIONALES [PROCEDIMIENTO]: MUESTRA LAS ZONAS FUNCIONALES DE ACUERDO A UN DISEÑO DADO
Zonas_Funcionales(int CV[], TAdy VAdy[], vert PDist[][MAX],int CPM){
	int Componentes[MAX][MAX],CZC,i,j,h,k,kk,b,costo,opc,w;
	int dy,dx;
	char aux[20];
	do{
    	mm();
	    for(i=30;i<88;i++){
	        mvaddch(10,i,ACS_HLINE);
	    	mvaddch(12,i,ACS_HLINE);
	    	mvaddch(28,i,ACS_HLINE);
	    	mvaddch(30,i,ACS_HLINE);
	    	if(i<50){
	        	mvaddch(i-19,87,ACS_VLINE);
	        	mvaddch(i-20,30,ACS_VLINE);
	        }
	    }
      	mvaddch(10,30,ACS_ULCORNER);
    	mvaddch(10,87,ACS_URCORNER);
    	mvaddch(30,30,ACS_LLCORNER);
    	mvaddch(30,87,ACS_LRCORNER);
    	mvaddch(28,30,ACS_LTEE);
    	mvaddch(28,87,ACS_RTEE);
    	mvaddch(12,30,ACS_LTEE);
    	mvaddch(12,87,ACS_RTEE);
    	mvaddstr(11,31," SELECCIONE EL DISENO QUE DESEA REVISAR ");
    	j=13;
    	i=34;
    	for(w=0;w<CPM;w++){
		    move(j,i);
    		printw("Disenio N° %d",w+1);
		    if(j>26){
		        j=13;
		        i+=16;
		    }
		    else{
		        j+=1;
			}
    	}
    	move(29,70);
		echo();
    	curs_set(1);
    	printw("Opcion:");
    	    scanw(" %[^\n]",aux);
    	    curs_set(0);
        opc=atoi(aux);
        if((opc<1||opc>CPM)&&aux[0]!='S'){
        	ERROR(1);
        	erase();
		}
    }while((opc<1||opc>CPM)&&aux[0]!='S');
    w=opc-1;
        erase();
    mm();
		for(i=8;i<30;i++){
			mvaddch(i,13,ACS_VLINE);
			mvaddch(i,108,ACS_VLINE);
		}
		for(i=14;i<109;i++){
			mvaddch(8,i,ACS_HLINE);
			mvaddch(10,i,ACS_HLINE);
			mvaddch(30,i,ACS_HLINE);
		}
		mvaddch(10,108,ACS_RTEE);
		mvaddch(10,13,ACS_LTEE);
		mvaddch(8,13,ACS_ULCORNER);
		mvaddch(8,108,ACS_URCORNER);
		mvaddch(30,13,ACS_LLCORNER);
		mvaddch(30,108,ACS_LRCORNER);
		move(9,15);
	printw("ZONAS CONECTADAS DEL DISENIO No. %d  :: GAZPROM CORPORATION",w+1);
	dy=10;
	dx=15; 
	move(dy,dx);
        	h=0;
				for(i=0;i<CV[w];i++){
			    	for(j=0;j<CV[w];j++){
		        		Componentes[i][j]=0;
		            }
	            }
			CComponentes(Componentes,&CZC,CV,w);
        	for(i=0;i<CV[w];i++){
        		for(j=0;j<CV[w];j++){
        		    Componentes[i][j]-=1;
				}
			}
			costo=0;
			///VERIFICA QUE LAS COMPONENTES CONEXAS SEAN MAYOR QUE 1, YA QUE LAS IMPRIME POR SEPARADO
	        if(CZC>1){
	            for(j=0;j<CV[w];j++){
				    if(Componentes[0][j]>-1){
				    	dy+=2;
				    	dx=15;
	    	    		move(dy,dx);
					    printw("ZONA CONECTADA No. %d : ",h+1);
                        refresh();
	                	for(i=-1;i<CV[w]-1;i++){
	                		if(Componentes[i+1][j]>-1){
	                			if(strncmp(PDist[w][Componentes[i+1][j]].nombre, "Planta",6)==0||strncmp(PDist[w][Componentes[i+1][j]].nombre, "Punto",5)==0){
	                		    	printw("%s%d  ",PDist[w][Componentes[i+1][j]].nombre,PDist[w][Componentes[i+1][j]].ind);
	                		    	refresh();
							    }
							    if(strncmp(PDist[w][Componentes[i+1][j]].nombre, "Planta",6)!=0&&strncmp(PDist[w][Componentes[i+1][j]].nombre, "Punto",5)!=0){
	                		    	printw("%s ",PDist[w][Componentes[i+1][j]].nombre);
	                		    	refresh();
							    }
	                		}
						}
						dy+=1;
						move(dy,dx);
						for(k=0;k<CV[w];k++){
						if(strcmp(PDist[w][Componentes[k][j]].nombre, "Planta")==0){
							printw(" <> Funcional: Si");
							refresh();
							break;
						}
						else{
							printw(" <> Funcional: No");
							refresh();
							break;
						}
						dy+=2;
					    }
					}
                    if(Componentes[0][j+1]>-1){
                    	h+=1;
			    	}
			    	
	            }
			}///SI COMPONENTES CONEXAS, ENTONCES SON IGUAL A CERO Ó IGUALES A UNO, ASI QUE PARA LOS DOS CASOS SE CUMPLE
			else{
				move(12,15);
				printw("Todos los componentes quedaron conectados.");
			    refresh();
			}
			ERROR(3);
    }

///COSTO [PROCEDIMIENTO]: MUESTRA EL COSTO DE CADA ZONA FUNCIONAL DE ACUERDO A UN DISEÑO DADO
Costo(int CV[], TAdy VAdy[], vert PDist[][MAX],int CPM){
	int Componentes[MAX][MAX],CZC,i,j,h,k,kk,b,costo,opc,w;
	int dy,dx;
	char aux[20];
	do{
    	mm();
	    for(i=30;i<88;i++){
	        mvaddch(10,i,ACS_HLINE);
	    	mvaddch(12,i,ACS_HLINE);
	    	mvaddch(28,i,ACS_HLINE);
	    	mvaddch(30,i,ACS_HLINE);
	    	if(i<50){
	        	mvaddch(i-19,87,ACS_VLINE);
	        	mvaddch(i-20,30,ACS_VLINE);
	        }
	    }
      	mvaddch(10,30,ACS_ULCORNER);
    	mvaddch(10,87,ACS_URCORNER);
    	mvaddch(30,30,ACS_LLCORNER);
    	mvaddch(30,87,ACS_LRCORNER);
    	mvaddch(28,30,ACS_LTEE);
    	mvaddch(28,87,ACS_RTEE);
    	mvaddch(12,30,ACS_LTEE);
    	mvaddch(12,87,ACS_RTEE);
    	mvaddstr(11,31," SELECCIONE EL DISENO QUE DESEA REVISAR ");
    	j=13;
    	i=34;
    	for(w=0;w<CPM;w++){
		    move(j,i);
    		printw("Disenio N° %d",w+1);
		    if(j>26){
		        j=13;
		        i+=16;
		    }
		    else{
		        j+=1;
			}
    	}
    	move(29,70);
    	curs_set(1);
    	printw("Opcion:");
    	    scanw(" %[^\n]",aux);
    	    curs_set(0);
        opc=atoi(aux);
        if((opc<1||opc>CPM)&&aux[0]!='S'){
        	ERROR(1);
        	erase();
		}
    }while((opc<1||opc>CPM)&&aux[0]!='S');
    w=opc-1;
        erase();
    mm();
		for(i=8;i<30;i++){
			mvaddch(i,13,ACS_VLINE);
			mvaddch(i,108,ACS_VLINE);
		}
		for(i=14;i<109;i++){
			mvaddch(8,i,ACS_HLINE);
			mvaddch(10,i,ACS_HLINE);
			mvaddch(30,i,ACS_HLINE);
		}
		mvaddch(10,108,ACS_RTEE);
		mvaddch(10,13,ACS_LTEE);
		mvaddch(8,13,ACS_ULCORNER);
		mvaddch(8,108,ACS_URCORNER);
		mvaddch(30,13,ACS_LLCORNER);
		mvaddch(30,108,ACS_LRCORNER);
		move(9,15);
	printw("ZONAS CONECTADAS DEL DISENIO No. %d  :: GAZPROM CORPORATION",w+1);
	dy=10;
	dx=15; 
	move(dy,dx);
        	h=0;
				for(i=0;i<CV[w];i++){
			    	for(j=0;j<CV[w];j++){
		        		Componentes[i][j]=0;
		            }
	            }
			CComponentes(Componentes,&CZC,CV,w);
        	for(i=0;i<CV[w];i++){
        		for(j=0;j<CV[w];j++){
        		    Componentes[i][j]-=1;
				}
			}
			costo=0;
			///VERIFICA QUE LAS COMPONENTES CONEXAS SEAN MAYOR QUE 1, YA QUE LAS IMPRIME POR SEPARADO
	        if(CZC>1){
	            for(j=0;j<CV[w];j++){
				    if(Componentes[0][j]>-1){
				    	dy+=2;
				    	dx=15;
	    	    		move(dy,dx);
					    printw("ZONA CONECTADA No. %d : ",h+1);
                        refresh();
					    costo=0;
					    for(k=0;k<CV[w]-1;k++){
					    	for(kk=k+1;kk<CV[w];kk++){
					    		if(Componentes[k+1][j]!=-1){
					    			costo+=VAdy[w].Ady[Componentes[k][j]][Componentes[kk][j]].costo;
					    		}
					    	}
					    }
					    printw(" %d US$",costo);
					}
                    if(Componentes[0][j+1]>-1){
                    	h+=1;
			    	}
			    	
	            }
			}///SI COMPONENTES CONEXAS, ENTONCES SON IGUAL A CERO Ó IGUALES A UNO, ASI QUE PARA LOS DOS CASOS SE CUMPLE
			else{
				move(10,15);
			    costo=0;
			    for(j=0;j<CV[w];j++){
			    	if(Componentes[0][j]>-1){
			    		for(k=0;k<CV[w]-1;k++){
			    			for(kk=k+1;kk<CV[w];kk++){
			    				if(Componentes[k+1][j]>-1&&VAdy[w].Ady[Componentes[k][j]][Componentes[kk][j]].est==1){
			    					costo+=VAdy[w].Ady[Componentes[k][j]][Componentes[kk][j]].costo;
			    				}
			    			}
			    		}
			    	}
			    }
			    printw("%d US$",costo);
			    refresh();
			}
			ERROR(3);
    }

/// GASODUCOUT [PROCEDIMIENTO]: CREA EL ARCHIVO 'gasoduc.out' CON LA INFORMACION RESUMIDA DE CADA UNA DE LAS TUBERIAS Y/O ARCOS DE TODOS LOS DISEÑOS QUE SE IMPLEMENTARON EN EL PROYECTO
Gasoducout(TAdy Vady[], int CV[],int CPM, vert PDist[][MAX],VVC VeCo[]){
FILE *puntero;
double pv, nrt;
char ID1[3],ID2[3];
int w,i,j,h,m,i1,i2,l,k;
int Componentes[MAX][MAX];
int costo,CZC,aux1[2],kk,band,sol_parcial[MAX],TUS,Cam[MAX][MAX],sol_enc;
puntero=fopen("gasoduc.out","w");
	for(w=0;w<CPM;w++){
		fprintf(puntero,"Diseño %d de un sistema de Gaseoductos:\n\n",w+1);
		fprintf(puntero,"Tuberias del Sistema: \n");
		for(i=0;i<CV[w];i++){
            for(j=0;j<CV[w];j++){
            	if(VAdy[w].Ady[i][j].exarc==1){
				    pv=VAdy[w].Ady[i][j].ATM * VAdy[w].Ady[i][j].vol;
				    nrt=MOL * GI * VAdy[w].Ady[i][j].temp;
				    pv=pv*100000;
				    nrt=nrt*100000;
				    aux1[0]=pv;
				    aux1[1]=nrt;
				    pv=aux1[0];
				    nrt=aux1[1];
				    if(pv-nrt>0.0001&&nrt<pv){
				    	nrt+=1;
				    }
				    else if (nrt-pv>0.0001&&nrt>pv){
				    	pv+=1;
				    }
				    pv=pv/100000;
				    nrt=nrt/100000;
				    if(pv==0&&nrt==0){
				    fprintf(puntero,"%s%d %s%d %.0f %.0f\n",PDist[w][i].tipo,PDist[w][i].ind,PDist[w][j].tipo,PDist[w][j].ind,pv,nrt);
					}
				    else if(pv==nrt){
				        fprintf(puntero,"%s%d %s%d %.5f %.5f\n",PDist[w][i].tipo,PDist[w][i].ind,PDist[w][j].tipo,PDist[w][j].ind,pv,nrt);
					}
					else{
						fprintf(puntero,"%s%d %s%d %.5f %.5f inestable\n",PDist[w][i].tipo,PDist[w][i].ind,PDist[w][j].tipo,PDist[w][j].ind,pv,nrt);
					}
				}
			}
		}
		fprintf(puntero,"\n");
		fprintf(puntero,"Zonas Conectadas:\n");
		h=0;
		for(i=0;i<CV[w];i++){
			for(j=0;j<CV[w];j++){
				Componentes[i][j]=0;
			}
		}
		CComponentes(Componentes,&CZC,CV,w);
		for(i=0;i<CV[w];i++){
			for(j=0;j<CV[w];j++){
				Componentes[i][j]-=1;
		    }
		}
		///VERIFICA QUE LAS COMPONENTES CONEXAS SEAN MAYOR QUE 1, YA QUE LAS IMPRIME POR SEPARADO
		if(CZC>1){
			for(j=0;j<CV[w];j++){
			    costo=0;
			    if(Componentes[0][j]>-1){
					fprintf(puntero,"Zona %d: Costo de la Zona %d:",h+1,h+1);
					///COSTO DE LA ZONAS
					for(k=0;k<CV[w]-1;k++){
						for(kk=k+1;kk<CV[w];kk++){
							if(Componentes[k+1][j]!=-1){
								costo+=VAdy[w].Ady[Componentes[k][j]][Componentes[kk][j]].costo;
							}
						}
					}
					fprintf(puntero," %d US$",costo);
					///DETERMINA FUNCIONALIDAD DE LAS ZONAS ESTABLES
					for(k=0;k<CV[w];k++){
						if(strcmp(PDist[w][Componentes[k][j]].nombre, "Planta")==0){
							fprintf(puntero," Funcional: SI\n");
							break;
						}
						else{
							fprintf(puntero," Funcional: NO\n");
							break;
						}
					}
					for(i=-1;i<CV[w]-1;i++){
						if(Componentes[i+1][j]>-1){
							if(strncmp(PDist[w][Componentes[i+1][j]].nombre, "Planta",6)==0||strncmp(PDist[w][Componentes[i+1][j]].nombre, "Punto",5)==0){
								fprintf(puntero,"%s%d: %s%d\n",PDist[w][Componentes[i+1][j]].tipo,PDist[w][Componentes[i+1][j]].ind,PDist[w][Componentes[i+1][j]].nombre,PDist[w][Componentes[i+1][j]].ind);
							}
							if(strncmp(PDist[w][Componentes[i+1][j]].nombre, "Planta",6)!=0&&strncmp(PDist[w][Componentes[i+1][j]].nombre, "Punto",5)!=0){
								fprintf(puntero,"%s%d: %s\n",PDist[w][Componentes[i+1][j]].tipo,PDist[w][Componentes[i+1][j]].ind,PDist[w][Componentes[i+1][j]].nombre,PDist[w][Componentes[i+1][j]].ind);
							}
						}
					}
				}
				if(Componentes[0][j+1]>-1){
                    	h+=1;
				}
			}
		}///SI COMPONENTES CONEXAS, ENTONCES SON IGUAL A CERO Ó IGUALES A UNO, ASI QUE PARA LOS DOS CASOS SE CUMPLE
		else{
    		fprintf(puntero,"Todos los componentes quedaron conectados.\n");
			fprintf(puntero,"Costo del Sistema de Gaseoductos: ");
			///COSTO DE LA ZONA COMPLETA
			costo=0;
			for(j=0;j<CV[w];j++){
				if(Componentes[0][j]>-1){
					for(k=0;k<CV[w]-1;k++){
						for(kk=k+1;kk<CV[w];kk++){
							if(Componentes[k+1][j]>-1&&VAdy[w].Ady[Componentes[k][j]][Componentes[kk][j]].est==1){
								costo+=VAdy[w].Ady[Componentes[k][j]][Componentes[kk][j]].costo;
							}
						}
					}
				}
			}
			fprintf(puntero,"%d US$",costo);
		}
		fprintf(puntero,"\n\n");
        i=0;
    	band=0;
        while(band==0){
    	    if(VeCo[w].VC[i][0].tipo[0]=='P'||VeCo[w].VC[i][0].tipo[0]=='D'||VeCo[w].VC[i][0].tipo[0]=='C'){
				for(l=0;l<CV[w+1];l++){
					sol_parcial[l]=-1;
				}
    	    	strcpy(ID1,VeCo[w].VC[i][0].tipo);
    	    	i1=VeCo[w].VC[i][0].ind;
    	        strcpy(ID2,VeCo[w].VC[i][1].tipo);
    	        i2=VeCo[w].VC[i][1].ind;
    		    CCAM(Cam,w,CV,VAdy);
                sol_enc=0;
                Camino_Finder(ID1,ID2,i1,i2,&sol_enc,Cam,sol_parcial,PDist,CV,w,TUS);
				if(sol_enc==1){
                    m=0;
                    TUS=0;
                    costo=0;                                
                    for(k=1;k<CV[w];k++){
                    	if(sol_parcial[k]>-1&&strcmp(PDist[w][sol_parcial[k-1]].tipo, ID2)!=0){
							if(VAdy[w].Ady[sol_parcial[k-1]][sol_parcial[k]].trans==1){
						    	costo+=20000;
							}
							if(VAdy[w].Ady[sol_parcial[k-1]][sol_parcial[k]].temp<=0){
						    	costo+=15000;
							}
							if(0<VAdy[w].Ady[sol_parcial[k-1]][sol_parcial[k]].temp&&VAdy[w].Ady[sol_parcial[k-1]][sol_parcial[k]].temp<30){
								costo+=10000;
							}
							if(30<=VAdy[w].Ady[sol_parcial[k-1]][sol_parcial[k]].temp&&VAdy[w].Ady[sol_parcial[k-1]][sol_parcial[k]].temp<=45){
								costo+=20000;
							}
						}
					}
                    fprintf(puntero,"Camino del Gas desde %s%d hasta %s%d Costo de la Linea de Distribución: %d US$\n",ID1,i1,ID2,i2,costo);
                    for(k=0;k<CV[w];k++){
					    if(sol_parcial[k]>-1&&strcmp(PDist[w][sol_parcial[k-1]].tipo, ID2)!=0){
					    	if(strncmp(PDist[w][sol_parcial[k]].nombre, "Planta",6)==0||strncmp(PDist[w][sol_parcial[k]].nombre, "Punto",5)==0){
					            fprintf(puntero,"%s%d: %s%d",PDist[w][sol_parcial[k]].tipo,PDist[w][sol_parcial[k]].ind,PDist[w][sol_parcial[k]].nombre,PDist[w][sol_parcial[k]].ind);
						    }
						    else if(strncmp(PDist[w][sol_parcial[k]].nombre, "Planta",6)!=0&&strncmp(PDist[w][sol_parcial[k]].nombre, "Punto",5)!=0){
					           fprintf(puntero,"%s%d: %s",PDist[w][sol_parcial[k]].tipo,PDist[w][sol_parcial[k]].ind,PDist[w][sol_parcial[k]].nombre);
						    }
					    }
			            if(sol_parcial[k]>-1&&sol_parcial[k+1]>-1){
			            	fprintf(puntero," - ");
			            }
					}
				}
				else{
					fprintf(puntero,"No es posible que fluya gas desde %s%d hasta %s%d",ID1,i1,ID2,i2);
				}
				fprintf(puntero,"\n\n");
                i+=1;
			}
			else{
				band=1;
			}
		}
			fprintf(puntero,"\n");
	}
	fclose(puntero);
}

/// CUERPO PRINCIPAL DEL CODIGO DEL SISTEMA DE ADMINISTRACION DE GAZPROM CORPORATION DONDE SE HACEN LAS LLAMADAS DE LOS PROCEDIMIENTOS Y FUNCIONES ANTERIORMENTE NOMBRADAS
main(){
	///FORMA PARTE DE LA VARIABLES GLOBALES
    int Cam[MAX][MAX],sol_parcial[MAX],TUS;
	int op,i,j;
	int ctrl;
	initscr();
	ctrl=0;
	///PRESENTACION DE BIENVENIDA    
	///pres();	
	///erase();
	///echo();
	do{
		echo();
		///MENU PRINCIPAL DEL SISTEMA DE ADMINISTRACION DE GAZPROM CORPORATION
	    menu(&op);
	    switch(op){
	        case 1:{
	            if(ctrl==0){
	                Gasoducin(PDist,VAdy,CV,VeCo,&CPM);
	                ERROR(7);
	                ctrl=1;
			    }
			    else{
			    	erase();
			    	ERROR(4);
				}
	    	}break;
	    	case 2:{
	            if(ctrl==1){
	                MODIFICA(CPM,CV,PDist,VAdy);
				}
				else{
			    	erase();
			    	ERROR(5);
				}
	    	}break;
	    	case 3:{
                if(ctrl==1){
                    NUEVO(&CPM,CV,PDist,VAdy);
				}
				else{
			    	erase();
			    	ERROR(5);
				}
	    	}break;
	    	case 4:{
	    	    if(ctrl==1){
	    	        MEstabilidad(VAdy,CV,CPM,PDist);
				}
				else{
			    	erase();
			    	ERROR(5);
				}
	    	}break;
	    	case 5:{
                if(ctrl==1){
					Estabilidad(VAdy,CV,CPM,PDist);
	    	        Zonas_Funcionales(CV,VAdy,PDist,CPM);
				}
				else{
			    	erase();
			    	ERROR(5);
				}
	        }break;
	    	case 6:{
                if(ctrl==1){
					Estabilidad(VAdy,CV,CPM,PDist);
	    	        Costo(CV,VAdy,PDist,CPM);
				}
				else{
			    	erase();
			    	ERROR(5);
				}
	    	}break;
	    	case 7:{
	    	    if(ctrl==1){
	    	    	erase();
	    	    	mm();
	   			    Estabilidad(VAdy,CV,CPM,PDist);
	                Consultas(PDist,sol_parcial,TUS,VeCo,CV,VAdy,Cam);
				}
				else{
					erase();
					ERROR(5);
				}
	    	}break;
	    	case 8:{
	    		for(i=30;i<90;i++){
	    			for(j=14;j<28;j++){
	    				mvaddch(j,i,' ');
					}
				}
	        	mvaddstr(15,38,"Sistema de Administracion GAZPROM CORPORATION");
	            mvaddstr(18,33,"Este Proyecto esta bajo licencia GNU GPLv2");
	            mvaddstr(19,33,"Fué Desarrollado en C con NCurses en Ubuntu 8.04");
	            mvaddstr(21,43,".:: FACYT - COMPUTACION 2007-2008 ::.");
	            mvaddstr(23,33,"Prof. Johana Guerrero");
	            mvaddstr(24,33,"Desarrolladores: Osval Reyes           <ojr2>");
	            mvaddstr(25,50,"Manuel Pinto          <Er_Galactico>");
	            mvaddstr(26,50,"Samantha Borjas       <Samy>");
	            for(i=30;i<90;i++){
	                mvaddch(14,i,ACS_HLINE);
	                mvaddch(16,i,ACS_HLINE);
	                mvaddch(28,i,ACS_HLINE);
	            }
	            for(i=14;i<28;i++){
	                mvaddch(i,30,ACS_VLINE);
	            	mvaddch(i,90,ACS_VLINE);
	            }
	            mvaddch(14,30,ACS_ULCORNER);
	            mvaddch(14,90,ACS_URCORNER);
	            mvaddch(28,30,ACS_LLCORNER);
	            mvaddch(28,90,ACS_LRCORNER);
	            mvaddch(16,30,ACS_LTEE);
	            mvaddch(16,90,ACS_RTEE);
	            noecho();
	            curs_set(0);
	            refresh();
	            sleep(8);
	            echo();
	    	}break;
	    	case 9:{
	    		Estabilidad(VAdy,CV,CPM,PDist);
	    		Gasoducout(VAdy,CV,CPM,PDist,VeCo);
	            endwin();
	            exit(0);
	        }break;
	    }
    }while(1<2);
}
