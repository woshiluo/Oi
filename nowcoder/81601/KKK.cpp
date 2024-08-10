#include<bits/stdc++.h>
#define LL long long
using namespace std;
int n,K,KKK,a[5010],MINst[5010],MAXst[5010],MINTOP,MAXTOP;
LL f[5010][5010],g[5010][5010],b[5010];
struct SegmenTree
{int l,r;LL data,add,color;}st[20010];
void upd(int p)
{st[p].data=min(st[p<<1].data,st[p<<1|1].data);}
void build(int p,int l,int r)
{
    st[p].l=l;st[p].r=r;st[p].color=-19260817;
    st[p].add=0;st[p].data=1e18;
    if(l==r)
        return st[p].data=f[KKK][l-1],void();
    int mid=(l+r)>>1;
    build(p<<1,l,mid);
    build(p<<1|1,mid+1,r);
    upd(p);
}
void spread(int p)
{
    if(st[p].color!=-19260817){
        st[p<<1].color=st[p].color;
        st[p<<1|1].color=st[p].color;
        st[p<<1].data=st[p].color;
        st[p<<1|1].data=st[p].color;
        st[p<<1].add=st[p<<1|1].add=0;
        st[p].color=-19260817;
    }
    if(!st[p].add){
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
inline int read(int x=0)
{scanf("%d",&x);return x;}
int main()
{

    memset(f,0x3f,sizeof f);
    f[0][0]=0;
    n=20;mt19937 mt(233);
    for(int i=1;i<=n;i++)
        b[i]=a[i]=mt()%100000+1;
    sort(b+1,b+1+n);
    for(int i=1;i<=n;i++){
        int temp=0;
        for(int j=1;j<=n;j++)
        if(b[j]<a[i])
            temp++;
        a[i]=temp+1;
    }
    for(KKK=0;KKK<n;KKK++){
        MINTOP=MAXTOP=0;
        for(int i=1;i<=n;i++){
            int Max,Min;
            Max=Min=a[i];
            for(int j=i;j;j--){
                Max=max(Max,a[j]);Min=min(Min,a[j]);
                if(f[KKK][j-1]+Max-Min<=f[KKK+1][i]){
                    f[KKK+1][i]=f[KKK][j-1]+Max-Min;
                    g[KKK+1][i]=j-1;
                }
            }
        }
    }
    for(int i=1;i<=n;i++)
        cout<<a[i]<<" \n"[i==n];
    for(int K=1;K<=n;K++){
        for(int i=1;i<=n;i++){
            printf("%3d",g[K][i]);
           // cout<<g[K][i]<<" \n"[i==n];
        }
        cout << endl;
    }
    for(int i=1;i<=n;i++)
        printf("%lld\n",f[i][n]);
}