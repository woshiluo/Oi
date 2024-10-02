#include<bits/stdc++.h>
using namespace std;
const long double eps=1e-10;
long double X1,Y1,X2,Y2,X3,Y3,X4,Y4,H1,H2,ans=1e18;
long double dx1,dy1,dx2,dy2,len1,len2,h1,h2;
int sgn(long double x)
{
    if(fabs(x)<eps)return 0;
    if(x>0)return 1;
    return -1;
}
long double cross(long double A,long double B,long double C,long double D)
{return A*D-C*B;}
long double dot(long double A,long double B,long double C,long double D)
{return A*C+B*D;}
int check(long double x1,long double y1,long double x2,long double y2,long double x3,long double y3,long double x4,long double y4)
{
    // cout<<x1<<','<<y1<<','<<x2<<','<<y2<<','<<x3<<','<<y3<<','<<x4<<','<<y4<<'\n';
    if(sgn(cross(x1-x2,y1-y2,x3-x2,y3-y2))==sgn(cross(x1-x2,y1-y2,x4-x2,y4-y2)))
        return 0;
    swap(x2,x3);swap(y2,y3);
    // cout<<x1<<' '<<y1<<' '<<x2<<' '<<y2<<' '<<x3<<' '<<y3<<' '<<x'<<y4<<'\n';
    // cout<<x1<<','<<y1<<','<<x2<<','<<y2<<','<<x3<<','<<y3<<','<<x4<<','<<y4<<'\n';

    if(sgn(cross(x1-x2,y1-y2,x3-x2,y3-y2))==sgn(cross(x1-x2,y1-y2,x4-x2,y4-y2)))
        return 0;
    swap(x2,x4);swap(y2,y4);
    // cout<<x1<<' '<<y1<<' '<<x2<<' '<<y2<<' '<<x3<<' '<<y3<<' '<<x4<<' '<<y4<<'\n';
    // cout<<x1<<','<<y1<<','<<x2<<','<<y2<<','<<x3<<','<<y3<<','<<x4<<','<<y4<<'\n';

    if(sgn(cross(x1-x2,y1-y2,x3-x2,y3-y2))==sgn(cross(x1-x2,y1-y2,x4-x2,y4-y2)))
        return 0;
    return 1;
}
pair<long double,long double>po(long double x1,double y1,double x2,double y2,long double rate)
{return {x1+(x2-x1)*rate,y1+(y2-y1)*rate};}
long double calc(long double x1,double y1,double x2,double y2,pair<long double,long double>pp)
{
    long double x3=pp.first,y3=pp.second;
    return sqrt((x3-x1)*(x3-x1)+(y3-y1)*(y3-y1))+sqrt((x3-x2)*(x3-x2)+(y3-y2)*(y3-y2));
}
long double calc(int i,int j)
{
    long double x1,y1,x2,y2,x3,y3;
    long double x4,y4,x5,y5,x6,y6;
    if(i==1)x1=X1,y1=Y1,x2=X2,y2=Y2;
    if(j==1)x4=X3,y4=Y3,x5=X4,y5=Y4;
    if(i==2)x1=X2,y1=Y2,x2=X2-dy1,y2=Y2+dx1;
    if(j==2)x4=X4,y4=Y4,x5=X4-dy2,y5=Y4+dx2;
    if(i==3)x2=X1-dy1,y2=Y1+dx1,x1=X2-dy1,y1=Y2+dx1;
    if(j==3)x5=X3-dy2,y5=Y3+dx2,x4=X4-dy2,y4=Y4+dx2;
    if(i==4)x1=X1-dy1,y1=Y1+dx1,x2=X1,y2=Y1;
    if(j==4)x4=X3-dy2,y4=Y3+dx2,x5=X3,y5=Y3;
    x3=(x1+x2)/2-(y2-y1)*h1/len1;
    y3=(y1+y2)/2+(x2-x1)*h1/len1;

    x6=(x5+x4)/2-(y5-y4)*h2/len2;
    y6=(y5+y4)/2+(x5-x4)*h2/len2;

    long double Dx1,Dy1,Dx2,Dy2;
    Dx1=x6-x3;Dy1=y6-y3;Dx2=-Dx1;Dy2=-Dy1;

    // cout << i<<' '<<j<<' '<<x1<<' '<<y1<<' '<<x2<< ' '<<y2<<' '<<x3<<' '<<y3<<' '<<x4<<' '<<y4<<' '<<x5<<' '<<y5<<' '<<x6<<' '<<y6<<' '<<Dx1<<' '<<Dy1<< endl;

    if(dot(Dx1,Dy1,x1-x3,y1-y3)<0&&dot(Dx1,Dy1,x2-x3,y2-y3)<0)return 1e18;
    if(dot(Dx2,Dy2,x4-x6,y4-y6)<0&&dot(Dx2,Dy2,x5-x6,y5-y6)<0)return 1e18;

    // if(check(x3,y3,x4,y4,x5,y5,x6,y6)||check(x6,y6,x1,y1,x2,y2,x3,y3))
    //     return 1e18;
    // if(sgn(dot(x3-(x1+x2)/2,y3-(y1+y2)/2,(x4+x5)/2-(x1+x2)/2,(y4+y5)/2-(y1+y2)/2)<0&&sgn(cross(x6-(x4+x5)/2,y6-(y4+y5)/2,(x1+x2)/2-(x4+x5)/2,(y1+y2)/2-(y4+y5)/2))))
        // return 1e18;
    long double ddx1,ddy1,ddx2,ddy2,fx1,fy1,fx2,fy2;
    long double mx1,mx2,my1,my2;
    mx1=(x1+x2)/2;mx2=(x4+x5)/2;
    my1=(y1+y2)/2;my2=(y4+y5)/2;
    fx1=x3-mx1;fx2=x6-mx2;
    fy1=y3-my1;fy2=y6-my2;
    ddx1=mx2-mx1;
    ddy1=my2-my1;
    ddx2=-ddx1;
    ddy2=-ddy1;
    if(0==sgn(cross(ddx1,ddy1,fx1,fy1))&&sgn(dot(ddx1,ddy1,fx1,fy1))>0)
        return 1e18;
    if(0==sgn(cross(ddx2,ddy2,fx2,fy2))&&sgn(dot(ddx2,ddy2,fx2,fy2))>0)
        return 1e18;
    if(sgn(cross(fx1,fy1,fx2,fy2))==0){
        if(sgn(dot(ddx1,ddy1,fx1,fy1))>0&&sgn(dot(ddx2,ddy2,fx2,fy2))>0)
            return 1e18;
    }else{
        if(sgn(cross(ddx1,ddy1,fx1,fy1))!=sgn(cross(fx2,fy2,fx1,fy1))&&sgn(cross(ddx2,ddy2,fx2,fy2))!=sgn(cross(fx1,fy1,fx2,fy2)))
            return 1e18;
    }
    // cout<<check(x3,y3,x4,y4,x5,y5,x6,y6)<<' '<<check(x6,y6,x1,y1,x2,y2,x3,y3)<<endl;
    // cout << i<<' '<<j<<' '<<x1<<' '<<y1<<' '<<x2<< ' '<<y2<<' '<<x3<<' '<<y3<<' '<<x4<<' '<<y4<<' '<<x5<<' '<<y5<<' '<<x6<<' '<<y6<<' '<<Dx1<<' '<<Dy1<< endl;
    // if(sgn(cross(Dx1,Dy1,x1-x3,y1-y3))!=sgn(cross(Dx1,Dy1,x2-x3,y2-y3))&&sgn(cross(Dx2,Dy2,x4-x6,y4-y6))!=sgn(cross(Dx2,Dy2,x5-x6,y5-y6)))

    if(dot(Dx1,Dy1,x1-x3,y1-y3)>0&&dot(Dx1,Dy1,x2-x3,y2-y3)>0&&dot(Dx2,Dy2,x4-x6,y4-y6)>0&&dot(Dx2,Dy2,x5-x6,y5-y6)>0&&sgn(cross(Dx1,Dy1,x1-x3,y1-y3))!=sgn(cross(Dx1,Dy1,x2-x3,y2-y3))&&sgn(cross(Dx2,Dy2,x4-x6,y4-y6))!=sgn(cross(Dx2,Dy2,x5-x6,y5-y6)))
        return sqrt(Dx1*Dx1+Dy1*Dy1);
    // cout << i<<' '<<j<<' '<<x1<<' '<<y1<<' '<<x2<< ' '<<y2<<' '<<x3<<' '<<y3<<' '<<x4<<' '<<y4<<' '<<x5<<' '<<y5<<' '<<x6<<' '<<y6<<' '<<Dx1<<' '<<Dy1<< endl;

    if(sgn(cross(Dx1,Dy1,x1-x3,y1-y3))==sgn(cross(Dx1,Dy1,x2-x3,y2-y3))&&sgn(cross(Dx2,Dy2,x4-x6,y4-y6))==sgn(cross(Dx2,Dy2,x5-x6,y5-y6))){
        // cout<<sqrt((x1-x4)*(x1-x4)+(y1-y4)*(y1-y4))+sqrt((x3-x1)*(x3-x1)+(y3-y1)*(y3-y1))+sqrt((x6-x4)*(x6-x4)+(y6-y4)*(y6-y4))<<endl;
        // cout<<sqrt((x2-x4)*(x2-x4)+(y2-y4)*(y2-y4))+sqrt((x3-x2)*(x3-x2)+(y3-y2)*(y3-y2))+sqrt((x6-x4)*(x6-x4)+(y6-y4)*(y6-y4))<<endl;
        // cout<<sqrt((x1-x5)*(x1-x5)+(y1-y5)*(y1-y5))+sqrt((x3-x1)*(x3-x1)+(y3-y1)*(y3-y1))+sqrt((x6-x5)*(x6-x5)+(y6-y5)*(y6-y5))<<endl;
        // cout<<sqrt((x2-x5)*(x2-x5)+(y2-y5)*(y2-y5))+sqrt((x3-x2)*(x3-x2)+(y3-y2)*(y3-y2))+sqrt((x6-x5)*(x6-x5)+(y6-y5)*(y6-y5))<<endl;

        // long double L=0,R=1,LM,RM,T;
        // while(R-L>eps){
        //     // printf("%.6Lf %.6Lf\n",L,R);
        //     LM=(L*2+R)/3;
        //     RM=(L+R*2)/3;
        //     long double Ld,Rd;
        //     Ld=calc(x3,y3,x6,y6,po(x1,y1,x2,y2,LM));
        //     Rd=calc(x3,y3,x6,y6,po(x1,y1,x2,y2,LM));
        //     if(Ld>Rd)L=LM;
        //     else R=RM;
        // }
        // cout<<"ABCABC\n"<<endl;
        // return min(calc(x3,y3,x6,y6,po(x1,y1,x2,y2,LM)),calc(x3,y3,x6,y6,po(x1,y1,x2,y2,RM)));
        return min(min(
                sqrt((x1-x4)*(x1-x4)+(y1-y4)*(y1-y4))+sqrt((x3-x1)*(x3-x1)+(y3-y1)*(y3-y1))+sqrt((x6-x4)*(x6-x4)+(y6-y4)*(y6-y4)),
                sqrt((x2-x4)*(x2-x4)+(y2-y4)*(y2-y4))+sqrt((x3-x2)*(x3-x2)+(y3-y2)*(y3-y2))+sqrt((x6-x4)*(x6-x4)+(y6-y4)*(y6-y4))
                ),min(
                sqrt((x1-x5)*(x1-x5)+(y1-y5)*(y1-y5))+sqrt((x3-x1)*(x3-x1)+(y3-y1)*(y3-y1))+sqrt((x6-x5)*(x6-x5)+(y6-y5)*(y6-y5)),
                sqrt((x2-x5)*(x2-x5)+(y2-y5)*(y2-y5))+sqrt((x3-x2)*(x3-x2)+(y3-y2)*(y3-y2))+sqrt((x6-x5)*(x6-x5)+(y6-y5)*(y6-y5))
                ));
    }
    // cout << i<<' '<<j<<' '<<x1<<' '<<y1<<' '<<x2<< ' '<<y2<<' '<<x3<<' '<<y3<<' '<<x4<<' '<<y4<<' '<<x5<<' '<<y5<<' '<<x6<<' '<<y6<<' '<<Dx1<<' '<<Dy1<< endl;

    if(sgn(cross(Dx1,Dy1,x1-x3,y1-y3))==sgn(cross(Dx1,Dy1,x2-x3,y2-y3))){
        swap(x1,x4);swap(y1,y4);
        swap(x2,x5);swap(y2,y5);
        swap(x3,x6);swap(y3,y6);
        swap(Dx1,Dx2);swap(Dy1,Dy2);
    }
    long double temp=1e18;
    if(sgn(cross(x4-x3,y4-y3,x1-x3,y1-y3))==sgn(cross(x4-x3,y4-y3,x2-x3,y2-y3))||dot(x4-x3,y4-y3,x1-x3,y1-y3)<0||dot(x4-x3,y4-y3,x2-x3,y2-y3)<0){
        temp=min(temp,min(
                sqrt((x1-x4)*(x1-x4)+(y1-y4)*(y1-y4))+sqrt((x3-x1)*(x3-x1)+(y3-y1)*(y3-y1))+sqrt((x6-x4)*(x6-x4)+(y6-y4)*(y6-y4)),
                sqrt((x2-x4)*(x2-x4)+(y2-y4)*(y2-y4))+sqrt((x3-x2)*(x3-x2)+(y3-y2)*(y3-y2))+sqrt((x6-x4)*(x6-x4)+(y6-y4)*(y6-y4))
        ));
        // cout<<"ABC "<<temp<<'\n';
    }else{
        temp=min(temp,sqrt((x6-x4)*(x6-x4)+(y6-y4)*(y6-y4))+sqrt((x3-x4)*(x3-x4)+(y3-y4)*(y3-y4)));
        // cout<<"DEF "<<temp<<' '<<sqrt((x6-x4)*(x6-x4)+(y6-y4)*(y6-y4))<<' '<<sqrt((x3-x4)*(x3-x4)+(y3-y4)*(y3-y4))<<'\n';
    }
    if(sgn(cross(x5-x3,y5-y3,x1-x3,y1-y3))==sgn(cross(x5-x3,y5-y3,x2-x3,y2-y3))||dot(x5-x3,y5-y3,x1-x3,y1-y3)<0||dot(x5-x3,y5-y3,x2-x3,y2-y3)<0){
        temp=min(temp,min(
                sqrt((x1-x5)*(x1-x5)+(y1-y5)*(y1-y5))+sqrt((x3-x1)*(x3-x1)+(y3-y1)*(y3-y1))+sqrt((x6-x5)*(x6-x5)+(y6-y5)*(y6-y5)),
                sqrt((x2-x5)*(x2-x5)+(y2-y5)*(y2-y5))+sqrt((x3-x2)*(x3-x2)+(y3-y2)*(y3-y2))+sqrt((x6-x5)*(x6-x5)+(y6-y5)*(y6-y5))
                ));
        // cout<<"GHI "<<temp<<endl;
    }else{
        temp=min(temp,sqrt((x6-x5)*(x6-x5)+(y6-y5)*(y6-y5))+sqrt((x3-x5)*(x3-x5)+(y3-y5)*(y3-y5)));
        // cout<<"JKL "<<temp<<endl;
    }
    // cout << i<<' '<<j<<' '<<x1<<' '<<y1<<' '<<x2<< ' '<<y2<<' '<<x3<<' '<<y3<<' '<<x4<<' '<<y4<<' '<<x5<<' '<<y5<<' '<<x6<<' '<<y6<<' '<<Dx1<<' '<<Dy1<< endl;

    return temp;
}
int main()
{
    // cout<<check(1,1,0,0,0,10,10,0)<<endl;
    cin>>X1>>Y1>>X2>>Y2>>H1;
    cin>>X3>>Y3>>X4>>Y4>>H2;
    dx1=X2-X1;dx2=X4-X3;
    dy1=Y2-Y1;dy2=Y4-Y3;
    len1=sqrt(dx1*dx1+dy1*dy1);
    len2=sqrt(dx2*dx2+dy2*dy2);
    h1=sqrt(len1*len1/4+H1*H1);
    h2=sqrt(len2*len2/4+H2*H2);
    // cout<<calc(1,2)<<endl;return 0;
    for(int i=1;i<=4;i++)
    for(int j=1;j<=4;j++){
        long double temp=calc(i,j);
        ans=min(ans,temp);
        // printf("%d %d %.10Lf\n",i,j,temp);
        // cout<<i<<' '<<j<<' '<<temp<<'\n';
    }
        
    printf("%.10Lf\n",ans);
}
/*
-25 -50 0 -34 73
-90 -83 -46 -95 83
172.3647737981


174084.670254182

0 0 100 100 20
23 23 18 18 2


0 0 10 0 4
9 18 34 26 42

60.866649532


0 0 0 1 0.9
0 1 0 0 0.9
*/