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
void dfs(int x)
{
    f[x]=0;sIze[x]=1;
    tot[x]=a[x];
    for(int y:G[x]){
        dfs(y);
        f[x]+=f[y];
        f[x]+=tot[x]*(sIze[y]-tot[y]);
        f[x]+=tot[y]*(sIze[x]-tot[x]);
        sIze[x]+=sIze[y];
        tot[x]+=tot[y];
    }
}
int calc()
{
    dfs(1);
    int sum=0;
    for(int i=1;i<=n;i++)
    sum+=f[i];
    return sum;
}
LL ksm(LL B,LL K,LL A=1)
{
    for(;K;K>>=1,B=B*B%mod)
    if(K&1)A=A*B%mod;
    return A;
}
int main()
{
    int T=read();
    while(T --> 0){
        n=read();K=read();End=1<<n;
        for(int i=1;i<=n;i++)
            G[i].clear();
        for(int i=2;i<=n;i++){
            int fa=read();
            G[fa].push_back(i);
        }
        int Max=0,Cnt=0;
        for(int i=0;i<End;i++){
            for(int j=1;j<=n;j++)
            if(i>>(j-1)&1)
                a[j]=1;
            else a[j]=0;
            int temp=calc();
            if(temp>Max){
                Max=temp;Cnt=1;
            }else if(temp==Max)
                Cnt++;
        }
        cout<<ksm(Cnt,K)<<'\n';
    }
}