#include <bits/stdc++.h>

using namespace std;
#define ll long long

struct Segtree {
    struct node
    {
        ll lt, rt; //  左右端点
        ll sum; //     值
        ll cnt;
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

    inline void update(ll lt, ll rt){
        rangeupdate(1, lt, rt);
    }

    ll query(ll lt, ll rt){
        return rangequery(1, lt, rt);
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
    区间修改
    时间复杂度O(log n)
    u  当前节点标号
    lt 左端点
    rt 右端点
    */
    inline void rangeupdate(ll u, ll lt, ll rt){
        if(segtree[u].cnt >= 6) return;
        if(segtree[u].lt >= lt && segtree[u].rt <= rt && segtree[u].rt == segtree[u].lt){
            segtree[u].sum = sqrt(segtree[u].sum);
            segtree[u].cnt ++;
            return;
        }
        if(segtree[u].lt >= lt && segtree[u].rt <= rt){ //当前u区间完全包含在[lt, rt](子区间)
            rangeupdate(u<<1, lt, rt); //更新左节点
            rangeupdate(u<<1|1, lt, rt); //更新右节点
            segtree[u].cnt ++;
            pushup(u);
        }
        else if(segtree[u].lt > rt || segtree[u].rt < lt){ //u区间与[lt, rt]完全没有交集
            return; //不贡献
        }else{ //u区间与[lt, rt]有交集, 但不是[lt, rt]的子区间
            rangeupdate(u<<1, lt, rt); //更新左节点
            rangeupdate(u<<1|1, lt, rt); //更新右节点
            pushup(u);
        }
        return; //按理说不会执行到这
    }
};

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    int n;
    cin >> n;
    vector<ll> nums(n);
    for(int i=0;i<n;i++){
        cin >> nums[i];

    }
    Segtree st(nums);
    ll q;
    cin >> q;
    while (q--)
    {
        ll op, lt, rt;
        cin >> op >> lt >> rt;
        if( lt > rt){
            swap(lt ,rt);
        }
        if(op == 0){
            st.update(lt, rt);
        }else {
            cout << st.query(lt, rt) << '\n';
        }
    }
    


    return 0;
}