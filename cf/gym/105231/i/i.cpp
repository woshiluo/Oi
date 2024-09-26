#include<bits/stdc++.h>
using namespace std;
const double eps=1e-7;
int n,X[110],Y[110];
double Z[110];
struct VEC
{
    double x,y;
    VEC operator+(const VEC&n1)const{return(VEC){x+n1.x,y+n1.y};};
    VEC operator-(const VEC&n1)const{return(VEC){x-n1.x,y-n1.y};};
    VEC operator/(const double&r)const{return(VEC){x/r,y/r};};
    VEC operator*(const double&r)const{return(VEC){x*r,y*r};};
    VEC turn(){return(VEC){-y,x};}
};
struct LINE
{VEC st,ed;};
LINE get_line(VEC n1,VEC n2)
{return(LINE){(n1+n2)/2,(n1+n2)/2+(n1-n2).turn()};}
double dot(VEC n1,VEC n2)
{return n1.x*n2.x+n1.y*n2.y;}
double cross(VEC n1,VEC n2)
{return n1.x*n2.y-n1.y*n2.x;}
VEC calc(LINE l1,LINE l2)
{
    VEC v1=l1.ed-l1.st,v2=l2.ed-l2.st,v3=l1.st-l2.st;
    double t=cross(v2,v3)/cross(v1,v2);
    return l1.st+(v1*t);
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>X[i]>>Y[i],Z[i]=1e9;
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            double xx=(X[i]+X[j])/2.,yy=(Y[i]+Y[j])/2.,r=sqrt((X[i]-X[j])*(X[i]-X[j])+(Y[i]-Y[j])*(Y[i]-Y[j]))/2;
            int temp=0;
            for(int k=1;k<=n;k++)
            if(sqrt((xx-X[k])*(xx-X[k])+(yy-Y[k])*(yy-Y[k]))<=r+eps)
                temp++;
			Z[temp]=min(Z[temp],r);
        }
        for(int j=i+1;j<=n;j++)
        for(int k=j+1;k<=n;k++){
            LINE l1=get_line({X[i],Y[i]},{X[j],Y[j]}),l2=get_line({X[i],Y[i]},{X[k],Y[k]});
            VEC O=calc(l1,l2);
            double r=sqrt((O.x-X[i])*(O.x-X[i])+(O.y-Y[i])*(O.y-Y[i]));
            int temp=0;
            // cout<<i<<' '<<j<<' '<<k<<' '<<O.x<<' '<<O.y<<' '<<r<<'\n';
            for(int m=1;m<=n;m++)
            if(sqrt((O.x-X[m])*(O.x-X[m])+(O.y-Y[m])*(O.y-Y[m]))<=r+eps)
                temp++;
			Z[temp]=min(Z[temp],r);
        }
    }
    for(int i=2;i<=n;i++){
        for(int j=1;j<i;j++)
            printf("%.10lf\n",Z[i]);
    }
}
