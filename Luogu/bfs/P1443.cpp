#include <bits/stdc++.h>

using namespace std;

int n, m, x, y;

int d[8][2] = {{2, -1}, {2, 1}, {1, 2}, {-1, 2}, {-2, -1}, {-2, 1}, {-1, -2}, {1, -2}};

vector<vector<int>> vis;
queue<vector<int>> q;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    cin >> n >> m >> x >> y;    
    x--; y--;
    vis.assign(n, vector<int>(m,-1));

    q.push({x, y, 0});
    vis[x][y] = 0;
    while(q.size()){
        auto c = q.front(); q.pop();
        int cx = c[0], cy = c[1], cnt = c[2]+1;
        for(int i=0;i<8;i++){
            int nx = cx+d[i][0], ny = cy+d[i][1];
            if(nx<0 || ny<0 || nx>=n || ny>=m) continue;
            if(vis[nx][ny] != -1) continue;
            vis[nx][ny] = cnt;
            q.push({nx, ny, cnt});
        } 
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cout << vis[i][j] << ' ';
        }
        cout << endl;
    }
    return 0;
}