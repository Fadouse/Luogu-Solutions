#include <bits/stdc++.h>

using namespace std;

const int MAXN = 105;
const int INF = -0x3f3f3f3f;

int F,V;
int a[MAXN][MAXN];
int memo[MAXN][MAXN];
int path[MAXN][MAXN];
bool visited[MAXN][MAXN];

int dfs(int i, int j){
    if(i > F) return 0;
    if (visited[i][j]) return memo[i][j];

    if(V - j + 1 < F - i + 1) return INF;
    visited[i][j] = true;
    int &res = memo[i][j];
    res = INF;

    for (int k = j; k <= V - (F - i); k++) {
        int next = dfs(i + 1, k + 1);
        if (next != INF && a[i][k] + next > res) {
            res = a[i][k] + next;
            path[i][j] = k; 
        }
    }
    return res;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cin >> F >> V;
    for (int i = 1; i <= F; i++) {
        for (int j = 1; j <= V; j++) {
            cin >> a[i][j];
        }
    }
    memset(visited, false, sizeof(visited));
    memset(memo, 0, sizeof(memo));
    int ans = dfs(1, 1);
    cout << ans;

    vector<int> vases;
    int i = 1, j = 1;
    while (i <= F) {
        int v = path[i][j]; 
        vases.push_back(v);
        j = v + 1;
        i++;
    }
    
    cout << endl;
    for (int vase : vases) {
        cout << vase << " ";
    }

    return 0;
}