#include <bits/stdc++.h>

using namespace std;

#define ll long long

const int N = 1e5+5; //   原序列大小
ll ori[N]; // 原序列


struct node
{
    ll lt, rt; //  左右端点
    ll sum; //     值
    ll K, D; //     懒标记
}segtree[N*4];


/*
题目要求，维护原始数组
option
1: 区间修改
将区间[lt, rt]内元素应用一个等差数列的值，从lt开始每一项的值为[a_i + K + D*i]

2: 单点查询(代码相比原始线段树无需修改)
*/

/*
更新懒标记
时间复杂度O(1)
u 节点编号
add 需要懒更新的值
*/
ll addtag(ll u, ll K, ll D){
    //更新当前节点的值: 原始值+等差数列求和
    ll len = segtree[u].rt - segtree[u].lt + 1; //当前区间长度
    //首相+尾项*项数/2
    segtree[u].sum += (2*K + (len - 1) * D)*len / 2;
    //更新懒标记
    segtree[u].K += K; 
    segtree[u].D += D; 
    return 1;
}

/*
更新非叶子节点值
时间复杂度O(1)
u 节点编号
*/
ll pushup(ll u){
    segtree[u].sum = segtree[u<<1].sum+segtree[u<<1|1].sum;
    return segtree[u].sum;
}

/*
向下更新
时间复杂度O(1)
u 节点编号
*/
ll pushdown(ll u){
    if(segtree[u].K || segtree[u].D){
        addtag(u<<1, segtree[u].K, segtree[u].D);
        ll mid = (segtree[u].lt + segtree[u].rt) >> 1;
        addtag(u<<1|1, segtree[u].K + ((mid+1)-segtree[u].lt)*segtree[u].D, segtree[u].D); //标记
        segtree[u].K = 0;
        segtree[u].D = 0;
    }
    return 1;
}

/*
构建线段树
时间复杂度位O(N)
u  节点编号
lt 左端点
rt 右端点
*/
ll buildtree(ll u, ll lt, ll rt){
    segtree[u] = {lt, rt}; //更新左右端点
    if(lt == rt) segtree[u].sum=ori[lt]; //判断是否为叶子节点，如果是则更新原序列对应的值
    else{
        //更新左右子树
        ll mid = (lt + rt) >> 1;
        buildtree(u<<1, lt, mid); //左子树
        buildtree(u<<1|1, mid+1, rt); //右子树

        //更新当前节点的值
        pushup(u);
    }
    return 1;
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
区间修改 with 懒标记
时间复杂度O(log n)
u  当前节点标号
lt 左端点
rt 右端点
K  首相
D  公差
*/
ll rangeupdate(ll u, ll lt, ll rt, ll K, ll D){
    if(segtree[u].lt >= lt && segtree[u].rt <= rt){ //当前u区间完全包含在[lt, rt](子区间)
        return addtag(u, K + (segtree[u].lt - lt)*D, D); //添加懒标记
    }
    else if(segtree[u].lt > rt || segtree[u].rt < lt){ //u区间与[lt, rt]完全没有交集
        return 0; //不贡献
    }else{ //u区间与[lt, rt]有交集, 但不是[lt, rt]的子区间
        pushdown(u);
        rangeupdate(u<<1, lt, rt, K, D); //更新左节点
        rangeupdate(u<<1|1, lt, rt, K, D); //更新右节点
        pushup(u);
    }
    return 1; //按理说不会执行到这
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    ll n, m;
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        cin >> ori[i];
    }

    buildtree(1, 1, n);

    while (m--)
    {
        int op;
        cin >> op;
        switch (op){
            case 1:
                ll lt, rt, K, D;
                cin >> lt >> rt >> K >> D;
                rangeupdate(1, lt, rt, K, D);
                break;
            case 2:
                ll t;
                cin >> t;
                cout << singlequery(1, t)<< '\n';
                break;
        }
    }
    

    return 0;
}