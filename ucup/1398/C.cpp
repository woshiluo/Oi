#include <bits/stdc++.h>
using namespace std;
const int Mod=1e9+7,inv2=(1e9+8)/2;
int ans=0,Link[200010],tt,n;
int tot,dfn[200010],dep[200010],son[200010],sum[200010],top[200010],f[200010];
struct edge
{
    int v,nex;
}e[400010];    
struct SegmentTree
{
    int A[800010],B[800010],sum[800010],tag[800010];
    void Build(int p,int l,int r)
    {
        A[p]=1;B[p]=1;sum[p]=0;tag[p]=1;
        if (l==r) return ;
        int mid=(l+r)>>1;
        Build(p<<1,l,mid);Build(p<<1|1,mid+1,r);
        return ;
    }
    void PushDown(int p)
    {
        if (tag[p]==1) return ;
        B[p<<1]=1LL*B[p<<1]*tag[p]%Mod;
        sum[p<<1]=1LL*sum[p<<1]*tag[p]%Mod;
        tag[p<<1]=1LL*tag[p<<1]*tag[p]%Mod;
        B[p<<1|1]=1LL*B[p<<1|1]*tag[p]%Mod;
        sum[p<<1|1]=1LL*sum[p<<1|1]*tag[p]%Mod;
        tag[p<<1|1]=1LL*tag[p<<1|1]*tag[p]%Mod;
        tag[p]=1;
    }
    void PushUp(int p){
        sum[p]=(sum[p<<1]+sum[p<<1|1])%Mod;
        return ;
    }
    void Modiffy(int p,int l,int r,int L,int R,int v) {
        if (l==L&&r==R) {
            if (v==2) ans=(ans+sum[p])%Mod;
              else ans=(ans-1LL*sum[p]*v%Mod+Mod)%Mod;
            B[p]=1LL*B[p]*v%Mod;
            sum[p]=1LL*sum[p]*v%Mod;
            tag[p]=1LL*tag[p]*v%Mod;
            return ;
        }
        PushDown(p);
        int mid=(l+r)>>1;
        if (R<=mid) Modiffy(p<<1,l,mid,L,R,v);
          else if (L>mid) Modiffy(p<<1|1,mid+1,r,L,R,v);
            else Modiffy(p<<1,l,mid,L,mid,v),Modiffy(p<<1|1,mid+1,r,mid+1,R,v);
        PushUp(p);
    }
    void Modiffy0(int p,int l,int r,int x,int v) {
        if (l==r) {
            if (v==2) ans=(ans+1LL*A[p]*B[p]%Mod)%Mod,sum[p]=(sum[p]+1LL*A[p]*B[p]%Mod)%Mod;
              else ans=(ans-1LL*A[p]*B[p]%Mod*v%Mod+Mod)%Mod,sum[p]=(sum[p]-1LL*A[p]*B[p]%Mod*v%Mod+Mod)%Mod;
            A[p]=1LL*A[p]*v%Mod;
            return ;
        }
        PushDown(p);
        int mid=(l+r)>>1;
        if (x<=mid) Modiffy0(p<<1,l,mid,x,v);
          else Modiffy0(p<<1|1,mid+1,r,x,v);
        PushUp(p);
        return ;
    }
}t;
void Add_Edge(int x,int y)
{
    e[++tt].nex=Link[x];e[tt].v=y;Link[x]=tt;
    return ;
}
void dfs(int now,int fa)
{
    f[now]=fa;sum[now]=1;son[now]=0;dep[now]=dep[fa]+1;
    for (int i=Link[now];i;i=e[i].nex) {
        if (e[i].v==fa) continue;
        dfs(e[i].v,now);
        sum[now]+=sum[e[i].v];
        if (sum[e[i].v]>sum[son[now]]) son[now]=e[i].v;
    }
    return ;
}
void dfs1(int now,int to)
{
    dfn[now]=++tot;top[now]=to;
    if(!son[now]) return ;
    dfs1(son[now],to);
    for (int i=Link[now];i;i=e[i].nex) {
        if (e[i].v==f[now]||e[i].v==son[now]) continue;
        dfs1(e[i].v,e[i].v);
    }
    return ;
}
void Solve(int x,int y,int v)
{
    int fx=top[x],fy=top[y];
    while (fx!=fy) {
        if (dep[fx]>dep[fy]) swap(x,y),swap(fx,fy);
        t.Modiffy(1,1,n,dfn[fy],dfn[y],v);
        y=f[fy];fy=top[y];
    }
    if (dep[x]>dep[y]) swap(x,y);
    if (dfn[x]+1<=dfn[y]) t.Modiffy(1,1,n,dfn[x]+1,dfn[y],v);
    t.Modiffy0(1,1,n,dfn[x],v);
    return ;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n;
    for (int i=1;i<n;i++) {
        int x,y;
        cin>>x>>y;
        Add_Edge(x,y);Add_Edge(y,x);
    }
    dfs(1,0);
    dfs1(1,0);
    t.Build(1,1,n);
    int Q;
    cin>>Q;
    while (Q--) {
        string str;
        int x,y;
        cin>>str;
        cin>>x>>y;
        if (str[0]=='-') Solve(x,y,inv2);
          else Solve(x,y,2);
        cout<<ans<<'\n';
    }
    return 0;
}