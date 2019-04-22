# 狄利克雷卷积 && 杜教筛

## 狄利克雷卷积

### 数论函数

数论函数是指一类函数，其定义域是正整数，值域是一个数集

**积性函数**都是数论函数

常见的数论函数有

- $id(n) = n$ 单位函数，完全积性函数
- $\epsilon(n) = [n = 1]$ 元函数，完全积性函数
- $d(n)$ 约数个数，积性函数
- $\sigma(n)$ 约数和函数，积性函数
- $\mu(n)$ 莫比乌斯函数，积性函数
- $\varphi(n)$ 欧拉函数，积性函数

 
### 狄利克雷卷积

定义两个数论函数的狄利克雷卷积为 $*$:

若$t = f * g$

则
$$
t(n) = \sum_{i|n} f(n) g(\lfloor \frac{n}{i} \rfloor)
$$

在狄利克雷卷积中
- 单位元是 $\epsilon$
- 若$f * g = \epsilon$ 则我们称 $g$ 为 $f$ 的逆元
- $f * g = g * f$
- $(f * g) * h = f * (g * h)$
- $(f + g) * h = f * h + g * h$
- $(xf) * g = x(f*g)$

### 一些应用

#### 莫比乌斯反演

我们先来证明一点莫比乌斯反演里面的东西

$$
\sum_{d|n} \mu(d) = [n = 1]
$$

很明显，化成卷积的形式即为
$$
\mu * 1 = \epsilon
$$

然后我们来证明莫比乌斯反演

$$
g(n) = \sum_{d|n} f(d)\\
f(n) = \sum_{d|n} \mu(d) g(\lfloor \frac{n}{d} \rfloor)
$$
显然可以化为

$$
g = f * 1 
$$

$$
\begin{aligned}
f & = \mu * g \\
  & = \mu * f * 1 \\
  & = f * \epsilon \\
  & = f
\end{aligned}
$$

等式成立，展开后得到

$$
f(n) = \sum_{d|n} \mu(n) g(\lfloor \frac{n}{d} \rfloor)
$$

得证

#### 欧拉函数与莫比乌斯函数

已知

$$
n = \sum_{d|n} \varphi(d)
$$

显然

$$
\begin{aligned}
\varphi * 1 & = id\\
\varphi * 1 * \mu & = id * \mu\\
\varphi * \epsilon & = id * \mu\\
\varphi &= id*\mu
\end{aligned}
$$

展开得

$$
\varphi(n) = \sum_{d|n} \mu(d) \frac{n}{d}
$$

除于$n$得

$$
\frac {\varphi(n)}{n} = \sum_{d|n} \frac{\mu(d)}{d}
$$

(然后你可以用这个式子证明已知的公式)(证明证明证明)

## 杜教筛

杜教筛用于在小于线性的时间求一个积性函数

即 求 $\sum_{i=1}^n f(i)$

$f$ 为积性函数

为了愉快得求出这个式子我们需要设$h = f * g$ 

$h$ 和 $g$ 均为积性函数

记 $S$ 为 $f$ 前缀和

然后`Let's do it!`

$$
\begin{aligned}
\sum_{i=1}^n
& = \sum_{i=1}^n \sum_{d|i} g(d)  f(\frac{d}{i}) \\
& = \sum_{d=1}^n g(d) \sum_{i=1}^{\frac{n}{d}} f(i) \\
&=  \sum_{d=1}^n g(d) S(\frac{n}{d})
\end{aligned}
$$

让我们做一点微小的改变

显然

$$
g(1)S(n) = \sum_{i=1}^n h(i) - \sum_{d=2}^n g(d) S(\frac{n}{d})
$$

除法分块 + 递归处理

只要你$h(i)$得前缀和能在大约$O(1)$左右得时间求出来（预处理后$O(1)$也可以的）时间复杂度就是$O(n^{\frac{2}{3}})$

为什么？反正我是不会QAQ

来吧，上模板
### Luogu P4213 【模板】杜教筛（Sum）

#### 题目

##### 莫比乌斯函数

$$
S(n) = \sum_{i=1}^n \mu(i)
$$

众所周知$\mu * 1 = \epsilon$

$\epsilon$ 的前缀和过于显然——$1$

没什么说的了

#####  欧拉函数

$$
S(n) = \sum_{i=1}^n \varphi(i)
$$

众所周知$\varphi * 1 = id$

$id$ 的前缀和...等差数列了解一下

没什么说的了

### 代码

```cpp
#include <cstdio>

const int N = 2e6 + 10;

int T, n;
int sum_mu[N], sum_mu2[3400];
int mu[N], phi[N], pri[N], pcnt;
int has_phi[3400], has_mu[3400];
long long sum_phi[N], sum_phi2[3400];
bool vis[N];

void pre(){
    vis[1] = true; mu[1] = 1; phi[1] = 1;
    sum_mu[1] = sum_phi[1] = 1;
    for(int i = 2; i < N; i++){
        if(vis[i] == false){
            pri[ ++pcnt ] = i;
            mu[i] = -1;
            phi[i] = i - 1;
        }
        for(int j = 1; j <= pcnt; j++){
            int tmp = pri[j] * i;
            if(tmp >= N) 
                break;
            vis[tmp] = true;
            if(i % pri[j] == 0){
                mu[tmp] = 0;
                phi[tmp] = phi[i] * pri[j];
                break;
            }
            mu[tmp] = -mu[i];
            phi[tmp] = phi[i] * (pri[j] - 1);
        }
        sum_mu[i] = sum_mu[i - 1] + mu[i];
        sum_phi[i] = sum_phi[i - 1] + (long long)phi[i];
    }
}

long long ask_phi(int x){
    if(x < N) return sum_phi[x];
    int tmp = n / x;
    if(has_phi[tmp] == n)
        return sum_phi2[tmp];
    has_phi[tmp] = n;
    long long &ans = sum_phi2[tmp];
    ans = (1LL * (1LL + x) * x) / 2;
    for(int left = 2, rig; left <= x; left = rig + 1){
        rig = x / (x / left);
        ans -= (rig - left + 1) * ask_phi(x / left);
    }
    return ans;
}

int ask_mu(int x){
    if(x < N) return sum_mu[x];
    int tmp = n / x;
    if(has_mu[tmp] == n)
        return sum_mu2[tmp];
    has_mu[tmp] = n;
    int &ans = sum_mu2[tmp];
    ans = 1;
    for(int left = 2, rig; left <= x; left = rig + 1){
        rig = x / (x / left);
        ans -= (rig - left + 1) * ask_mu(x / left);
    }
    return ans;
}

int main(){
#ifdef woshiluo
    freopen("luogu.4213.in", "r", stdin);
    freopen("luogu.4213.out", "w" ,stdout);
#endif
    pre();
    scanf("%d", &T);
    while(T--){
        scanf("%d", &n);
        printf("%lld %d\n", ask_phi(n), ask_mu(n)); 
    }
    fclose(stdin);
    fclose(stdout);
}
```

## End

