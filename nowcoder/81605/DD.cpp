#include <bits/stdc++.h>
using namespace std;
int n,m,r0;
double K;
int p[100010];
double P[100010];
double f[1010][1010];
double Solve()
{
    double res=0;
    f[0][0]=r0;
    for (int i=1;i<=n;i++) {
        for (int j=0;j<=n;j++) f[i][j]=0;
        for (int j=max(0,i-m);j<=i;j++) {
            if (j==0) f[i][j]=f[i-1][j];
            else f[i][j]=max(f[i-1][j],f[i-1][j-1]*(1-K)+K*p[i]);
        }
    }
    for (int j=n-m;j<=n;j++) res=max(res,f[n][j]);
    return res;
}
int main()
{
    freopen("in.txt","r",stdin);
    freopen("ans.txt","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    srand(time(0));
    int T;
    cin>>T;
    while (T--) {
        cin>>n>>m>>K;
        cin>>r0;
        for (int i=1;i<=n;i++) cin>>p[i];
        double ans=Solve();
        cout<<fixed<<setprecision(15)<<ans<<'\n';
    }
    return 0;
}