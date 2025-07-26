#include <bits/stdc++.h>

using namespace std;
#define ll long long

struct Segtree{
    struct node
    {
        ll lt, rt; //  左右端点
        ll sum; //     值
        ll add; //     懒标记
    };
    vector<node> segtree;

    Segtree(const vector<ll>& nums){
        ll len = nums.size();
        segtree.assign(4*len, {0,0,0,0});
        buildtree(1, 1, len, nums);
    }

    Segtree(const ll* nums, ll size){
        ll len = size;
        segtree.assign(4*len, {0,0,0,0});
        vector<ll> vec; 
        copy(nums, nums + size, std::back_inserter(vec));
        buildtree(1, 1, len, vec);
    }

    /*
    更新懒标记
    时间复杂度O(1)
    u 节点编号
    add 需要懒更新的值
    */
    inline void addtag(ll u, ll add){
        segtree[u].sum += (segtree[u].rt - segtree[u].lt + 1)*add; //u区间子节点数量 x 单个节点需要更新的值
        segtree[u].add += add; //更新懒标记
    }

    /*
    向下更新
    时间复杂度O(1)
    u 节点编号
    */
    inline void pushdown(ll u){
        if(segtree[u].add){
            addtag(u<<1, segtree[u].add);
            addtag(u<<1|1, segtree[u].add);
            segtree[u].add = 0;
        }
    }

    /*
    更新非叶子节点值
    时间复杂度O(1)
    u 节点编号
    */
    inline void pushup(ll u){
        segtree[u].sum = segtree[u<<1].sum+segtree[u<<1|1].sum;
    }

    /*
    构建线段树
    时间复杂度位O(N)
    u  节点编号
    lt 左端点
    rt 右端点
    */
    inline void buildtree(ll u, ll lt, ll rt, const vector<ll>& nums){
        segtree[u] = {lt, rt}; //更新左右端点
        if(lt == rt) segtree[u].sum=nums[lt]; //判断是否为叶子节点，如果是则更新原序列对应的值
        else{
            //更新左右子树
            ll mid = (lt + rt) >> 1;
            buildtree(u<<1, lt, mid, nums); //左子树
            buildtree(u<<1|1, mid+1, rt, nums); //右子树

            //更新当前节点的值
            pushup(u);
        }
    }

    /*
    单点查询
    时间复杂度O(log n)
    u 当前节点编号
    t 目标元素(叶子节点)
    */
    ll singlequery(ll u, ll t){
        pushdown(u); //如果u有懒标记，则更新子节点
        if(segtree[u].lt == segtree[u].rt) return segtree[u].sum; //判断是否为叶子节点，如果是则返回
        ll mid = (segtree[u].lt + segtree[u].rt) >> 1;
        return (t<=mid)?
                    singlequery(u<<1, t): //目标节点在左子树
                    singlequery(u<<1|1, t); //目标节点在右子树
        return 1; //应该执行不到(?)
    }

    /*
    区间查询
    Q[lt, rt] = sigma(segtree.sum_i)
    时间复杂度O(log n)
    u  当前节点标号
    lt 左端点
    rt 右端点
    */
    ll rangequery(ll u, ll lt, ll rt){
        if(segtree[u].lt >= lt && segtree[u].rt <= rt){ //当前u区间完全包含在[lt, rt](子区间)
            return segtree[u].sum; //直接返回当前区间的值
        }
        else if(segtree[u].lt > rt || segtree[u].rt < lt){ //u区间与[lt, rt]完全没有交集
            return 0; //不贡献
        }else{ //u区间与[lt, rt]有交集, 但不是[lt, rt]的子区间
            pushdown(u); //如果u有懒标记，则更新子节点
            return rangequery(u<<1, lt, rt) + rangequery(u<<1|1, lt, rt);
        }
        return 1; //按理说不会执行到这
    }

    /*
    单点修改
    时间复杂度O(log n)
    u 当前节点编号
    t 目标元素(叶子节点)
    v 修改后的值
    */
    inline void singleupdate(ll u, ll t, ll v){
        if(segtree[u].lt == segtree[u].rt){
            segtree[u].sum = v; //更新目标节点的值
            return;
        }
        pushdown(u); //如果u有懒标记，则更新子节点
        ll mid = (segtree[u].lt + segtree[u].rt) >> 1;
        (t<=mid)?
                singleupdate(u<<1, t, v): //目标节点在左子树
                singleupdate(u<<1|1, t, v); //目标节点在右子树
        pushup(u); //更新当前节点
    }

    /*
    区间修改 with 懒标记
    时间复杂度O(log n)
    u  当前节点标号
    lt 左端点
    rt 右端点
    v  添加的值
    */
    inline void rangeupdate(ll u, ll lt, ll rt, ll v){
        if(segtree[u].lt >= lt && segtree[u].rt <= rt){ //当前u区间完全包含在[lt, rt](子区间)
            return addtag(u, v); //添加懒标记
        }
        else if(segtree[u].lt > rt || segtree[u].rt < lt){ //u区间与[lt, rt]完全没有交集
            return; //不贡献
        }else{ //u区间与[lt, rt]有交集, 但不是[lt, rt]的子区间
            pushdown(u);
            rangeupdate(u<<1, lt, rt, v); //更新左节点
            rangeupdate(u<<1|1, lt, rt, v); //更新右节点
            pushup(u);
        }
        return; //按理说不会执行到这
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<ll> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }

    vector<ll> b = a;
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    for(int i = 0; i < n; i++){
        a[i] = lower_bound(b.begin(), b.end(), a[i]) - b.begin() + 1;
    }
    int m = (int)b.size();

    Segtree st(vector<ll>(m+1, 0));  

    ll inv_count = 0;
    for(int i = 0; i < n; i++){
        if(a[i] < m){
            inv_count += st.rangequery(1, a[i]+1, m);
        }
        st.rangeupdate(1, a[i], a[i], 1);
    }

    cout << inv_count << "\n";
    return 0;
}
