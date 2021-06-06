/*
Author: QAQAutoMaton
Lang: C++
Code: A.cpp
Mail: lk@qaq-am.com
Blog: https://www.qaq-am.com/
*/
#include<bits/stdc++.h>
#include<tr1/unordered_map>
#define debug(qaq...) fprintf(stderr,qaq)
#define DEBUG printf("Passing [%s] in LINE %d\n",__FUNCTION__,__LINE__)
#define Debug debug("Passing [%s] in LINE %d\n",__FUNCTION__,__LINE__)
#define all(x) x.begin(),x.end()
#define x first
#define y second
#define unq(a) sort(all(a)),a.erase(unique(all(a)),a.end())
using namespace std;
typedef unsigned uint;
typedef long long ll;
typedef unsigned long long ull;
typedef complex<double> cp;
typedef pair<int,int> pii;
int inf;
const double eps=1e-8;
const double pi=acos(-1.0);
template<class T,class T2>int chkmin(T &a,T2 b){return a>b?a=b,1:0;}
template<class T,class T2>int chkmax(T &a,T2 b){return a<b?a=b,1:0;}
template<class T>T sqr(T a){return a*a;}
template<class T,class T2>T mmin(T a,T2 b){return a<b?a:b;}
template<class T,class T2>T mmax(T a,T2 b){return a>b?a:b;}
template<class T>T aabs(T a){return a<0?-a:a;}
template<class T>int dcmp(T a,T b){return a>b;}
template<int *a>int cmp_a(int x,int y){return a[x]<a[y];}
template<class T>bool sort2(T &a,T &b){return a>b?swap(a,b),1:0;}
#define min mmin
#define max mmax
#define abs aabs
struct __INIT__{
	__INIT__(){
		fill((unsigned char*)&inf,(unsigned char*)&inf+sizeof(inf),0x3f);
	}
}__INIT___;
namespace io {
	const int SIZE = (1 << 21) + 1;
	char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[55]; int f, qr;
	// getchar
	#define gc() (iS == iT ? (iT = (iS = ibuf) + fread (ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS ++)) : *iS ++)
	// print the remaining part
	inline void flush () {
		fwrite (obuf, 1, oS - obuf, stdout);
		oS = obuf;
	}
	// putchar
	inline void putc (char x) {
		*oS ++ = x;
		if (oS == oT) flush ();
	}
	template<typename A>
	inline bool read (A &x) {
		for (f = 1, c = gc(); c < '0' || c > '9'; c = gc()) if (c == '-') f = -1;else if(c==EOF)return 0;
		for (x = 0; c <= '9' && c >= '0'; c = gc()) x = x * 10 + (c & 15); x *= f;
		return 1;
	}
	inline bool read (char &x) {
		while((x=gc())==' '||x=='\n' || x=='\r');
		return x!=EOF;
	}
	inline bool read(char *x){
		while((*x=gc())=='\n' || *x==' '||*x=='\r');
		if(*x==EOF)return 0;
		while(!(*x=='\n'||*x==' '||*x=='\r'||*x==EOF))*(++x)=gc();
		*x=0;
		return 1;
	}
	template<typename A,typename ...B>
	inline bool read(A &x,B &...y){
		return read(x)&&read(y...);
	}
	template<typename A>
	inline bool write (A x) {
		if (!x) putc ('0'); if (x < 0) putc ('-'), x = -x;
		while (x) qu[++ qr] = x % 10 + '0',  x /= 10;
		while (qr) putc (qu[qr --]);
		return 0;
	}
	inline bool write (char x) {
		putc(x);
		return 0;
	}
	inline bool write(const char *x){
		while(*x){putc(*x);++x;}
		return 0;
	}
	inline bool write(char *x){
		while(*x){putc(*x);++x;}
		return 0;
	}
	template<typename A,typename ...B>
	inline bool write(A x,B ...y){
		return write(x)||write(y...);
	}
	//no need to call flush at the end manually!
	struct Flusher_ {~Flusher_(){flush();}}io_flusher_;
}
using io :: read;
using io :: putc;
using io :: write;
const int p=1000000007;
struct Z{
	uint x;
	Z(){}
	Z(uint a){
		x=a;
	}
};
inline uint modp(const uint x){
	return x<p?x:x-p;
}
inline Z operator+(const Z x1, const Z x2) { return modp(x1.x+x2.x);}
inline Z operator-(const Z x1, const Z x2) { return modp(x1.x+p-x2.x);}
inline Z operator-(const Z x) {return x.x?p-x.x:0;}
inline Z operator*(const Z x1, const Z x2) { return static_cast<ull>(x1.x)*x2.x%p;}
void exgcd(int a,int b,int &x,int &y){
	if(!b){x=1;y=0;return;}
	exgcd(b,a%b,y,x);
	y-=(a/b)*x;
}
inline Z Inv(const Z a){
	int x,y;
	exgcd(p,a.x,x,y);
	return y<0?y+=p:y;
}
inline Z operator/(const Z x1, const Z x2) { return x1*Inv(x2);}

