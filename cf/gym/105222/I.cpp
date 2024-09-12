#include <bits/stdc++.h>
using namespace std;
int n,l,h,a[55],b[55],x[55],y[55],r[55],u[55];
bool vis[55];
bool Check(int k,int xx,int yy)
{
    if (xx+a[k]>l||yy+b[k]>h) return false;
    for (int i=2;i<k;i++) {
        if (!vis[i]) continue;
        if ((xx>=x[i]&&xx<x[i]+a[i]||x[i]>=xx&&x[i]<xx+a[k])&&(yy>=y[i]&&yy<y[i]+b[i]||y[i]>=yy&&y[i]<yy+b[k]))
         return false;
    }
    return true;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>l>>h;
    for (int i=2;i<=n+1;i++) cin>>a[i]>>b[i],x[i]=l+1,y[i]=h+1;
    r[0]=0;u[1]=0;vis[0]=true;vis[1]=true;
    for (int i=2;i<=n+1;i++) {
        for (int j=0;j<i;j++)
          if (j!=1&&vis[j]) 
            for (int k=1;k<i;k++)
              if (vis[k]) {
                  if (r[j]>x[i]||r[j]==x[i]&&u[k]>y[i]) continue;
                  if (!Check(i,r[j],u[k])) continue;
                  x[i]=r[j];y[i]=u[k];
                  vis[i]=true;
              }
        // cout<<Check(i,5,0)<<'\n';
        r[i]=x[i]+a[i];u[i]=y[i]+b[i];
        if (vis[i]) cout<<x[i]<<' '<<y[i]<<'\n';
          else cout<<-1<<'\n';
    }
}