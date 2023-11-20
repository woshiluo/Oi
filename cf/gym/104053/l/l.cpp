#include<iostream>
#include<cstdio>
using namespace std;
const int N=100005;
const int MOD=998244353;
int qpow(int a,int b)
{
    int res=1;
    while(b)
    {
        if(b&1) res=(long long)res*a%MOD;
        a=(long long)a*a%MOD,b>>=1;
    }
    return res;
}
int getinv(int x)
{
    return qpow(x,MOD-2);
}
int fac[N],ifac[N];
void init(int n=100000)
{
    fac[0]=1;
    for(int i=1;i<=n;i++)
        fac[i]=(long long)fac[i-1]*i%MOD;
    ifac[n]=getinv(fac[n]);
    for(int i=n;i>=1;i--)
        ifac[i-1]=(long long)ifac[i]*i%MOD;
    return;
}
int C(int n,int m)
{
    if(m>n) return 0;
    if(m==0||m==n) return 1;
    return (long long)fac[n]*ifac[m]%MOD*ifac[n-m]%MOD;
}
void solve()
{
    int n,m;
    cin>>n>>m;
    int ans=(long long)C(n-1,m-1)*fac[n]%MOD;
    cout<<ans<<"\n";
    return;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr),cout.tie(nullptr);
    init();
    int T;
    cin>>T;
    while(T--)
        solve();
    return 0;
}