#include <bits/stdc++.h>
using namespace std;
const int Mod=1e9+7;
long long f[1000010][3],g[1000010][3];
int main()
{
    int n,kr,kg,kb;
    cin>>n>>kr>>kg>>kb;
    f[1][0]=f[1][1]=f[1][2]=1;
    g[1][0]=g[1][1]=g[1][2]=1;
    for (int i=2;i<=n;i++) {
        f[i][0]=g[i-1][1]-g[max(i-kr-1,0)][1]+g[i-1][2]-g[max(i-kr-1,0)][2];
        f[i][0]=(f[i][0]%Mod+Mod)%Mod;
        f[i][1]=g[i-1][0]-g[max(i-kg-1,0)][0]+g[i-1][2]-g[max(i-kg-1,0)][2];
        f[i][1]=(f[i][1]%Mod+Mod)%Mod;
        f[i][2]=g[i-1][0]-g[max(i-kb-1,0)][0]+g[i-1][1]-g[max(i-kb-1,0)][1];
        f[i][2]=(f[i][2]%Mod+Mod)%Mod;
        g[i][0]=(g[i-1][0]+f[i][0])%Mod;
        g[i][1]=(g[i-1][1]+f[i][1])%Mod;
        g[i][2]=(g[i-1][2]+f[i][2])%Mod;
        // cout<<i<<' '<<f[i][0]<<' '<<f[i][2]<<' '<<f[i][2]<<'\n';
    }
    cout<<(f[n][0]+f[n][1]+f[n][2])%Mod;
}