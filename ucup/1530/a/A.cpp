#include <bits/stdc++.h>
using namespace std;
const int Mod=998244353;
int a[210],c[210],f[205][300005],g[205][300005],p[210];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,T;
    cin>>n>>T;
    for (int i=1;i<=n;i++) cin>>c[i];
    for (int i=1;i<=n;i++) cin>>a[i];
    f[0][0]=1;
    for (int i=1;i<=n;i++) 
      for (int j=0;j<=T;j++) {
          f[i][j]=f[i-1][j];
          if (j>=a[i]) f[i][j]=(f[i][j]+f[i-1][j-a[i]])%Mod;
      }
    for (int i=0;i<=n;i++)
      for (int j=1;j<=T;j++)
        f[i][j]=(f[i][j]+f[i][j-1])%Mod;
    g[n+1][0]=1;
    for (int i=n;i>=1;i--) 
      for (int j=0;j<=T;j++) {
          g[i][j]=g[i+1][j];
          if (j>=a[i]) g[i][j]=(g[i][j]+g[i+1][j-a[i]])%Mod;
      }
    for (int i=1;i<=n+1;i++)
      for (int j=1;j<=T;j++)
        g[i][j]=(g[i][j]+g[i][j-1])%Mod;
    p[0]=1;
    for (int i=1;i<=n;i++) p[i]=(p[i-1]+p[i-1])%Mod;
    int ans=0;
    int s=0;
    for (int i=1;i<=n;i++) {
        if (a[i]<=T) ans+=1LL*c[i]*f[i-1][T-a[i]]%Mod*p[n-i]%Mod,ans%=Mod;
        if (s+a[i]<=T) ans+=1LL*c[i]*g[i+1][T-s-a[i]]%Mod*p[i-1]%Mod,ans%=Mod;
        s+=a[i];
    }
    cout<<ans;
    return 0;
}