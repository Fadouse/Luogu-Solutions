#include <bits/stdc++.h>

using namespace std;

#define ll long long

constexpr ll NEG_INF = -(ll)1e18;
const int N = 5e5+5; //   原序列大小
ll ori[N]; // 原序列


struct node
{
    ll lt, rt; //  左右端点
    ll sum; //     值
    ll maxsum;
    ll presum;
    ll subsum;
}segtree[N*4];

/*
题目要求
给出lt, rt
找出[lt, rt]的连续子区间 相加的最大值
*/

/*
更新非叶子节点值
时间复杂度O(1)
u 节点编号
left 左节点
right 右节点
*/
void pushup(node &root, node &left, node &right){
    root.sum = left.sum + right.sum;
    root.maxsum = max({left.maxsum, right.maxsum, left.subsum+right.presum});
    root.presum = max(left.presum, left.sum + right.presum);
    root.subsum = max(right.subsum, right.sum + left.subsum);
}

void pushup(ll u){
    pushup(segtree[u], segtree[u<<1], segtree[u<<1|1]);
}

/*
构建线段树
时间复杂度位O(N)
u  节点编号
lt 左端点
rt 右端点
*/
void buildtree(ll u, ll lt, ll rt){
    segtree[u] = {lt, rt}; //更新左右端点
    if(lt == rt) segtree[u].sum = segtree[u].maxsum = segtree[u].presum = segtree[u].subsum = ori[lt]; //判断是否为叶子节点，如果是则更新原序列对应的值
    else{
        //更新左右子树
        ll mid = (lt + rt) >> 1;
        buildtree(u<<1, lt, mid); //左子树
        buildtree(u<<1|1, mid+1, rt); //右子树

        //更新当前节点的值
        pushup(u);
    }
}


/*
单点修改
时间复杂度O(log n)
u 当前节点编号
t 目标元素(叶子节点)
v 修改后的值
*/
void singleupdate(ll u, ll t, ll v){
    if(segtree[u].lt == segtree[u].rt){
        segtree[u].sum = segtree[u].maxsum = segtree[u].presum = segtree[u].subsum = v; //更新目标节点的值
        return;
    }
    ll mid = (segtree[u].lt + segtree[u].rt) >> 1;
    (t<=mid)?
            singleupdate(u<<1, t, v): //目标节点在左子树
            singleupdate(u<<1|1, t, v); //目标节点在右子树
    pushup(u); //更新当前节点
}


/*
区间查询
Q[lt, rt] = sigma(segtree.sum_i)
时间复杂度O(log n)
u  当前节点标号
lt 左端点
rt 右端点
*/
node rangequery(ll u, ll lt, ll rt){
    if(segtree[u].lt >= lt && segtree[u].rt <= rt){ //当前u区间完全包含在[lt, rt](子区间)
        return segtree[u];
    }
    else if(segtree[u].lt > rt || segtree[u].rt < lt){ //u区间与[lt, rt]完全没有交集
        return node{0, 0,
                    0,           // sum = 0
                    NEG_INF,     // maxsum
                    NEG_INF,     // presum
                    NEG_INF};    // subsum
    }else{ //u区间与[lt, rt]有交集, 但不是[lt, rt]的子区间
        node rightResult = rangequery(u<<1|1, lt, rt);
        node leftResult = rangequery(u<<1, lt, rt);
        node res = {};
        pushup(res, leftResult, rightResult);
        return res;
    }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        cin >> ori[i];
    }
    buildtree(1, 1, n);
    while (m--)
    {
        ll op, lt, rt;
        cin >> op >> lt >> rt;

        if(op == 1){
            if(lt > rt){
                swap(lt, rt);
            }
            cout << rangequery(1, lt, rt).maxsum << endl;
        }else{
            singleupdate(1, lt, rt);
        }
    }
    
    return 0;
}