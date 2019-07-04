## Luogu  P2607 [ZJOI2008]骑士

> 题目链接: <https://www.luogu.org/problemnew/show/P2607>

题目意思非常简单，给你一张图，然后图中不能选最大相邻点，最后最大的选中的点的权值

很容易想到 没有上司的舞会 这种树形 DP 题目，但是显然，这，并不是一棵树

根据题目可得，每一个人只会有一条出边，即，这张图中，一张节点个数为 $n$ 的联通块，会有 $n$ 条边

环套树没得跑了

即每一个联通块中一定有一条边，删掉后就是树了

设这条边为 $u - v$ 的边，则 $\max(f_{u,0}, f_{u,1})$ 就是这个联通块的答案

建双向边判环即可

至于代码中的 xor ，当反向边即可

### 代码

```cpp
#include <cstdio>

inline long long Max(long long a, long long b) {return a > b? a: b;}

const int N = 1100000;

// edge start
struct node{
    int next, to;
}e[N << 1];
int ehead[N], ecnt;
inline void add_edge(int now, int to){
    ecnt ++; 
    e[ecnt].to = to;
    e[ecnt].next = ehead[now];
    ehead[now] = ecnt;
}
// edge end

int n, from, to, cir_edge;
int fig[N];
long long f[N][2];
bool vis[N];

void tarjan(int now, int fa){
    vis[now] = true;
    for(int i = ehead[now]; i > 1; i = e[i].next){
        if( (i ^ 1) == fa ) 
            continue;
        if(vis[ e[i].to ]){
            from = now, to = e[i].to; 
            cir_edge = i;
            continue;
        }
        tarjan(e[i].to, i);
    }
}

void dfs(int now, int fa){
    f[now][0] = 0;
    f[now][1] = fig[now];
    for(int i = ehead[now]; i > 1; i = e[i].next){
        if( (i ^ 1) == fa ) 
            continue;
        if(i == cir_edge || (i ^ 1) == cir_edge)
            continue;
        dfs(e[i].to, i);
        f[now][1] += f[ e[i].to ][0];
        f[now][0] += Max(f[ e[i].to ][1], f[ e[i].to ][0]);
    }
}

int main(){
    ecnt = 1;
    scanf("%d", &n);
    for(int i = 1, tmp; i <= n; i++){
        scanf("%d%d", &fig[i], &tmp);
        add_edge(i, tmp);
        add_edge(tmp, i);
    }
    long long ans = 0;
    for(int i = 1; i <= n; i++){
        if(vis[i])
            continue;
        tarjan(i, -2);
        dfs(from, -1);
        long long temp = f[from][0];
        dfs(to, -1);
        temp = Max(temp, f[to][0]);
        ans += temp;
    }
    printf("%lld", ans);
}
```

