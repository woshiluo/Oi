#include<bits/stdc++.h>
#define LL long long
using namespace std;
int n;
LL a[500010],D[500010],U[500010],ans;
struct SegmentTree
{int l,r;LL Max,Min;}st[2000010];
inline LL read()
{
    LL x=0;char ch=0,w=0;
    while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return w?-x:x;
}
void upd(int p)
{
    st[p].Max=max(st[p<<1].Max,st[p<<1|1].Max);
    st[p].Min=min(st[p<<1].Min,st[p<<1|1].Min);
}
void build(int p,int l,int r)
{
    st[p].l=l;st[p].r=r;
    if(l==r)return st[p].Min=D[l],st[p].Max=U[r],void();
    int mid=(st[p].l+st[p].r)>>1;
    build(p<<1,l,mid);
    build(p<<1|1,mid+1,r);
    upd(p);
}
pair<LL,LL>ask(int p,int l,int r)
{
    if(l<=st[p].l&&st[p].r<=r)
        return {st[p].Min,st[p].Max};
    int mid=(st[p].l+st[p].r)>>1;
    if(r<=mid)return ask(p<<1,l,r);
    if(mid<l)return ask(p<<1|1,l,r);
    pair<LL,LL>LT=ask(p<<1,l,r),RT=ask(p<<1|1,l,r);
    return{min(LT.first,RT.first),max(LT.second,RT.second)};
}
bool check(int l,int r)
{
    pair<LL,LL>temp=ask(1,l+1,r);
    return temp.first>=temp.second;
}
int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        a[i]=read();
        D[i]=1e18;
        U[i]=-1e18;
        if(a[i]==a[i-1]){

        }else if(a[i]>a[i-1]){
            D[i]=a[i]+a[i-1];
        }else U[i]=a[i]+a[i-1];
        cout<<i<<' '<<D[i]<<' '<<U[i]<<endl;
    }
    build(1,1,n);
    for(int l=1,r=2;r<=n&&l<=n;l++){
        while(r<n&&check(l,r+1))r++;
        ans+=r-l;
        cout<<l<<' '<<r<<endl;
    }
    cout<<ans<<endl;
}