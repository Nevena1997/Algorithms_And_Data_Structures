#include <iostream>
#include <vector>
#include <cmath>

void build_segment_tree(std::vector<int> &array, std::vector<int> &segment_tree, int k, int x, int y)
{
    if (x == y) {
        if (array[x] % 2 == 0)
                segment_tree[k] = 1;
            else
                segment_tree[k] = 0;
            return ;
    }

    int middle = (x + y) / 2;

    build_segment_tree(array, segment_tree, 2 * k + 1, x, middle);
    build_segment_tree(array, segment_tree, 2 * k + 2, middle + 1, y);

    segment_tree[k] = segment_tree[2 * k + 1] + segment_tree[2 * k + 2];
}

int count_even_elements(std::vector<int> &segment_tree, int x, int y, int a, int b, int k)
{
    if (x > b || y < a)
        return 0;

    if (x >= a && y <= b)
        return segment_tree[k];

    int middle = (x + y) / 2;

    return count_even_elements(segment_tree, x, middle, a, b, 2 * k + 1) + count_even_elements(segment_tree, middle + 1, y, a, b, 2 * k + 2);
}

int main ()
{
    std::vector<int> array = { 1, 2, 3, 4, 5, 6, 7, 8 };

    int n = array.size();

    int height = ceil(log2(n));

    n = pow(2, height);

    array.resize(n);

    //Zelimo da koren bude na poziciji 0 pa ce nam trebati 2 * n - 1 element u segmentnom stablu
    std::vector<int> segment_tree(2 * n - 1);

    //Formiramo segmentno stablo tako da se koren nalazi na poziciji 0
    //Elemente niza cemo zameniti vrednostima 1 ukoliko je element paran, 0 ukoliko je element neparan
    build_segment_tree(array, segment_tree, 0, 0 , n - 1);

    for (int x : segment_tree)
        std::cout << x << " ";

    std::cout << "\n";

    int a, b;

   //Ucitavamo segment [a, b] ciju sumu zelimo da izracunamo
   //Pretpostavljamo da su unete vrednosti validne
    std::cin >> a >> b;

    //Racunamo i ispisujemo sumu niza na segmentu [a,b]
    //Funkcija je ista kao i funkcija sum_of_range jer smo niz uredili tako da 1 oznacava da je element paran, a 0 da je neparan,
    //pa ce obicno sumiranje niza da nam da informaciju koliko je parnih elemenata u nekom segmentu
    std::cout << count_even_elements(segment_tree, 0, n - 1, a, b, 0) << "\n";

    return 0;
}
