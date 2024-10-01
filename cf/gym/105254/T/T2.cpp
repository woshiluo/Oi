#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;
using ll=long long;
using pii=pair<int,int>;
using vi=vector<int>;
using vl=vector<ll>;
#define pb push_back
#define all(a) begin(a),end(a)

const int N=300010,MOD=1e9+7;
const char en='\n';
const ll LLINF=1ll<<60;
const double eps=1e-11;

template<class T> int sgn(T x) {return (x>0)-(x<0);}
template<class T>
struct Point {
	typedef Point P;
	T x,y;
	explicit Point(T x=0,T y=0) : x(x), y(y) {}
	bool operator<(P p) const {return tie(x,y)<tie(p.x,p.y);}
	bool operator==(P p) const {return tie(x,y)==tie(p.x,p.y);}
	P operator+(P p) const {return P(x+p.x,y+p.y);}
	P operator-(P p) const {return P(x-p.x,y-p.y);}
	P operator*(T d) const {return P(x*d,y*d);}
	P operator/(T d) const {return P(x/d,y/d);}
	T dot(P p) const {return x*p.x+y*p.y;}
	T cross(P p) const {return x*p.y-y*p.x;}
	T cross(P a,P b) const {return (a-*this).cross(b-*this);}
	T dist2() const {return x*x+y*y;}
	double dist() const {return sqrt((double)dist2());}
	double angle() const {return atan2(y,x);}
	P unit() const {return *this/dist();}
	P perp() const {return P(-y,x);}
	P normal() const {return perp().unit();}
	P rotate(double a) const {
		return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a));}
	friend ostream& operator<<(ostream&os,P p) {
		return os<<"("<<p.x<<","<<p.y<<")";}
};

typedef Point<double> P;

double segDist(P&s,P&e,P&p)
{
	if (s==e) return (p-s).dist();
	auto d=(e-s).dist2(),t=min(d,max(.0,(p-s).dot(e-s)));
	return ((p-s)*d-(e-s)*t).dist()/d;
}

bool onSegment(P s,P e,P p)
{
	return segDist(s,e,p)<=eps;
}

vector<P> segInter(P a,P b,P c,P d)
{
	auto oa=c.cross(d,a),ob=c.cross(d,b),oc=a.cross(b,c),od=a.cross(b,d);
	if (sgn(oa)*sgn(ob)<0 && sgn(oc)*sgn(od)<0)
		return {(a*ob-b*oa)/(ob-oa)};
	set<P> s;
	if (onSegment(c,d,a)) s.insert(a);
	if (onSegment(c,d,b)) s.insert(b);
	if (onSegment(a,b,c)) s.insert(c);
	if (onSegment(a,b,d)) s.insert(d);
	return {all(s)};
}

P lineProj(P a,P b,P p,bool refl=false)
{
	P v=b-a;
	return p-v.perp()*(1+refl)*v.cross(p-a)/v.dist2();
}

pair<vector<P>,double> inp()
{
	double x1,y1,x2,y2,h;
	cin>>x1>>y1>>x2>>y2>>h;
	vector<P> v;
	v.pb(P(x1,y1));
	v.pb(P(x2,y2));
	for (int i=0;i<2;++i)
	{
		P a=v[(int)v.size()-2],b=v[(int)v.size()-1];
		v.pb(b+(b-a).perp());
	}
	return {v,h};
}

double dis(P a,P a1,P b1,P a2,P b2,P b)
{
	double an=LLINF;
	for (int k=0;k<2;++k)
	{
		for (int l=0;l<2;++l)
		{
			vector<P> v1=segInter(a,b,a1,b1),v2=segInter(a,b,a2,b2);
			if (v1.size()==1 && v2.size()==1) an=min(an,(a-v1[0]).dist()+(v1[0]-v2[0]).dist()+(b-v2[0]).dist());
			v2=segInter(a1,b,a2,b2);
			if (v2.size()==1) an=min(an,(a-a1).dist()+(a1-v2[0]).dist()+(b-v2[0]).dist());
			v2=segInter(b1,b,a2,b2);
			if (v2.size()==1) an=min(an,(a-b1).dist()+(b1-v2[0]).dist()+(b-v2[0]).dist());
			v1=segInter(a,a2,a1,b1);
			if (v1.size()==1) an=min(an,(a-v1[0]).dist()+(v1[0]-a2).dist()+(a2-b).dist());
			v1=segInter(a,b2,a1,b1);
			if (v1.size()==1) an=min(an,(a-v1[0]).dist()+(v1[0]-b2).dist()+(b2-b).dist());
			an=min(an,(a-a1).dist()+(a1-a2).dist()+(a2-b).dist());
			an=min(an,(a-a1).dist()+(a1-b2).dist()+(b2-b).dist());
			an=min(an,(a-b1).dist()+(b1-a2).dist()+(a2-b).dist());
			an=min(an,(a-b1).dist()+(b1-b2).dist()+(b2-b).dist());
			b=lineProj(a2,b2,b,1);
		}
		a=lineProj(a1,b1,a,1);
	}
	return an;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	pair<vector<P>,double> pir1=inp();
	pair<vector<P>,double> pir2=inp();
	double mi=LLINF;
	for (int i=0;i<4;++i) for (int j=0;j<4;++j)
	{
		P a1=pir1.x[i],b1=pir1.x[(i+1)%4];
		P a2=pir2.x[j],b2=pir2.x[(j+1)%4];
		P c1=(a1+b1+(b1-a1).perp())/2,c2=(a2+b2+(b2-a2).perp())/2;
		P p1=(a1+b1)/2,p2=(a2+b2)/2;
		double po1=(p1-c1).dist(),po2=(p2-c2).dist();
		P a=p1+(c1-p1)*(P(pir1.y,po1).dist()/po1);
		P b=p2+(c2-p2)*(P(pir2.y,po2).dist()/po2);
		mi=min(mi,dis(a,a1,b1,a2,b2,b));
	}
	cout<<fixed<<setprecision(10)<<mi<<en;
}