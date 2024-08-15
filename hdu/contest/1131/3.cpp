#include <bits/stdc++.h>
using namespace std;
const int Mod=1e9+7;
int ksm(int aa,int bb)
{
    int res=1;
    for (;bb;bb>>=1) {
        if (bb&1) res=1LL*res*aa%Mod;
        aa=1LL*aa*aa%Mod;
    }
    return res;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin>>T;
    while (T--) {
        int n;
        cin>>n;
        for (int i=1;i<=n;i++) cin>>a[i]>>b[i],p[i]=1LL*a[i]*ksm(b[i],Mod-2)%Mod;
        for (int len=2;len<=n;len+=2)
          for (int l=1;l<=n-len+1;l++) {
              int r=l+len-1;
              if (len==2) g[l][r]=1LL*p[l]*(1-p[r]+Mod)%Mod;
              else {
                  g[l][r]=1lL*g[l+1][r-1]*p[l]%Mod*(1-p[r]+Mod)%Mod;
                  for (int k=l+2;k<r;k+=2) g[l][r]=(g[l][r]+1LL*g[l][k-1]*g[k+1][r-1]%Mod)%Mod;
              }
          }
        for (int j=0;j<n;j++) {
            f[j][0][0]=1;
            f[j][0][1]=0;
            for (int i=1;i<=n;i++) {
                for (int k=max(1,i-j);k<i;k++) {
                    f[j][i][0]=(f[j][i][0]+1LL*f[j][k-1][0]*g[k+1][i-1]%Mod*(1-p[k]+Mod)%Mod)%Mod;
                    f[j][i][1]=(f[j][i][1]+1LL*f[j][k-1][1]*g[k+1][i-1]%Mod*(1-p[k]+Mod)%Mod)%Mod;
                }
                f[j][i][1]=(f[j][i][1]+1LL*(f[j][i-1][0]+f[j][i-1][1])*p[i]%Mod)%Mod;
            }
        }
         for (int j=0;j<n;j++) {
            ff[j][n+1][0]=1;
            ff[j][n+1][1]=0;
            for (int i=n;i>=1;i--) {
                for (int k=i+1;k<=min(i+j,n);k++) {
                    ff[j][i][0]=(ff[j][i][0]+1LL*ff[j][k+1][0]*g[i+1][k-1]%Mod*(1-p[k]+Mod)%Mod)%Mod;
                    ff[j][i][1]=(ff[j][i][1]+1LL*ff[j][k+1][1]*g[i+1][k-1]%Mod*(1-p[k]+Mod)%Mod)%Mod;
                }
                ff[j][i][1]=(f[j][i][1]+1LL*(f[j][i-1][0]+f[j][i-1][1])*p[i]%Mod)%Mod;
            }
        }
        for (int i=1;i<n;i++) 
          for (int j=1;j<=n-i;j++) {
              int tmp=1;
              if (i!=1) tmp=g[j+1][j+i-1];
              ans+=1LL*i*p[j]%Mod*(1-p[j+i]+Mod)%Mod*tmp%Mod*(1LL*f[i-1][j-1][0]*ff[j+i+1][j][0]%Mod+1LL*f[i-1][j-1][0]*ff[j+i+1][j][1]%Mod+1LL*f[i-1][j-1][1]*ff[j+i+1][j][0]%Mod)%Mod;
              ans%=Mod;
          }
                
                  
            }
        }
    }
}