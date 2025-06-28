#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = (1LL<<60);

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> price(n+1);
    for(int i=1;i<=n;i++){
        cin >> price[i];
    }

    // 构建正向和反向图
    vector<vector<int>> G(n+1), Gr(n+1);
    for(int i=0;i<m;i++){
        int u,v,z;
        cin>>u>>v>>z;
        G[u].push_back(v);
        Gr[v].push_back(u);
        if(z==2){
            G[v].push_back(u);
            Gr[u].push_back(v);
        }
    }

    // 1) 正向 SPFA: 计算 dpMin[i]
    vector<ll> dpMin(n+1, INF);
    vector<bool> inQ(n+1,false);
    queue<int> q;

    dpMin[1] = price[1];
    q.push(1);
    inQ[1] = true;
    while(!q.empty()){
        int u = q.front(); q.pop();
        inQ[u] = false;
        for(int v: G[u]){
            ll cand = min(dpMin[u], (ll)price[v]);
            if(cand < dpMin[v]){
                dpMin[v] = cand;
                if(!inQ[v]){
                    q.push(v);
                    inQ[v] = true;
                }
            }
        }
    }

    // 2) 反向 SPFA: 计算 dpMax[i]
    vector<ll> dpMax(n+1, -INF);
    fill(inQ.begin(), inQ.end(), false);
    dpMax[n] = price[n];
    q.push(n);
    inQ[n] = true;
    while(!q.empty()){
        int u = q.front(); q.pop();
        inQ[u] = false;
        for(int v: Gr[u]){
            ll cand = max(dpMax[u], (ll)price[v]);
            if(cand > dpMax[v]){
                dpMax[v] = cand;
                if(!inQ[v]){
                    q.push(v);
                    inQ[v] = true;
                }
            }
        }
    }

    // 3) 取最大差价
    ll ans = 0;
    for(int i=1;i<=n;i++){
        if(dpMin[i]<INF && dpMax[i]>-INF){
            ans = max(ans, dpMax[i] - dpMin[i]);
        }
    }

    cout << ans << "\n";
    return 0;
}
