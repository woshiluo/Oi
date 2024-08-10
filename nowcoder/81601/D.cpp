#include <bits/stdc++.h>
using namespace std;
int t=1,Link[100010],dfn[100010],low[100010],cnt,col[100010],tot,f[100010];
bool vis[100010],fla[400010];
struct edge
{
    int v,nex;
}e[400010];
struct Edge
{
    int X,Y,ty;
}E[200010];
void Insert(int x,int y) 
{
    e[++t].nex=Link[x];e[t].v=y;Link[x]=t;
    return ;
}
int Get(int x) {return f[x]==x?x:f[x]=Get(f[x]);}
void Tarjan(int x,int in)
{
    dfn[x]=low[x]=++cnt;
    for (int i=Link[x];i;i=e[i].nex) {
        if (!dfn[e[i].v]) {
            Tarjan(e[i].v,i);
            if (dfn[x]<low[e[i].v]) fla[i]=fla[i^1]=1;
            low[x]=min(low[x],low[e[i].v]);
        }
        else if (i!=(in^1))
          low[x]=min(low[x],dfn[e[i].v]);
    }
    return ;
}
void dfs(int now)
{
    vis[now]=true;col[now]=tot;
    for (int i=Link[now];i;i=e[i].nex) {
        if (vis[e[i].v]||fla[i]) continue;
        dfs(e[i].v);
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m;
    cin>>n>>m;
    for (int i=1;i<=m;i++) {
        int x,y;
        string str;
        cin>>x>>y>>str;
        E[i].X=x;E[i].Y=y;
        if (str[0]=='L') 
          Insert(x,y),Insert(y,x),E[i].ty=0;
        else E[i].ty=1;
    }
    for (int i=1;i<=n;i++)
      if (!dfn[i])
        Tarjan(i,0);
    for (int i=1;i<=n;i++)
        if (!vis[i]) {
            ++tot;
            dfs(i);
        }
    for (int i=1;i<=tot;i++) f[i]=i;
    vector<int> ans;
    for (int i=1;i<=m;i++)
      if (E[i].ty==1) {
          int fx=Get(col[E[i].X]),fy=Get(col[E[i].Y]);
          if (fx!=fy) ans.push_back(i),f[fx]=fy;
      }
    if ((int)ans.size()==tot-1) {
        cout<<"YES"<<'\n';
        int s=(int)ans.size();
        for (int i=1;i<=m;i++)
          if (E[i].ty==0&&col[E[i].X]==col[E[i].Y]) 
            s++;
        cout<<s<<'\n';
        for (int i=0;i<(int)ans.size();i++)
          cout<<E[ans[i]].X<<' '<<E[ans[i]].Y<<'\n';
        for (int i=1;i<=m;i++)
          if (E[i].ty==0&&col[E[i].X]==col[E[i].Y]) 
            cout<<E[i].X<<' '<<E[i].Y<<'\n';
    }
    else cout<<"NO";
    return 0;
}
