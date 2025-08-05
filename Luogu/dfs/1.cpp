#include <bits/stdc++.h>
using namespace std;

void dfs(int idx, int n, long long curSum, bool picked,
         const vector<long long>& v, unordered_set<long long>& sums)
{
    if (idx == n) {
        if (picked) sums.insert(curSum);
        return;
    }
    dfs(idx + 1, n, curSum + v[idx], true, v, sums);
    dfs(idx + 1, n, curSum, picked, v, sums);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    (cin >> n);

    vector<long long> v(n);
    for (int i = 0; i < n; ++i) cin >> v[i];

    unordered_set<long long> sums;
    dfs(0, n, 0LL, false, v, sums);

    cout << sums.size() << '\n';
    return 0;
}
