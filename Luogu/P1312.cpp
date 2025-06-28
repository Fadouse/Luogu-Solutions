#include <bits/stdc++.h>

using namespace std;

vector<int> g[5];
int maxDepth;

struct node{
    int x, y, d;
};

int del();
int check();
int dfs(int depth, vector<node> path);

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cin >> maxDepth; //输入步数
    for(int i=0;i<5;i++){
        int t;
        while (cin >> t && t != 0) {
          g[i].push_back(t);
        }
        
    }
    if(!dfs(0, {})){
        cout << -1;
    } 
    
    return 0;
}

int dfs(int depth, vector<node> path){
    if(depth == maxDepth){ //达到深度
        if(!check()) return 0; //判断是否清空棋盘
        for(int i=0;i<path.size();i++){ //输出路径
            node n = path[i];
            cout << n.x << " " << n.y << " " << n.d << endl;
        }
        return 1;
    }

    for(int i=0;i<5;i++){
        for(int j=0;j<g[i].size();j++){
            vector<int> tmp[5];
            for(int k=0;k<5;k++){
                tmp[k] = g[k]; //备份
            }
            if(i<4){
                if(j<g[i+1].size()){
                    swap(g[i][j], g[i+1][j]);
                } else {
                    g[i+1].push_back(g[i][j]);
                    g[i].erase(g[i].begin()+j);
                }
                while(del());
                path.push_back({i,j,1});
                if(dfs(depth+1, path) == 1) return 1;
                path.pop_back();
                for(int k=0;k<5;k++) g[k] = tmp[k];
            }
            if(i>0){
                if(j < g[i-1].size()){
                    swap(g[i][j], g[i-1][j]);
                } else {
                    g[i-1].push_back(g[i][j]);
                    g[i].erase(g[i].begin()+j);
                }
                while(del());
                path.push_back({i,j,-1});
                if(dfs(depth+1, path) == 1) return 1;
                path.pop_back();
                for(int k=0;k<5;k++) g[k] = tmp[k];
            }
        }
    }
    return 0;
}
//删除元素
int del(){
    set<pair<int,int>,greater<pair<int,int>>> tags;
    for(int i=0;i<5;i++){
        for(int j=0;j<g[i].size();j++){
            if(i<3 && j<g[i].size() && j<g[i+1].size() && j<g[i+2].size()
               && g[i][j] == g[i+1][j] && g[i][j] == g[i+2][j]){
                tags.insert({i,j});
                tags.insert({i+1,j});
                tags.insert({i+2,j});
            } // row
            if(j + 2<g[i].size()
               && g[i][j] == g[i][j+1] && g[i][j] == g[i][j+2]){
                tags.insert({i,j});
                tags.insert({i,j+1});
                tags.insert({i,j+2});
            } // column
        }
    }

    int delted = tags.size()>0;
    for(auto it:tags){ 
        //由于使用了greater，所以删除不成问题(待删除元素位置保持不变)
        /*
        A B C D E
        0 1 2 3 4
        假设我们要删除 B C D E
        第一次 删除 D(3) (由于3>2>1)
        第二次 删除 C(2) (由于2>1)
        第三次 删除 B(1) 
        */
        g[it.first].erase(g[it.first].begin()+it.second);
    }
    return delted; //1代表删除了元素 0代表没有删除元素
}

//检查是否还有元素
int check(){
    for(int i=0;i<5;i++){
        if(g[i].size() != 0) return 0; 
    }
    return 1; 
}