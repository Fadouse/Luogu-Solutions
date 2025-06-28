#include <bits/stdc++.h>

using namespace std;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    
    int X, Y, Mx, My;
    cin >> X >> Y >> Mx >> My;
    
    // Adjust to 0-indexed for easier processing
    Mx--; My--;
    
    // Grid to store the state: -1 = grass, 0 = rock
    vector<vector<int>> grid(Y, vector<int>(X, -1));
    
    // Read the grid from bottom to top (as specified in the problem)
    for (int i = Y - 1; i >= 0; i--) {
        for (int j = 0; j < X; j++) {
            char c;
            cin >> c;
            if (c == '*') grid[i][j] = 0; // rock
        }
    }
    
    // BFS queue to simulate spreading
    queue<pair<int, int>> q;
    q.push({My, Mx}); // Start at the initial milkweed position
    grid[My][Mx] = 1; // Mark initial position as invaded in week 1
    
    int maxWeek = 1; // Track the maximum week
    
    // Process the BFS queue
    while (!q.empty()) {
        int y = q.front().first;
        int x = q.front().second;
        q.pop();
        
        int currentWeek = grid[y][x];
        maxWeek = max(maxWeek, currentWeek);
        
        // Try all 8 directions (including diagonals)
        for (int dy = -1; dy <= 1; dy++) {
            for (int dx = -1; dx <= 1; dx++) {
                if (dx == 0 && dy == 0) continue;
                
                int ny = y + dy;
                int nx = x + dx;
                
                // Check if in bounds
                if (ny < 0 || ny >= Y || nx < 0 || nx >= X) continue;
                
                // Check if it's grass and not yet invaded
                if (grid[ny][nx] == -1) {
                    grid[ny][nx] = currentWeek + 1; // Mark as invaded in next week
                    q.push({ny, nx});
                }
            }
        }
    }
    
    cout << maxWeek - 1; // Subtract 1 since we started counting from week 1
    
    return 0;
}