inline Z &operator++(Z &x1){x1.x==p-1?x1.x=0:++x1.x;return x1;} 
inline Z &operator--(Z &x1){x1.x?--x1.x:x1.x=p-1;return x1;}
inline Z &operator+=(Z &x1, const Z x2) { return x1 = x1 + x2; }
inline Z &operator-=(Z &x1, const Z x2) { return x1 = x1 - x2; }
inline Z &operator*=(Z &x1, const Z x2) { return x1 = x1 * x2; }
inline Z &operator/=(Z &x1, const Z x2) { return x1 = x1 / x2; }
inline Z fpm(Z a,int b){Z c(1);for(;b;b>>=1,a*=a)if(b&1)c*=a;return c;}
const int B=1000000;
Z phi[B+5],mphi[B+5],phis[B+5],mphis[B+5];
bitset<B+5>np;
int pri[B+5],ps;
int las[B+5];

namespace _phi{
	Z S(int x){return ((ll)x*(x+1)>>1)%p;}
	Z G(int x){return x;}
	tr1::unordered_map<int,Z> mp;
	Z F(int x){
	    if(x<=B)return phis[x]; //sF[x]为F(x)
	    if(mp.count(x))return mp[x];
	    Z ans=S(x);
	    for(int l=2,r;l<=x;l=r+1){
	        r=x/(x/l);
	        ans=(ans-(G(r)-G(l-1))*F(x/r));
	    }
	    return mp[x]=ans;
	}
}

namespace _mphi{
	Z S(int x){return _phi::F(x);}
	Z G(int x){return x;}
	tr1::unordered_map<int,Z> mp;
	Z F(int x){
	    if(x<=B)return mphis[x]; //sF[x]为F(x)
	    if(mp.count(x))return mp[x];
	    Z ans=S(x);
	    for(int l=2,r;l<=x;l=r+1){
	        r=x/(x/l);
	        ans=(ans-(G(r)-G(l-1))*F(x/r));
	    }
	    return mp[x]=ans;
	}
}

void init(int n){
	phi[1]=mphi[1]=1;
	phis[1]=mphis[1]=1;
	for(int i=2;i<=n;++i){
		if(!np[i]){
			phi[i]=i-1;mphi[i]=i-2;
			las[i]=1;
			pri[++ps]=i;
		}
		for(int j=1;j<=ps && i*pri[j]<=n;++j){
			np[i*pri[j]]=1;
			if(i%pri[j]){
				las[i*pri[j]]=i;
				phi[i*pri[j]]=phi[i]*(pri[j]-1);
				mphi[i*pri[j]]=mphi[i]*(pri[j]-2);
			}
			else{
				las[i*pri[j]]=las[i];
				phi[i*pri[j]]=phi[i]*pri[j];
				mphi[i*pri[j]]=mphi[las[i]]*phi[i/las[i]]*(pri[j]-1);
				break;
			}
		}
		phis[i]=phi[i]+phis[i-1];
		mphis[i]=mphi[i]+mphis[i-1];
	}
}
signed main(){
#ifdef QAQAutoMaton 
	freopen("A.in","r",stdin);
	freopen("A.out","w",stdout);
#endif
	freopen("a.in","r",stdin);
	int n,m;	
	read(n,m);
	if(n>m)swap(n,m);
	init(B);
	Z ans(0);
	Z las=0;
	for(int i=1,j;i<=n;i=j+1){
		j=min(n/(n/i),m/(m/i));
		Z nex=_mphi::F(j);
		ans+=(nex-las)*(n/i)*(m/i);
		las=nex;
	}
	/*for(int i=1;i<=n;++i){
		ans+=mphi[i]*(n/i)*(m/i);
	}*/
	write(ans.x,'\n');
	return 0;
}
