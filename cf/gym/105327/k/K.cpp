#include <bits/stdc++.h>
using namespace std;
int a[110],A[110],B[110];
bool f[110][10010],vis[110];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin>>n;
    int s=0;
    for (int i=1;i<=n;i++) cin>>a[i],s+=a[i];
    if (s&1) {
        cout<<-1;
        return 0;
    }
    f[0][0]=1;
    for (int i=1;i<=n;i++) 
      for (int j=0;j<=s;j++) {
          f[i][j]=f[i-1][j];
          if (j>=a[i]) f[i][j]=f[i-1][j]||f[i-1][j-a[i]];
      }
    if (!f[n][s/2]) {
        cout<<-1;
        return 0;
    }
    int p=s/2;
    for (int i=n;i>=1;i--)
      if (!f[i-1][p]) {
        vis[i]=true;
        p-=a[i];
      }
    int l=0,r=0;
    for (int i=1;i<=n;i++)
      if (vis[i]) A[++l]=a[i];
        else B[++r]=a[i];
    int x=0,y=0;
    for (int i=1;i<=n;i++)
      if (x<=y) {
          cout<<A[l]<<' ';
          x+=A[l];l--;
      }
      else {
          cout<<B[r]<<' ';
          y+=B[r];r--;
      }
    return 0;
}