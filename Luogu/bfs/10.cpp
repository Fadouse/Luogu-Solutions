#include <bits/stdc++.h>

using namespace std;

//bfs version 最大面积
vector<vector<int>> mp, vis;
int ans = 0;
int n, m;

int d[4][2] = {{-1,0}, {0,1}, {1, 0}, {0, -1}};

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cin >> n >> m;
    mp.assign(n, vector<int>(m));
    vis.assign(n, vector<int>(m));

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin >> mp[i][j];
        }
    }

    for(int x=0;x<n;x++){
        for(int y=0;y<m;y++){
            if(vis[x][y] || !mp[x][y]) continue;
            int size = 0;

            queue<pair<int, int>> q;
            q.push({x, y});
            vis[x][y] = 1;
            
            // bfs
            while(q.size()){
                int cx = q.front().first, cy = q.front().second;
                q.pop();
                size++;
                for(int i=0;i<4;i++){
                    int nx = cx + d[i][0], ny = cy + d[i][1];
                    if(nx < 0 || ny < 0 || nx >= n || ny >= m || vis[nx][ny]) continue;
                    if(!mp[nx][ny]) continue;
                    vis[nx][ny] = 1;
                    q.push({nx, ny});
                }
            }
            ans = max(ans, size);
        }
    }
    cout << ans;
    return 0;
}