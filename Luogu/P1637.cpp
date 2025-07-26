#include <bits/stdc++.h>

using namespace std;
#define ll long long

struct Segtree {
    struct node
    {
        ll lt, rt; //  左右端点
        ll sum; //     值
    };
    vector<node> segtree;

    Segtree(const vector<ll>& nums){
        ll len = nums.size();
        segtree.assign(4*len, {});
        buildtree(1, 1, len, nums);
    }
    ll query(ll lt, ll rt) {
        if (lt > rt) return 0;
        return rangequery(1, lt, rt);
    }


    inline void update(ll idx, ll val){
        singleupdate(1, idx, val);
    }

private:

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
        if(lt == rt) segtree[u].sum=nums[lt-1]; //判断是否为叶子节点，如果是则更新原序列对应的值
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
            segtree[u].sum += v; //更新目标节点的值
            return;
        }
        ll mid = (segtree[u].lt + segtree[u].rt) >> 1;
        (t<=mid)?
                singleupdate(u<<1, t, v): //目标节点在左子树
                singleupdate(u<<1|1, t, v); //目标节点在右子树
        pushup(u); //更新当前节点
    }

};

int main() {
     ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // 离散化
    vector<ll> vals = a;
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    int m = vals.size();
    vector<int> id(n);
    for (int i = 0; i < n; i++) {
        id[i] = int(lower_bound(vals.begin(), vals.end(), a[i]) - vals.begin()) + 1;
    }

    // 前缀和线段树 和 后缀和线段树
    Segtree pre(vector<ll>(m, 0)), suf(vector<ll>(m, 0));
    // 后缀树初始化：把所有元素都加进来
    for (int i = 0; i < n; i++) {
        suf.update(id[i], 1);
    }

    ll ans = 0;
    for (int j = 0; j < n; j++) {
        // 当前 a[j] 从后缀中移除
        suf.update(id[j], -1);
        // 计算以 j 为中点的三元组左右两侧小于 / 大于 的数量
        ll L = pre.query(1, id[j] - 1);
        ll R = suf.query(id[j] + 1, m);
        ans += L * R;
        // 把 a[j] 加入前缀
        pre.update(id[j], 1);
    }

    cout << ans << "\n";
    return 0;
}