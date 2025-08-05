#include <bits/stdc++.h>

using namespace std;

int n, a, b;

map<int, int> vis, mp;
queue<pair<int, int>> q;


int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cin >> n >> a >> b;
    a--; b--;
    for(int i=0;i<n;i++){
        cin >> mp[i];
    }
    
    q.push({a, 0});
    vis[a] = 1;

    while(q.size()){
        auto [cur, cnt] = q.front(); q.pop();
        if(cur == b){
            cout << cnt;
            return 0;
        }    
        if(cur - mp[cur] >= 0 && !vis[cur - mp[cur]]){
            q.push({cur - mp[cur], cnt+1});
            vis[cur - mp[cur]] = 1;
        };
        if(cur + mp[cur] < n && !vis[cur + mp[cur]]){
            q.push({cur + mp[cur], cnt+1});
            vis[cur + mp[cur]] = 1;
        } 
    }
    cout << -1;
    return 0;
}