#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Edge { int x, y; };
struct Q { int X, Y, idx, sgn; };

struct Fenwick {
    int n;
    vector<int> f;
    Fenwick(int _n): n(_n), f(n+1,0) {}
    void update(int i, int v=1){
        for (; i<=n; i+=i&-i) f[i]+=v;
    }
    int query(int i){
        int s=0;
        for (; i>0; i-=i&-i) s+=f[i];
        return s;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<ll> a(n+1);
    for(int i=1;i<=n;i++) cin>>a[i];

    // 1. 找最近邻
    vector<pair<ll,int>> ord;
    ord.reserve(n);
    for(int i=1;i<=n;i++) ord.emplace_back(a[i], i);
    sort(ord.begin(), ord.end());

    vector<Edge> edges;
    edges.reserve(2*n);
    for(int i=0;i<n;i++){
        int idx = ord[i].second;
        // 考虑前驱
        if(i>0){
            int jdx = ord[i-1].second;
            ll d1 = llabs(a[idx]-a[jdx]);
            // 如果两边距离相同，则都加
            if(i+1<n){
                int kdx = ord[i+1].second;
                ll d2 = llabs(a[idx]-a[kdx]);
                if(d1 < d2) edges.push_back({idx,jdx});
                else if(d2 < d1) edges.push_back({idx,kdx});
                else edges.push_back({idx,jdx}), edges.push_back({idx,kdx});
            } else {
                edges.push_back({idx,jdx});
            }
        }
        // 考虑后继
        if(i+1<n){
            int jdx = ord[i+1].second;
            // 前面已在上面处理过相等情况，就只补前向
            if(i==0){
                edges.push_back({idx,jdx});
            }
        }
    }

    // 2. 拆查询
    vector<ll> ans(m+1,0);
    vector<Q> qs;
    qs.reserve(4*m);
    for(int i=1;i<=m;i++){
        int l, r;
        cin>>l>>r;
        // count = F(r,r)-F(l-1,r)-F(r,l-1)+F(l-1,l-1)
        qs.push_back({r, r, i, +1});
        qs.push_back({l-1, r, i,-1});
        qs.push_back({r, l-1, i,-1});
        qs.push_back({l-1,l-1, i,+1});
    }

    // 3. 离线排序+扫描
    sort(edges.begin(), edges.end(), [](auto &l, auto &r){
        return l.x < r.x;
    });
    sort(qs.begin(), qs.end(), [](auto &l, auto &r){
        return l.X < r.X;
    });

    Fenwick bit(n);
    int ei = 0;
    for(auto &q: qs){
        while(ei < (int)edges.size() && edges[ei].x <= q.X){
            bit.update(edges[ei].y, 1);
            ei++;
        }
        if(q.Y >= 1)
            ans[q.idx] += (ll)q.sgn * bit.query(min(q.Y, n));
    }

    // 4. 累加 weighted sum
    ll res = 0;
    for(int i=1;i<=m;i++){
        res += ans[i] * i;
    }
    cout << res << "\n";
    return 0;
}