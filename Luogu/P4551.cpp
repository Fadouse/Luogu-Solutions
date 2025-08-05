#include <bits/stdc++.h>

using namespace std;
#define ll long long

const int N = 2;

struct trie{
    struct Node {
        int nxt[N];
        int terminal;
        Node() : terminal(false) { memset(nxt, 0, sizeof nxt); }
    };
    vector<Node> tr{Node()}; 

    void add(int t) {
        int u = 0;
        for (int i = 31; i >= 0; --i) {    
            int bit = (t >> i) & 1;
            if (tr[u].nxt[bit] == 0) {
                tr[u].nxt[bit] = tr.size();
                tr.emplace_back();
            }
            u = tr[u].nxt[bit];
        }
        tr[u].terminal = true;
    }

    int find(int t){
        int u = 0, res = 0;
        for (int i = 31; i >= 0; --i) {    
            int bit = (t >> i) & 1;
            if(tr[u].nxt[!bit]){
                u = tr[u].nxt[!bit];
                res=2*res + 1;
            }else if(tr[u].nxt[bit]){
                u = tr[u].nxt[bit];
                res = 2*res;
            }
        }
        return res;
    }
};

void dfs(vector<int> &x, vector<vector<pair<int, int>>> &tree, int node){
    for(pair<int, int> idx : tree[node]){
        x[idx.first] = x[node] ^ idx.second;
        dfs(x, tree, idx.first);
    }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    trie tr;
    int n;
    cin >> n;
    vector<vector<pair<int, int>>> tree(n+1);
    vector<int> x(n+1, 0);
    for(int i=0;i<n-1;i++){
        int u, v, w;
        cin >> u >> v >> w;
        tree[u].emplace_back(v, w);
    }

    dfs(x, tree, 1);

    for(int i=1; i<= n;i++){
        // cout << x[i]<< endl;
        tr.add(x[i]);
    }
    int ans = 0;
    for(int i=1;i<=n;i++){
        ans = max(ans, tr.find(x[i]));
    }
    cout << ans;

    return 0;
}