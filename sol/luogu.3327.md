## 0x00 莫比乌斯反演

> 道理我都懂，考试时这东西能推？
>
> 本人菜鸡，有问题请指出

鉴于不同博客对于整除符号$|$的定义不同， 特此表明本博客的整除定义

> $a | b$ 表明 $b$ 是 $a$ 的倍数

### 0x01 什么是反演

对于一个数列${f_n}​$,如果有另外一个数列${g_n}​$满足如下条件
$$
g_n = \sum_{i = 1}^n a_if_i
$$
反演的过程是用$ g_n$来表示 $f_n$
$$
f_n = \sum_{i = 0}^n b_ig_i
$$

 ### 0x02 莫比乌斯函数

> 设$n = p_1^{a_1} \times p_2^{a_2} \times p_3^{a_3} \cdots \times p_k^{a_k}$ ,其中 $p$ 为质数，则定义如下
> $$
> \mu(n) = 
> \begin{cases} 1 & n = 1 \\ 
> (-1) ^ m & \prod\limits_{i = 1} ^ {m} a_i = 1 \\
> 0 & \textrm{otherwise}(a_i \gt 1) 
> \end{cases}
> $$

#### 性质 1

$\mu​$ 函数是积性函数

没啥可以说的，线性筛就完事了

```cpp
void get_pri(){
    vis[1] = 1; mu[1] = 1;
    for(int i = 2; i <= N; i++){
        if( vis[i] == false ){
            pri[ ++pcnt ] = i;
            mu[i] = -1;
        }
        for(int j = 1; j <= pcnt; j++){
            if( pri[j] * i > N ) 
                break;
            vis[ i * pri[j] ] = true;
            if( i % pri[j] == 0 ){
                mu[ pri[j] * i ] = 0;
                break;
            }
            else 
                mu[ pri[j] * i ] = -mu[i];	
        }
    }
}
```

#### 性质 2

对于任意的非负整数
$$
\sum_{d|n}\mu(d)=
\begin{cases}
1 & n = 1\\
0 & n > 1
\end{cases}
$$

### 0x03 莫比乌斯反演

有两个数论函数$f(n)​$和$g(n)​$ ,且满足条件
$$
g(n) = \sum_{d|n}f(d)
$$
则一定存在
$$
f(n) = \sum_{d|n}\mu(d)g(\lfloor \frac{n}{d}\rfloor)
$$

#### 证明

我们这里用性质证明QAQ
$$
\begin{align}
f(n) & = \sum_{d|n}\mu(d)g(\lfloor \frac{n}{d} \rfloor)\\
	& = \sum_{d|n}\mu(d) \sum_{d'|\lfloor \frac{n}{d} \rfloor} f(d')\\
	& = \sum_{d|n} f(d) \sum_{d'|\lfloor \frac{n}{d} \rfloor} \mu(d')\\
	&= f(n)
\end{align}
$$

## 0x10 P3327 [SDOI2015]约数个数和

### 0x11 题目

> 题目链接: <https://www.luogu.org/problemnew/show/P3327>

题目需要让我们求 $\sum_{i=1}^n \sum_{j=1}^m d(i j)​$

其中$ d ​$为约数个数

显然$d(ij) = \sum_{x|i} \sum_{y|j} [gcd(x,y) = 1]​$

给一个比较感性的解释

显然，这个式子在枚举$i,j​$ 的所有约数的 gcd 

如果 两个约数 gcd 为 1，则代表在 $i \cdot j$ 里可以有一个新的约数$x \cdot y$，否则表明这个已经被之前枚举过了

然后开始我们的~~魔法~~吧
$$
\sum_{i=1}^n \sum_{j=1}^m d(i j) \\
\begin{align}
& = \sum_{i=1}^n \sum_{j=1}^m  \sum_{x|i} \sum_{y|j} [gcd(x,y) = 1]\\
& = \sum_{i=1}^n \sum_{j=1}^m \lfloor \frac{n}{i} \rfloor \lfloor \frac{m}{j} \rfloor [gcd(i,j) = 1] \\
\end{align}
$$
接下来的~~魔法~~需要莫比乌斯反演

