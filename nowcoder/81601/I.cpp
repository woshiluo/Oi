#include<bits/stdc++.h>
#define LL long long
using namespace std;
int n,K,KKK,a[5010],MINst[5010],MAXst[5010],MINTOP,MAXTOP;
int f[5010][5010];
struct SegmenTree
{int l,r,data,add;}st[20010];
void upd(int p)
{st[p].data=min(st[p<<1].data,st[p<<1|1].data);}
void build(int p,int l,int r)
{
    st[p].l=l;st[p].r=r;
    st[p].add=0;st[p].data=1e9;
    if(l==r)
        return st[p].data=f[KKK][l-1],void();
    int mid=(l+r)>>1;
    build(p<<1,l,mid);
    build(p<<1|1,mid+1,r);
    upd(p);
}
void spread(int p)
{
    if(st[p].add){
        st[p<<1].add+=st[p].add;
        st[p<<1|1].add+=st[p].add;
        st[p<<1].data+=st[p].add;
        st[p<<1|1].data+=st[p].add;
        st[p].add=0;
    }
}
LL ask(int p,int l,int r)
{
    if(l<=st[p].l&&st[p].r<=r)
        return st[p].data;
    spread(p);
    int mid=(st[p].l+st[p].r)>>1;
    LL temp=1e18;
    if(l<=mid)temp=min(temp,ask(p<<1,l,r));
    if(mid<r)temp=min(temp,ask(p<<1|1,l,r));
    return temp;
}
void change(int p,int l,int r,int delta)
{
    if(l<=st[p].l&&st[p].r<=r)
        return st[p].data+=delta,st[p].add+=delta,void();  
    spread(p);
    int mid=(st[p].l+st[p].r)>>1;
    if(l<=mid)change(p<<1,l,r,delta);
    if(mid<r)change(p<<1|1,l,r,delta);
    upd(p);
}
inline int read()
{
    int x=0,w=0;char ch=0;
    while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return w?-x:x;
}
int main()
{
    
}
