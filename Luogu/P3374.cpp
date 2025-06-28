#include <bits/stdc++.h>

using namespace std;

class BIT {
private:
    vector<long long> tree;
    int n;
    
public:
    BIT(int size) {
        n = size;
        tree.assign(n + 1, 0);
    }
    
    void update(int pos, int val) {
        for (int i = pos; i <= n; i += i & (-i)) {
            tree[i] += val;
        }
    }
    
    long long query(int pos) {
        long long sum = 0;
        for (int i = pos; i > 0; i -= i & (-i)) {
            sum += tree[i];
        }
        return sum;
    }
    
    long long rangeQuery(int l, int r) {
        return query(r) - query(l - 1);
    }
};

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    
    int n, m;
    cin >> n >> m;
    
    BIT bit(n);
    
    for (int i = 1; i <= n; i++) {
        int val;
        cin >> val;
        bit.update(i, val);
    }
    
    for (int i = 0; i < m; i++) {
        int op;
        cin >> op;
        
        if (op == 1) {
            int x, k;
            cin >> x >> k;
            bit.update(x, k);
        } else {
            int x, y;
            cin >> x >> y;
            cout << bit.rangeQuery(x, y) << "\n";
        }
    }
    
    return 0;
}