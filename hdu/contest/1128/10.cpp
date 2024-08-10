#include <bits/stdc++.h>
using namespace std;
int t,Link[200010],pos,n,son[200010],F[200010],top[200010],dfn[200010],tot,rk[200010];
bool tag[200010];
long long c[200010],w[200010];
int sum_[200010],sl[55],sr[55];
long long s[800010],sum[800010],ans,ss;
struct edge
{
    int v,nex;
}e[400010];
struct quu
{
    int op,K,S;
}qu[200010];
void Insert(int x,int y)
{
    e[++t].nex=Link[x];e[t].v=y;Link[x]=t;
    return ;
}
void dfs(int now)
{
    sum_[now]=1;son[now]=0;
    for (int i=Link[now];i;i=e[i].nex) {
        if (e[i].v==F[now]) continue;
        dfs(e[i].v);
        sum_[now]+=sum_[e[i].v];
        if (sum_[e[i].v]>sum_[son[now]]) son[now]=e[i].v;
    }
    return ;
}
void dfs1(int now,int to)
{
    top[now]=to;dfn[now]=++tot;rk[tot]=now;
    if (!son[now]) return ;
    dfs1(son[now],to);
    for (int i=Link[now];i;i=e[i].nex) {
        if (e[i].v==F[now]||e[i].v==son[now]) continue;
        dfs1(e[i].v,e[i].v);
    }
    return;
}
void Build(int p,int l,int r)
{
    tag[p]=0;
    if (l==r) {
        s[rk[l]]=w[rk[l]];sum[rk[l]]=c[rk[l]]*w[rk[l]];
        // cout<<l<<' '<<w[rk[l]]<<' '<<c[rk[l]]<<endl;
        return ;
    }
    int mid=(l+r)>>1;
    Build(p<<1,l,mid);Build(p<<1|1,mid+1,r);
    s[p]=s[p<<1]+s[p<<1|1];
    sum[p]=sum[p<<1]+sum[p<<1|1];
    cout<<p<<' '<<s[p]<<' '<<sum[p]<<endl;
    return ;
}
void Pass(int p)
{
    if (!tag[p]) return ;
    sum[p<<1]=s[p<<1]=0;sum[p<<1|1]=s[p<<1|1]=0;
    tag[p<<1]=tag[p<<1|1]=1;
    tag[p]=0;
    return ;;
}
void Modiffy(int p,int l,int r,int x)
{
    if (l==r) {
        s[p]=w[rk[l]];sum[p]=c[rk[l]]*w[rk[l]];
        return ;
    }
    Pass(p);
    int mid=(l+r)>>1;
    if (x<=mid) Modiffy(p<<1,l,mid,x);
      else Modiffy(p<<1|1,mid+1,r,x);
    s[p]=s[p<<1]+s[p<<1|1];
    sum[p]=sum[p<<1]+sum[p<<1|1];
    return ;
}
void Modiffy0(int p,int l,int r,int L,int R)
{
    if (l==L&&r==R) {
        s[p]=sum[p]=0;
        tag[p]=1;
        return ;
    }
    Pass(p);
    int mid=(l+r)>>1;
    if (R<=mid) Modiffy0(p<<1,l,mid,L,R);
    else if (L>mid) Modiffy0(p<<1|1,mid+1,r,L,R);
      else Modiffy0(p<<1,l,mid,L,mid),Modiffy0(p<<1|1,mid+1,r,mid+1,R);
    s[p]=s[p<<1]+s[p<<1|1];
    sum[p]=sum[p<<1]+sum[p<<1|1];
    return ;
}
pair<long long,long long> Query(int p,int l,int r,int L,int R)
{
    if (l==L&&r==R) return make_pair(s[p],sum[p]);
    int mid=(l+r)>>1;
    Pass(p);
    if (R<=mid) return Query(p<<1,l,mid,L,R);
    if (L>mid) return Query(p<<1|1,mid+1,r,L,R);
    pair<long long,long long> tmp1=Query(p<<1,l,mid,L,mid),tmp2=Query(p<<1|1,mid+1,r,mid+1,R);
    return make_pair(tmp1.first+tmp2.first,tmp1.second+tmp2.second);
}
void Find(int p,int l,int r)
{
    if (l==r) {
        ans+=min(w[rk[l]],ss)*c[rk[l]];
        if (w[rk[l]]>=ss) w[rk[l]]-=ss,ss=0;
          else ss-=w[rk[l]],w[rk[l]]=0;
        pos=l;
        return ;
    }
    Pass(p);
    int mid=(l+r)>>1;
    if (s[p<<1]>=ss) Find(p<<1,l,mid);
    else {
        ans+=sum[p<<1];ss-=s[p<<1];
        Find(p<<1|1,mid+1,r);
    }
    return ;
}
bool Calc(int p,int l,int r,int L,int R) 
{
    if (l==L&&r==R) {
        if (s[p]>=ss) {
            Find(p,l,r);
            return true;
        }
        ans+=sum[p];ss-=s[p];
        return false;
    }
    Pass(p);
    int mid=(l+r)>>1;
    if (R<=mid) return Calc(p<<1,l,mid,L,R);
    if (L>mid) return Calc(p<<1|1,mid+1,r,L,R);
    if (Calc(p<<1,l,mid,L,mid)) return true;
    return Calc(p<<1|1,mid+1,r,mid+1,R);
}
void Solve(int x,long long lim)
{
    int fx=top[x];
    int tt=0;
    // cout<<x<<' '<<fx<<endl;
    while (fx!=1) {
        // cout<<x<<' '<<fx<<endl;
        tt++;
        sl[tt]=dfn[fx];sr[tt]=dfn[x];
        x=F[fx];fx=top[x];
    }
    tt++;sl[tt]=dfn[1];sr[tt]=dfn[x];
    int p=tt;ans=0;ss=lim;
    bool fla=false;
    cout<<tt<<endl;
    for (int i=tt;i>=1;i--) {
        pair<long long,long long>tmp=Query(1,1,n,sl[i],sr[i]);
        cout<<sl[i]<<' '<<sr[i]<<' '<<tmp.first<<' '<<tmp.second<<endl;
        if (tmp.first>=ss) {
            p=i;
            fla=true;
            break;
        }
        ss-=tmp.first;ans+=tmp.second;
        Modiffy0(1,1,n,sl[i],sr[i]);
    }
    if (!fla) return;
    Calc(1,1,n,sl[p],sr[p]);
    if (sl[p]<pos) Modiffy0(1,1,n,sl[p],pos-1);
    Modiffy(1,1,n,pos);
    return ;
}
int main()
{
#ifdef woshiluo
	freopen( "10.in", "r", stdin );
#endif
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    int T;
    cin>>T;
    while (T--) {
        int Q;
        cin>>Q>>c[1]>>w[1];n=1;
        int num=0;
        for (int i=1;i<=Q;i++) {
            int opt;
            cin>>opt;
            if (opt==1) {
                int x,y;
                cin>>x>>y;
                x++;y++;
                cin>>c[x]>>w[x];
                Insert(y,x);F[x]=y;
                n++;
            }
            else if (opt==2) {
                qu[++num].op=2;
                cin>>qu[num].K>>qu[num].S;
                qu[num].K++;
            }
            else {
                qu[++num].op=3;
                cin>>qu[num].K;
                qu[num].K++;
            }
        }
        tot=0;
        dfs(1);
        dfs1(1,1);
        Build(1,1,n);
        for (int i=1;i<=num;i++) 
          if (qu[i].op==2) {
              Solve(qu[i].K,qu[i].S);
              cout<<qu[i].S-ss<<' '<<ans<<'\n';
          }
          else {
            w[qu[i].K]=0;
            Modiffy(1,1,n,dfn[qu[i].K]);
          }
        t=0;
        for (int i=1;i<=n;i++) Link[i]=0;
    }
}
