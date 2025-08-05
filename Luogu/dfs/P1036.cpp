#include <bits/stdc++.h>

using namespace std;

bool isPrim(int x){
    if (x <= 1) return false;
    for(int i=2;i*i<=x;i++) if(x % i == 0) return false;
    return true;
}

int dfs(vector<int>& vec, int idx, int sum, int used, int &target){
    if(used == target){
        if(isPrim(sum)) return 1;
        else return 0;
    }
    if(idx == vec.size()) return 0;

    return dfs(vec, idx+1, sum, used, target) + dfs(vec, idx+1, sum+vec[idx], used+1, target);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int n, k;
    cin >> n >> k;
    vector<int> nums(n);
    for(int &i:nums) cin>>i;

    cout << dfs(nums, 0, 0, 0, k);
    
    return 0;
}