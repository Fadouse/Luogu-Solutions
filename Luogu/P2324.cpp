#include <bits/stdc++.h>

using namespace std;

string target = "111110111100*110000100000";
pair<int, int> dxy[8] = {{-2,1},{-1,2},{1,2},{2,1},
                         {2,-1},{1,-2},{-1,-2},{-2,-1}};

int fun(string stat){
    int res=0;
    for(int i=0;i<25;i++){
        if(stat[i] != target[i] && stat[i] != '*'){
            res ++;
        }
    }
    return res;
}

bool dfs(string start, int depth, int maxdepth){
    if(depth+fun(start) > maxdepth){
        return false;
    }
    if(start == target) return true;
    int pos = start.find('*');
    int x = pos/5, y = pos%5;
    for(int i=0;i<8;i++){
        int nx = x + dxy[i].first;
        int ny = y + dxy[i].second;
        if(nx < 0 || nx > 4 || ny < 0 || ny > 4) continue;
        int npos = nx*5 + ny;
        string tmp = start;
        swap(tmp[pos], tmp[npos]);
        if(dfs(tmp, depth+1, maxdepth)){
            return true;
        }
    }
    return false; 
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int t;
    cin >> t;
    while(t--){
        string s, line;
        for(int i=0;i<5;i++){
            cin >> line;
            s += line;
        }
        int maxdepth;
        for(maxdepth = 0;maxdepth<=15 ;maxdepth++){
            if(dfs(s, 0, maxdepth)){
                break;
            }
        }
        if(maxdepth <= 15)
            cout << maxdepth << endl;
        else
            cout << -1 << endl;
    }
    return 0;
}
