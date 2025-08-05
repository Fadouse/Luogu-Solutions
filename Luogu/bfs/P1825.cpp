#include <bits/stdc++.h>

using namespace std;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int dx[4] = {-1, 0, 0, 1};
    int dy[4] = {0, -1, 1, 0};

    int n, m, sx, sy;
    cin >> n >> m;

    unordered_map<char, vector<pair<int, int>>> trans;

    vector<vector<int>> mp(n, vector<int>(m, 0)), vis(n, vector<int>(m, 0));
    // 0可通行，1障碍，字母表示传送, 3表示出口
    for(int x = 0;x<n;x++){
        for(int y=0;y<m;y++){
            char c;
            cin >> c;
            if('A' <= c && c <= 'Z'){
                trans[c].push_back({x, y});
                mp[x][y] = c;
            }else if(c == '@'){
                sx = x;
                sy = y;
            }else if(c == '#'){
                mp[x][y] = 1;
            }else if(c == '='){
                mp[x][y] = 3;
            }
        }
    }


    queue<vector<int>> q;

    auto push = [&](int x, int y, int t){
        if(x<0 || y<0 || x>=n || y>=m || vis[x][y] || mp[x][y] == 1) return;
        int cv = mp[x][y];
        if(cv >= 'A'){
            vis[x][y] = 1;
            auto pairs = trans[cv];
            for (auto [tx, ty] : trans[char(cv)]) { 
                if (tx == x && ty == y) continue; 
                q.push({tx, ty, t});     
            }
        }else{
            vis[x][y] = 1;
            q.push({x, y, t});
        }
    };

    push(sx, sy, 0);

    while(q.size()){
        auto cur = q.front(); q.pop();
        int cx = cur[0], cy = cur[1], time = cur[2];
        if(mp[cx][cy] == 3){
            cout << time;
            return 0;
        }
        for(int i=0;i<4;i++){
            int nx = cx + dx[i], ny = cy + dy[i];
            push(nx, ny, time+1);
        }
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cout << vis[i][j];
        }
        cout << endl;
    }

    cout << -1;
    return 0;
}