#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int mod=1000000009;
LL m,n,ans;
LL ksm(LL B,LL K,LL A=1)
{
    for(;K;K>>=1,B=B*B%mod)
    if(K&1)A=A*B%mod;
    return A;
}
int main()
{
    cin>>m>>n;
    for(int i=1;i<=n;i++)
        (ans+=m+1ll*m*m*(n-i)%mod*ksm(i*m-i+1,mod-2))%=mod;
    cout<<ans<<'\n';
}