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

    void add(string str){
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
};

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    trie tr;
    int n, m;
    cin >> n;
    for(int i=0;i<n;i++){
        string s;
        cin >> s;
        tr.add(s);
    }
    cin >> m;
    map<string, bool> mp;

    for(int i=0;i<m;i++){
        string s;
        cin >> s;
        if(tr.find(s)){
            if(mp[s]){
                cout << "REPEAT" << endl;
            }else {
                cout << "OK" << endl;
                mp[s] = true;
            }
        }else{
            cout << "WRONG" << endl;
        }
    }

    return 0;
}