#include<bits/stdc++.h>
#define LL long long
using namespace std;
int n,a[100010],lsh[100010];
LL ans=1e18,K;
priority_queue<int>q;
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
    for(int i=1;i<=n;i++)
        q.push(a[i]);
    LL cnt=0;
    while(q.top()>1){
        ans=min(ans,cnt+q.top());
        int x=q.top();x/=K;
        q.pop();
        q.push(x);cnt++;
    }
    ans=min(ans,cnt+q.top());
    cout<<ans<<'\n';
}