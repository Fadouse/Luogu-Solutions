#include <bits/stdc++.h>

using namespace std;

int N,K,M,S,T;
int cultures[101]; //记录国家对应的文化
int learned[101]; //记录已经学习的文化
int minCost[101]; //记录最小花费
int conflict[101][101]; //记录国家间文化冲突
int INF = 0x3f3f3f3f; //无穷大

vector<vector<pair<int, int>>> G; //邻接表
vector<vector<int>> conflictList; //记录文化冲突列表

// Hack数据如下
/*
Input: 
4 4 4 1 4
1 2 3 4
0 0 0 0
0 0 0 0
0 0 0 0
0 1 0 0
1 2 1
2 3 1
1 3 2
3 4 1

Output:
3
*/

int best = 0x3f3f3f3f; //全局记录当前已找到的最优解，用于剪枝

int dfs(int country, int cost){
    if (cost >= best) return INF; //如果已超过目前找到的最优解，直接剪枝
    int culture = cultures[country]; //获取当前国家的文化
    if (learned[culture]) return INF; //如果已经学习过，返回无穷大
    if (minCost[country] <= cost) return INF; //如果当前花费大于等于最小花费，返回无穷大
    if (country == T) {
        best = min(best, cost); //更新全局最优解
        return cost;
    }
    int ans = INF, lastMinCost = minCost[country];
    learned[culture] = 1;
    minCost[country] = cost; //更新本次查询的最小花费

    for(int i=0;i<G[country].size();i++){
        int nc = G[country][i].first;
        int distance = G[country][i].second;
        bool valid = true;
        for (int conflictedCulture : conflictList[cultures[nc]]) {
            if (learned[conflictedCulture] == 1) {
                valid = false;
                break;
            }
        }
        if (!valid) continue; //如果有文化冲突，跳过
        ans = min(ans, dfs(nc, cost + distance));
    }

    if(ans == INF) minCost[country] = lastMinCost; //如果没有找到可行路径，恢复最小花费
    learned[culture] = 0; //回溯
    return ans;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    memset(minCost, 0x3f, sizeof(minCost)); //初始化最小花费为无穷大
    cin >> N >> K >> M >> S >> T;
    S--; T--; //将起点和终点转换为0-indexed

    G.resize(N+1); //初始化邻接表大小
    conflictList.resize(K); //初始化文化冲突列表大小

    for (int i = 0; i < N; i++) {
        int c;
        cin >> c; //记录国家对应的文化
        c--; //将文化编号转换为0-indexed
        cultures[i] = c;
    }

    for (int i = 0; i<K; i++){
        for(int j=0;j<K;j++){
            cin >> conflict[i][j]; //记录文化冲突
        }
    }

    for (int i = 0; i < M; i++){
        int u, v, d;
        cin >> u >> v >> d;
        u--; v--; //将国家编号转换为0-indexed
        G[u].push_back({v,d}); //邻接表存储
        G[v].push_back({u,d}); //无向图
    }

    for (int i = 0; i < N; i++){ //优先尝试较小花费的边，提高效率
        sort(G[i].begin(), G[i].end(), [](const pair<int,int> &a, const pair<int,int> &b) {
            return a.second < b.second;
        });
    }

    for (int i = 0; i < K; i++){
        for (int j = 0; j < K; j++){
            if (conflict[i][j])
                conflictList[i].push_back(j); //降低遍历冲突时的次数，最坏情况无优化
        }
    }

    int ans = dfs(S, 0); //深度优先搜索
    if(ans == INF) cout << -1 << endl; //如果无解，输出 -1
    else cout << ans << endl; //输出最小花费

    return 0;
}

