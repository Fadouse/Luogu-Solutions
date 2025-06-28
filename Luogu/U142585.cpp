#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 1D 树状数组，支持 [1..n] 前缀和 & 单点加
struct BIT {
    int n;
    vector<ll> t;
    BIT(int _n): n(_n), t(n+1,0){}
    void add(int i, ll v) { for(; i<=n; i+=i&-i) t[i]+=v; }
    ll sum(int i){ ll s=0; for(; i>0; i-=i&-i) s+=t[i]; return s; }
};

int n;
vector<int> a;

// 统计所有子区间中位数 ≤ x 的子区间个数
ll count_le(int x) {
    // 把 a[i] ≤ x 映射为 +1，否则 -1，前缀和 > 0 即说明该子区间中 ≤x 的个数 > 大于 x 的个数
    int offset = n + 1;
    BIT bit(2*n + 5);
    ll res = 0;
    int prefix = 0;
    bit.add(offset, 1);         // 前缀和为 0 的情况
    for(int i = 0; i < n; i++){
        prefix += (a[i] <= x ? 1 : -1);
        int idx = prefix + offset;
        // 统计之前有多少前缀和 < 当前前缀和
        res += bit.sum(idx - 1);
        bit.add(idx, 1);
    }
    return res;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    a.resize(n);
    for(int i = 0; i < n; i++) cin >> a[i];

    // 离散化
    vector<int> v = a;
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());

    // 子区间总数 & 中位数所在位置
    ll total = (ll)n * (n + 1) / 2;
    ll k = total / 2 + 1;

    // 二分答案
    int l = 0, r = (int)v.size() - 1, ans = v[0];
    while(l <= r){
        int mid = (l + r) >> 1;
        if(count_le(v[mid]) >= k){
            ans = v[mid];
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    cout << ans << "\n";
    return 0;
}