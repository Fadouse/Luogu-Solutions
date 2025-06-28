#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n;
    double x[16], y[16];
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }
    
    // Calculate distances between points
    vector<vector<double>> dist(n + 1, vector<double>(n + 1, 0));
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
                // Point 0 is the origin (0,0)
                if (i == j) dist[i][j] = 0;
                else if (i == 0) dist[i][j] = sqrt(x[j-1] * x[j-1] + y[j-1] * y[j-1]);
                else dist[i][j] = sqrt(x[i-1] * x[i-1] + y[i-1] * y[i-1]);
            } else {
                dist[i][j] = sqrt(pow(x[i-1] - x[j-1], 2) + pow(y[i-1] - y[j-1], 2));
            }
        }
    }
    
    // DP state: dp[mask][last] = min distance to visit all points in mask, ending at point last
    vector<vector<double>> dp(1 << n, vector<double>(n + 1, 1e9));
    dp[0][0] = 0; // Start at origin
    
    for (int mask = 0; mask < (1 << n); mask++) {
        for (int last = 0; last <= n; last++) {
            if (dp[mask][last] >= 1e9) continue;
            
            for (int next = 1; next <= n; next++) {
                if (mask & (1 << (next - 1))) continue; // Already visited
                
                int new_mask = mask | (1 << (next - 1));
                dp[new_mask][next] = min(dp[new_mask][next], dp[mask][last] + dist[last][next]);
            }
        }
    }
    
    // Find minimum among all final states
    double ans = 1e9;
    for (int i = 1; i <= n; i++) {
        ans = min(ans, dp[(1 << n) - 1][i]);
    }
    
    cout << fixed << setprecision(2) << ans << endl;
    return 0;
}