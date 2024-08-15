#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int mod=998244353;
int n,m,a[110],ans,cnt;
inline int read()
{
    int x=0,w=0;char ch=0;
    while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return w?-x:x;
}
void dfs(int tot,LL rate)
{
    bool flag=1,flag2=0;
    // cout<<tot<<' '<<rate<<'\n';
    for(int i=1;i<=n;i++)
    if(!a[i])flag=0;
    else flag2=1;
    if(!flag2)
        return(ans+=tot*rate)%=mod,(cnt+=rate)%=mod,void();
    for(int i=1;i<=n;i++)
    if(a[i]>0){
        a[i]--;
        dfs(tot+flag,rate*(a[i]+1)%mod);
        a[i]++;
    }
}
LL ksm(LL B,LL K,LL A=1)
{
    for(;K;K>>=1,B=B*B%mod)
    if(K&1)A=A*B%mod;
    return A;
}
int main()
{
    cout<<__gcd(258048,1*2*3*4*5*6*7*8)<<'\n';
    // cout<<__gcd(3240,1*2*3*4*5*6)<<'\n';
    cout<<258048/__gcd(258048,1*2*3*4*5*6*7*8)<<' '<<1*2*3*4*5*6*7*8/__gcd(258048,1*2*3*4*5*6*7*8)<<'\n';
    cout<<147456/1152<<' '<<1*2*3*4*5*6*7*8/1152<<'\n';
    cout<<__gcd(147456,1*2*3*4*5*6*7*8)<<'\n';
    cout<<147456/1152<<' '<<1*2*3*4*5*6*7*8/1152<<'\n';
    return 0;
    int T=read();
    for(n=4;n<=4;n++)
    for(m=2;m<=2;m++){
        for(int i=1;i<=n;i++)
            a[i]=m;
        ans=0;cnt=0;
        dfs(0,1);
        cout<<n<<' '<<m<<' '<<ans<<' '<<cnt<<' '<<1ll*ans*ksm(cnt,mod-2)%mod<<'\n';
    }
}
/*
4
3 3
2 5
5 2
3 4

213909510
332748126
823947724
931694738
*/