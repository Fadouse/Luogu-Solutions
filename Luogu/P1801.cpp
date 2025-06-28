#include <bits/stdc++.h>
using namespace std;



int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    cin >> m >> n;

    vector<long long> a(m);
    for (int i = 0; i < m; i++) {
        cin >> a[i];
    }

    vector<int> u(n);
    for (int j = 0; j < n; j++) {
        cin >> u[j];
    }

    priority_queue<long long> L;
    priority_queue<long long, vector<long long>, greater<long long>> R;

    int p = 0;      
    int getCnt = 0; 
    for (int i = 1; i <= m; i++) {
        long long x = a[i - 1];
        R.push(x);

        if (!L.empty() && R.top() < L.top()) {
            long long rmin = R.top(); R.pop();
            long long lmax = L.top(); L.pop();
            L.push(rmin);
            R.push(lmax);
        }

        while (p < n && u[p] == i) {
            getCnt++;

            long long v = R.top();
            R.pop();
            L.push(v);

            cout << L.top() << "\n";
            // 移向下一个 GET
            p++;
        }
    }

    return 0;
}
