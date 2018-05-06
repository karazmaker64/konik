#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "postscript.h"

#define NN 200  /* liczba odcinkow */

/************************ DANE EDYTOWALNE ***************************/
/********************************************************************/
#define N 5 /*Liczba pól (Wielkość Szachownicy)*/		  /**/
#define X0 0 /*Początkowa pozycja konia dla osi x*/		  /**/
#define Y0 0 /*Początkowa pozycja konia dla osi y*/		  /**/
/********************************************************************/
/********************************************************************/

int roz[N+4][N+4]; /*Tablica globalna o 4 większa od wielkości szachownicy,
                      żeby wszystko działało */

struct {
    float ax, bx, ay, by;
  } map;

float tab_x[N*N]; /*Tablica współrzędnych x dla konia*/
float tab_y[N*N]; /*Tablica współrzędnych y dla konia*/


/* =================== PROCEDURY DLA KONIA ================= */

/*Procedura przygotowująca tablicę do pracy*/
void zeruj_tab (int tab[N+4][N+4])
{
    int i,j;
  	for (i=0;i<N+4;i++)
    		for (j=0;j<N+4;j++)
      			tab[i][j]=1; /*Wpisanie jedynek w tablicę*/
  	for (i=2;i<N+2;i++)
    		for (j=2;j<N+2;j++)
      			tab[i][j]=0; /*Wyzerowanie środka tablicy*/
} /*ZERUJ_TAB*/

/*Procedura wypisująca zawartość tablicy*/
void pisz_tab (int tab[N+4][N+4])
{
    int i,j;
    for (i=2; i<N+2; i++){
        for (j=2; j<N+2;j++) printf("%3d ", tab[i][j]);
        printf("\n");
    }
    printf("\n");
} /*PISZ_TAB*/

/*Procedura przypisująca wartości jednej tablicy do drugiej*/
void przypisz (int tab1[N+4][N+4], int tab2[N+4][N+4]){
  int i,j;
  
  for (i=2; i<N+2; i++)
    for (j=2; j<N+2; j++){
      tab1[i][j] = tab2[i][j];
      tab_x[tab1[i][j]] = i-2; /* Przy okazji przypisanie "współrzędnych x"
                                  tablicy tab_x */
      tab_y[tab1[i][j]] = j-2; /* Przy okazji przypisanie "współrzędnych y"
                                  tablicy tab_y */
      }
} /*PRZYPISZ*/

/* ===================================================== */


int strona (int n) {
  if (tab_x[n] < tab_x[n+1]) return 1;
  else return 0;
} /*STRONA*/


/* ///////////////// PROCEDURY RYSUJĄCE ///////////////////////// */

float opcja1 (float x)
{
  return 2*x;
} /*OPCJA1*/

float opcja2 (float x)
{
  return x/2;
} /*OPCJA2*/

float opcja3 (float x)
{
  return -x/2;
} /*OPCJA3*/

float opcja4 (float x)
{
  return -2*x;
} /*OPCJA4*/

/* ////////////////////////////////////////////////////////////////// */

void InitMapping ( float xmin, float xmax, float ymin, float ymax,
                   float ximin, float ximax, float etamin, float etamax )
{
  map.ax = (ximax-ximin)/(xmax-xmin);
  map.bx = ximin - map.ax*xmin;
  map.ay = (etamax-etamin)/(ymax-ymin);
  map.by = etamin - map.ay*ymin;
} /*InitMapping*/

float MapX ( float x )
{
  return map.ax*x + map.bx;
} /*MapX*/

float MapY ( float y )
{
  return map.ay*y + map.by;
} /*MapY*/

void DrawAxes ( float xmin, float xmax, float dx, float y0,
                float ymin, float ymax, float dy, float x0 )
{
  float xi0, xi1, xi, eta0, eta1, eta, x, y;

         /* rysuj os pozioma */
  xi0 = MapX ( xmin );
  xi1 = MapX ( xmax-1 );
  eta = MapY ( y0 );
  PSSetLineWidth ( 1.5 );
  PSDrawLine ( xi0, eta, xi1, eta );
  if ( dx > 0 ) {
    PSSetLineWidth ( 1.5 );
    x = x0;
    while ( x < xmax ) {
      xi = MapX ( x );
      PSDrawLine ( xi, eta-0.0, xi, eta+(N*((9-N/2)*100/1.5)));
      x = x + dx;
    }
    x = x0-dx;
    while ( x >= xmin ) {
      xi = MapX ( x );
      PSDrawLine ( xi, eta-0.0, xi, eta+0.0 );
      x = x - dx;
    }
  }
         /* rysuj os pionowa */
  eta0 = MapY ( ymin );
  eta1 = MapY ( ymax-1 );
  xi = MapX ( x0 );
  PSSetLineWidth ( 1.5 );
  PSDrawLine ( xi, eta0, xi, eta1 );
  if ( dy > 0 ) {
    PSSetLineWidth ( 1.5 );
    y = y0;
    while ( y < ymax ) {
      eta = MapY ( y );
      PSDrawLine ( xi-0.0, eta, xi+(N*((9-N/2)*100/1.5)), eta );
      y = y + dy;
    }
    y = y0 - dy;
    while ( y >= ymin ) {
      eta = MapY ( y );
      PSDrawLine ( xi-0.0, eta, xi+0.0, eta );
      y = y - dy;
    }
  }
} /*DrawAxes*/

