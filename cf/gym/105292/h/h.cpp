#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int mod=998244353;
LL n,m,fact[2000010],inv[2000010];
inline int read()
{
    int x=0,w=0;char ch=0;
    while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return w?-x:x;
}
LL ksm(LL B,LL K,LL A=1)
{
    for(;K;K>>=1,B=B*B%mod)
    if(K&1)A=A*B%mod;
    return A;
}
LL C(int N,int M)
{
    if(N<M||M<0)return 0;
    return fact[N]*inv[N-M]%mod*inv[M]%mod;
}
int main()
{
    fact[0]=1;
    for(int i=1;i<=2000000;i++)
        fact[i]=fact[i-1]*i%mod;
    inv[2000000]=ksm(fact[2000000],mod-2);
    for(int i=2000000-1;i>=0;i--)
        inv[i]=inv[i+1]*(i+1)%mod;
    n=read();m=read();
    LL sum=0;
    for(int i=0;i<m;i++){
        LL temp=0,mul=0;
        temp=C(m-1,i)*fact[m]%mod;
        if(i==0){
            mul=fact[n]*2%mod;
            mul=(mul+fact[n]*(n-1)%mod)%mod;
        }
        if(i>0){
            mul=(C(n-1,i)*2+C(n-1,i-1)+C(n-1,i+1))*fact[n]%mod;
        }
        (sum+=temp*mul)%=mod;
    }
    sum=ksm(sum,mod-2);
    for(int i=0;i<m;i++){
        LL temp=0,mul=0;
        temp=C(m-1,i)*fact[m]%mod;
        if(i==0){
            mul=fact[n]*2%mod;
            mul=(mul+fact[n]*(n-1)%mod)%mod;
        }
        if(i>0){
            mul=(C(n-1,i)*2+C(n-1,i-1)+C(n-1,i+1))*fact[n]%mod;
        }
        printf("%lld%c",temp*mul%mod*sum%mod," \n"[i==m-1]);
    }
}
