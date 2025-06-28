#include <bits/stdc++.h>

using namespace std;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n;
    char c;
    cin >> n >> c;
    
    // Create the n×n matrix filled with '.'
    vector<vector<char>> matrix(n, vector<char>(n, '.'));
    
    // Calculate the middle position
    int mid = n / 2;
    
    // Fill the diamond pattern
    for (int i = 0; i < n; i++) {
        int distance_from_mid = abs(i - mid);
        int start = distance_from_mid;
        int end = n - 1 - distance_from_mid;
        
        for (int j = start; j <= end; j++) {
            int distance = abs(j - mid) + abs(i - mid);
            char letter = c - distance;
            if (letter < 'A')
                letter = '.';
            matrix[i][j] = letter;
        }
    }
    
    // Print the matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j];
        }
        cout << '\n';
    }
    
    return 0;
}