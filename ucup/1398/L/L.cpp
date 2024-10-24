#include<bits/stdc++.h>
#define LL long long
using namespace std;
int n,fa[200010],Lp[200010],Rp[200010],Log[200010];
LL a[200010],d[200010],ans=0,Max[2][100010][20];
struct SYZ
{
    LL d;int l,r,ll,rr;
    int operator<(const SYZ n2)const{
        return n2.d<d;
    }
};
priority_queue<SYZ>q;
inline LL read()
{
    LL x=0;char ch=0,w=0;
    while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return w?-x:x;
}
int getfa(int x)
{return fa[x]==x?x:fa[x]=getfa(fa[x]);}
int getL(int x)
{
    x--;
    while(Lp[getfa(x)]!=Rp[getfa(x)])x=Lp[getfa(x)]-1;
    return x;
}
int getR(int x)
{
    x++;
    while(Lp[getfa(x)]!=Rp[getfa(x)])x=Rp[getfa(x)]+1;
    return x;
}
void merge(int x,int y)
{
    x=getfa(x);y=getfa(y);
    Lp[x]=min(Lp[x],Lp[y]);
    Rp[x]=max(Rp[x],Rp[y]);
    fa[y]=x;
}
int check(SYZ temp){
    if(Lp[getfa(temp.ll)]!=Rp[getfa(temp.ll)])
        return 0;
    if(Lp[getfa(temp.rr)]!=Rp[getfa(temp.rr)])
        return 0;
    return 1;
}
void prepare()
{
    Log[0]=-1;
    for(int i=1;i<=n;i++){
        Log[i]=Log[i>>1]+1;
        Max[i&1][(i+1)/2][0]=d[i+1];
    }
    for(int t=1;t<=Log[n/2];t++)
    for(int i=1,len1=1<<(t-1),len2=1<<t;i+len2-1<=n/2;i++){
        Max[0][i][t]=max(Max[0][i][t-1],Max[0][i+len1][t-1]);
        Max[1][i][t]=max(Max[1][i][t-1],Max[1][i+len1][t-1]);
    }
}
LL calc(int l,int r)
{
    int len=(r-l+1)/2,LOG=Log[len];
    // cout<<"CALC"<<endl;
    // cout<<(l+1)/2<<' '<<LOG<<' '<<len;
    if(l&1)
        return max(Max[1][(l+1)/2][LOG],Max[1][(l+1)/2+len-1-(1<<LOG)+1][LOG]);
    return max(Max[0][(l+1)/2][LOG],Max[0][(l+1)/2+len-1-(1<<LOG)+1][LOG]);
}
void upd(int x)
{
    if(x==0||x==n+1)return;
    if(getfa(x)!=getfa(x-1)){
        if(Lp[getfa(x-1)]!=Rp[getfa(x-1)])
            merge(x,x-1);
    }
    if(getfa(x)!=getfa(x+1)){
        if(Lp[getfa(x+1)]!=Rp[getfa(x+1)])
            merge(x,x+1);
    }
}
int main()
{
    n=read();
    for(int i=1;i<=n;i++)
        a[i]=read();
    sort(a+1,a+1+n);
    Lp[n+1]=Rp[n+1]=fa[n+1]=n+1;
    for(int i=1;i<=n;i++)
        d[i]=a[i]-a[i-1],Lp[i]=Rp[i]=fa[i]=i;
    for(int i=2;i<=n;i++)
        q.push({d[i],i,i-1,i-1,i});
    // cout<<"DEF\n";
    prepare();
    // cout<<"ABC\n";
    for(int i=1;i+i<=n;i++){
        while(!check(q.top()))q.pop();
        SYZ temp=q.top();q.pop();
        merge(temp.l,temp.ll);
        merge(temp.r,temp.rr);
        upd(temp.l);upd(temp.r);
        upd(temp.ll);upd(temp.rr);
        ans=max(ans,calc(temp.ll,temp.rr));
        int L=getL(temp.ll),nl;
        int R=getR(temp.rr),nr;
        nl=min({temp.l,temp.r,temp.ll,temp.rr});
        nr=max({temp.l,temp.r,temp.ll,temp.rr});
        temp.ll=nl;temp.rr=nr;
        // cout<<temp.l<<' '<<temp.r<<' '<<temp.ll<<' '<<temp.rr<<' '<<L<<' '<<R<<endl;
        if(L!=0&&R!=n+1)
            q.push({calc(L,R),temp.ll,temp.rr,L,R});
        if(L!=0){
            int L2=getL(L);
            // cout<<L<<','<<L2<<endl;
            if(L2!=0)
                q.push({calc(L2,temp.rr),temp.ll,temp.rr,L2,L});
        }
        if(R!=n+1){
            int R2=getR(R);
            // cout<<R<<','<<R2<<endl;
            if(R2!=n+1)
                q.push({calc(temp.ll,R2),temp.ll,temp.rr,R,R2});
        }
        printf("%lld ",ans);
    }
}
/*
6
100 13 20 14 10 105
*/