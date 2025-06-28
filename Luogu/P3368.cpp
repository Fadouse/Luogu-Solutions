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
    
    void update(int pos, long long val) {
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
};

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    
    vector<long long> a(n + 1);
    BIT bit(n + 1);  

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        bit.update(i, a[i] - a[i-1]);  // d[i] = a[i] - a[i-1]
    }
    
    while (m--) {
        int op;
        cin >> op;
        
        if (op == 1) {
            int x, y;
            long long k;
            cin >> x >> y >> k;

            bit.update(x, k);
            bit.update(y + 1, -k);
        } else {
            int x;
            cin >> x;
            cout << bit.query(x) << "\n";
        }
    }
    
    return 0;
}