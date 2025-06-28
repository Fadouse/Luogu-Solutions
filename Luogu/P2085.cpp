#include <bits/stdc++.h>

using namespace std;

struct Node {
    int value;
    int func_id;
    int x;
    
    bool operator>(const Node& other) const {
        return value > other.value;
    }
};

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> fc(n, vector<int>(3, 0));

    for (int i = 0; i < n; i++) {
        cin >> fc[i][0] >> fc[i][1] >> fc[i][2];
    }

    priority_queue<Node, vector<Node>, greater<Node>> pq;

    for (int i = 0; i < n; i++) {
        int val = fc[i][0] + fc[i][1] + fc[i][2]; 
        pq.push({val, i, 1});
    }

    for (int i = 0; i < m; i++) {
        Node current = pq.top();
        pq.pop();
        
        cout << current.value;
        if (i < m - 1) cout << " ";
        
        int next_x = current.x + 1;
        int func_id = current.func_id;
        int next_val = fc[func_id][0] * next_x * next_x + 
                      fc[func_id][1] * next_x + 
                      fc[func_id][2];
        pq.push({next_val, func_id, next_x});
    }

    return 0;
}