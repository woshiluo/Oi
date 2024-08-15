#include <bits/stdc++.h>
using namespace std;
int n,t,Link[1000010],F[1000010],sum[1000010];
int c[1000010],dfn[1000010],tot;
bool fla[2000010];
vector<int> V[1000010];
struct edge
{
    int v,nex;
}e[2000010];
void Insert(int x,int y)
{
    e[++t].nex=Link[x];e[t].v=y;Link[x]=t;
    fla[t]=true;
}
void dfs(int now,int fa)
{
    sum[now]=1;dfn[now]=++tot;
    for (int i=Link[now];i;i=e[i].nex) {
        if (e[i].v==fa) continue;
        dfs(e[i].v,now);
        sum[now]+=sum[e[i].v];
    }
    return ;
}
void Add(int x,int val)
{
    for (;x<=n;x+=x&(-x)) c[x]+=val;
    return ;
}
int Get(int x)
{
    int res=0;
    for (;x;x-=x&(-x)) res+=c[x];
    return res;
}
void dfs1(int now,int fa,int las) 
{
    int s=0;
    for (int i=0;i<(int)V[now].size();i++) 
        Add(dfn[V[now][i]],1),s++;
    if (fa) {
        int r=dfn[now]+sum[now]-1,l=dfn[now];
        int res=s-Get(r)+Get(l-1);
        if (!res) fla[las]=false;
    }
    for (int i=Link[now];i;i=e[i].nex) {
        if (e[i].v==fa) continue;
        int r=dfn[e[i].v]+sum[e[i].v]-1,l=dfn[e[i].v];
        int res=Get(r)-Get(l-1);
        if (!res) fla[i]=false;
    }
    for (int i=0;i<(int)V[now].size();i++)
      Add(dfn[V[now][i]],-1);
    for (int i=Link[now];i;i=e[i].nex) {
        if (e[i].v==fa) continue;
        dfs1(e[i].v,now,i^1);
    }
    return ;
}
bool Solve(int now,int fa)
{
    if (F[now]&&F[now]!=fa) return false;
    if (F[now]) return true;
    F[now]=fa;
    for (int i=Link[now];i;i=e[i].nex) {
        if (e[i].v==fa) continue;
        if (!Solve(e[i].v,now)) return false;
    }
    return true;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin>>T;
    while (T--) {
        cin>>n;
        t=1;
        for (int i=1;i<=n;i++) Link[i]=0,V[i].clear(),F[i]=0;
        for (int i=2;i<=n;i++) {
            int x;
            cin>>x;
            V[x].push_back(i);
            V[i].push_back(x);
        }
        for (int i=2;i<=n;i++) {
            int x;
            cin>>x;
            Insert(x,i);Insert(i,x);   
        }
        tot=0;
        dfs(1,0);
        dfs1(1,0,0);
        bool ff=true;
        for (int i=2;i<=t;i+=2)
          if (!fla[i]&&!fla[i+1]) {
              ff=false;
              break;
          }
        if (!ff) {
            cout<<-1<<'\n';
            continue;
        }
        for (int i=1;i<=n;i++) 
          for (int j=Link[i];j;j=e[j].nex) 
            if (fla[j]&&!fla[j^1]) {
                cout<<i<<' '<<e[j].v<<endl;
                if (!Solve(e[j].v,i)) {
                    ff=false;
                    break;
                }
            }
        if (!ff) {
            cout<<-1<<'\n';
            continue;
        }
        int res=0;
        for (int i=1;i<=n;i++) 
          if (!F[i]) {res=i;break;}
        cout<<res<<'\n';
    }
}
/*
1
5
1 1 2 2
1 5 2 2
*/