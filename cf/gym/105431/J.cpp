#include <bits/stdc++.h>
using namespace std;
int a[2010],b[2010],cnta[4010],cntb[4010];
bool vis[2010];
int main()
{
	// freopen( "J.in", "r", stdin );
	// freopen( "J.out", "w", stdout );
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin>>n;
    for (int i=1;i<=n;i++) {
        cin>>a[i]>>b[i];
        cnta[a[i]]++;
        cntb[b[i]]++;
    }
    if (n==1) {
        if (a[1]==2&&b[1]==2) 
          cout<<"NO";
        else cout<<"YES"<<'\n'<<1<<' '<<1<<'\n';
        return 0;
    }
    cout<<"YES"<<'\n';
    for (int i=1;i<=n;i++)
      if (cnta[2*i]==0) {
          for (int j=1;j<=n;j++) 
            cout<<i<<' '<<j<<'\n';
          return 0;
      }
    for (int i=1;i<=n;i++)
      if (cntb[2*i]==0) {
          for (int j=1;j<=n;j++)
            cout<<j<<' '<<i<<'\n';
          return 0;
      }
    for (int i=1;i<=n;i++) vis[i]=false;
    int cnt=0;
    for (int i=1;i<=n;i++)
      if (a[i]==2) {
          for (int j=1;j<=n&&cnt<n;j++) 
            if (!vis[j]&&j+j!=b[i]) {
                cout<<1<<' '<<j<<'\n';
                cnt++;
                vis[j]=true;
                if (j<=b[i]&&b[i]-j<=n) vis[b[i]-j]=true;
            }
      }
    for (int i=1;i<=n;i++) vis[i]=false;
      for (int i=1;i<=n;i++)
      if (a[i]==4) {
          for (int j=1;j<=n&&cnt<n;j++) 
            if (!vis[j]&&j+j!=b[i]) {
                cout<<2<<' '<<j<<'\n';
                cnt++;
                vis[j]=true;
                if (j<=b[i]&&b[i]-j<=n) vis[b[i]-j]=true;
            }
      }
}
