#include <bits/stdc++.h>

using namespace std;

int M, last = 0;
int d[4][2] = {{-1,0}, {0,1}, {1, 0}, {0, -1}};

vector<vector<int>> mp, vis, target;
unordered_map<int, vector<pair<int, int>>> ss;
queue<vector<int>> q;

//复杂版本，可以预处理优化

void hit(vector<vector<int>>& vec, vector<pair<int, int>> poss, int t){
    for(auto pos : poss){
        auto [x, y] = pos;
        vec[x][y] = t;
        if(x>0) vec[x-1][y] = t;
        if(x<301) vec[x+1][y] = t;
        if(y>0) vec[x][y-1] = t;
        if(y<301) vec[x][y+1] = t;
    }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cin >> M;
    mp.assign(302, vector<int>(302, 0));
    vis.assign(302, vector<int>(302, 0));
    target.assign(302, vector<int>(302, 1));

    for(int i=0;i<M;i++){
        int x, y, t;
        cin >> x >> y >> t;
        ss[t].push_back({x,y});
        hit(target, {{x, y}}, 0);
    }

    hit(mp, ss[0], 1);
    if(mp[0][0]){
        cout << -1;
        return 0;
    }
    vis[0][0] = 1;
    q.push({0, 0, 0});
    while(q.size()){
        auto cur = q.front(); q.pop();
        int x = cur[0], y = cur[1], time = cur[2];
        if(target[x][y]){ //抵达安全点
            cout << time;
            return 0;
        }
        if(last != time){ //新的时刻，开始更新当前地图
            last = time;
            hit(mp, ss[time+1], 1);
        }

        for(int i = 0; i<4; i++){ //移动
            int nx = x+d[i][0], ny = y+d[i][1];
            if(nx < 0 || ny < 0 || nx >= 302 || ny >= 302 || vis[nx][ny] || mp[nx][ny]) continue;
            q.push({nx, ny, time+1});
            vis[nx][ny] = 1;
        }
    }
    cout << -1;

    return 0;

}