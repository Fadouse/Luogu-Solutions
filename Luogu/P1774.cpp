#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 树状数组
struct Fenwick {
    int n;
    vector<ll> t;
    Fenwick(int _n): n(_n), t(n+1,0) {}
    // 在 i 上加 v
    void update(int i, ll v=1) {
        for (; i<=n; i+=i&-i) t[i]+=v;
    }
    // 查询前缀和 [1..i]
    ll query(int i) {
        ll s=0;
        for (; i>0; i-=i&-i) s+=t[i];
        return s;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<ll> a(n), b;
    b.reserve(n);
    for(int i=0;i<n;i++){
        cin >> a[i];
        b.push_back(a[i]);
    }
    // 离散化
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    int m = b.size();
    Fenwick fw(m);

    ll ans = 0;
    // 从右向左遍历，统计比 a[i] 小的已出现次数
    for(int i=n-1;i>=0;i--){
        int r = int(lower_bound(b.begin(), b.end(), a[i]) - b.begin()) + 1;
        ans += fw.query(r-1);
        fw.update(r, 1);
    }

    cout << ans << "\n";
    return 0;
}