#include <bits/stdc++.h>
using namespace std;
using pii = pair<int,int>;
using tiii = tuple<int,int,int>;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<int> a(n+2);
    for(int i=1;i<=n;i++) cin >> a[i];

    vector<int> L(n+2), R(n+2);
    vector<bool> removed(n+2,false);
    for(int i=0;i<=n+1;i++){
        L[i]=i-1;
        R[i]=i+1;
    }

    // 小根堆： (差值, 左端点i, 右端点j)
    priority_queue<tiii, vector<tiii>, greater<tiii>> pq;
    auto push_pair = [&](int i,int j){
        if(i>=1 && j<=n && !removed[i] && !removed[j] && s[i-1]!=s[j-1]){
            pq.emplace(abs(a[i]-a[j]), i, j);
        }
    };

    // 初始化所有相邻异性对
    for(int i=1;i<n;i++){
        push_pair(i, i+1);
    }

    vector<pii> ans;
    while(!pq.empty()){
        auto [d,i,j] = pq.top(); pq.pop();
        if(removed[i] || removed[j] || R[i]!=j) continue;
        // 确认删除
        removed[i] = removed[j] = true;
        ans.emplace_back(min(i,j), max(i,j));
        // 断开 i–j 之间的链接
        int li = L[i], rj = R[j];
        R[li] = rj;
        L[rj] = li;
        // 新的相邻可能形成新的候选
        push_pair(li, rj);
    }

    // 输出
    cout << ans.size() << "\n";
    for(auto &p: ans){
        cout << p.first << " " << p.second << "\n";
    }
    return 0;
}