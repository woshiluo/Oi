#include <bits/stdc++.h>
using namespace std;
long long a[1010][1010];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m,k,l;
    cin>>n>>m>>k>>l;
    for (int i=1;i<=n;i++)
      for (int j=1;j<=m;j++)
        cin>>a[i][j];
    for (int i=1;i<=n;i++)
      for (int j=1;j<=m;j++)
        a[i][j]+=a[i][j-1];
    for (int j=1;j<=m;j++)
      for (int i=1;i<=n;i++)
        a[i][j]+=a[i-1][j];
    long long ans=0;
    for (int i=1;i<=k;i++)
      for (int j=1;j<=l;j++) {
          //(i,j)->(n-(k-i+1)+1,m-(l-j+1)+1);
          int x=i,y=j,xx=n-(k-i+1)+1,yy=m-(l-j+1)+1;
          long long sum=a[xx][yy]-a[x-1][yy]-a[xx][y-1]+a[x-1][y-1];
          ans+=abs(sum);
      }
    cout<<ans;
    return 0;
}