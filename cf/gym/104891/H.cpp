#include <bits/stdc++.h>
using namespace std;
const int Mod=998244353;
int t=0,Link[100010],dep[100010],f[100010][105];
int tmp[105],g[105],sum[100010];
int fac[300010],inv[300010];
struct edge
{
    int v,nex;
}e[100010];
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
void dfs(int now)
{
    sum[now]=1;
    if (!Link[now]) {
        for (int i=0;i<=dep[now];i++) 
          f[now][i]=1;
        return ;
    }
    for (int i=Link[now];i;i=e[i].nex) {
        dep[e[i].v]=dep[now]+1;
        dfs(e[i].v);
        sum[now]+=sum[e[i].v];
    }
    for (int i=0;i<=dep[now]+1;i++) g[i]=0;
    int s=0;
    g[0]=1;
    for (int i=Link[now];i;i=e[i].nex) {
        for (int j=0;j<=dep[now]+1;j++) tmp[j]=0;
        for (int j=0;j<=dep[now]+1;j++)//s+j
          for (int k=0;k<=dep[e[i].v]&&k<=dep[now]+1-j;k++)//s1+k 
            tmp[j+k]+=1LL*g[j]*f[e[i].v][k]%Mod*fac[s+j+sum[e[i].v]+k]%Mod*inv[s+j]%Mod*inv[sum[e[i].v]+k]%Mod,tmp[j+k]%=Mod;
        s+=sum[e[i].v];
        for (int j=0;j<=dep[now]+1;j++) 
          g[j]=tmp[j];
    }
    // cout<<now<<'\n';
    // cout<<g[0]<<' '<<g[1]<<'\n';
    for (int j=0;j<=dep[now]+1;j++)
      for (int i=0;i<=dep[now]+1&&i+j-1<=dep[now];i++) 
        if (i||j) f[now][i+j-1]+=1LL*g[i]*fac[s+i+j]%Mod*inv[s+i]%Mod*inv[j]%Mod,f[now][i+j-1]%=Mod;
    // cout<<f[now][0]<<' '<<f[now][1]<<'\n';
    return ;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin>>n;
    int N=3*n;
    fac[0]=1;
    for (int i=1;i<=N;i++) fac[i]=1LL*fac[i-1]*i%Mod;
    inv[N]=ksm(fac[N],Mod-2);
    for (int i=N-1;i>=0;i--) inv[i]=1LL*inv[i+1]*(i+1)%Mod;
    for (int i=2;i<=n;i++) {
        int x;
        cin>>x;
        Insert(x,i);
    }
    dfs(1);
    cout<<f[1][0];
    return 0;
}