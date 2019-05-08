## 「BJOI2019」光线 

> 题目链接: <https://oj.woshiluo.site/problem/2055> / <https://www.luogu.org/problemnew/show/P5323>

我看到题目的一瞬间

> 我是在学 oi 还是在学物理？

然后我仔细思考了一下，这两个镜子来回反射，您这是要求极限？

然后我仔细思考了一下

设 $f_i$ 为从 $1$ 到 $i$ 的透光率，$g_i$ 为从 $i$ 到 $1$ 的反光率

则
$$
\begin{aligned}
f_i & = f_{i - 1} \times a_i  \times \sum_{j = 0} ^ {\infty} (g_{i - 1} \times b_i) ^ j\\
g_i & = b_i + g_{i - 1} \times  a_i^2  \times \sum_{j = 0} ^ {\infty} (g_{i - 1} \times b_i) ^ j
\end{aligned}
$$
所以，这个无限是个啥？

好消息在于，对于无限等比数列 $ a_i = a_{i - 1} \times p$  ，若是 $-1 < p < 1$ 竟然有一个公式

~~这群数学家每天都在研究啥啊~~

即$\sum_{i = 1}^{\infty} a_i  = \frac{a_1}{1 - p}$

套进去就完事了

### 代码

```cpp
#include <cstdio>

const int N = 5e5 + 1e4;
const int mod = 1e9 + 7;

inline int mul(int a, int b){return (1LL * a * b) % mod;}
inline int dec(int a, int b){a -= b; return a < 0? a + mod: a;}

int ksm(int a, int p = mod - 2){
    int res = 1;
    while(p){
        if(p & 1)
            res = (1LL * res * a) % mod;
        a = (1LL * a * a) % mod;
        p >>= 1;
    }
    return res;
}

int n;
int a[N], b[N], f[N], g[N];

int main(){
    scanf("%d", &n);
    int inv100 = ksm(100);
    for(int i = 1; i <= n; i++){
        scanf("%d%d", &a[i], &b[i]);
        a[i] = mul(inv100, a[i]);
        b[i] = mul(inv100, b[i]);
    }

    f[0] = 1;
    for(int i = 1, p; i <= n; i++){
        p = ksm( dec(1, mul(g[i - 1], b[i])) );	
        f[i] = mul(mul(f[i - 1], a[i]), p);
        g[i] = (b[i] + mul(mul(g[i - 1], mul(a[i], a[i])), p)) % mod;
    }
    printf("%d", f[n]);
}
```