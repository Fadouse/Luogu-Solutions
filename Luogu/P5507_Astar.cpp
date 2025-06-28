#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> PIS;

int start, target=0, mp[12][4], dist[1<<24];
PIS pre[1<<24];
priority_queue<PIS, vector<PIS>, greater<PIS>> q;

int fun(int stat){
    int res=0;
    for(int i=0;i<12;i++){
        if(stat >> (i*2)&3 != 0){
            res += 5-(stat>>(i*2)&3);
        }
    }
    return res/2.0;
}

void Astar(){
    memset(dist,0x3f,sizeof(dist));
    q.push({fun(start),start});
    dist[start] = 0;
    while(q.size()){
        PIS p = q.top(); q.pop();
        int stat = p.second;
        if(stat == target){
            cout<<dist[stat]<<endl;
            vector<int> ans;
            while(stat != start){
                ans.push_back(pre[stat].first);
                stat = pre[stat].second;
            }
            for(int i=ans.size()-1;i>=0;i--){
                cout<<ans[i]+1<<" ";
            }
            return;
        }

        for(int i=0;i<12;i++){ // 12
            int tmp=stat;
            int ii= mp[i][tmp>>(i*2)&3];
            int iadd = ((tmp>>(i*2)&3)+1)%4;
            int iiadd = ((tmp>>(ii*2)&3)+1)%4;
            tmp &= ~(3<<(i*2));
            tmp &= ~(3<<(ii*2));
            tmp |= iadd<<(i*2);
            tmp |= iiadd<<(ii*2);
            if(dist[stat]+1 < dist[tmp]){
                dist[tmp] = dist[stat]+1;
                pre[tmp] = {i,stat};
                q.push({dist[tmp]+fun(tmp),tmp}); //log(n)
            }
        }
    }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int a,b,c,d,e;
    for(int i=0;i<12;i++){
        cin>>a>>b>>c>>d>>e;
        start |= (a-1)<<(i*2); // 0~3转为二进制掩码
        mp[i][0] = b-1;
        mp[i][1] = c-1;
        mp[i][2] = d-1;
        mp[i][3] = e-1;
    }
    Astar();
    
    return 0;
}