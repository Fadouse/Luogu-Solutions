#include <bits/stdc++.h>

using namespace std;
#define ll double

struct Segtree {
    struct node
    {
        int lt, rt; //  左右端点
        ll sum; //     值
        ll qsum;
        ll add; //     懒标记

    };
    vector<node> segtree;

    Segtree(const vector<ll>& nums){
        ll len = nums.size();
        segtree.assign(4*len, {});
        buildtree(1, 1, len, nums);
    }


    inline void update(ll lt, ll rt, ll v){
        rangeupdate(1, lt, rt, v);
    }

    pair<ll, ll> query(ll lt, ll rt){
        return rangequery(1, lt, rt);
    }

private:
    /*
    更新懒标记
    时间复杂度O(1)
    u 节点编号
    add 需要懒更新的值
    */
    inline void addtag(int u, ll add){
        ll oldsum = segtree[u].sum;
        segtree[u].sum += (segtree[u].rt - segtree[u].lt + 1)*add; //u区间子节点数量 x 
        segtree[u].qsum = segtree[u].qsum + 2*add*oldsum + (segtree[u].rt - segtree[u].lt + 1)*add*add; //平方和
        segtree[u].add += add; //更新懒标记
    }

    /*
    向下更新
    时间复杂度O(1)
    u 节点编号
    */
    inline void pushdown(int u){
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
    inline void pushup(int u){
        segtree[u].sum = segtree[u<<1].sum+segtree[u<<1|1].sum;
        segtree[u].qsum = segtree[u<<1].qsum+segtree[u<<1|1].qsum;
    }

    /*
    构建线段树
    时间复杂度位O(N)
    u  节点编号
    lt 左端点
    rt 右端点
    */
    inline void buildtree(int u, int lt, int rt, const vector<ll>& nums){
        segtree[u] = {lt, rt}; //更新左右端点
        if(lt == rt){
            segtree[u].sum=nums[lt-1]; //判断是否为叶子节点，如果是则更新原序列对应的值
            segtree[u].qsum = nums[lt-1] * nums[lt-1];
        }
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
    pair<ll, ll> rangequery(int u, int lt, int rt){
        if(segtree[u].lt >= lt && segtree[u].rt <= rt){ //当前u区间完全包含在[lt, rt](子区间)
            return {segtree[u].sum, segtree[u].qsum}; //直接返回当前区间的值
        }
        else if(segtree[u].lt > rt || segtree[u].rt < lt){ //u区间与[lt, rt]完全没有交集
            return {0, 0}; //不贡献
        }else{ //u区间与[lt, rt]有交集, 但不是[lt, rt]的子区间
            pushdown(u); //如果u有懒标记，则更新子节点
            auto left = rangequery(u<<1, lt, rt);
            auto right = rangequery(u<<1|1, lt, rt);
            return {left.first + right.first,left.second +right.second};
        }
    }

    /*
    区间修改 with 懒标记
    时间复杂度O(log n)
    u  当前节点标号
    lt 左端点
    rt 右端点
    v  添加的值
    */
    inline void rangeupdate(int u, int lt, int rt, ll v){
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
    cout.setf(ios::fixed);
    cout << setprecision(4);
    int n, q;
    cin >> n >> q;
    vector<ll> nums(n,0);
    for(int i=0; i<n;i++){
        cin >> nums[i];
    }
    Segtree st = Segtree(nums);
    while (q--)
    {
        double op, lt, rt, v;
        cin >> op >> lt >> rt;
        if(op == 1){
            cin >> v;
            st.update(lt, rt, v);
        }else if(op == 2){
            cout << (double) st.query(lt, rt).first / (rt - lt + 1) << '\n';
        }else if(op == 3){
            auto temp = st.query(lt, rt);
            double sum = temp.first;
            double qsum = temp.second;
            double len = rt - lt + 1;
            cout << (qsum - sum * sum / len) / len << '\n';
        }
    }
    
    return 0;
}