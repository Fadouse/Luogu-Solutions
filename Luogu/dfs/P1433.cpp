#include <bits/stdc++.h>

using namespace std;

int n;
vector<pair<double, double>> cheeses;
double lens[15][15];
double dp[1 << 15][15];

double dfs(int mask, int idx) {
    if (mask == (1 << n) - 1) {
        return 0.0;
    }
       if (dp[mask][idx] != -1.0) {
        return dp[mask][idx];
    }
       double min_len = 1e18;
       for (int i = 0; i < n; ++i) {
                      if (!((mask >> i) & 1)) {
                       double new_len = lens[idx][i] + dfs(mask | (1 << i), i);
                       min_len = min(min_len, new_len);
        }
    }

       return dp[mask][idx] = min_len;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    cin >> n;
    cheeses.assign(n, {0, 0});
    for (auto &i : cheeses) {
        cin >> i.first >> i.second;
    }

       for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            double xl = cheeses[i].first - cheeses[j].first;
            double yl = cheeses[i].second - cheeses[j].second;
            double length = sqrt(xl * xl + yl * yl);
            lens[i][j] = length;
            lens[j][i] = length;
        }
    }

       for(int i = 0; i < (1 << n); ++i) {
        for(int j = 0; j < n; ++j) {
            dp[i][j] = -1.0;
        }
    }

    double result = 1e18;
       for (int i = 0; i < n; ++i) {
               double dist_from_origin = sqrt(cheeses[i].first * cheeses[i].first + cheeses[i].second * cheeses[i].second);
                             double current_path = dist_from_origin + dfs(1 << i, i);

               result = min(result, current_path);
    }

    std::cout << std::fixed << std::setprecision(2);
    cout << result << endl;

    return 0;
}