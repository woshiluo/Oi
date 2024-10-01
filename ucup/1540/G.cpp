#include <bits/stdc++.h>
using namespace std;
int n,Q,m,K;
string str[310];
unsigned long long h[310][60005],P[60005];
unsigned long long Calc(int k,int l,int r)
{
    return h[k][r]-h[k][l-1]*P[r-l+1];
}
int Solve(int k)
{
    int p=1;
    if (Calc(k,1,m)==Calc(n+1,1,m)) return 0;
    for (int i=1;i<=11;i++) {
        int l=p,r=m;
        while (l<r) {
            int mid=(l+r)>>1;
            if (Calc(k,p,mid)==Calc(n+1,p,mid)) l=mid+1;
              else r=mid;
        }
        p=l+1;
        if (p>m||Calc(k,p,m)==Calc(n+1,p,m)) return i;
    }
    return 11;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>Q>>m>>K;
    P[0]=1;
    for (int i=1;i<=m;i++) P[i]=P[i-1]*131;
    for (int i=1;i<=n;i++) cin>>str[i];
    for (int i=1;i<=n;i++) {
        h[i][0]=0;
        for (int j=1;j<=m;j++)
          h[i][j]=h[i][j-1]*131+str[i][j-1]-'a';
    }
    while (Q--) {
        cin>>str[n+1];
        h[n+1][0]=0;
        for (int i=1;i<=m;i++)
          h[n+1][i]=h[n+1][i-1]*131+str[n+1][i-1]-'a';
        int ans=0;
        for (int i=1;i<=n;i++)
          if (Solve(i)<=K) ans++;
        cout<<ans<<'\n';
    }
}