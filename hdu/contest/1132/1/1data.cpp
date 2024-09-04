#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int mod=998244353;
int n,K,cnt,End,sum,f[1010],a[1010],tot[1010],sIze[1010];
vector<int>G[1010];
inline LL read()
{
    LL x=0,w=0;char ch=0;
    while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return w?-x:x;
}
LL ksm(LL B,LL K,LL A=1)
{
    for(;K;K>>=1,B=B*B%mod)
    if(K&1)A=A*B%mod;
    return A;
}
int main()
{
    int T=5;
    cout<<T<<'\n';
    mt19937 mt(time(0));
    while(T --> 0){
        n=20;K=1;
        cout<<n<<' '<<K<<'\n';
        for(int i=2;i<=n;i++){
            cout<<mt()%(i-1)+1<<' ';
        }
        cout<<endl;
    }
}