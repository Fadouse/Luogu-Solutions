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

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    int n;
    cin >> n;
    string s;
    cin >> s;
    auto next = buildNext(s);
    long long ans = 0;

    for(int i=0;i<next.size();i++){
        int j = next[i];
        while (j && next[j-1])
        {
            j = next[j-1];
        }
        next[i] = j;
    }

    for(int i=0;i<next.size();i++){
        int j = next[i];
        // while (j && next[j-1])
        // {
        //     j = next[j-1];
        // }
        // next[i] = j;
        // // int shorestS = 0;
        // int j = next[i];
        // cout << shorestS << " "<< i+1-shorestS << endl;
        if(j)
            ans += i+1-j;
    }
    cout << ans;
    return 0;
}