>>>>>>>>>>>>>>>>>>>>>>>>>>>>> PROGRAM KONIK.C <<<<<<<<<<<<<<<<<<<<<<<<<<<<<
Na samym początku programu znajdują się tak zwane DANE EDYTOWALNE, czyli
wielkość szachownicy - N, początkowa pozycja dla konia względem osi X - X0,
początkowa pozycja konia względem osi Y - Y0. Są one dostępne do modyfikacji
jedynie tam.

Dla N<5 wyświetli się błąd związany z niemożliwością wyznaczenia trasy dla
szachownic o polu <5.

Dla X0, Y0 nie zawierających się w szachownicy (liczonej od 0 do N-1)
również wyświetli się błąd.

Dla X0, Y0, dla których nie istnieje możliwe przejście zostanie wyświetlona
pusta tablica o boku długości N. Udało mi się sprawdzić to dla N = 5, X0 = 1,
Y0 = 2, dla większych N program za długo myślał.

-- Działanie programu: -------------------------------------------------
Na początku funkcja SPRAWDZACZ sprawdza, czy podane wartości X0, oraz Y0
znajdują się w tablicy szachownicy, oraz czy N nie jest mniejsze od 5.
Gdy wszystko jest w porządku, funkcja zwraca wartość 1 i następuje
wyzerowanie tablicy pomocniczej o nazwie TABLICA, oraz wyzerowanie tablicy z
rozwiązaniem o nazwie ROZ. Obie te tablice mają wielkość N+4 na N+4.
Zerowanie tablic odbywa się za pomocą procedury zeruj_tab, która na początku
przypisuje wszystkim miejscom wartość 1, a potem środek wypełnia zerami tak,
że powstaje prostokąt zer otoczony z każdej strony dwiema jedynkami.

			11111111111
			11111111111
			11000000011
			11000000011
			11000000011
			11000000011
			11000000011
			11000000011
			11000000011
			11111111111
			11111111111

Następnie zostaje wywołana procedura SKOCZEK. Znajdują się w niej dwie
tablice DX, oraz DY, w których zapisane są możliwe ruchy odpowiednio dla
każdej z osi: X i Y.
Procedura ta sprawdza, czy dane miejsce jest wolne (wartość tablicy dla
danych x i y jest równa 0), a jeśli tak, przypisuje mu kolejną liczbę
całkowitą, poczynając od 1, a jeśli liczba przypisywana jest równa
kwadratowi N, przypisuje rozwiązanie z tablicy pomocniczej TAB do tablicy
globalnej ROZ (przy okazji przypisując współrzędne kolejnych liczb
naturalnych dwóm tablicom globalnym TAB_X i TAB_Y), uruchamia procedurę
RYSUJ, i z sukcesem kończy program.
W przypadku, gdy liczba jest mniejsza od N*N, następuje kolejne możliwe
przesunięcie po szachownicy z wykorzystaniem tablic DX i DY zaaplikowanych
do kolejnego stadium rekurencji procedury SKOCZEK. Po wykorzystaniu
wszystkich ośmiu możliwych ruchów i nieznalezieniu wolnego miejsca,
procedura przypisuje danej pozycji wartość 0.

Procedura RYSUJ korzysta w większości z procedur zawartych w programie
"wykres.c". Procedura DRAWAXES została o tyle zmieniona, że oznaczenia
kolejnych wielkości na tablicy zostały wydłużone z jednej strony (dla osi X
i osi Y o dodatnich wartościach), aby utworzyć szachownicę.
Pętla for dla liczb naturalnych od 1 do N*N-1 uruchamia procedurę
RYSUJDROGE dla danej liczby.

Procedura RYSUJDROGE najpierw za pomocą funkcji STRONA wyznacza początek i
koniec przedziału liczbowego względem osi X, w którym zawierać się będzie
wykres (linia prosta prowadząca z jednego punktu do drugiego).
Zmienna b jest tutaj wyrazem wolnym, tak jak w funkcji y = ax + b. Istnieją
cztery możliwe procedury rysujące: OPCJA1, OPCJA2, OPCJA3 i OPCJA4, które
zwracają x z współczynnikiem kierunkowym 2, 1/2, -1/2 lub -2, jako iż są to
jedyne możliwe współczynniki kierunkowe dla skoku konia.
Wyraz wolny b odpowiada za umiejscowienie funkcji tak, żeby pojawiła się w
danym przedziale w odpowiednim miejscu (tworzy to iluzję, jakby funkcja była
rysowana od jednego punktu do drugiego, gdy w rzeczywistości jest po prostu
ograniczona do danego przedziału).

W procedurze PlotGraph do x i f(x) zostało dodane 0.5, aby podnieść i
przesunąć wykres o 0.5 tworząc iluzję skoku ze środka pola w środek pola
(bez tego linie zaczynałyby się w dolnym lewym rogu każdego z kwadracików).

-- Informacje dodatkowe: -----------------------------------------------
Ze względu na brutalny algorytm problemu konia szachowego (możliwe, że
niskie osiągi mojego linuxa również nie pomagają) o ile dla N równego 5, 6,
czy 7 program kończy działanie błyskawicznie, o tyle dla N=8 muszę czekać
około 80 sekund, a czekanie na N=9 przerwałem po 30 minutach wrażeniem, że
marnuję czas.

Postanowiłem nie wysyłać skompilowanego programu, żeby wykluczyć możliwość
sfałszowania programu podstawieniem innego o tej samej nazwie.
===============================================================================
