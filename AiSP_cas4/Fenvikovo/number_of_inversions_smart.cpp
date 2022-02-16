#include <iostream>
#include <vector>
#include <algorithm>

// Funkcija pomocu koje dodajemo element u stablo. Dodajemo element na odgovaraucem indeksu, i uvecavamo vrednosti svih cvorova na koje on utice
void add_to_tree(std::vector<int> &fenwick_tree, int n, int index, int value)
{
  // Uvecavamo indeks za 1 jer nam u stablu indeksiranje krece od 1, a u pocetnom nizu od 0
  index++;

  // Krecemo se dok ne dodjemo do poslednjeg cvora stabla, tj kraja niza
  while (index <= n) {
    // Odgovarajuci cvor uvecavamo
    fenwick_tree[index] += value;

    // Pomeramo indeks na sledecu vrednost indeksa na koju utice promena prethodne vrednosti
    index += index & -index;
  }
}

// Ova funkcija racuna sumu svih vrednosti [0, index - 1)
int sum_to_index(std::vector<int> &fenwick_tree, int index)
{
  int sum = 0;

  // Krecemo se uz stablo tj kroz nizs
  while (index > 0) {
    // Dodajemo na sumu odgovarajuci element
    sum += fenwick_tree[index];
    // Pomeramo indeks na odgovarajuci nacin
    index -= index & -index;
  }

  return sum;
}

// Funkcija convert ce od niza elemenata napraviti niz indeksa. Ako smo imali niz { 1, -5, 6, 2 } on ce postati { 2, 1, 4, 3 }
void convert(std::vector<int> &array, int n)
{
  // Uzimamo pomocni niz u koji smestamo nas niz
  std::vector<int> pom(array.begin(), array.end());

  // Sortiramo niz rastuce
  /********* C++ deo *********/
  // Funkcija std::sort sortira kolekciju elemenata, a kao argumente dobija pocetak, kraj kolekcije i eventualno funkciju bool compare(<T> el1, <T> el2) gde <T> predstavlja bilo koji tip
  // Ukoliko je prosledjena funkcija ona se koristi za sortiranje inace je sortiranje po default-u u rastucem poretku
  std::sort(pom.begin(), pom.end());

  // Krecemo se kroz niz elemenata i dodeljujemo odgovarajuci indeks elementu
  /********* C++ deo *********/
  // Funkcija std::lower_bound() prima pocetak kolekcije, kraj kolekcije, i jedan element. Kao rezultat vraca pokazivac na prvi element koji nije manji (veci ili jednak) datom elementu
  // Za nase potrebe mi dobijamo pokazivac na element array[i] u sortiranom nizu, a nakon toga pomocu std::distance trazimo koliko je on daleko od pocetka
  // Funkcija std::distance() vraca udaljenost elementa iz kolekcije od pocetka kolekcije. Kao argumente dobija iterator na pocetak (begin()) i iterator (pokazivac) na element za koji
  // se trazi udaljenost (kod nas povratna vrednost funkcije std::lower_bound()). Dodajemo 1, jer ako je nas element na pocetku kolekcije std::distance vraca 0, a mi indeksiranje zelimo
  // od 1.
  for (int i = 0; i < n; i++) {
    array[i] = std::distance(pom.begin(), std::lower_bound(pom.begin(), pom.end(), array[i])) + 1;
  }
}

int main ()
{
  std::vector<int> array = { 7, -90, 100, 1 };

  //U ovom zadatku su nebitne konkretne vrednost elemenata u nizu, bitan je njihov odnos
  //Zato cemo svaki element niza zameniti njegovom pozicijom u sortiranom nizu
  //Ukoliko postoji vise istih elemenata, svaki zamenjujemo prvom pozicijom na kojoj se taj element pojavljuje u sortiranom nizu
  //Npr: niz je [3, 5, 6, 1, 10] sortirani niz je [1, 3, 5, 6, 10]
  //Posle zamene dobijamo niz [2, 3, 4, 1, 5] (3 se javlja na 2. mestu u sortiranom nizu, 5 na 3. ... )
  //Nadalje posmatramo niz [2, 3, 4, 1, 5]

  //Zadatak mozemo resiti na 2.nacina koristeci Fenvikovo stablo

  //1.Obilazimo niz sa leve strane i obradjujemo element po element
  //U nizu cije vrednosti cuva Fenvikovo stablo cemo beleziti frekvencije pojavljivanja nekog elementa na nekoj poziciji
  //Npr. ukoliko obradjujemo element 4, u nizu koje se cuva u Fenvikovom stablu se nalaze sledece vrednosti [0, 1, 1, 0, 0] jer smo za sada obradili samo elemente 2 i 3
  //Posto trazimo broj parova (a,b) takvih da je a > b, u slucaju kada obradjujemo element 4, trazimo broj elemenata koji su do sada obradjeni
  //a koji su strogo veci od 4 ( (a, 4) gde je a > 4) )
  //To cemo dobiti kao sumu segmenta (4, 5] jer je u ovom slucaju 5 maksimalna pozicija
  //Tu vrednost mozemo dobiti iz Fenvikovog stabla
  //Ona ce se izracunati kao razlika vrednosti dobijene pozivanjem funckije sum za segmente (0, 3] i (0, 5]
  //U opstem slucaju, ukoliko obradjujemo element k
  //Broj inverzija u kojima element k ucestvuje kao druga vrednost (_, k) jeste broj elemenata koji su do sada obradjeni i koji su strogo veci od k
  //A taj broj dobijamo kao sumu elemenata segmenta (k, max_position]


  //2.Obilazimo niz sa desne strane i obradjujemo element po element
  //Sada trazimo broj elemenata koji su do sada obradjeni, a koji su strogo manji od trenutnog elementa koji obradjujemo
  //U opstem slucaju, ukoliko obradjujemo element k
  //Broj inverzija u kojima element k ucestvuje kao prva vrednost (k, _) jeste broj elemenata koji su do sada obradjeni i koji su strogo manji od k
  //A taj broj dobijamo kao sumu elemenata segmena (0, k - 1]
  //Ova metoda je malo efikasnija jer samo jednom pozivamo funckiju za racunanje sume segmenta oblika (0, a]
  //U prvom slucaju smo pozivali 2 puta


  //Ovde je prikazana implementacija 2.nacina
  int n = array.size();

  int max = *std::max_element(array.begin(), array.end());

  std::vector<int> fenwick_tree(n + 1);

  std::fill(fenwick_tree.begin(), fenwick_tree.end(), 0);

  int result = 0;

  convert(array, n);

  //Niz obradjujemo sa desne strane
  for (int i = n - 1; i >= 0; i--) {
    result += sum_to_index(fenwick_tree, array[i]);

    add_to_tree(fenwick_tree, n, array[i] - 1, 1);
  }

  std::cout << result << std::endl;

  return 0;
}
