#include <bits/stdc++.h>

using namespace std;

int count(vector<int>& nums, int v, int a, int b){
    if(v == nums.size()) return max(a, b);
   //第一个选
   int r1 = count(nums, v+1, a+nums[v], b);

   //第二个选
   int r2 = count(nums, v+1, a, b+nums[v]);

   return min(r1, r2);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int s1, s2, s3, s4;
    cin >> s1 >> s2 >> s3 >> s4;
    vector<int> A(s1), B(s2), C(s3), D(s4);
    for(int &i:A) cin>>i;
    for(int &i:B) cin>>i;
    for(int &i:C) cin>>i;
    for(int &i:D) cin>>i;
    // cout << count(A, 0, 0, 0) << " " << count(B, 0, 0, 0) << " " << count(C, 0, 0, 0) << " " << count(D, 0, 0, 0) << endl; 
    cout << count(A, 0, 0, 0) + count(B, 0, 0, 0) + count(C, 0, 0, 0) + count(D, 0, 0, 0);

    return 0;
}