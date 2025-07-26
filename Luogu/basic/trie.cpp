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

