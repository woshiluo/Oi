#include <bits/stdc++.h>
using namespace std;
const long double eps=1e-13;
int n,m,top,cnt,askx[210],asky[210],askc,allc,dead[410];
long double dis[410][410];
struct VEC
{
    long double x,y;
    VEC operator-(const VEC p1){return{x-p1.x,y-p1.y};}
    VEC operator*(const long double t){return{x*t,y*t};}
    VEC operator+(const VEC p1){return{x+p1.x,y+p1.y};}
    VEC turn90(){return {-y,x};}
    VEC turn(long double alpha){return{x*cos(alpha)-y*sin(alpha),x*sin(alpha)+y*cos(alpha)};}
    long double len(){return sqrt(x*x+y*y);}
}p[210],st[210],ZX,sheep[210],e,allnode[410];
struct LINE
{VEC st,ed;};
struct CIRCLE
{VEC O;long double R;}ans;
int sgn(long double x)
{
    if(fabs(x)<eps)return 0;
    if(x>0)return 1;
    return -1;
}
long double cross(VEC n1,VEC n2)
{return n1.x*n2.y-n2.x*n1.y;}
long double dot(VEC n1,VEC n2)
{return n1.x*n2.x+n1.y*n2.y;}
int cmp(VEC n1,VEC n2)
{
    double temp=cross(n1-p[1],n2-p[1]);
    return sgn(temp)>0||(sgn(temp)==0&&(n1-p[1]).len()>(n2-p[1]).len());
}
int on_segment(VEC p,VEC n1,VEC n2)
{
    return sgn(cross(p-n1,p-n2))==0&&sgn(dot(p-n1,p-n2))<=0;
}
VEC get_intersection(VEC n1,VEC n2,VEC n3,VEC n4)
{
    VEC v1=n2-n1,v2=n4-n3,v3=n1-n3;
    long double t=cross(v2,v3)/cross(v1,v2);
    return n1+v1*t;
}
bool seg_intersection(VEC n1,VEC n2,VEC n3,VEC n4)
{
    long double c1=cross(n2-n1,n4-n1),c2=cross(n2-n1,n3-n1);
    long double c3=cross(n4-n3,n1-n3),c4=cross(n4-n3,n2-n3);
    return sgn(c1)*sgn(c2)<=0&&sgn(c3)*sgn(c4)<=0;
}
LINE get_line(VEC n1,VEC n2)
{return {(n1+n2)*0.5,(n1+n2)*0.5+(n1-n2).turn90()};}
CIRCLE get_circle(VEC n1,VEC n2,VEC n3)
{
    LINE l1=get_line(n1,n2),l2=get_line(n2,n3);
    VEC n4=get_intersection(l1.st,l1.ed,l2.st,l2.ed);
    return {n4,(n1-n4).len()};
}
int main()
{
    cin>>n;e={1,0};
    for(int i=1;i<=n;i++){
        long double x,y;
        cin>>x>>y;
        p[i]={x,y};
    }
    p[n+1]=p[1];
    ans={p[1],0};
    for(int i=2;i<=n;i++){
    if(sgn(ans.R-(ans.O-p[i]).len())<0){
        ans={p[i],0};
        for(int j=1;j<i;j++)
        if(sgn(ans.R-(ans.O-p[j]).len())<0){
            ans={(p[i]+p[j])*0.5,(p[i]-p[j]).len()/2};
            for(int k=1;k<j;k++)
            if(sgn(ans.R-(ans.O-p[k]).len())<0)
                ans=get_circle(p[i],p[j],p[k]);
        }
        //cout<<i<<' '<<ans.O.x<<','<<ans.O.y<<','<<ans.R<<'\n';
    }
    }
    // cout<<ans.O.x<<','<<ans.O.y<<','<<ans.R<<'\n';
    cin>>m;
    for(int i=1;i<=m;i++){
        int opt;
        cin>>opt;
        if(opt==1){
            int flag=0;cnt++;
            cin>>sheep[cnt].x>>sheep[cnt].y;
            if(sgn(ans.R-(sheep[cnt]-ans.O).len())<0)dead[n+cnt]=1;
            else{
                int tot=0;
                for(int du=0;du<360;du++){
                    VEC PO=sheep[cnt]+e.turn(3.141592653589*du/180)*2*ans.R;
                    tot=0;
                    for(int j=1;j<=n;j++)
                    if(seg_intersection(p[j],p[j+1],PO,sheep[cnt])&&on_segment(get_intersection(p[j],p[j+1],PO,sheep[cnt]),p[j],p[j+1]))
                        tot++;
                    if(tot%2==0)flag=1;
                }
                if(flag)dead[n+cnt]=1;
            }
        }else{
            askc++;
            cin>>askx[askc]>>asky[askc];
        }
    }
    // for(int i=1;i<=cnt;i++)
    //     cout<<sheep[i].x<<','<<sheep[i].y<<endl;
    allc=n;
    for(int i=1;i<=n;i++)allnode[i]=p[i];
    for(int i=1;i<=cnt;i++)
        allnode[++allc]=sheep[i];
    for(int x=1;x<=allc;x++)
    for(int y=1;y<=allc;y++)
    if(x==y)dis[x][y]=0;
    else{
        dis[x][y]=1e18;
        if(dead[x]||dead[y])continue;
        bool flag=0;
        for(int z=1;z<=n;z++)
        if(seg_intersection(p[z],p[z+1],allnode[x],allnode[y])&&on_segment(get_intersection(p[z],p[z+1],allnode[x],allnode[y]),p[z],p[z+1])){
            if(z==x||z==y||z==x-1||z==y-1||(z==n&&x==1)||(z==n&&y==1)){

            }else flag=1;
        }
        if(!flag)dis[x][y]=(allnode[x]-allnode[y]).len();
    }
    for(int z=1;z<=allc;z++)
    if(!dead[z])
    for(int x=1;x<=allc;x++)
    if(!dead[x])
    for(int y=1;y<=allc;y++)
    if(!dead[y])
        dis[x][y]=min(dis[x][y],dis[x][z]+dis[z][y]);
    for(int i=1;i<=askc;i++)
        printf("%.5Lf\n",dis[n+askx[i]][n+asky[i]]);
    return 0;
}