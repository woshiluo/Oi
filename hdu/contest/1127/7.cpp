#include<bits/stdc++.h>
#define LL long long
using namespace std;
int n,q,a[250010],b[500010],Log[500010],Max[500010][20],vis[500010];
int BLO,tot,bel[250010],Lp[100010],Rp[100100],Min[100010];
LL ans=0;
inline int read()
{
    int x=0,w=0;char ch=0;
    while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return w?-x:x;
}
void prepare()
{
    Log[0]=-1;
    for(int i=1;i<=n+n;i++)
        Log[i]=Log[i>>1]+1;
    for(int i=1;i<=n+n;i++)
        Max[i][0]=b[i];
    //cout<<Log[n+n]<<endl;
    for(int t=1;t<=Log[n+n];t++)
    for(int i=1;i+(1<<t)-1<=n+n;i++)
        Max[i][t]=max(Max[i+(1<<(t-1))][t-1],Max[i][t-1]);
    BLO=ceil(sqrt(n/sqrt(30)));
    tot=n/BLO;
    for(int i=1;i<=tot;i++){
        Lp[i]=(i-1)*BLO+1;
        Rp[i]=i*BLO;
    }
    if(Rp[tot]<n){
        Rp[tot+1]=n;
        Lp[tot+1]=Rp[tot]+1;
        tot++;
    }
    memset(Min,0x3f,sizeof Min);
    for(int i=1;i<=tot;i++)
    for(int j=Lp[i];j<=Rp[i];j++){
        bel[j]=i;
        Min[i]=min(Min[i],a[j]);
    }
}
int ask(int l,int r)
{
    int t=Log[r-l+1];
    return max(Max[l][t],Max[r-(1<<t)+1][t]);
}
void calc(int delta)
{
    if(vis[delta])return;
    vis[delta]=1;
    for(int i=1;i<=tot;i++){
        int l=Lp[i],r=Rp[i];
        if(ask(l+delta,r+delta)<=Min[i])continue;
        Min[i]=1e9;
        for(int j=Lp[i];j<=Rp[i];j++){
            ans-=a[j];
            a[j]=max(a[j],b[j+delta]);
            ans+=a[j];
            Min[i]=min(Min[i],a[j]);
        }
    }
}
int main()
{
    int T=read();
    while(T --> 0){
        memset(vis,0,sizeof vis);
        n=read();q=read();ans=0;
        for(int i=1;i<=n;i++)
            a[i]=read(),ans+=a[i];
        for(int i=1;i<=n;i++)
            b[i]=b[i+n]=read();
        prepare();
        // for(int i=1;i<=n;i++)
        //    cout<<bel[i]<<" \n"[i==n];
        // for(int i=1;i<=tot;i++)
        //    cout<<Lp[i]<<' '<<Rp[i]<<endl;
        while(q --> 0){
            calc(read());
            printf("%lld\n",ans);
            //for(int i=1;i<=n;i++)
            //    cout<<a[i]<<' ';
            //    cout<<endl;
        }
    }
}
