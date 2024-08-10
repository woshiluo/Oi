#include <bits/stdc++.h>
using namespace std;
const int Mod=1e9+7;
const int N=2e6+10;
int T,fac[N],inv[N],f[100010][3],a[100010],b[100010];
int ksm(int aa,int bb)
{
    int res=1;
    for (;bb;bb>>=1) {
        if (bb&1) res=1LL*res*aa%Mod;
        aa=1LL*aa*aa%Mod;
    }
    return res;
}
int C(int n,int m)
{
    if (n<0||m<0||n<m) return 0;
    return 1LL*fac[n]*inv[m]%Mod*inv[n-m]%Mod;
}
int Calc(int n,int m)
{
    return C(n+m+1,m);
}
int Solve(int n,int m)
{
    if (n<0||m<0) return 0;
    if (n==0) return 1;
    return Calc(n-1,m);
}
int A(int n,int m)//
{
    if (n<0||m<0) return 0;
    if (n==0) return m==0;
    return C(m-1+n,n-1);
}
int F(int x,int y)
{
    if (x<0||y<0) return 0;
    return (C(x+y+2,x+1)-2+Mod)%Mod;
}
int main()
{
	freopen("2.in","r",stdin);
	freopen("2.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin>>T;
    fac[0]=1;
    for (int i=1;i<N;i++) fac[i]=1LL*fac[i-1]*i%Mod;
    inv[N - 1]=ksm(fac[N - 1],Mod-2);
    for (int i=N-2;i>=0;i--) inv[i]=1LL*inv[i+1]*(i+1)%Mod;
	for( int o = 1; o <= T; o ++ ) {
        int n;
        cin>>n;
        for (int i=1;i<=n;i++) cin>>a[i]>>b[i];
        f[0][0]=f[0][1]=0;
        f[0][2]=1;
        int ans=1;
        for (int i=0;i<n;i++) {
            f[i+1][0]=f[i+1][1]=f[i+1][2]=0;
            if (a[i+1]==0&&b[i+1]==0) {
                f[i+1][0]=f[i][0];
                f[i+1][1]=f[i][1];
                f[i+1][2]=f[i][2];
                continue;
            }
            //f[i][0];
            if (a[i+1]) ans=ans+1LL*f[i][0]*(F(a[i+1]-1,b[i+1])+1)%Mod,ans%=Mod;
            if (b[i+1]) ans=ans+1LL*f[i][1]*(F(a[i+1],b[i+1]-1)+1)%Mod,ans%=Mod;
            ans=ans+1LL*f[i][2]*F(a[i+1],b[i+1])%Mod;ans%=Mod;
            f[i+1][0]=1LL*f[i][0]*Solve(a[i+1],b[i+1]-1)%Mod;
            f[i+1][1]=1LL*f[i][0]*Solve(b[i+1]+1,a[i+1]-2)%Mod;
            if (a[i+1]) f[i+1][2]=1LL*(A(a[i+1]-1,b[i+1])+A(b[i+1],a[i+1]-1))%Mod*f[i][0]%Mod;
            //f[i][1]
            f[i+1][0]=(f[i+1][0]+1LL*f[i][1]*Solve(a[i+1]+1,b[i+1]-2)%Mod)%Mod;
            f[i+1][1]=(f[i+1][1]+1LL*f[i][1]*Solve(b[i+1],a[i+1]-1)%Mod)%Mod;
            if (b[i+1]) f[i+1][2]=(f[i+1][2]+1LL*(A(a[i+1],b[i+1]-1)+A(b[i+1]-1,a[i+1]))%Mod*f[i][1]%Mod)%Mod;
            //f[i][2]
            f[i+1][0]=(f[i+1][0]+1LL*f[i][2]*Solve(a[i+1]+1,b[i+1]-1)%Mod)%Mod;
            f[i+1][1]=(f[i+1][1]+1LL*f[i][2]*Solve(b[i+1]+1,a[i+1]-1)%Mod)%Mod;
            f[i+1][2]=(f[i+1][2]+1LL*(A(a[i+1],b[i+1])+A(b[i+1],a[i+1]))%Mod*f[i][2]%Mod)%Mod;
        }
		std::cout << ans << "\n";
    }
}
