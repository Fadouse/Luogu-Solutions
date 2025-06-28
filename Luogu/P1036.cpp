#include <bits/stdc++.h>

using namespace std;

int n, k;
int nums[21];

bool isPrime(int x){
    if (x < 2) return false;
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) return false;
    }
    return true;
}

int dfs(int x , int y, int z){
    if(n - x < k - y) return 0; // not enough elements left to fill the remaining slots
    if(y == k) { // all slots filled
        if(z != 0 && isPrime(z)) { // check if the sum is prime and not already counteds
            return 1; // found a valid combination        
        }else{
            return 0;
        }
    }
    return dfs(x + 1, y, z) + dfs(x + 1, y + 1, z + nums[x]);
}
int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    cout << dfs(0,0,0);
    return 0;
}