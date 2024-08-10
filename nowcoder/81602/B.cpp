#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int mod=1000000007;
int n,m,K;
LL f[2][1010];
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
LL calc()
{
    memset(f,0,sizeof f);
    f[0][0]=1;
    for(int i=1;i<=n;i++){
        memset(f[i&1],0,sizeof f[i&1]);
        LL inv=ksm(i+1,mod-2);
        for(int j=0;j<=i;j++)
        for(int k=0;k+j<=1000;k++)
            (f[i&1][j+k]+=f[(i+1)&1][k])%=mod;
    }
    LL temp=0;
    for(int i=0;i<=30;i++){
        temp=(temp+f[n&1][i])%mod;
        cout<<i<<':'<<f[n&1][i]<<" \n"[i==30];
    }
    return temp;
}
int main()
{
    int T=read();
    while(T --> 0){
        n=read();
        printf("%lld\n",calc());
    }
}