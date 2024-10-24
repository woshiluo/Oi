#include <bits/stdc++.h>
using namespace std;
int n;
int a[110],s[110];
int f[110][110],g[110][110][110];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,L,R;
    cin>>n>>L>>R;
    for (int i=1;i<=n;i++) cin>>a[i],s[i]=s[i-1]+a[i];
    for (int i=0;i<=n;i++)
      for (int j=0;j<=n;j++) {
            f[i][j]=1e9;
            for (int k=0;k<=n;k++) 
              g[i][j][k]=1e9;
      }
    for (int len=1;len<=n;len++) 
      for (int l=1;l<=n-len+1;l++) {
          int r=l+len-1;
          if (len==1) {
              f[l][r]=0;
              g[l][r][1]=0;
              continue;
          }
          for (int k=2;k<=R;k++) 
            for (int t=l+1;t<=r;t++)
              if (g[l][t-1][k-1]!=1e9) g[l][r][k]=min(g[l][r][k],g[l][t-1][k-1]+f[t][r]);
          for (int k=L;k<=R;k++)
            f[l][r]=min(f[l][r],g[l][r][k]+s[r]-s[l-1]);
          g[l][r][1]=f[l][r];
      }
    if (f[1][n]==1e9) cout<<0;
      else cout<<f[1][n];
    return 0;
}