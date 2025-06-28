#include <bits/stdc++.h>

using namespace std;

int M, N;
int MIN = 0x3f3f3f, MAX = -1;

int g[1001][1001];

int vis[1001][1001];

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    
    cin>>M>> N;
    for(int i=0;i<M;i++){
        for(int j=0;j<N;j++){
            cin>>g[i][j];
        }
    }

    for(int i=0;i<M;i++){
        for(int j=0;j<N;j++){
            if(vis[i][j] || !g[i][j]) continue;
            queue<pair<int, int>> q;
            q.push({i, j});
            vis[i][j] = 1;
            int cnt = 0;
            while(!q.empty()){
                auto [x, y] = q.front();
                q.pop();
                cnt++;
                for(int dx=-1;dx<=1;dx++){
                    for(int dy=-1;dy<=1;dy++){
                        if(abs(dx) == abs(dy)) continue;
                        int nx = x + dx, ny = y + dy;
                        if(nx<0 || nx>=M || ny<0 || ny>=N) continue;
                        if(vis[nx][ny]) continue;
                        if(g[nx][ny]){
                            q.push({nx, ny});
                            vis[nx][ny] = 1;
                        }
                    }
                }
            }
            if(cnt < MIN) MIN = cnt;
            if(cnt > MAX) MAX = cnt;
        }
    }
    // cout << MIN << " " << MAX << endl;
    cout<<MAX - MIN<<endl;
    return 0;
}