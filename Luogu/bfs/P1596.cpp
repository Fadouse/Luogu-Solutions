#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> mp;
vector<vector<int>> vis;
queue<pair<int, int>> q;

int n,m;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    cin >> n >> m;
    mp.assign(n, vector<int>(m,0));
    vis.assign(n, vector<int>(m,0));

    for(int i=0;i<n;i++){
        string s;
        cin >> s;
        for(int j=0;j<m;j++){
            char c = s[j];
            if(c == 'W') mp[i][j] = 1;
        }
    }
    int cnt = 0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(!mp[i][j] || vis[i][j]) continue;
            cnt ++;
            q.push({i,j});
            vis[i][j] = 1;
            while(q.size()){
                auto [x, y] = q.front(); q.pop();
                for(int dx = -1; dx <= 1; dx++){
                    for(int dy = -1; dy <= 1; dy++){
                        if(!dx && ! dy) continue;
                        int nx = x + dx, ny = y + dy;
                        if(nx < 0 || ny <0 || nx >= n || ny >= m || vis[nx][ny] || !mp[nx][ny]) continue;
                        vis[nx][ny] = 1;
                        q.push({nx, ny});
                    }
                }
            }
        }
    }

    cout << cnt;
    return 0;
}