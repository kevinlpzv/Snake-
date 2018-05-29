/*  CIENCIAS DE LA COMPUTACIÓN
        Kevin López Venegas 306007
        Daniel Benavides Acosta 317652
Profesor:Raymundo Cornejo Garcia */

#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <ctime>
#include <fstream>
#include <stdexcept>
/**
*@def ARRIBA 72, IZQUIERDA 75, DERECHA 77, ABAJO 80, ESC 27
*@brief Se definen las flechas del teclado en base a la orientacion correcta
                      */
#define ARRIBA 72
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80
#define ESC 27

using namespace std;

int cuerpo[200][2],dif=0;
int n=1,tam=3,x=10,y=12,dir=3,xc=30,yc=15,puntos=0 ;
char tecla;
char  nombre[20];
/**
*@fn gotoxy
*@brief Funcion utilizada para posicionar el cursor, @param "x" y @param "y" son para asignar las coordenadas
o posicionamiento del cursor; todo esto con ayuda de el HANDLE y COORD que son manejadores que estan definidas
en la libreria windows.h.
*/
void gotoxy(int x, int y);
/**
*@fn pared
*@brief mediante un ciclo realizamos las paredes horizontales y verticales; mediante la @var i se controla la longitud
de la pared tanto vartical como horizontal con ayuda de la funcion @see gotoxy para posicionar el cursor
en el lugar donde se desea imprimir los caracteres que limitaran las paredes.
Para colocar las esquinas de nuestras paredes no requerimos de ningun ciclo, ya que solo utilizando los caracteres necesarios
y con @see gotoxy los posicionamos en donde son necesarios.
*/
void pared();
/**
*@fn guardar_posicion
*@brief La funcion tiene como objetivo ir guardando la posicion del cuerpo inicial de la  viborita que es de tamaño dos; esto
con un arreglo llamado cuerpo en el cual se le asigna los valores de tal en las @var "x" y "y" para el posicionamiento del cursor
de manera que vaya guardando el cuerpo de la viborita haciendo que se mueva; usamos un condicional if para reiniciar el tamaño de
la viborita y no guarde la posicion anterior y no cresca sola en @see dibujar_cuerpo.
*/
void guardar_posicion();
/**
*@fn dibujar_cuerpo
*@brief La funcion se encargade dibujar el cuerpo de la viborita con un ciclo for con el cual se controla el tamaño de manera que
 no creesca de mas al dibujarse los caracteres que conforman el cuerpo.
*/
void dibujar_cuerpo();
/**
*@fn borrar_cuerpo
*@brief Aqui se borra el caracter que conforma el cuerpo de la viborita evitando dejar un rastro de ella misma.
*/
void borrar_cuerpo();
/**
*@fn teclear
*@brief La funcion se encarga de que las teclas de direccion sean las correctas y que al presionarlas se cumpla lo esperado.
Esto se controla mediante un condicional if y un switch. El condicional if verifica con el kbhit que se presione una tecla, una
vez que verifica que si se presiono, la variable @var tecla se declara como de tipo getch() que se encarga de leer caracter a
caracter leido del teclado sin mostrarlo en pantalla. Luego en el switch se evalua la variable @var tecla para los casos ya sea
ARRIBA, ABAJO, DERECHA O ABAJO, donde en cada uno tiene un if que su funcionalidad es evitar que si se va para ARRIBA no se permita
la interaccion de ABAJO asi como DERECHA e IZQUIERDA ya que seria @see chocar con ella misma y es manera de perder.
*/
void teclear();
/**
*@fn comida
*@brief Aqui es donde la comida aparece dentro del juego que da la puntuacion y ayuda a crecer a la viborita.
Primero se usa srand(time(NULL)) que es para que aparesca comida en un lugar aleatorio dentro del area de juego
para controlar que aparesca dentro del area de juego se emplea el uso de un condicional if que verifica que las coordenadas
de la comida @var "xc" y "yc" sean igual a las coordenadas @var "x" y "y" si esto se cumple se le asigna a "xc" y "yc"
un generador random con el posicionamiento de 4 a 55 y de 4 a 18 que es el rango de cordenadas que estan dentro del area de juego.
Cada vez que coma @var tam aumentara en 1 y ala vez @var puntos se le sumara 2; seguido con @see gotoxy con @param "xc" y "yc"
imprimen el caracter elegido para la comida en el lugar que de srand cada que coma una.
*/
void comida();
/**
*@fn choque.
*@brief Esta funcion de tipo booleano se usa para evaluar si es que la viborita choca con una pared o consigo misma.
usando un condicional if que evalua que si @var "x" o "y"  es igual a la posicion donde estan las paredes que tienen
las coordenadas 3,23,2,60 y @return false. si no es el caso entonces con un ciclo for se verifica con las coordenadas
de @see guardar_posicion, @see dibujar_posicion y @see borrar_posicion que tam-1 hasta que j>0 a j se le restara 1
asi que cuando cuerpo sea igual que @var "x" o igual a @var "y" que @return false.
*@return true.
*/
bool choque();
/**
*@fn puntaje.
*@brief Con ayuda de @see gotoxy se mostrara la puntuacion del jugador dependiendo de @see comida, apareciendo en
las coordenadas 3,1.
*/
void puntaje();
/**
*@fn jugador.
*@brief En esta funcion el jugador tendra la oportunidad de poner el nombre guste una vez terminada su partida.
*/
void jugador();
/**
*@fn jugador_puntuacion.
*@brief Crea y abre un archivo en el cual se guardaran el nombre y puntuacion del jugador.
*@param titulo crea un arreglo de tipo char de 30 caracteres.
*/
char jugador_puntuacion(char titulo[30]);
/**
*@fn menu.
*@brief Despliega y muestra en pantalla el menu donde tu seleccionas la opcion que deseas elegir
y con el switch evaluando @var opcion eliges entre juego nuevo o ver las puntuaciones de los jugadores.
*/
int menu();
/**
*@fn dificultad.
*@brief se elige el nivel de dificultad que gustar jugar esto es en base a que tan rapido quieres que vaya la viborita
mostrando en pantalla cual nivel deseas elegir y mediante el swicth se selecciona editando @var dif que disminuye el sleep
que su funcion es ponerle un retardo a el movimiento de la viborita; despues se ejecuta @see juego lo que te manda directo
al juego.
*/
int dificultad();
/**
*@fn records.
*@brief Se usa para poder abrir y leer el archivo en donde se encuentran las puntuaciones de los jugadores que se creo
@see jugador_puntuacion; se emplea el uso de un if y un while con excepciones para verificar que el archivo se abra y
que se muestre lo que contiene de lo contrario mostrara un mensaje de error archivo no se pudo abrir. Si tiene exito
mostrara los jugadores y sus puntuaciones.
*/
int records();
/**
*@fn juego.
*@brief Dentro de esta funciones se mandan a llamar las demas funciones requeridas para correr el juego. Primero se
usa @see pared para que se dibuje el mapa asi como tambien @see gotoxy con @param "xc"y"yc" para generar la primer comida.
Luego mediant un while que evalua que mientras @var tecla sea diferent de @def ESC y no se cumpla @see choque se llamaran
a ejecutar @see borrar_cuerpo, @see guardar_posicion, @see dibujar_cuerpo, @see comida, @see puntuaje, @see teclear, y
las condiones if que asignan que @var dir igual a 1 y se mueva hacia ABAJO, @var dir igual a 2 se mueva hacia ARRIBA,
@var dir igual a 3 se mueva hacia la DERECHA, @var dir igual a 4 se mueva hacia la IZQUIEDA cada uno con su respectivo sleep
para que tengan una velocidad constante almenos que se modifique en la @see dificultad. Cuando terminar el juego o se cumplen
las condiciones del while se llama @see jugador y @see jugador_puntuacion y al final el @see menu para si el usuario quiero jugar de nuevo o ver los puntuajes.
*/
int juego();

