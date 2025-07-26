#include <bits/stdc++.h>

using namespace std;
#define ll long long

struct Segtree {
    struct node
    {
        ll lt, rt; //  左右端点
        ll mask; //     值
        ll color; //     懒标记
    };
    vector<node> segtree;

    Segtree(const vector<ll>& nums){
        ll len = nums.size();
        segtree.assign(4*len, {});
        buildtree(1, 1, len, nums);
    }

    Segtree(const ll* nums, ll size){
        ll len = size;
        segtree.assign(4*len, {});
        vector<ll> vec; 
        copy(nums, nums + size, std::back_inserter(vec));
        buildtree(1, 1, len, vec);
    }

    inline void update(ll lt, ll rt, ll v){
        rangeupdate(1, lt, rt, v);
    }

    ll query(ll lt, ll rt){
        return rangequery(1, lt, rt);
    }

private:
    /*
    更新懒标记
    时间复杂度O(1)
    u 节点编号
    add 需要懒更新的值
    */
    inline void addtag(ll u, ll color){
        segtree[u].mask = 1<<color; //u区间子节点数量 x 单个节点需要更新的值
        segtree[u].color = color; //更新懒标记
    }

    /*
    向下更新
    时间复杂度O(1)
    u 节点编号
    */
    inline void pushdown(ll u){
        if(segtree[u].color){
            addtag(u<<1, segtree[u].color);
            addtag(u<<1|1, segtree[u].color);
            segtree[u].color = 0;
        }
    }

    /*
    更新非叶子节点值
    时间复杂度O(1)
    u 节点编号
    */
    inline void pushup(ll u){
        segtree[u].mask = segtree[u<<1].mask | segtree[u<<1|1].mask;
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
        if(lt == rt) segtree[u].mask=1<<nums[lt-1]; //判断是否为叶子节点，如果是则更新原序列对应的值
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
            return segtree[u].mask; //直接返回当前区间的值
        }
        else if(segtree[u].lt > rt || segtree[u].rt < lt){ //u区间与[lt, rt]完全没有交集
            return 0; //不贡献
        }else{ //u区间与[lt, rt]有交集, 但不是[lt, rt]的子区间
            pushdown(u); //如果u有懒标记，则更新子节点
            return rangequery(u<<1, lt, rt) | rangequery(u<<1|1, lt, rt);
        }
        return 1; //按理说不会执行到这
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

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    int L, T, O;
    cin >> L >> T >> O;
    Segtree st = Segtree(vector<ll>(L, 1));
    while (O--)
    {
        char op;
        ll lt, rt, c;
        cin >> op >> lt >> rt;
        if(lt > rt){
            swap(lt, rt);
        }
        if(op == 'C'){
            cin >> c;
            st.update(lt, rt, c);
        }else{
            cout << __builtin_popcount(st.query(lt, rt)) << '\n';
        }
    }
    
    return 0;
}