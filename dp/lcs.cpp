#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string a, b;
    cout << "Podaj dwa napisy:\n";
    if (!(cin >> a >> b)) return 0;

    int n = a.size(), m = b.size();
    // dp[i][j] - dlugosc LCS dla prefiksow a[0..i-1] i b[0..j-1]
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (a[i - 1] == b[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    cout << "Dlugosc LCS: " << dp[n][m] << "\n";

    // Rekonstrukcja najdluzszego wspolnego podciagu
    string lcs;
    int i = n, j = m;
    while (i > 0 && j > 0) {
        if (a[i - 1] == b[j - 1]) {
            lcs.push_back(a[i - 1]);
            --i; --j;
        } else if (dp[i - 1][j] >= dp[i][j - 1]) {
            --i; // idziemy w gore
        } else {
            --j; // idziemy w lewo
        }
    }
    reverse(lcs.begin(), lcs.end());
    cout << "Najdluzszy wspolny podciag: " << lcs << "\n";

    return 0;
}
