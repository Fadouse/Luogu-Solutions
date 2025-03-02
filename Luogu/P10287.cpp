#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int MAX_WEIGHT = 10;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> weight(n+1);
    for(int i = 1; i <= n; i++){
        cin >> weight[i];
    }
    
    vector<vector<int>> graph(n+1);
    vector<int> indegree(n+1, 0);
    for(int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        indegree[v]++;
    }
    
    vector<vector<int>> dp(n+1, vector<int>(MAX_WEIGHT+1, 0));
    
    queue<int> q;
    for (int i = 1; i <= n; i++){
        if(indegree[i] == 0){
            q.push(i);
            
            dp[i][ weight[i] ] = 1;
        }
    }
    
    
    int ans = 0;
    
    while(!q.empty()){
        int u = q.front();
        q.pop();
        
        
        for (int w = 1; w <= MAX_WEIGHT; w++){
            ans = max(ans, dp[u][w]);
        }
        
        for(auto v : graph[u]){
            
            
            for (int w = 1; w <= MAX_WEIGHT; w++){
                dp[v][w] = max(dp[v][w], dp[u][w]);
            }
            
            
            for (int w = 1; w <= weight[v]; w++){
                dp[v][ weight[v] ] = max(dp[v][ weight[v] ], dp[u][w] + 1);
            }
            
            
            indegree[v]--;
            if(indegree[v] == 0){
                
                
                dp[v][ weight[v] ] = max(dp[v][ weight[v] ], 1);
                q.push(v);
            }
        }
    }
    
    cout << ans << "\n";
    return 0;
}
