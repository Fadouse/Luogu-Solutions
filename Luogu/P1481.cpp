#include <bits/stdc++.h>

using namespace std;
#define ll long long

struct trie{
    struct Node {
        int nxt[26];
        bool terminal;
        Node() : terminal(false) { memset(nxt, -1, sizeof nxt); }
    };
    vector<Node> tr{Node()}; 

    void insert(string str){
        int u = 0;
        for(char c : str){
            int v = c - 'a';
            if(tr[u].nxt[v]<0){
                tr[u].nxt[v]=tr.size();
                tr.emplace_back();
            }
            u = tr[u].nxt[v];
        }
        tr[u].terminal = true;
    }

    bool find(string str){
        int u = 0;
        for(char c : str){
            int v = c - 'a';
            if((u=tr[u].nxt[v])<0) return false;
        }
        return tr[u].terminal;
    }

    long long dfs(int u, long long cnt) {
        if (tr[u].terminal) ++cnt;               // 经过单词节点
        long long best = cnt;
        for (int v : tr[u].nxt)
            if (v != -1) best = max(best, dfs(v, cnt));
        return best;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;  cin >> N;
    trie tr;
    string s;
    for (int i = 0; i < N; ++i) {
        cin >> s;
        tr.insert(s);
    }
    cout << tr.dfs(0, 0) << '\n';
    return 0;
}