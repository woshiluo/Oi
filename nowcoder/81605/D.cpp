#include <bits/stdc++.h>
using namespace std;
const int lim=500;
int n,m,r0;
double K;
int p[100010];
double P[100010];
double f[100010][510];
bool vis[100010][510];
double Solve()
{
    double res=0;
    f[0][0]=r0;
    for (int i=1;i<=n;i++) {
        for (int j=0;j<=lim;j++) f[i][j]=0;
        for (int j=max(0,i-m);j<=min(i,lim);j++) {
            if (j==0) f[i][j]=f[i-1][j];
            else f[i][j]=max(f[i-1][j],f[i-1][j-1]*(1-K)+K*p[i]);
        }
    }
    for (int j=n-m;j<=min(n,lim);j++) res=max(res,f[n][j]);
    return res;
}
double Solve1()
{

    double res=0;
    int N=max(lim,n-m);
    P[0]=1;
    for (int i=1;i<=N;i++) P[i]=P[i-1]*(1-K);
    res=r0*P[N];
    int tmp=max(0,n-m-lim);
    for (int i=0;i<=lim;i++) f[tmp][i]=0,vis[tmp][i]=false;
    vis[tmp][0]=true;
    for (int i=max(1,n-m-lim+1);i<=n;i++) {
        f[i][0]=0;vis[i][0]=true;
        for (int j=1;j<=lim;j++) f[i][j]=0,vis[i][j]=false;
        for (int j=1;j<=min(lim,i);j++) {
            if (vis[i-1][j]) {
                vis[i][j]=true;
                f[i][j]=max(f[i][j],f[i-1][j]);
            }
            if (vis[i-1][j-1]) {
                f[i][j]=max(f[i][j],f[i-1][j-1]+K*P[lim-j]*p[i]);
                vis[i][j]=true;
            }
        }
    }
    if (vis[n][lim]) res+=f[n][lim];
    return res;
}
int main()
{
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
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
        if (n>lim) ans=max(ans,Solve1());
        cout<<fixed<<setprecision(15)<<ans<<'\n';
    }
    return 0;
}