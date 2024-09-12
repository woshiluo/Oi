#include<bits/stdc++.h>
typedef long long LL;
using namespace std;
long long x,y,r,dx,dy,lx,ly,rx,ry;
LL cross(LL A,LL B,LL C,LL D)
{return A*D-C*B;}
LL mul(LL A,LL B,LL C,LL D)
{return A*C+B*D;}
LL sgn(LL t)
{
    if(t==0)return 0;
    if(t>0)return 1;
    return -1;
}
bool check(LL xx,LL yy,LL xxx,LL yyy)
{
    pair<LL,LL>n1={x,y},n2={x,y},n3={xx,yy},n4={xxx,yyy};
    LL rate=1e9,one=1;
    if(dx)rate=min(rate,abs(10000000ll/dx)+one);
    if(dy)rate=min(rate,abs(10000000ll/dy)+one);
    n2.first+=rate*dx;
    n2.second+=rate*dy;
    LL 
    c1=cross(n2.first-n1.first,n2.second-n1.second,n4.first-n1.first,n4.second-n1.second),
    c2=cross(n2.first-n1.first,n2.second-n1.second,n3.first-n1.first,n3.second-n1.second),
    c3=cross(n4.first-n3.first,n4.second-n3.second,n1.first-n3.first,n1.second-n3.second),
    c4=cross(n4.first-n3.first,n4.second-n3.second,n2.first-n3.first,n2.second-n3.second);
    return sgn(c1)*sgn(c2)<=0&&sgn(c3)*sgn(c4)<=0;
}
bool calc()
{
    if(lx>rx||ly>ry)return 0;
    if(lx<=x&&x<=rx&&ly<=y&&y<=ry)
        return 1;
    if(lx==rx&&ly==ry){
        if(cross(dx,dy,lx-x,ly-y)==0&&mul(dx,dy,lx-x,ly-y)>=0)
            return 1;
        return 0;
    }
    if(lx^rx){
        if(check(lx,ly,rx,ly))return 1;
        if(check(lx,ry,rx,ry))return 1;
    }
    if(ly^ry){
        if(check(lx,ly,lx,ry))return 1;
        if(check(rx,ly,rx,ry))return 1;
    }
    return check(lx,ly,rx,ry)|check(lx,ry,rx,ly);
}
int main()
{
    ios::sync_with_stdio(false);
    int T;cin>>T;
    while(T --> 0){
        cin>>x>>y>>r>>dx>>dy>>lx>>ly>>rx>>ry;
        lx+=r;ly+=r;rx-=r;ry-=r;
        cout<<(calc()?"Yes\n":"No\n");
    }
}