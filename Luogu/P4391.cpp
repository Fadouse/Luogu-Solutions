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

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n;
    cin >> n;

    string s;
    cin >> s;
    auto next = buildNext(s);
    cout << n - next[n-1];
    
    return 0;
}