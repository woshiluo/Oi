#include<bits/stdc++.h>
#define LL long long
using namespace std;
int n,a[100010],lsh[100010];
LL ans=1e18,K;
inline int read()
{
    int x=0,w=0;char ch=0;
    while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return w?-x:x;
}
int main()
{
    n=read();K=read();
    for(int i=1;i<=n;i++)
        lsh[i]=a[i]=read();
    sort(lsh+1,lsh+1+n);
    if(K==1)
        return printf("%d\n",lsh[n]),0;
    for(int i=1;i<=lsh[n];i++){
        LL cost=i,temp=i;
        while(temp<=1000000000){
            cost+=n-(upper_bound(lsh+1,lsh+1+n,temp)-lsh)+1;
            temp*=K;
        }
        cout<<i<<' '<<cost<<'\n';
    }
    for(int i=1;i<=n;i++){
        LL cost=a[i],temp=a[i];
        while(temp<=1000000000){
            cost+=n-(upper_bound(lsh+1,lsh+1+n,temp)-lsh)+1;
            temp*=K;
        }
        ans=min(ans,cost);
    }
    cout<<ans<<'\n';
}