设
$$
f(x) = \sum_{i=1}^n \sum_{j=1}^m \lfloor \frac{n}{i} \rfloor \lfloor \frac{m}{j} \rfloor [gcd(i,j) = x]\\
g(x) = \sum_{d|x} f(d)
$$
显然
$$
g(x) = \sum_{i=1}^n \sum_{j=1}^m \lfloor \frac{n}{i} \rfloor \lfloor \frac{m}{j} \rfloor [x|gcd(i,j)]
$$
然后提一下$x​$
$$
g(x) = \sum_{i=1}^{\lfloor \frac{n}{x} \rfloor} \sum_{j=1}^{\lfloor \frac{m}{x} \rfloor} \lfloor \frac{n}{xi} \rfloor \lfloor \frac{m}{xj} \rfloor
$$
嗯

然后因为我们求的是$f(1)​$，则
$$
\begin{align}
f(1)& = \sum_{1|d} \mu(\frac{d}{1}) g(d)\\
& = \sum_{d=1}^{n} \mu(d) g(d)\\
&= \sum_{d=1}^{n} \mu(d) \sum_{i=1}^{\lfloor \frac{n}{x} \rfloor} \sum_{j=1}^{\lfloor \frac{m}{x} \rfloor} \lfloor \frac{n}{xi} \rfloor \lfloor \frac{m}{xj} \rfloor
\end{align}
$$
后面的显然可以数论分块，先预处理出$\sum_{i=1}^{n}\lfloor \frac{n}{i} \rfloor​$即可

显然，$\sum_{i=1}^{n}\lfloor \frac{n}{i} \rfloor​$ 和 $\sum_{i=1}^n d(i)​$ 是一样的

然而$d(i)$是积性函数，一起放给线性筛处理即可

### 0x02 代码

```cpp
#include <cstdio>

inline int Min(int a, int b){return a < b? a: b;}

const int N = 51000;

int _case;
int n, m, pcnt;
long long ans;
bool vis[N + 20];
int pri[N + 20], mu[N + 20], smu[N + 20], d[N + 20], sum_d[N + 20], Min_pri[N + 20];

void pre(){
    mu[1] = 1; d[1] = 1; vis[1] = true;
    for(int i = 2; i <= N; i++){
        if( vis[i] == false ){
            pri[ ++pcnt ] = i;
            d[i] = 2; Min_pri[i] = 1;
            mu[i] = -1;
        }
        for(int j = 1; j <= pcnt; j++){
            if( pri[j] * i > N )
                break;
            vis[ pri[j] * i ] = true;
            if( i % pri[j] == 0 ){
                mu[ pri[j] * i ] = 0;	
                d[ pri[j] * i ] = d[i] / (Min_pri[i] + 1) * (Min_pri[i] + 2);
                Min_pri[ pri[j] * i ] = Min_pri[i] + 1;
            }
            else {
                mu[ pri[j] * i ] = -mu[i];
                d[ pri[j] * i ] = d[i] << 1;
                Min_pri[ pri[j] * i ] = 1;
            }
        }
    }
    for(int i = 1; i <= N; i++)
        smu[i] = smu[i - 1] + mu[i];
    for(int i = 1; i <= N; i++)
        sum_d[i] = sum_d[i - 1] + d[i];
}

int main(){
    pre();
    scanf("%d", &_case);
    while( _case -- ){
        scanf("%d%d", &n, &m);
        ans = 0;
        if(n > m) {int tmp = m; m = n; n = tmp;}
        for(int left = 1, rig; left <= n; left = rig + 1){
            rig = Min(n / (n / left), m / (m / left));	
            ans += 1LL * (smu[rig] - smu[left - 1]) * sum_d[n / left] * sum_d[m / left];
        }
        printf("%lld\n", ans);
    }
}
```

