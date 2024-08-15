#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int mod=998244353;
int n,K,a[200010],b[20];
LL f[200010];
vector<int>POS[200010];
struct SegmentTree
{int l,r;LL data,len,val,sum;}st[800010];
inline int read()
{
	int x=0,w=0;char ch=0;
	while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
	while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return w?-x:x;
}
void upd(int p)
{
    if(st[p].l^st[p].r)
        st[p].len=(st[p<<1].len+st[p<<1|1].len)%mod;
	if(st[p].data)st[p].sum=0;
	else if(st[p].l==st[p].r)st[p].sum=st[p].len;
	else st[p].sum=(st[p<<1].sum+st[p<<1|1].sum)%mod;
}
void build(int p,int l,int r)
{
	st[p].l=l;st[p].r=r;st[p].data=st[p].len=st[p].sum=0;
	if(l==r)return st[p].len=0,void();
	int mid=(l+r)>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
	upd(p);
}
void change(int p,int l,int r,int delta)
{
	if(l<=st[p].l&&st[p].r<=r){
		st[p].data+=delta;
		return upd(p);
	}
	int mid=(st[p].l+st[p].r)>>1;
	if(l<=mid)change(p<<1,l,r,delta);
	if(mid<r)change(p<<1|1,l,r,delta);
	upd(p);
}
void modify(int p,int l,int r,int val)
{
    if(l<=st[p].l&&st[p].r<=r){
		st[p].len=val;
		return upd(p);
	}
	int mid=(st[p].l+st[p].r)>>1;
	if(l<=mid)modify(p<<1,l,r,val);
	if(mid<r)modify(p<<1|1,l,r,val);
	upd(p);
}
int main()
{
    n=read();K=read();
    for(int i=1;i<=n;i++){
        a[i]=read();
        POS[i].emplace_back(0);
    }
    for(int i=1;i<=K;i++)
        b[i]=read();
    build(1,1,n);
    modify(1,1,1,1);
    for(int i=1;i<=n;i++){
        POS[a[i]].emplace_back(i);
        int cnt=POS[a[i]].size()-1;
        for(int j=1;j<=K;j++)
        if(cnt>=b[j]){
            int r=POS[a[i]][cnt-b[j]+1],l=POS[a[i]][cnt-b[j]]+1;
            change(1,l,r,1);
            if(cnt>=b[j]+1){
                r=POS[a[i]][cnt-b[j]],l=POS[a[i]][cnt-b[j]-1]+1;
                change(1,l,r,-1);
            }
        }
        f[i]=st[1].sum;
        if(i<n)modify(1,i+1,i+1,f[i]);
        // cout<<i<<' '<<f[i]<<' '<<st[1].sum<<'\n';
    }
    cout<<f[n]<<'\n';
}