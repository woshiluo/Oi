#include<bits/stdc++.h>
#define LL long long
const int mod=998244353;
using namespace std;
inline int read()
{
    int x=0,w=0;char ch=0;
    while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return w?-x:x;
}
LL ksm(LL B,LL K,LL A=1)
{
    if(K==2)K=1;
    for(;K;K>>=1,B=B*B%mod)
    if(K&1)A=A*B%mod;
    return A;
}
int main()
{
    int T=read();
    while(T --> 0){
        int x=read();
        if(x%3==2)x--;
        printf("%lld\n",ksm(2,x));
    }
}
/*
2
2
8
16
16
64
128
128
512
1024
1024
4096
8192
8192
32768
*/