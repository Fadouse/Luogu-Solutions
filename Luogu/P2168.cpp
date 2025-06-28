#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;

struct Node {
    ull w;
    int d;
};

struct Cmp {
    bool operator()(const Node &a, const Node &b) const {
        if (a.w != b.w) return a.w > b.w;
        return a.d > b.d;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<ull> w(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i];
    }
    if (n == 1) {
        cout << 0 << "\n" << 0 << "\n";
        return 0;
    }

    priority_queue<Node, vector<Node>, Cmp> pq;
    for (ull wi : w) {
        pq.push({wi, 0});
    }

    int r = (n - 1) % (k - 1);
    int delta = r == 0 ? 0 : (k - 1) - r; //创建虚拟叶子节点
    while (delta--) {
        pq.push({0ULL, 0});
    }

    ull total = 0;
    while (pq.size() > 1) {
        ull sumw = 0;
        int maxd = 0;
        for (int i = 0; i < k; i++) {
            auto nd = pq.top();
            pq.pop();
            sumw += nd.w;
            maxd = max(maxd, nd.d);
        }
        total += sumw;
        pq.push({sumw, maxd + 1});
    }

    int maxLen = pq.top().d;
    cout << total << "\n" << maxLen << "\n";
    return 0;
}
