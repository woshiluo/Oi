## Luogu 1248 加工生产调度

### 题目

> 题目链接: <https://www.luogu.org/problemnew/show/P1248>

这道题目暴力显然不可取$ 1000！$ , DP 的状态不太容易定义，只能贪心大法

#### 分析贪心

我们可以先假设只有两个物品$ A $ 和$ B $,则存在以下两种情况($ x $代表物品在 A 工厂加工所需时间，$ y $ 代表 B 工厂，以下同理）

1. 先加工$ A $后加工$ B $，则时间为$ A.x + B.y + \max(A.y, B.x) $
2. 先加工$ B $后加工$ A $，则时间为$ A.y + B.x + \max(A.x, B.y) $

则若先加工 A 比先加工 B 优，应满足
$$
A.x + B.y + \max(A.y, B.x) < A.y + B.x + \max(A.x, B.y) \\
\begin{align}
&= \max(A.y, B.x) - A.y - B.x < \max(A.x, B.y) - A.y - B.x \\
&= -\min(A.y, B.x) < -\min(A.x, B.y) \\
&= \min(A.x, B.y) < \min(A.y, B.x)
\end{align}
$$
然后放到`cmp`里，A 了？

等一下，这个方法……是错误的

#### 为什么错误？

首先，我们需要知道在 C++ 标准库中，`sort` 要求排序运算符必须保证**严格排序**

##### 什么是严格排序

若一个比较运算符，则应当满足

非自反性，非对称性，传递性，不可比性的传递性 这四点

好消息是，我们的函数并不具有不可比性的传递性

即我们的排序函数可能汇出形如下面的状况：

$ x < y $ 且 $y < z$ 但$ x \geq z$

这样一来，我们排出来的序列就不满足之前的要求了

#### 排序的改进

所以我们的目的很简单，使我们的排序符号变成保证**严格排序**的

我们可以把相等的情况单独提出来讨论

1. $A.x < B.x$ 且 $A.y < B.y$ 按 $A.x < A.y$ 排序
2. $A.x = B.x $ 且 $A.y = B.y $ 不做处理
3. $ A.x > B.x $ 且  $A.y > B.y$ 按 $B.y < B.x$ 排序

多关键字排序即可

### 代码

```cpp
#include <cstdio>
#include <algorithm>

inline int Max(int a, int b){return a > b? a: b;}

const int N = 1100;

int n;
struct node{
	int x, y, d, id;
}a[N];

bool cmp(node x, node y){
	if(x.d == y.d){
		if(x.d <= 0) 
			return x.x < y.x;
		else 
			return x.y > y.y;
	}
	else return x.d < y.d;
}

int main(){
#ifdef woshiluo
	freopen("luogu.1248.in", "r", stdin);
	freopen("luogu.1248.out", "w", stdout);
#endif
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){ scanf("%d", &a[i].x); }
	for(int i = 1; i <= n; i++){ 
		scanf("%d", &a[i].y); 
		a[i].id = i;
		a[i].d = (a[i].x == a[i].y ? 0: (a[i].x > a[i].y ? 1: - 1));
	}

	std::sort(a + 1, a + n + 1, cmp);

	int time_a = a[1].x, time_b = a[1].x + a[1].y;
	for(int i = 2; i <= n; i++){
		time_a += a[i].x;
		time_b = Max(time_a, time_b) + a[i].y;
	}
	printf("%d\n", time_b);
	for(int i = 1; i <= n; i++){ printf("%d ", a[i].id); }
}
```

### 后记

对与邻项排序的各种各样问题 ouuan 大佬的博客里有一篇讲的十分清楚 <https://ouuan.github.io/%E6%B5%85%E8%B0%88%E9%82%BB%E9%A1%B9%E4%BA%A4%E6%8D%A2%E6%8E%92%E5%BA%8F%E7%9A%84%E5%BA%94%E7%94%A8%E4%BB%A5%E5%8F%8A%E9%9C%80%E8%A6%81%E6%B3%A8%E6%84%8F%E7%9A%84%E9%97%AE%E9%A2%98/>

博主也是根据这篇博文学的，%%% ouuan