#include<bits/stdc++.h>
#define LL long long
using namespace std;
int n,top;
LL ans;
struct VEC
{
	LL x,y;
	bool operator==(const VEC&P1){return x==P1.x&&y==P1.y;}
	VEC operator+(const VEC&P1){return(VEC){x+P1.x,y+P1.y};}
	VEC operator-(const VEC&P1){return(VEC){x-P1.x,y-P1.y};}
	VEC operator*(const LL K1){return(VEC){x*K1,y*K1};}
	VEC operator/(const LL K1){return(VEC){x/K1,y/K1};}
	VEC turn(LL K1){return(VEC){x*cos(K1)-y*sin(K1),x*sin(K1)+y*cos(K1)};}
	VEC turn90(){return(VEC){-y,x};}
	LL len(){return x*x+y*y;};
}p[50010],st[50010];
struct POLY
{vector<VEC>p;};
inline int read()
{
	int x=0,w=0;char ch=0;
	while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
	while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return w?-x:x;
}
LL dot(VEC n1,VEC n2)
{return n1.x*n2.x+n1.y*n2.y;}
LL cross(VEC n1,VEC n2)
{return n1.x*n2.y-n2.x*n1.y;}
LL get_angle(VEC n1,VEC n2)
{return acos(dot(n1,n2)/(n1.len()*n2.len()));}
LL get_area(VEC n1,VEC n2,VEC n3)
{return cross(n2-n1,n3-n1);}
bool cmp(VEC n1,VEC n2)
{
	LL temp=cross(n1-p[1],n2-p[1]);
	return temp>0||(temp==0&&(n1-p[1]).len()<(n2-p[1]).len());
}
int main()
{
	n=read();
	for(int i=1;i<=n;i++){
		int x=read(),y=read();
		p[i]=(VEC){x,y};
		if(i>1&&(p[i].y<p[1].y||(p[i].y==p[1].y&&(p[i]-p[0]).len()<(p[1]-p[0]).len())))
			swap(p[1],p[i]);
	}
    
	sort(p+2,p+1+n,cmp);
	st[top=1]=p[1];
	for(int i=2;i<=n;i++){
		while(top>1&&cross(st[top]-st[top-1],p[i]-st[top])<=0)top--;
		st[++top]=p[i];
	}
	st[top+1]=st[1];
	ans=(st[1]-st[2]).len();
	for(int i=1,j=3;i<=top;i++){
		while(abs(get_area(st[i],st[i+1],st[j]))<abs(get_area(st[i],st[i+1],st[j%top+1])))j=j%top+1;
		ans=max(ans,max((st[i]-st[j]).len(),(st[i+1]-st[j]).len()));
	}
	printf("%lld\n",ans);
}