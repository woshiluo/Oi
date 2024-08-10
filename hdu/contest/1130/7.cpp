#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int mod=1000000007;
int n,cnt,f[100010][3],g[100010];
LL m,K,a[100010],lsh[100010];
struct SegmentTree
{int l,r,data;}st[400010];
inline LL read()
{
    LL x=0,w=0;char ch=0;
    while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return w?-x:x;
}
void build(int p,int l,int r)
{
    st[p].l=l;st[p].r=r;st[p].data=0;
    if(l==r)return;
    int mid=(l+r)>>1;
    build(p<<1,l,mid);
    build(p<<1|1,mid+1,r);
}
int ask(int p,int l,int r)
{
    if(l>r)return 0;
    if(l<=st[p].l&&st[p].r<=r)
        return st[p].data;
    int mid=(st[p].l+st[p].r)>>1,temp=0;
    if(l<=mid)temp=ask(p<<1,l,r);
    if(mid<r)temp=max(temp,ask(p<<1|1,l,r));
    return temp;
}
void change(int p,int pos,int val)
{
    if(st[p].l==st[p].r)
        return st[p].data=max(st[p].data,val),void();
    int mid=(st[p].l+st[p].r)>>1;
    if(pos<=mid)change(p<<1,pos,val);
    else change(p<<1|1,pos,val);
    st[p].data=max(st[p<<1].data,st[p<<1|1].data);
}
int main()
{
    LL T=read();
    while(T --> 0){
        n=read();cin>>m>>K;
        for(int i=1;i<=n;i++)
            a[i]=lsh[i]=read();
        sort(lsh+1,lsh+1+n);
        cnt=unique(lsh+1,lsh+1+n)-lsh-1;
        for(int i=1;i<=n;i++)
            a[i]=lower_bound(lsh+1,lsh+1+cnt,a[i])-lsh;
        build(1,1,cnt);
        for(int i=1;i<=n;i++){
            int L=lower_bound(lsh+1,lsh+1+cnt,lsh[a[i]]-K)-lsh;
            int R=upper_bound(lsh+1,lsh+1+cnt,lsh[a[i]]+K)-lsh-1;
            f[i][0]=ask(1,L,a[i]-1);
            f[i][1]=ask(1,a[i],a[i]);
            f[i][2]=ask(1,a[i]+1,R);
            change(1,a[i],i);
        }
        int q=read();
        while(q --> 0){
            int l=read(),r=read();
            memset(g,0,sizeof g);
            int ans=0;
            for(int i=l;i<=r;i++){
                g[i]=max(g[i],g[f[i][0]]+1);
                g[i]=max(g[i],g[f[i][1]]+1);
                g[i]=max(g[i],g[f[i][2]]+1);
                ans=max(ans,g[i]);
            }
            cout<<r-l+1-ans<<"\n";
        }
    }
}