#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 5;
long long n,k,m,a[N];
int next1[N],next2[N],ans[N];

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    cin >> n >> k >> m;
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }

    int left =1,right = k+1;
    for(int i=1;i<=n;i++){
        while(right+1<=n && a[right+1]-a[i]<a[i]-a[left]){
            right++;
            left++;
        }
        if(a[right]-a[i]>a[i]-a[left]){
            next1[i] = right;
        }else{
            next1[i] = left;
        }
    }
    for(int i=1;i<=n;i++) ans[i] = i;
    while(m){
        if(m&1){
            for(int i=1;i<=n;i++){
                ans[i]=next1[ans[i]];
            }
        }
        m = m>>1;
        memcpy(next2,next1,sizeof(next1));
        for(int i=1;i<=n;i++){
            next1[i] = next2[next1[i]];
        }
    }
    for(int i=1;i<=n;i++){
        cout << ans[i] << " ";
    }


    return 0;
}