int main()
	{try{
	    menu();





	}catch(bad_exception &e){
        cerr<<"Error,file is couldn't open"<<e.what()<<endl;
    }
    return 0;
	}

 void gotoxy(int x, int y) // posicion del cursor
{
    HANDLE hCon;
    COORD Pos;

    Pos.X = x;
    Pos.Y = y;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hCon,Pos);
}
void pared()
{
    int i;
	for(i=2;i<60;i++)//horizontal
		{
	 		gotoxy(i,3);cout<<(char)205<<endl;
            gotoxy(i,23);cout<<(char)205<<endl;
		}

	for(i=4;i<23;i++)//vertical
		{
	 		gotoxy(2,i);cout<<(char)186<<endl;
	 		gotoxy(60,i);cout<<(char)186<<endl;
		}
	//esquinas
	gotoxy(2,3);cout<<(char)201<<endl;
    gotoxy(2,23);cout<<(char)200<<endl;
	gotoxy(60,3);cout<<(char)187<<endl;
	gotoxy(60,23);cout<<(char)188<<endl;

}
void guardar_posicion()
{
	cuerpo[n][0]=x;
	cuerpo[n][1]=y;
    n++;
	if(n==tam)n=1;
}
void dibujar_cuerpo()
{
	int i;
	for(i=1;i<tam;i++)
		{
			gotoxy(cuerpo[i][0],cuerpo[i][1]);
			cout<<(char)254<<endl;
		}
}
void borrar_cuerpo()
{
	gotoxy(cuerpo[n][0],cuerpo[n][1]);
	cout<<" "<<endl;
}
void teclear()
{
	if(kbhit())
	{
		tecla=getch();
	    switch(tecla)
		{
			case ARRIBA:
			    if(dir!=2)
				dir=1;break;
			case ABAJO:
				if(dir!=1)
				dir=2;break;
			case DERECHA:
				if(dir!=4)
				dir=3;break;
			case IZQUIERDA:
				if(dir!=3)
				dir=4;break;
		}
	}

}
void comida()
{
    srand(time(NULL));
	if(x==xc && y==yc)
	{
		xc=(rand()%55)+4;
		yc=(rand()%18)+4;
		tam++;
		puntos+=2;
		gotoxy(xc,yc);cout<<(char)248<<endl;
	}
}
bool choque()
{int j;
	if(y==3 || y==23 || x==2 || x==60)return false;
	for(j=tam-1;j>0;j--)
	{
		if(cuerpo[j][0]==x && cuerpo[j][1]==y)
		return false;
	}
	return true;
}
void puntaje()
{
	gotoxy(3,1);cout<<"Puntaje:"<<" "<<puntos<<endl;
}
void jugador ()
{
 	gotoxy(4,2);cout<<"Nombre:";
	 cin>>nombre;
}
char jugador_puntuacion(char titulo[30])
{
	FILE *arch;
	arch = fopen(titulo,"at");
	if(arch!=NULL)
	{
		fprintf(arch,"Jugador: %s \t Puntaje:  %i  \n",nombre,puntos);
	}
	fclose(arch);

}
int menu(){
    int opcion=0;
    cout<<"\n\t^^MENU^^"<<endl;
    cout<<"\t1:Juego nuevo"<<endl;
    cout<<"\t2:Puntuajes"<<endl;
    cin>>opcion;
    switch(opcion){
        case 1:dificultad();break;
        case 2:records();break;
        default:cout<<"JULISSA CAMATE PO FAVO"; menu();break;
    }
}
int juego(){


            system("cls");
            pared();
            gotoxy(xc,yc);cout<<(char)248<<endl;
            while(tecla!=ESC && choque() )
			{
		 		borrar_cuerpo();
 				guardar_posicion();
 				dibujar_cuerpo();


	 			comida();
	 			comida();
	 			comida();
                puntaje();
 				teclear();
 				teclear();

	 			if(dir==1)y--;
	 			Sleep(dif);
 				if(dir==2)y++;
 				Sleep(dif);
 				if(dir==3)x++;
 				if(dir==4)x--;
 		   		Sleep(dif-10);
 		    }
            jugador();
            jugador_puntuacion("puntuación.txt");
            pared();
            system("cls");
            menu();
}
int dificultad(){
    system("cls");
    int op=0;
    cout<<"\t^^Dificultad^^"<<endl;
    cout<<"\t1:Facil"<<endl;
    cout<<"\t2:Medio"<<endl;
    cout<<"\t3:Dificil"<<endl;
    cin>>op;
    switch(op){
    case 1: dif=30;juego();break;
    case 2: dif=20;juego();break;
    case 3: dif=12;juego();break;
    default:dificultad();break;
    }
}
int records(){
    system("cls");
    ifstream arch;
    string texto;
    //arch.exceptions(ifstream::badbit|ifstream::failbit);
    arch.open("puntuación.txt",ios::in);
    if(arch.is_open()){
       while(!arch.eof()){
        getline(arch,texto);
        cout<<texto<<endl;
        }

    }else
        throw "Error, file couldn´t open";
    system("pause");
    system("cls");
    return menu();
}
