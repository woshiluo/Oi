#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL mod=998244353;
LL n;
LL ans,sze[100010],sum[100010];
vector<int>G[100010];
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
void dfs(int x,int F)
{
    sze[x]=1;sum[x]=0;
    for(int y:G[x]){
        if(y==F)continue;
        dfs(y,x);
        (sze[x]+=sze[y])%=mod;
        (sum[x]+=sum[y])%=mod;
    }
    for(int y:G[x]){
        if(y==F)continue;
        (ans+=(sum[x]-sum[y])*sum[y]%mod)%=mod;
    }
    (ans+=sze[x]*sze[x]%mod*(n-sze[x])%mod*(n-sze[x])%mod)%=mod;
    (ans+=sum[x]*(n-sze[x])%mod*(n-sze[x])%mod*2)%=mod;
    (sum[x]+=sze[x]*sze[x])%=mod;
    // cout<<x<<','<<ans<<endl;
}
int main()
{
    // cin.tie(0)->sync_with_stdio(false);
    int T;T=read();
    while(T --> 0){
        n=read();
        for(int i=1;i<=n;i++)G[i].clear();
        for(int i=1;i<n;i++){
            int x=read(),y=read();
            G[x].emplace_back(y);
            G[y].emplace_back(x);
        }
        ans=0;
        dfs(1,0);
        // cout<<ans<<endl;
        (ans*=ksm(1ll*n*(n-1)/2%mod,(mod-2)*2))%=mod;
        cout<<(ans+mod)%mod<<endl;
    }
}