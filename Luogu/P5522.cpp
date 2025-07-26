#include <bits/stdc++.h>

using namespace std;
#define ll long long

struct Segtree {
    struct node
    {
        ll lt, rt; //  左右端点
        ll mask1;
        ll mask0;
    };
    vector<node> segtree;

    Segtree(const vector<pair<ll,ll>>& masks){
        ll len = masks.size();
        segtree.assign(4*len, {});
        buildtree(1, 1, len, masks);
    }


    inline void set(ll idx, pair<ll,ll> v){
        singleupdate(1, idx, v);
    }

    pair<ll,ll> query(ll lt, ll rt){
        return rangequery(1, lt, rt);
    }

private:
    
    /*
    更新非叶子节点值
    时间复杂度O(1)
    u 节点编号
    */
    inline void pushup(ll u){
        segtree[u].mask0 = segtree[u<<1].mask0 | segtree[u<<1|1].mask0;
        segtree[u].mask1 = segtree[u<<1].mask1 | segtree[u<<1|1].mask1;
    }

    /*
    构建线段树
    时间复杂度位O(N)
    u  节点编号
    lt 左端点
    rt 右端点
    */
    inline void buildtree(ll u, ll lt, ll rt, const vector<pair<ll,ll>>& masks){
        segtree[u] = {lt, rt}; //更新左右端点
        if(lt == rt){
            segtree[u].mask1=masks[lt-1].first; 
            segtree[u].mask0=masks[lt-1].second; 
        }
        else{
            //更新左右子树
            ll mid = (lt + rt) >> 1;
            buildtree(u<<1, lt, mid, masks); //左子树
            buildtree(u<<1|1, mid+1, rt, masks); //右子树
            //更新当前节点的值
            pushup(u);
        }
    }

    /*
    区间查询
    Q[lt, rt] = sigma(segtree.sum_i)
    时间复杂度O(log n)
    u  当前节点标号
    lt 左端点
    rt 右端点
    */
    pair<ll,ll> rangequery(ll u, ll lt, ll rt){
        if(segtree[u].lt >= lt && segtree[u].rt <= rt){ //当前u区间完全包含在[lt, rt](子区间)
            return {segtree[u].mask1, segtree[u].mask0}; //直接返回当前区间的值
        }
        else if(segtree[u].lt > rt || segtree[u].rt < lt){ //u区间与[lt, rt]完全没有交集
            return {0,0}; //不贡献
        }else{ //u区间与[lt, rt]有交集, 但不是[lt, rt]的子区间
            pair<ll, ll> lr = rangequery(u<<1, lt, rt), rr =  rangequery(u<<1|1, lt, rt);
            return {lr.first | rr.first, lr.second | rr.second};
        }
    }

    /*
    单点修改
    时间复杂度O(log n)
    u 当前节点编号
    t 目标元素(叶子节点)
    v 修改后的值
    */
    inline void singleupdate(ll u, ll t, pair<ll,ll> v){
        if(segtree[u].lt == segtree[u].rt){
            segtree[u].mask1 = v.first; //更新目标节点的值
            segtree[u].mask0 = v.second; //更新目标节点的值
            return;
        }
        ll mid = (segtree[u].lt + segtree[u].rt) >> 1;
        (t<=mid)?
                singleupdate(u<<1, t, v): //目标节点在左子树
                singleupdate(u<<1|1, t, v); //目标节点在右子树
        pushup(u); //更新当前节点
    }


};

pair<ll,ll> getMasks(string str){
    ll mask1 = 0, mask0 = 0;
    for(int i=0;i<str.length();i++){
        if(str[i] == '1'){
            mask1 |= 1<<i;
        }else if(str[i] == '0'){
            mask0 |= 1<<i;
        }
    }
    return {mask1, mask0};
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    ll n, m, q;
    cin >> n >> m >> q;
    vector<pair<ll,ll>> masks(m);
    for(int i=0;i<m;i++){
        string s;
        cin >> s;
        masks[i] = getMasks(s);
    }
    Segtree st(masks);

    ll ans = 0;
    while(q--){
        int op; cin >> op;
        if(op == 0){
            ll l, r; cin >> l >> r;
            auto [mask1, mask0] = st.query(l, r);
            if(mask1 & mask0) ans ^= 0;
            else{
                int unknown = n - __builtin_popcountll(mask1 | mask0);
                ans ^= (1LL << unknown);
            }
        }else{
            ll pos; string s;
            cin >> pos >> s;
            st.set(pos, getMasks(s));
        }
    }
    cout << ans << '\n';
}