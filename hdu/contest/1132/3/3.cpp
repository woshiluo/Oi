#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int mod=998244353;
int n,cnt;
LL ans,a[1000010];
inline LL read()
{
    LL x=0,w=0;char ch=0;
    while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return w?-x:x;
}
int main()
{
    int T=read();
    while(T --> 0){
        n=read();
        for(int i=1;i<=n;i++)
            a[i]=read();
        ans=0;
        for(int i=1;i<n;i++){
            (ans+=a[i]*a[n]%mod*(a[i]+a[n])%mod)%=mod;
            (a[n]+=a[i])%=mod;
        }
        cout<<ans<<'\n';
    }
}