void PlotGraph ( float xmin, float xmax, float (*f)(float x), float b )
{
  point p[NN+1];
  float dx, x;
  int   i;

  dx = (xmax-xmin)/NN;
  x = xmin;
  for ( i = 0; i <= NN; i++ ) {
    x = x + dx;
    p[i].x = MapX ( x +0.5 );
    p[i].y = MapY ( f ( x )+b+0.5 );
  }
  PSSetLineWidth ( 14.0 );
  PSDrawPolyline ( NN+1, p, 0 );
} /*PlotGraph*/


/* ============== PROCEDURY KONIOTWÓRCZE ============== */
void RysujDroge (int m)
{
  int n=0;
  int kon=0, pocz=0;
  float b=0;
  float xa,yb,xc;
  
  n=m;
  xa = tab_x[n+1]-tab_x[n];
  yb = tab_y[n+1]-tab_y[n];
  xc = xa;
    if (strona(n) == 1) {
      kon = tab_x[n+1];
      pocz = tab_x[n];
      }
    else {
      kon = tab_x[n];
      pocz = tab_x[n+1];
    }
    if ((xa < 0)&&(yb < 0)) {xa = -xa; yb = -yb;}
    if (tab_x[n+1]-tab_x[n] == 0) printf("\n\nUWAGA! BLAD DANYCH! DZIELENIE PRZEZ ZERO!\n\n");
    b = (tab_y[n]*tab_x[n+1] - tab_y[n+1]*tab_x[n])/xc;
    if ((yb == 2)&&(xa == 1)) PlotGraph(pocz,kon, opcja1, b);
    else {
      if ((yb == 1)&&(xa == 2)) PlotGraph(pocz,kon, opcja2, b);
      else {
        if (((yb == -1)&&(xa == 2))|((yb == 1)&&(xa == -2))) PlotGraph(pocz,kon, opcja3, b);
        else {
          if (((yb == -2)&&(xa == 1))|((yb == 2)&&(xa == -1))) PlotGraph(pocz,kon, opcja4, b);
          else printf ("Nie dziala\n");
        }
      }
    }
} /*RYSUJDROGE*/

/* Procedura rysująca jedynie pole o boku N, wykorzystywana, gdy program
  nie znajduje przejścia */
void rysuj_blad (void) {
PSOpenFile ( "wykres.ps", 600 );
  InitMapping ( 0.0, 1.5, 0.0, 1.5,
                100.0, (10-N/2)*100, 100.0, (10-N/2)*100 );
  DrawAxes ( 0.0, N+1, 1, 0.0, 0.0, N+1, 1, 0.0 );
  PSSetRGB ( 1.0, 0.0, 0.0 );

  PSCloseFile ();
} /*RYSUJBLAD*/

void rysuj (void) {
  int p;
  
  PSOpenFile ( "wykres.ps", 600 );
  InitMapping ( 0.0, 1.5, 0.0, 1.5,
                100.0, (10-N/2)*100, 100.0, (10-N/2)*100 );
  DrawAxes ( 0.0, N+1, 1, 0.0, 0.0, N+1, 1, 0.0 );
  PSSetRGB ( 1.0, 0.0, 0.0 );

  for (p=1; p<N*N; p++)
    RysujDroge(p);	/* Dla każdego kolejnego p naturalnego rysowany jest
                            jeden "skok" konia */
  PSCloseFile ();
} /*RYSUJ*/

/* Procedura poszukująca przejście konia z pozycji początkowej (x,y) */
void skoczek(int x,int y,int n,int tab[N+4][N+4])
{
  int dx[] = {2, 1, -1, -2, 2, 1, -1, -2}; /*tablica z ruchami dla współrzędnej x*/
  int dy[] = {1, 2, 2, 1, -1, -2, -2, -1}; /*tablica z ruchami dla współrzędnej y*/
  int k; /*Zmienna k obsługuje ruchy konia*/
  
  if (tab[x][y]==0)
    {
    tab[x][y]=n; /*Jeśli zostanie znalezione puste (zerowe miejsce), zostanie 
                    mu przypisana kolejna liczba całkowita*/
   	 if (n==N*N)
    	{
                przypisz(roz,tab); /*Przypisanie rozwiązania do tablicy globalnej*/
                rysuj();
		exit(0); /* Kończy program */

    	}
   	 else{
    		for (k=0; k<8; k++)
    		  skoczek(x+dx[k], y+dy[k], n+1,tab); /*Kolejne ruchy konia dla kolejnych
                                            wartości k*/
   		tab[x][y]=0; /*Pozycja zeruje się, gdy koń wyjdzie z pętli*/
	if (tab[X0+2][Y0+2] == 0) {printf("Dla danych X0, Y0 przejście nie istnieje\n"); rysuj_blad(); return;}
    	}
    }

} /*SKOCZEK*/

/* =============================================================== */

/* Funkcja sprawdza, czy miejsce startu zawiera się w tablicy, oraz
  czy tablica jest odpowiedniej wielkości, żeby istniała możliwość
  wyznaczenia trasy */
int sprawdzacz (int x, int y, int n)
{
  if ((x<0)|(x>n-1)|(y<0)|(y>n-1)|(n<5)) return 0;
  else return 1;
} /*SPRAWDZACZ*/

int main ()
{
  int tablica[N+4][N+4]; /*Tablica o 4 większa od ustalonej wielkości
                    szachownicy, aby zmieścić dodatkowy pas jedynek*/
  if (sprawdzacz(X0+2,Y0+2,N) == 1) {
    zeruj_tab(tablica); /*Zerujemy tablicę, z jedynkową otoczką*/
    zeruj_tab(roz); /* Tym razem zerujemy tablicę globalną */
    skoczek(X0+2,Y0+2,1,tablica); /*Wywołanie procedury SKOCZEK*/
  }
  else printf("Podane dane X0, Y0 lub N sa nieprawidlowe!\n");
} /*main*/
