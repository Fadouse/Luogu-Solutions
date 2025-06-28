#include <iostream>
#include <queue>
#include <unordered_set>
#include <string>
#include <vector>
#include <utility>   
#include <algorithm>  

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
     
     
    string start;
    for (int i = 0; i < 9; ++i) {
        char c;
        cin >> c;
        start.push_back(c);
    }
    
     
     
     
     
    string target = "123804765";
    
     
    if (start == target) {
        cout << 0 << "\n";
        return 0;
    }
    
     
    queue<pair<string, int>> q;
     
    unordered_set<string> visited;
    
    q.push({start, 0});
    visited.insert(start);
    
     
    vector<int> dx = {-1, 1, 0, 0};   
    vector<int> dy = {0, 0, -1, 1};   

     
    while (!q.empty()) {
        auto current = q.front();
        q.pop();
        
        string curState = current.first;
        int steps = current.second;
        
         
        int pos = curState.find('0');
         
        int x = pos / 3;   
        int y = pos % 3;   
        
         
        for (int d = 0; d < 4; ++d) {
            int newX = x + dx[d];
            int newY = y + dy[d];
             
            if (newX < 0 || newX >= 3 || newY < 0 || newY >= 3)
                continue;
            
             
            int newPos = newX * 3 + newY;
             
            string newState = curState;
            swap(newState[pos], newState[newPos]);
            
             
            if (visited.find(newState) == visited.end()) {
                 
                if (newState == target) {
                    cout << steps + 1 << "\n";
                    return 0;
                }
                 
                q.push({newState, steps + 1});
                visited.insert(newState);
            }
        }
    }
    
     
    return 0;
}
