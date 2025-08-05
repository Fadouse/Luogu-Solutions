#include <bits/stdc++.h>

using namespace std;

int n, x, y;
vector<vector<int>> mp;
map<int, int> vis; //标注已经经过的
queue<pair<int, int>> q;//第一个表示第几个人，第二个表示第几次

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    
    cin >> n >> x >> y;
    x--; y--;
    mp.assign(n, vector<int>());
    
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            int t;
            cin>>t;
            if(t) mp[i].push_back(j);
        }
    }

    q.push({x, 0});
    vis[x] = 1;
    while (!q.empty())
    {
        auto [cur, cnt] = q.front(); q.pop();
        if(cur == y){
            cout << cnt - 1;
            break;
        }

        for(int i:mp[cur]){
            if(vis[i]) continue;
            vis[i] = 1;
            q.push({i, cnt+1});
        }
    }
    

    return 0;
}