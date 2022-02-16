#include <iostream>
#include <vector>
#include <cmath>


void build_segment_tree (std::vector<int> &array, std::vector<int> &segment_tree, int k, int x, int y)
{
    if (x == y) {
        segment_tree[k] = array[x];
        return;
    }

    int middle = (x + y) / 2;

    build_segment_tree(array, segment_tree, 2 * k, x, middle);
    build_segment_tree(array, segment_tree, 2 * k + 1, middle + 1, y);

    segment_tree[k] = segment_tree[2 * k] + segment_tree[2 * k + 1];
}

//Funkcija koja iterativno racuna sumu segmenta [a, b]
int sum_of_segment_iterative(std::vector<int> &segment_tree, int n, int a, int b)
{
    //Uvecavamo indekse a i b za n jer se element u pocetnom nizu na poziciji k sada nalazi na poziciji n + k u segmentnom stablu
    a += n;
    b += n;
    int sum = 0;

    while(a <= b) {
        //Kada je levi kraj desno dete cvora, moramo ga dodatni posebno
        //Cvor je desno dete ukoliko se nalazi na neparnoj poziciji jer smo koren smestili na poziciju 1, pa ce desno dete cvora na poziciji k biti na poziciji 2 * k + 1
        if(a % 2 == 1)
            sum += segment_tree[a++];
        //Kada je desni kraj levo dete cvora moramo ga dodatni posebno
        //Cvor je levo dete ukoliko se nalazi na parnoj poziciji jer smo koren smestili na poziciju 1, pa ce levo dete cvora na poziciji k biti na poziciji 2 * k
        if(b % 2 == 0)
            sum += segment_tree[b--];

        a /= 2;
        b /= 2;
    }

    return sum;
}

int main ()
{
    std::vector<int> array = { 1, 2, 3, 4, 5, 6, 7, 8 };

    int n = array.size();

    int height = ceil(log2(n));

    n = pow(2, height);

    array.resize(n);

    std::vector<int> segment_tree(2 * n);

    //Formiramo segmentno stablo tako da se koren nalazi na poziciji 1
    build_segment_tree(array, segment_tree, 1, 0 , n - 1);

    for (int x : segment_tree)
        std::cout << x << " ";

    std::cout << "\n";

    int a, b;

    //Ucitavamo segment [a, b] ciju sumu zelimo da izracunamo
    //Pretpostavljamo da su unete vrednosti validne
    std::cin >> a >> b;

    //Racunamo i ispisujemo sumu niza na segmentu [a,b]
    std::cout << sum_of_segment_iterative(segment_tree, n, a, b) << "\n";

    return 0;
}
