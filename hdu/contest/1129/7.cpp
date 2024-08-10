#include <bits/stdc++.h>
using namespace std;
const int Mod=998244353;
int t=0,Link[100010],a[100010],b[100010],f[100010],g[100010],p[200010],c[200010][22];
int cnt=0,dfn[100010],F[100010],dep[100010];
bool vis[100010];
struct edge
{
    int v,nex;
}e[200010];
void Insert(int x,int y)
{
    e[++t].nex=Link[x];e[t].v=y;Link[x]=t;
    return;
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
void dfs(int now,int fa)
{
    f[now]=1;F[now]=fa;p[++cnt]=now;dfn[now]=cnt;
    dep[now]=dep[fa]+1;
    for (int i=Link[now];i;i=e[i].nex) {
        if (e[i].v==fa) continue;
        dfs(e[i].v,now);
        f[now]=1LL*f[now]*(f[e[i].v]+1)%Mod;
        p[++cnt]=now;
    }
    return ;
}
void dfs1(int now,int fa)
{
    for (int i=Link[now];i;i=e[i].nex) {
        if (e[i].v==fa) continue;
        g[e[i].v]=1LL*(g[now]+1)*f[now]%Mod*ksm(f[e[i].v]+1,Mod-2)%Mod;
        dfs1(e[i].v,now);
    }
    return ;
}
void Pre()
{
    for (int i=1;i<=cnt;i++) c[i][0]=p[i];
    for (int i=1;i<=20;i++)
      for (int j=1;j<=cnt-(1<<i)+1;j++)
        if (dep[c[j][i-1]]<dep[c[j+(1<<(i-1))][i-1]]) c[j][i]=c[j][i-1];
          else c[j][i]=c[j+(1<<(i-1))][i-1];
    return ;
}
int Get_Lca(int x,int y)
{
    if (dfn[x]>dfn[y]) swap(x,y);
    int l=dfn[x],r=dfn[y],len=log2(r-l+1);
    return dep[c[l][len]]<dep[c[r-(1<<len)+1][len]]?c[l][len]:c[r-(1<<len)+1][len];
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin>>T;
    while (T--) {
        int n;
        cin>>n;
        t=0;
        for (int i=1;i<=n;i++) Link[i]=0,vis[i]=0; 
        for (int i=1;i<=n;i++)
          cin>>a[i],b[a[i]]=i;
        for (int i=1;i<n;i++) {
            int x,y;
            cin>>x>>y;
            Insert(x,y);Insert(y,x);
        }
        cnt=0;
        dfs(1,0);
        dfs1(1,0);
        // for (int i=1;i<=n;i++) cout<<f[i]<<' '<<g[i]<<endl;
        Pre();
        int rt=b[0],ans,res;
        ans=res=1LL*f[rt]*(g[rt]+1)%Mod;vis[rt]=true;
        for (int i=1;i<n;i++) {
            if (vis[b[i]]) {
                ans=(ans+res)%Mod;
                continue;
            }
            int k=Get_Lca(rt,b[i]);
            if (k==rt) {
                int las=b[i],now=F[b[i]];
                res=1LL*res*f[b[i]]%Mod;vis[b[i]]=true;
                while (!vis[now]) {
                    res=1LL*res*f[now]%Mod*ksm(f[las]+1,Mod-2)%Mod;
                    vis[now]=true;
                    las=now;now=F[now];
                }
                res=1LL*res*ksm(f[las]+1,Mod-2)%Mod;
            }
            else if (k==b[i]) {
                res=1LL*res*ksm(g[rt]+1,Mod-2)%Mod;
                int las=rt,now=F[rt];
                while (1) {
                    res=1LL*res*f[now]%Mod*ksm(f[las]+1,Mod-2)%Mod;
                    vis[now]=true;
                    if (now==b[i]) break;
                    las=now;now=F[now];
                }
                rt=b[i];
                res=1LL*res*(g[rt]+1)%Mod;
            }
            else {
                int las=rt,now=F[rt];
                res=1LL*res*ksm(g[rt]+1,Mod-2)%Mod;
                while (now!=k) {
                    res=1LL*res*f[now]%Mod*ksm(f[las]+1,Mod-2)%Mod;
                    vis[now]=true;
                    las=now;now=F[now];
                }
                res=1LL*res*ksm(f[las]+1,Mod-2)%Mod;
                res=1LL*res*f[b[i]]%Mod;
                las=b[i],now=F[b[i]];vis[b[i]]=true;
                while (now!=k) {
                    res=1LL*res*f[now]%Mod*ksm(f[las]+1,Mod-2)%Mod;
                    vis[now]=true;
                    las=now;now=F[now];
                }
                res=1LL*res*ksm(f[las]+1,Mod-2)%Mod;
                rt=k;
                vis[k]=true;res=1LL*res*f[k]%Mod;
                res=1LL*res*(g[rt]+1)%Mod;
            }
            ans=(ans+res)%Mod;
            // cout<<res<<endl;
        }
        cout<<ans<<'\n';
    }
    return 0;
}