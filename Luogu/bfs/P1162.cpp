#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int dx[4] = {0, 1, -1, 0};
    int dy[4] = {1, 0, 0, -1};

    int n;
    cin >> n;
    vector<vector<int>> mp(n, vector<int>(n,0)), vis(n, vector<int>(n,0));
    queue<pair<int, int>> q;

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin >> mp[i][j];
        }
    }

    auto push = [&](int x, int y){
        if (x < 0 || y < 0 || x >= n || y >= n || vis[x][y] || mp[x][y]) return;
        vis[x][y] = 1;
        q.push({x, y});
    };
    
    for(int i=0;i<n;i++){
        push(0, i);
        push(i, 0);
        push(n-1, i);
        push(i, n-1);
    }
    
    while(q.size()){
        auto [cx, cy] = q.front(); q.pop();
        for(int i=0;i<4;i++){
            int nx = cx + dx[i], ny = cy + dy[i];
            push(nx, ny);
        }
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(!vis[i][j] && !mp[i][j]){
                mp[i][j] = 2;
            }
            cout << mp[i][j] << ' ';
        }
        cout << endl;
    }
    return 0;
}

