#include <bits/stdc++.h>
using namespace std;
int a[200010],t=0,Link[600010],num,sum,n,m,c[600010];
int vis[600010];
struct edge
{
    int v,nex;
}e[1000010];
void Add_Edge(int x,int y)
{
    e[++t].nex=Link[x];e[t].v=y;Link[x]=t;
    return ;
}
bool dfs(int now,int fa,int k)
{
    vis[now]=num;c[now]=k;
    if (now>n) sum+=k;
    bool ff=false;
    for (int i=Link[now];i;i=e[i].nex) {
        if (e[i].v==fa) continue;
        ff=true;
        if (now<=n) {
            if (vis[e[i].v]!=num) return dfs(e[i].v,now,(-k-a[now]+6)%3);
              else {
                  if ((k+a[now]+c[e[i].v])%3==0) return true;
                    return false;
              }
        }
        else if (!dfs(e[i].v,now,k)) return false;
    }
    if (!ff&&now<=n) {
        if ((k+a[now])%3) return false;
    }
    return true;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m;
    string str;
    cin>>str;
    for (int i=1;i<=n;i++)
      if (str[i-1]=='R') a[i]=0;
        else if (str[i-1]=='G') a[i]=1;
          else a[i]=2;
    for (int i=1;i<=m;i++) {
        int k;
        cin>>k;
        for (int j=1;j<=k;j++) {
            int x;
            cin>>x;
            Add_Edge(n+i,x);Add_Edge(x,n+i);
        }
    }
    int ans=0;
    for (int i=1;i<=m;i++) 
      if (!vis[n+i]) {
          int Min=-1;
          for (int j=0;j<3;j++) {
              sum=0;
              ++num;
              if (dfs(n+i,0,j)&&(Min==-1||sum<Min)) Min=sum;
          }
          if (Min==-1) {
              cout<<"impossible";
              return 0;
          }
          ans+=Min;
        //   cout<<i<<' '<<Min<<'\n';
      }
    for (int i=1;i<=n;i++)
      if (!vis[i]&&a[i]) {
          cout<<"impossible";
          return 0;
      }
    cout<<ans;
    return 0;
}
