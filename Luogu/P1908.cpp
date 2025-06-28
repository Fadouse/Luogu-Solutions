#include <bits/stdc++.h>

using namespace std;

class BIT {
private:
    vector<long long> tree;
    long long n;

public:
    BIT(long long size) {
        n = size;
        tree.assign(n + 1, 0);
    }
    
    void update(long long pos, long long val) {
        for (long long i = pos; i <= n; i += i & (-i)) {
            tree[i] += val;
        }
    }
    
    long long query(long long pos) {
        long long sum = 0;
        for (long long i = pos; i > 0; i -= i & (-i)) {
            sum += tree[i];
        }
        return sum;
    }
    
    long long rangeQuery(long long l, long long r) {
        return query(r) - query(l - 1);
    }
};

long long n;
long long a[500005];
int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    long long n;
    cin >> n;
    BIT bit(n);
    for (long long i=0;i<n;i++){
        cin >> a[i];
    }
    //离散化
    vector<long long> v(a, a + n);
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    for (long long i=0;i<n;i++){
        a[i] = lower_bound(v.begin(), v.end(), a[i]) - v.begin() + 1;
    }

    long long ans = 0;
    for (long long i=0;i<n;i++){
        ans += bit.query(a[i]);
        bit.update(1, 1);
        bit.update(a[i], -1);
    }

    cout << ans;

    return 0;
}