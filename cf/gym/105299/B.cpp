#include <bits/stdc++.h>
using namespace std;
int a[100010],s[100010],n;
long long ans=0;
struct Node
{
    int al,ar,ml,mr;
};
Node t[400010];
int Calc(int l,int r)
{
    if (!l || !r || l>r) return -1;
    return s[r]-s[l-1];
}
bool Check(const int l,const int r,const int ll,const int rr)
{
    const int A=Calc(l,r);
    const int B=Calc(ll,rr);
    if (A==B) {
        if (l==ll) return r-l+1<rr-ll+1;
        return l<ll;
    }
    return A>B;
}
Node Merge(const Node &p1,const Node &p2,const int l,const int r,const int mid)
{
    Node p;
    p.al=p.ar=p.ml=p.mr=0;
    if (Check(p1.al,p1.ar,p.al,p.ar)) p.al=p1.al,p.ar=p1.ar;
    if (Check(p2.al,p2.ar,p.al,p.ar)) p.al=p2.al,p.ar=p2.ar;
    if (p1.mr&&p2.ml&&Check(p1.mr,p2.ml,p.al,p.ar)) p.al=p1.mr,p.ar=p2.ml;
    p.ml=p1.ml;
    if (p2.ml&&Calc(l,p2.ml)>Calc(l,p1.ml)&&Calc(l,p2.ml)>0)
      p.ml=p2.ml;
    p.mr=p2.mr;
    if (p1.mr) {
        if (!p2.mr&&Calc(p1.mr,r)>=0) p.mr=p1.mr;
        else if (p2.mr&&Calc(p1.mr,r)>=Calc(p2.mr,r)) p.mr=p1.mr;
    }
    return p;
}
void Build(int p,int l,int r)
{
    if (l==r) {
        if (a[l]>0) {
            t[p].al=l;t[p].ar=l;
            t[p].ml=l;t[p].mr=l;
        }
        return ;
    }
    int mid=(l+r)>>1;
    Build(p<<1,l,mid);Build(p<<1|1,mid+1,r);
    t[p]=Merge(t[p<<1],t[p<<1|1],l,r,mid);
    return ;
}
Node Query(const int p,const int l,const int r,const int L,const int R)
{
	if ( L == l && r == R ) return t[p];
    const int mid=(l+r)>>1;
    if (R<=mid) return Query(p<<1,l,mid,L,R);
    if (L>mid) return Query(p<<1|1,mid+1,r,L,R);
    return Merge(Query(p<<1,l,mid,L,mid),Query(p<<1|1,mid+1,r,mid+1,R),L,R,mid);
}
void Solve(int l,int r)
{
//	std::cout << l << ' ' << r << '\n';
    if (l>r) return ;
    if (l==r) {
        if (a[r]==1) ans++;
        return ;
    }
    Node res=Query(1,1,n,l,r);
//    cout<<l<<' '<<r<<' '<<res.al<<' '<<res.ar<<'\n';
    if (res.al==0) return;
    ans+=1LL*(res.ar-res.al+1)*(res.ar-res.al+1);
    Solve(l,res.al-1);
	Solve(res.ar+1,r);
    return ;
}
int main()
{
#ifdef woshiluo
	freopen( "B.in", "r", stdin );
//	freopen( "B.out", "w", stdout );
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n;
    for (int i=1;i<=n;i++) {
        cin>>a[i];
        if (!a[i]) a[i]=-1;
        s[i]=s[i-1]+a[i];
    }
    Build(1,1,n);
    Solve(1,n);
    cout<<ans;
}
