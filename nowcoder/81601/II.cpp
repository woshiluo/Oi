#include <bits/stdc++.h>
using namespace std;
int a[1000010];
long long s[1000010],L[1000010],R[1000010],f[2][1000010];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin>>T;
    while (T--) {
        int n,m;
        cin>>n>>m;
        for (int i=1;i<=n;i++)
          for (int j=1;j<=m;j++) {
              int id=(i-1)*m+j;
              cin>>a[id];
          }
        for (int i=1;i<=n;i++) {
            int d=(i-1)*m;
            for (int j=1;j<=m;j++) 
                s[j]=s[j-1]+a[d+j];
            int p=i&1;R[0]=0;;
            for (int j=1;j<=m;j++) 
              R[j]=max(R[j-1]+a[d+j],0LL);
            L[m+1]=0;
            for (int j=m;j>=1;j--)
              L[j]=max(L[j+1]+a[d+j],0LL);
            if (i==1) {
                for (int j=1;j<=m;j++)
                  f[p][j]=R[j-1]+L[j+1]+a[j+d];
                continue;
            }
            // for (int j=1;j<=m;j++) cout<<i<<' '<<L[j]<<' '<<R[j]<<endl;
            long long Max=-1e18;
            for (int j=1;j<=m;j++) f[p][j]=-1e18;
            for (int j=1;j<=m;j++) {
                Max=max(Max,f[p^1][j]+R[j-1]-s[j-1]);
                f[p][j]=max(f[p][j],s[j]+L[j+1]+Max);
                // cout<<i<<' '<<j<<' '<<Max<<' '<<f[p][j]<<endl;
            }
            Max=-1e18;
            for (int j=m;j>=1;j--) {
                Max=max(Max,f[p^1][j]+L[j+1]+s[j]);
                f[p][j]=max(f[p][j],Max+R[j-1]-s[j-1]);
                // cout<<i<<' '<<j<<' '<<f[p][j]<<endl;
            }
        }
        long long ans=-1e18;
        for (int i=1;i<=m;i++) 
          ans=max(ans,f[n&1][i]);
        cout<<ans<<'\n';
    }
    return 0;
}