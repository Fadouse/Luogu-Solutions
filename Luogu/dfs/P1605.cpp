#include <bits/stdc++.h>

using namespace std;

int n, m, t;
int sx, sy, fx, fy;

int d[4][2] = {{-1,0}, {0,1}, {1, 0}, {0, -1}};

vector<vector<int>> mp, vis;
vector<int> o;

int dfs(int x, int y){
    if(x<0 || y<0 || x>=n || y>=m) return 0;
    if(vis[x][y] || mp[x][y]) return 0;
    if(x == fx-1 && y == fy-1) return 1;
    int r = 0;
    vis[x][y] = 1;
    for(int i=0; i<4;i++){
        int dx = d[i][0];
        int dy = d[i][1];
        r += dfs(x+dx, y+dy);
    }
    vis[x][y] = 0;
    return r;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cin >> n >> m >> t;
    cin >> sx >> sy >> fx >> fy;
    mp.assign(n, vector<int>(m, 0));
    vis.assign(n, vector<int>(m, 0));

    while(t--){
        int x, y;
        cin >> x >> y;
        mp[x-1][y-1] = 1; //标记有障碍物 0-based
    }

    cout << dfs(sx-1, sy-1);

    return 0;
}
