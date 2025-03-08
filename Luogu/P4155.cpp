#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;
struct node{
    int id, left, right;
}a[2*N];
int go[2*N][30];
int n,m,ans[N];
bool cmp(node &a, node &b){
    return a.right < b.right;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        a[i].id = i;
        cin >> a[i].left >> a[i].right;
        if(a[i].right < a[i].left){
            a[i].right += m;
        }
    }

    sort (a+1, a+n+1, cmp);
    for(int i=1;i<=n;i++){
        a[i+n].left = a[i].left + m;
        a[i+n].right = a[i].right + m;
    }
    for(int i=1, j =i;i<=2*n;i++){
        while(j<=2*n && a[j].left <= a[i].right){
            j++;
        }
        go[i][0] = j-1;
    }

    for(int j=1; j<20;j++){
        for(int i=1;i+(1<<j)-1<=2*n;i++){
            go[i][j] = go[go[i][j-1]][j-1];
        }
    }
    for(int start =1; start <=n; start ++){
        int t=start;
        int cnt = 1;
        for(int x=19;x>=0;x--){
            int end = go[t][x];
            if(end !=0 && a[end].right - a[start].left + 1 <= m){
                cnt += (1<<x);
                t = end;
            }
        }
        ans[a[start].id] = cnt+1;
    }
    for(int i=1;i<=n;i++){
        cout << ans[i] << " ";
    }
    return 0;
}