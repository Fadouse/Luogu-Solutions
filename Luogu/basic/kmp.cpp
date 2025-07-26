#include <bits/stdc++.h>

using namespace std;

vector<int> buildNext(string p){
    vector<int> next(p.size());
    int j = 0;
    for(int i=1; i<p.size(); i++){
        while( j && p[j] != p[i]) j = next[j-1];
        if(p[j] == p[i]) j++;
        next[i] = j;
    }
    return next;
}

vector<int> kmp(string t, string p){
    vector<int> pos;
    auto next = buildNext(p);
    for(int i=0, j=0; i<t.size(); i++){
        while (j && t[i] != p[j]) j = next[j-1];
        if(p[j] == t[i]) j++;
        if(j == p.size()){
            pos.push_back(i-j+1);
            j = next[j-1];
        } 
    }
    return pos;
}