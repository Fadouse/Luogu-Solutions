#include <bits/stdc++.h>

using namespace std;
const int N=20, INF=0X3f3f3f3f3f;
int n,m,ans=INF;
int g[N][N];
int depth[N];
bool vis[N];
int lg2[1<<12];
int f[1<<12][N][N];

int lowbit(int x) {
    return x & (-x);
}

void dfs(int u, int cnt, int cost, int stat){
    if(cost>=ans) return;
    if(f[stat][u][depth[u]]<=cost){
        return;
    }
    f[stat][u][depth[u]] = cost;
    if(cnt == n){
        ans = min(ans, cost);
        return;
    }
    for(int i=stat; i; i-=lowbit(i)){
        int u = lg2[lowbit(i)] + 1;
        for(int v=1;v<=n;v++){
            if(g[u][v] == INF || vis[v]) continue;
            depth[v] = depth[u]+1;
            vis[v] = true;
            dfs(v, cnt+1,cost+depth[u]*g[u][v], stat|(1<<(v-1)));
            vis[v] = false;
        }
    }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    
    for(int i=1;i<=12;i++){
        lg2[1<<i] = i;
    }
    cin >> n >> m;
    int u,v,w;
    memset(g, 0x3f, sizeof(g));
    while(m--){
        cin >> u >> v >> w;
        if(u == v) continue;
        g[u][v] = g[v][u] = min(g[u][v], w);
    }
    memset(f, 0x3f, sizeof(f));
    for(int i=1;i<=n;i++){
        memset(vis,0,sizeof(vis));
        memset(depth,0,sizeof(depth));
        vis[i] = true;
        depth[i] = 1;
        dfs(i,1,0,1<<(i-1));
    }
    cout << ans;

    return 0;
}