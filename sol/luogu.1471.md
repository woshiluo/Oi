## Luogu P1471 方差

> 我都快忘记还有一种公式叫完全平方公式了...

$$ (a + b) ^ 2 = a ^ 2 + b ^ 2 + 2ab $$

对，就是它，这道题目的核心

### 0x01 分析题目

> 题目链接: [https://www.luogu.org/problemnew/show/P1471]

让我们看看什么是方差

> 对于一个长度为 $ n $ 的数列 $ A $ ,其方差为
> $$ \frac{1}{n} \sum^{n}\_{i=1}(A\_i - k)^2 $$
> 其中，$ k $ 为 $ A $ 数列的平均数

emmm, 看起来好复杂啊，等一下，这里有个平方

$$
\begin{align}
\frac{1}{n} \sum^{n}\_{i=1}(A\_i - k)^2 &= \frac{1}{n} \sum^{n}\_{i=1}{A\_i ^ 2 + k ^ 2 + 2A\_ik} \\\\
&= \frac{1}{n} [\sum^{n}\_{i=1}{A\_i ^ 2} + nk^2 + 2k(\sum^{n}\_{i=1}A\_i)] 
\end{align}
$$

恩，舒服多了

看一下操作，区间加，区间平均数（区间求和),区间方差？

区间方差怎么求？

先回到刚才的式子

然后，$ nk^2 $可以直接线段树求和处理出来  
$2k(\sum^{n}\_{i=1}A\_i)$ 同上


$ \sum^{n}\_{i=1}{A\_i ^ 2} $怎么办？

回到完全平方公式，我们求平方和的时候，给数字$A\_i$加$x$相当于把这个原$A\_i^2$加上 $ (A\_i + x) ^ 2 - A\_i ^ 2 = (A\_i ^ 2 + x ^ 2 + 2A\_ix) - A\_i ^ 2 = x ^ 2 + 2A\_ix $

这不归根结底还是求和线段树吗......直接双标记线段树即可

### 0x02 代码

```cpp
#include <cstdio>

const int N = 110000;

int op, n, m, x, y;
double k, z, tmp_double;

struct node{
    double sum, square;
    void operator+=(const node &b){
        this -> sum += b.sum;
        this -> square += b.square;
    }
}tmp;

node tree[N << 2];
double lazy[N << 2];
inline void pushup(int now){
    tree[now].sum = tree[now << 1].sum + tree[now << 1 | 1].sum;
    tree[now].square = tree[now << 1].square + tree[now << 1 | 1].square;
}
inline void pushdown(int now, int lson, int rson){
    if(lazy[now]){
        tree[now << 1].square  = tree[now << 1].square + (lazy[now] * tree[now << 1].sum * 2.0) + (lazy[now] * lazy[now]) * lson;
        tree[now << 1].sum += lazy[now] * lson;
        tree[now << 1 | 1].square  = tree[now << 1 | 1].square + (lazy[now] * tree[now << 1 | 1].sum * 2.0) + (lazy[now] * lazy[now]) * rson;
        tree[now << 1 | 1].sum += lazy[now] * rson;
        lazy[now << 1] += lazy[now];
        lazy[now << 1 | 1] += lazy[now];
        lazy[now] = 0;
    }
}
inline void query_add(int now, int left, int rig, int from, int to, double val){
    if(from <= left && rig <= to){
        tree[now].square = tree[now].square + ((val * tree[now].sum ) * 2) + (val * val) * (rig - left + 1);
        tree[now].sum = tree[now].sum + val * (rig - left + 1);
        lazy[now] += val;
        return ;
    }
    int mid = (left + rig) >> 1;
    pushdown(now, mid - left + 1, rig - mid);
    if(from <= mid) query_add(now << 1, left, mid, from, to, val);
    if(to > mid) query_add(now << 1 | 1, mid + 1, rig, from, to, val);
    pushup(now);
}
inline node query_sum(int now, int left, int rig, int from, int to){
    if(from <= left && rig <= to){
        return tree[now];
    }
    int mid = (left + rig) >> 1; node res = (node){0, 0};
    pushdown(now, mid - left + 1, rig - mid);
    if(from <= mid) res += query_sum(now << 1, left, mid, from, to);
    if(to > mid) res += query_sum(now << 1 | 1, mid + 1, rig, from, to);
    return res;
}

int main(){
#ifdef woshiluo
    freopen("luogu.1471.in", "r", stdin);
    freopen("luogu.1471.out", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++){
        scanf("%lf", &z);
        query_add(1, 1, n, i, i, z);
    }
    while(m--){
        scanf("%d", &op);
        if(op == 1){
            scanf("%d%d%lf", &x, &y, &z);
            k += (y - x + 1) * z;
            query_add(1, 1, n, x, y, z);
        }
        else if(op == 2){
            scanf("%d%d", &x, &y);
            tmp = query_sum(1, 1, n, x, y);
            printf("%.4lf\n", tmp.sum / (y - x + 1));
        }
        else if(op == 3){
            scanf("%d%d", &x, &y);
            tmp = query_sum(1, 1, n, x, y);
            printf("%.4lf\n", ( (tmp.square + (tmp.sum / (y - x + 1)) * tmp.sum - ( 2 * tmp.sum * (tmp.sum / (y - x + 1)) ) ) / (y - x + 1) ) );
        }
    }
}
```

