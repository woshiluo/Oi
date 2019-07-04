# 线段树?前缀和?主席树! -- 主席树初步 -- Luogu P3834 【模板】可持久化线段树 1（主席树）

> 值得一提的是，静态主席树比单纯的线段树求区间和要短……

## 0 前置技能点

- 线段树
- 前缀和
- 离散化(权值线段树求第k大前置技能）
- ~~正常状况下的大脑~~ 一定的Debug能力

## 1 主席树

### 1.1 静态
#### 1.1.1 权值线段树
我们现在看一下这个问题

> 区间第$k$大

我会排序！

> $ N,M \leq 2e5$

我会排序！等下，**时间复杂度**不对

是的，显然这需要一个**数据结构**来维护它

> 我们来想想，如果**只求**第$k$大的话，有什么做法？

平衡树，权值线段树

> 加上区间查询？

我会`Splay`！

> 嗯，`Splay`是一个比较优秀的解决方案

但是权值线段树真的没有用武之地吗
#### 1.1.2 可持久化

> 可持久化

这是一个非常有趣的名词

许多数据结构都可以**可持久化**

> eg: **可持久化**数组，**可持久化**平衡树，**可持久化**并查集等

什么是可持久化呢

可以访问**历史版本**的数据结构，我们通常就称其为**可持久化数据结构**
#### 1.1.3 前缀和与权值线段树

我们先来回顾一下如果我们查询**全局**第$k$大时的步骤

1. 离散化
2. 按排名建立权值线段树
3. 按照与二叉搜索树中查找第$k​$大一样的方法查找并输出

有一种办法，建立 $ n^2 ​$ 棵线段树（枚举每个区间），但这种做法显然是不且实际的

但是如果我们仔细思考便会发现，我们对与区间$ [1,1] [1,2] [1,3] [1,4] \cdots [1,n] ​$ 中建立的权值线段树中的每一个节点都满足前缀和性质

也就是说我们只需要建立$n$棵权值线段树了

#### 1.1.4 可持久化与权值线段树  

到了这一步，我们的问题在空间与时间上都存在了

很明显，我们的空间有太多重复的叶子节点**[区间相同，权值相同]**

所以如果两个节点，它们的左节点（或者右节点）**重复**，我们可以将它们指向一个叶子

经过这么操作我们的时间也得到了大幅度优化，从原来的$O(n^2log(n))​$变成了$O(nlog(n))​$,空间也优化到$nlog(n)​$

这么一来，这些线段树变成一个数据结构，我们可以**访问历史版本**

是的，这就是**可持久化**权值线段树，也称**主席树**

#### 1.1.5 静态主席树
```cpp
#include <cstdio>
#include <algorithm>

const int N=2e5+1e4;

int n,m,l,r,k,tcnt,idcnt;
int nid[N],rt[N],rk[N];

struct val{
    int now,id;
}a[N];

bool cmp(val a,val b){
    return a.now<b.now;
}

struct Persistable_Segment_Tree{
    int left,rig;
    int sum;
}tree[N*20];

void update(int &root,int left,int rig,int val){
    tree[tcnt++]=tree[root];
    tree[tcnt-1].sum++;
    root=tcnt-1;
    if(left==rig) return ;
    int mid=(left+rig)>>1;
    if(val<=mid) update(tree[root].left,left,mid,val);
    else update(tree[root].rig,mid+1,rig,val);
}

int query(int left_root,int rig_root,int k,int left,int rig){
    int dep=tree[tree[rig_root].left].sum-tree[tree[left_root].left].sum;
    if(left==rig) return left;
    int mid=(left+rig)>>1;
    if(k<=dep) return query(tree[left_root].left,tree[rig_root].left,k,left,mid);
    else return query(tree[left_root].rig,tree[rig_root].rig,k-dep,mid+1,rig);
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
    scanf("%d",&a[i].now);
    a[i].id=i;
    }
    std::sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;i++)
    rk[a[i].id]=i;
    tcnt=1;
    for(int i=1;i<=n;i++){
    rt[i]=rt[i-1];
    update(rt[i],1,n,rk[i]);
    }
    for(int i=1;i<=m;i++){
    scanf("%d%d%d",&l,&r,&k);
    printf("%d\n",a[query(rt[l-1],rt[r],k,1,n)].now);
    }
}
```
### 1.2 动态（带修）

# Waiting For Updating
