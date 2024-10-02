#include<bits/stdc++.h>
using namespace std;
int A,B,C,D;
int main()
{
    cin>>A>>B>>C>>D;
    for(int i=0;i<=1000000;i++){
        long double maxx=0,minx=0,maxy=0,miny=0,alpha=3.1415926535897*i/2000000,xx,yy;
        int x=C,y=0;
        xx=x*cos(alpha)-y*sin(alpha);
        yy=x*sin(alpha)+y*cos(alpha);
        maxx=max(maxx,xx);
        minx=min(minx,xx);
        maxy=max(maxy,yy);
        miny=min(miny,yy);
        x=C,y=D;
        xx=x*cos(alpha)-y*sin(alpha);
        yy=x*sin(alpha)+y*cos(alpha);
        maxx=max(maxx,xx);
        minx=min(minx,xx);
        maxy=max(maxy,yy);
        miny=min(miny,yy);
        x=0;y=D;
        xx=x*cos(alpha)-y*sin(alpha);
        yy=x*sin(alpha)+y*cos(alpha);
        maxx=max(maxx,xx);
        minx=min(minx,xx);
        maxy=max(maxy,yy);
        miny=min(miny,yy);
        if(maxx-minx<=A&&maxy-miny<=B)
            return printf("YES\n"),0;
    }
    cout<<"NO\n";
}