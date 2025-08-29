#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, W;
    cout << "Podaj liczbe przedmiotow i pojemnosc plecaka: ";
    if (!(cin >> n >> W)) return 0;

    vector<int> w(n + 1), v(n + 1);
    for (int i = 1; i <= n; ++i) {
        cout << "Podaj wage i wartosc przedmiotu " << i << ": ";
        cin >> w[i] >> v[i];
    }

    // dp[i][j] - maksymalna wartosc dla pierwszych i przedmiotow
    // i pojemnosci plecaka j
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= W; ++j) {
            dp[i][j] = dp[i - 1][j];  // nie bierzemy i-tego przedmiotu
            if (w[i] <= j) {
                // bierzemy i-ty przedmiot
                dp[i][j] = max(dp[i][j], dp[i - 1][j - w[i]] + v[i]);
            }
        }
    }

    cout << "Maksymalna wartosc: " << dp[n][W] << "\n";

    // Rekonstrukcja rozwiazania
    vector<int> chosen;
    int j = W;
    for (int i = n; i >= 1; --i) {
        if (dp[i][j] != dp[i - 1][j]) {
            chosen.push_back(i); // przedmiot i jest w rozwiazaniu
            j -= w[i];
        }
    }
    reverse(chosen.begin(), chosen.end());

    cout << "Wybrane przedmioty (indeksy): ";
    for (int idx : chosen) cout << idx << ' ';
    cout << "\n";

    return 0;
}
