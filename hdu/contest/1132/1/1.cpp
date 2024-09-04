#include <bits/stdc++.h>
using namespace std;
const int N=2e5;
const int Mod=998244353;
int fac[200010],inv[200010],cnt[200010],Link[200010],f[200010],sum[200010];
int t;
struct edge
{
    int v,nex;
}e[200010];
void Insert(int x,int y)
{
    e[++t].nex=Link[x];e[t].v=y;Link[x]=t;
}
int ksm(int aa,int bb)
{
    int res=1;
    for (;bb;bb>>=1) {
        if (bb&1) res=1LL*res*aa%Mod;
        aa=1LL*aa*aa%Mod;
    }
    return res;
}
int C(int n,int m)
{
    if (n<0||m<0||n<m) return 0;
    return 1LL*fac[n]*inv[m]%Mod*inv[n-m]%Mod;
}
void dfs(int now)
{
    sum[now]=1;f[now]=1;int s=0;
    for (int i=Link[now];i;i=e[i].nex) {
        dfs(e[i].v);
        sum[now]+=sum[e[i].v];
        f[now]=1LL*f[now]*f[e[i].v]%Mod;
        if (sum[e[i].v]%2==0) f[now]=(f[now]+f[now])%Mod;
          else s++;
    }
    if (s&1) f[now]=1LL*f[now]*C(s,s/2)%Mod;
      else f[now]=1LL*(C(s,s/2)+C(s,s/2-1))%Mod*f[now]%Mod;
    return ;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin>>T;
    fac[0]=1;
    for (int i=1;i<=N;i++) fac[i]=1LL*fac[i-1]*i%Mod;
    inv[N]=ksm(fac[N],Mod-2);
    for (int i=N-1;i>=0;i--) inv[i]=1LL*inv[i+1]*(i+1)%Mod;
    while (T--) {
        int n,K;
        cin>>n>>K;
        int ans=2;
        for (int i=1;i<=n;i++) cnt[i]=0;
        t=0;
        for (int i=1;i<=n;i++) Link[i]=0;
        for (int i=2;i<=n;i++) {
            int x;
            cin>>x;
            Insert(x,i);
        }
        dfs(1);
        // for (int i=1;i<=n;i++) 
        //   if (cnt[i]) {
        //       if (cnt[i]&1) ans=1LL*ans*C(cnt[i],cnt[i]/2)%Mod;
        //         else ans=1LL*(C(cnt[i],cnt[i]/2)+C(cnt[i],cnt[i]/2-1))%Mod*ans%Mod;
        //   }
        // ans=1LL*ans*ksm(2,cnt[1])%Mod;
        f[1]=(f[1]+f[1])%Mod;
        cout<<ksm(f[1],K)<<'\n';
    }
}