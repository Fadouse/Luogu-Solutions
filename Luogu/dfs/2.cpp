#include <bits/stdc++.h>

using namespace std;

int ans = 0;

vector<vector<int>> mp;
vector<vector<int>> vis;
int n, m;

int d[4][2] = {{-1, 0}, {0,-1}, {1,0}, {0,1}};

int dfs(int x, int y){
    if(x<0 || y<0 || x>=n || y>=m || vis[x][y] || !mp[x][y])
        return 0;
    vis[x][y] = 1;
    int t=1;
    for(int i=0;i<4;i++){
        t += dfs(x+d[i][0], y+d[i][1]);
    }
    return t;
}  

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    cin >> n >> m;
    mp.assign(n, vector<int>(m, 0));
    vis.assign(n, vector<int>(m, 0));
    for(vector<int> &v : mp){
        for(int &i : v){
            cin >> i;
        }
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            ans = max(ans, dfs(i,j));
        }
    }

    cout << ans;

    return 0;
}