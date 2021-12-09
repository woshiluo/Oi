//12252024832524
#include <bits/stdc++.h>
#define TT template<typename T>
using namespace std;

typedef long long LL;
const int MAXN = 2000005;
int n,m,tt;
int a[MAXN],b[MAXN],c[MAXN],cnt[MAXN];
vector<int> A[MAXN];

LL Read()
{
	LL x = 0,f = 1; char c = getchar();
	while(c > '9' || c < '0'){if(c == '-') f = -1;c = getchar();}
	while(c >= '0' && c <= '9'){x = (x*10) + (c^48);c = getchar();}
	return x * f;
}
TT void Put1(T x)
{
	if(x > 9) Put1(x/10);
	putchar(x%10^48);
}
TT void Put(T x,char c = -1)
{
	if(x < 0) putchar('-'),x = -x;
	Put1(x); if(c >= 0) putchar(c);
}
TT T Max(T x,T y){return x > y ? x : y;}
TT T Min(T x,T y){return x < y ? x : y;}
TT T Abs(T x){return x < 0 ? -x : x;}

int B[MAXN];
int lowbit(int x){return x & -x;}
void Add(int x){for(int i = x;i <= tt;i += lowbit(i)) ++B[i];}
int Sum(int x){int ret = 0;for(int i = x;i >= 1;i -= lowbit(i)) ret += B[i];return ret;}

#define lc (x<<1)
#define rc (x<<1|1)
int MIN[MAXN << 2],lz[MAXN << 2];
void calc(int x,int v){MIN[x] += v;lz[x] += v;}
void down(int x){if(!lz[x])return;calc(lc,lz[x]);calc(rc,lz[x]);lz[x]=0;}
void up(int x){MIN[x] = Min(MIN[lc],MIN[rc]);}
void Add(int x,int l,int r,int ql,int qr,int v)
{
	if(ql <= l && r <= qr) {calc(x,v);return;}
	int mid = (l+r) >> 1;
	down(x);
	if(ql <= mid) Add(lc,l,mid,ql,qr,v);
	if(mid+1 <= qr) Add(rc,mid+1,r,ql,qr,v);
	up(x); 
}
void Build(int x,int l,int r)
{
	lz[x] = MIN[x] = 0;
	if(l == r) return;
	int mid = (l+r) >> 1;
	Build(lc,l,mid); Build(rc,mid+1,r);
}

int main()
{
    // freopen("e.in","r",stdin);
	// freopen("e.out","w",stdout);
	for(int T = Read(); T ;-- T)
	{
		n = Read(); m = Read();
		for(int i = 1;i <= n;++ i) c[i] = a[i] = Read();
		for(int i = 1;i <= m;++ i) c[n+i] = b[i] = Read();
		sort(c+1,c+n+m+1);
		tt = unique(c+1,c+n+m+1) - c - 1;
		for(int i = 1;i <= tt;++ i) B[i] = cnt[i] = 0,A[i].clear();
		for(int i = 1;i <= n;++ i) a[i] = lower_bound(c+1,c+tt+1,a[i]) - c,A[a[i]].emplace_back(i);
		for(int i = 1;i <= m;++ i) b[i] = lower_bound(c+1,c+tt+1,b[i]) - c,++cnt[b[i]];
		LL ans = 0;
		Build(1,0,n+1);
		for(int i = 1;i <= n;++ i) Add(a[i]),ans += i - Sum(a[i]),Add(1,0,n+1,i+1,n+1,1);
		for(int i = 1;i <= tt;++ i)
		{
			for(auto x : A[i]) Add(1,0,n+1,x+1,n+1,-1);
			for(auto x : A[i-1]) Add(1,0,n+1,0,x-1,1);
			if(!cnt[i]) continue;
			ans += 1ll * cnt[i] * MIN[1];
		}
		Put(ans,'\n');
	}
	return 0;
}
