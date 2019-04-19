# 狄利克雷卷积 && 杜教筛

## 狄利克雷卷积

### 数论函数

数论函数是指一类函数，其定义域是正整数，值域是一个数集

**积性函数**都是数论函数

常见的数论函数有

- $id(n) = n$ 元函数，完全积性函数
- $\epsilon(n) = [n = 1]$ 单位函数，完全积性函数
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
\phi(n) = \sum_{d|n} \mu(d) \frac{n}{d}
$$