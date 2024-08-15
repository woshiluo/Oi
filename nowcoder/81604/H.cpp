#include<bits/stdc++.h>
#define LL long long
using namespace std;
const long double PI=acos(-1);
int n,top;
LL ans;
long double ZC;
struct VEC
{
	LL x,y;
	VEC operator-(const VEC&P1){return(VEC){x-P1.x,y-P1.y};}
	LL len(){return x*x+y*y;}
}p[2000010],st[2000010];
inline int read()
{
	int x=0,w=0;char ch=0;
	while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
	while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return w?-x:x;
}
LL cross(VEC n1,VEC n2)
{return n1.x*n2.y-n2.x*n1.y;}
LL get_area(VEC n1,VEC n2,VEC n3)
{return cross(n2-n1,n3-n1);}
bool cmp(VEC n1,VEC n2)
{
	LL temp=cross(n1-p[1],n2-p[1]);
	return temp>0||(temp==0&&(n1-p[1]).len()<(n2-p[1]).len());
}
int main()
{
    int T=read();
    p[0]=(VEC){0,0};
    while(T --> 0){
        ans=0;ZC=0;
        n=read();
        for(int i=1;i<=n;i++){
            LL x=read(),y=read();
            p[i]=(VEC){x,y};
        }
        for(int i=2;i<=n;i++)
            ZC+=sqrtl((p[i]-p[i-1]).len());
        ZC+=sqrtl((p[1]-p[n]).len());
        n=read();
        for(int i=1;i<=n;i++){
            LL x=read(),y=read();
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
            LL temp=max((st[i]-st[j]).len(),(st[i+1]-st[j]).len());
            ans=max(ans,temp);
        }
        printf("%.20Lf\n",sqrtl(ans)*PI*2+ZC);
    }
}