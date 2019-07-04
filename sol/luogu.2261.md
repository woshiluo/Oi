## [CQOI2007]余数求和

### 题目

一开始老是把思路和做$i \mod k $  和$k \mod i$ 弄混……

然后陷入思维死角，感谢题解把我拉了出来

$$
\sum_{i = 1}^{n} k \mod i \\
= \sum_{i=1}^{n} k - i \times \lfloor \frac{k}{i} \rfloor \\
= n \times k - \sum_{i=1}^{n} i \times \lfloor  \frac{k}{i} \rfloor
$$

然后就是除法分块，这个转化是真的要命QAQ

### 代码

```cpp
#include <cstdio>

long long n,k,ans=0;

inline long long Min(long long a,long long b){return a<b?a:b;}

int main(){
    scanf("%lld%lld",&n,&k);
    ans=n*k;
    for(long long l=1,r;l<=n;l=r+1){
        if(k/l!=0) r=Min(k/(k/l),n);
        else r=n;
        ans-=(k/l)*(r-l+1)*(l+r)/2;
    }
    printf("%lld",ans);
}
```

