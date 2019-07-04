## 最大流问题
> 给定一个有向图，有两个特别的点$S$和$T$，每条边都有一个容量限制 ，现询问，从 $ S $ 到 $ T $ 最大可以流多少过去  

第一眼看过去，跟水厂子往水管里灌水一样简单

问题在于这个东西并不好计算

有没有办法计算它呢

如果我们每次都枚举我们怎么走的话,时间复杂度是不可估计的

我们有没有办法让我们走过去的流反悔呢？

有，这里就要引入两个概念: **残余网络** && **反向边**
### 残余网络

对于每次我们跑出来的一条流过过后以每条边现能通过的**最大流量**所成的网络图叫**残余网络**

### 反向边
> 反向边是在给算法一个反悔的机会

如果原图中有一个从 $ u $ 到 $ v $ 的边，则从 $ v $ 到 $ u $ 的边就是这条边的反向边

反向边如何后悔呢？

## EK 算法

我们在每一次流过去大小为 $ t $ 一条流时，除了将原有的边上流量减去$ t $之外，也需要将其反向边的流来**加上**$ t $ 

这样以来，我们就保证以下的两点
- 残余网络中总流量和原图相同
- 在残余网络中走出来的流一定存在

至于怎么解释，咱的看法是，写两边就明白了，看别人的解释之后越看越懵

我们一直寻找可行的流，直到**无法**流到$ t $为止，已经的流过去的和就一定是一个最大流

复杂度： $O(EK(n,m))=O(m^2n)=O(TLE)$

## Dinic 算法

EK算法使用bfs寻找流，但bfs寻找流的一些特性决定其不容易实现**当前弧优化**，以及**多路增广**

而且EK算法还会走回路...

这种情况下我们又要引出一个新概念: 分层图

### 分层图

我们以$ S $为根，可以往下走的边流大于0，然后像树一样记录每个节点的深度（多次访问取第一次）

这样以来我们可以确定以下两点:
- 避免了回路的可能
- 如果存在可行流，则点$ T $深度一定存在

等一下，如果我们搜索的时候都限制只能往当前节点深度+1的点去搜了，我们是不是就可以dfs了？
是的qwq

不过我们先来看一下普通的Dinic吧[Luogu P3376]
```cpp
#include <cstdio>
#include <cstring>

inline int Min(int a,int b){return a<b?a:b;}

const int N=11000;
const int M=110000;

int n,m,s,t,u,v,w;

// edge start
struct edge{
    int next,to,val,un;
}e[M<<1];
int ehead[N],ecnt;
inline void add_edge(int now,int to,int val,int un){
    ecnt++;
    e[ecnt].to=to;
    e[ecnt].val=val;
    e[ecnt].next=ehead[now];
    e[ecnt].un=ecnt+un;
    ehead[now]=ecnt;
}
// edge end

namespace Dinic{
    int depth[N];
    int q[N],head,tail;
    inline bool bfs(){
        memset(depth,0,sizeof(depth));
        head=tail=0;
        q[head]=s;
        depth[s]=1;
        while(head<=tail){
            for(int i=ehead[q[head]];i;i=e[i].next){
                if(e[i].val>0&&depth[e[i].to]==0){
                    q[++tail]=e[i].to;
                    depth[e[i].to]=depth[q[head]]+1;
                }
            }
            head++;
        }
        if(depth[t]==0) return false;
        else return true;
    }

    int dfs(int now,int dist){
        if(now==t) return dist;
        for(int i=ehead[now];i;i=e[i].next){
            if(depth[e[i].to]==depth[now]+1&&e[i].val!=0){
                int di=dfs(e[i].to,Min(dist,e[i].val));
                if(di>0){
                    e[i].val-=di;
                    e[e[i].un].val+=di;
                    return di;
                }
            }
        }
        return 0;
    }
    inline int dinic(){
        int ans=0;
        while(bfs()){
            while(int d=dfs(s,0x7fffffff)) ans+=d;
        }
        return ans;
    }
}

int main(){
    scanf("%d%d%d%d",&n,&m,&s,&t);
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&u,&v,&w);
        add_edge(u,v,w,1);
        add_edge(v,u,0,-1);
    }
    printf("%d",Dinic::dinic());
}
```
好了，我们来讲讲两个优化: **当前弧优化** && **多路增广**
### 当前弧优化

