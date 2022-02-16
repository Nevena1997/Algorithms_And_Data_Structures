#include<iostream>
#include<vector>
#include<algorithm>


using namespace std;

int brojParticija(int n, int smax, vector<vector<int>>& memo) {
    cout << n << " " << smax << endl;
    if (memo[n][smax] != -1)
        return memo[n][smax];
    if (n == 0) return memo[n][smax] = 1;
    if (smax == 0) return memo[n][smax] = 0;

    int broj = brojParticija(n, smax-1, memo);
    if (n >= smax)
        broj += brojParticija(n-smax, smax, memo);

    return memo[n][smax] = broj;
}

int brojParticija(int n) {
    vector<vector<int>> memo(n + 1);
    for (int i = 0; i <= n; i++)
        memo[i].resize(n+1, -1);
    int broj = brojParticija(n, n, memo);

    for(int i = 0; i < n + 1; i++) {
        for(int j = 0; j < n + 1; j++) {
            cout << memo[i][j] << " ";
        }
        cout << endl;
    }

    return broj;
}

int main() {
    int broj = brojParticija(6);
    cout << "Broj particija je: " << broj << endl;
return 0;
}
