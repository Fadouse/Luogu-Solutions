#include <bits/stdc++.h>

using namespace std;
#define MAX 0x3f3f3f3f

int n;
vector<pair<int, int>> ps;

int dfs(int idx, int s, int b, int used){
    if(idx == ps.size()){
        if(!used) return MAX;
        return abs(s - b);
    }
    return min(dfs(idx+1, s*ps[idx].first, b+ps[idx].second, used+1), dfs(idx+1, s, b, used));
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    
    cin >> n;
    ps.resize(n);

    for(int i=0;i<n;i++){
        cin >> ps[i].first >> ps[i].second;
    }

    cout << dfs(0, 1, 0, 0);

    return 0;
}