在当前状况下已经有一次从$ u $到$ v $的增广,则不存在第二次从$ u $到$ v $的增广

故此在我们遍历边的时候，我们可以不从`ehead[now]`开始，而是从上一次遍历过的边的下一个开始

```cpp
namespace Dinic{
    int depth[N],rnow[N];
    int q[N],head,tail;
    inline bool bfs(){
        memset(depth,0,sizeof(depth));
        head=tail=0;
        q[head]=s;
        depth[s]=1;
        while(head<=tail){
            for(int i=ehead[q[head]];i;i=e[i].next){
                if(e[i].val>0&&depth[e[i].to]==0){
                    q[++tail]=e[i].to;
                    depth[e[i].to]=depth[q[head]]+1;
                }
            }
            head++;
        }
        if(depth[t]==0) return false;
        else return true;
    }

    int dfs(int now,int dist){
        if(now==t) return dist;
        for(int& i=rnow[now];i;i=e[i].next){
            if(depth[e[i].to]==depth[now]+1&&e[i].val!=0){
                int di=dfs(e[i].to,Min(dist,e[i].val));
                if(di>0){
                    e[i].val-=di;
                    e[e[i].un].val+=di;
                    return di;
                }
            }
        }
        return 0;
    }
    inline int dinic(){
        int ans=0;
        while(bfs()){
            for(int i=1;i<=n;i++) rnow[i]=ehead[i];
            while(int d=dfs(s,0x7fffffff)) ans+=d;
        }
        return ans;
    }
}
```

### 多路增广

很多时候在dfs的时候，我们的`dist`还没用完就`return`了，很可惜了有没有

多路增广就可以避免这些问题，我们把剩下的`dist`，继续往下找！
```cpp
#include <cstdio>
#include <cstring>

inline int Min(int a,int b){return a<b?a:b;}

const int N=11000;
const int M=110000;

int n,m,s,t,u,v,w;

// edge start
struct edge{
    int next,to,val,un;
}e[M<<1];
int ehead[N],ecnt;
inline void add_edge(int now,int to,int val,int un){
    ecnt++;
    e[ecnt].to=to;
    e[ecnt].val=val;
    e[ecnt].next=ehead[now];
    e[ecnt].un=ecnt+un;
    ehead[now]=ecnt;
}
// edge end

namespace Dinic{
    int depth[N],rnow[N];
    int q[N],head,tail;
    inline bool bfs(){
        memset(depth,0,sizeof(depth));
        head=tail=0;
        q[head]=s;
        depth[s]=1;
        while(head<=tail){
            for(int i=ehead[q[head]];i;i=e[i].next){
                if(e[i].val>0&&depth[e[i].to]==0){
                    q[++tail]=e[i].to;
                    depth[e[i].to]=depth[q[head]]+1;
                }
            }
            head++;
        }
        if(depth[t]==0) return false;
        else return true;
    }

    int dfs(int now,int dist){
        if(now==t) return dist;
        int fl=0,di;
        for(int& i=rnow[now];i;i=e[i].next){
            if(depth[e[i].to]==depth[now]+1&&e[i].val!=0){
                di=dfs(e[i].to,Min(dist,e[i].val));
                if(di>0){
                    e[i].val-=di;
                    e[e[i].un].val+=di;
                    fl+=di;
                    dist-=di;
                    if(!dist) break;
                }
            }
        }
        return fl;
    }
    inline int dinic(){
        int ans=0;
        while(bfs()){
            for(int i=1;i<=n;i++) rnow[i]=ehead[i];
            while(int d=dfs(s,0x7fffffff)) ans+=d;
        }
        return ans;
    }
}

int main(){
    scanf("%d%d%d%d",&n,&m,&s,&t);
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&u,&v,&w);
        add_edge(u,v,w,1);
        add_edge(v,u,0,-1);
    }
    printf("%d",Dinic::dinic());
}
```

就这些了，那么优化过后的复杂度是什么呢
$O(Dinic(n,m))=O(n^2m)=O(AC)$

还有一个ISAP算法，不在今天的讨论之内，毕竟复杂度和`Dinic`差别不大且常数略大

## End
