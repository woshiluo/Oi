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
int ask(int p,int l,int r)
{
    if(l<=st[p].l&&st[p].r<=r)
        return st[p].data;
    spread(p);
    int mid=(st[p].l+st[p].r)>>1;
    int temp=1e9;
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
inline int read(int x=0)
{scanf("%d",&x);return x;}
int main()
{
    memset(f,0x3f,sizeof f);
    f[0][0]=0;
    n=read();
    for(int i=1;i<=n;i++)
        a[i]=read();
    for(KKK=0;KKK<n;KKK++){
        build(1,KKK+1,n);
        MINTOP=MAXTOP=0;
        for(int i=KKK+1;i<=n;i++){
            while(MINTOP&&a[i]<a[MINst[MINTOP]]){
                change(1,MINst[MINTOP-1]+1,MINst[MINTOP],a[MINst[MINTOP]]);
                MINTOP--;
            }
            while(MAXTOP&&a[i]>a[MAXst[MAXTOP]]){
                change(1,MAXst[MAXTOP-1]+1,MAXst[MAXTOP],-a[MAXst[MAXTOP]]);
                MAXTOP--;
            }
            change(1,MINst[MINTOP]+1,i,-a[i]);
            change(1,MAXst[MAXTOP]+1,i,a[i]);
            MINst[++MINTOP]=i;
            MAXst[++MAXTOP]=i;
            f[KKK+1][i]=ask(1,KKK+1,i);
        }
    }
    for(int i=1;i<=n;i++)
        printf("%d\n",f[i][n]);
}


/*
83036
83036
83036
83036
83036
80105
78811
78811
59324
59324
58030
57186
53272
47004
45710
30121
12642
6374
1294
0
*//*
83036
83036
83036
83036
83036
83036
83036
83036
59324
59324
59324
59324
59324
59324
59324
41845
29504
7562
1294
0
*/