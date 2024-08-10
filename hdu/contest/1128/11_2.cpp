#include<bits/stdc++.h>
#define LL long long
const int mod=1000000007;
using namespace std;
int vis[200050],ans,n;
inline int read()
{
    int x=0,w=0;char ch=0;
    while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return w?-x:x;
}
LL ksm(LL B,LL K,LL A=1)
{
    if(K==2)K=1;
    for(;K;K>>=1,B=B*B%mod)
    if(K&1)A=A*B%mod;
    return A;
}
void dfs(int num)
{   
    if(!vis[num])vis[num]=1,ans++;
    for(int i=1;i<=n;i++){
        int temp=num;
        temp^=(1<<(i-1));
        if(i>1)temp^=1<<(i-2);
        if(i<n)temp^=1<<(i);
        if(!vis[temp])
            dfs(temp);
    }
}
int main()
{
    cout<<(1-ksm(998244353,mod-2)+mod)%mod<<endl;
    int T=read();
    while(T --> 0){
        n=read();ans=0;
        memset(vis,0,sizeof vis);
        dfs(0);
        printf("%lld\n",ans);
    }
        
}