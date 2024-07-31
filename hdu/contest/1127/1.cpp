#include<bits/stdc++.h>
#define LD long double
using namespace std;
const LD eps=1e-12;
int N,n,cnt,XX[20],YY[20],ZZ[20],vis[20];
bool g[4010][4010];
LD rand_eps()
{return ((LD)rand()/RAND_MAX-0.5)*eps;}
struct VER
{
    LD x,y,z;
    VER(LD X=0,LD Y=0,LD Z=0){
        x=X;y=Y;z=Z;
    }
    void shake(){
        x+=rand_eps();
        y+=rand_eps();
        z+=rand_eps();
    }
    VER operator+(const VER&n2){return (VER){x+n2.x,y+n2.y,z+n2.z};}
    VER operator-(const VER&n2){return (VER){x-n2.x,y-n2.y,z-n2.z};}
    VER operator*(const VER&n2){
        return(VER){y*n2.z-z*n2.y,z*n2.x-x*n2.z,x*n2.y-y*n2.x};
    }
    LD operator^(const VER&n2){
        return x*n2.x+y*n2.y+z*n2.z;
    }
    LD len(){return sqrt(x*x+y*y+z*z);}
}p[2010];
int sgn(LD VAL)
{
    if(-eps<VAL&&VAL<eps)return 0;
    if(eps<=VAL)return 1;
    return -1;
}
VER cross(VER n1,VER n2)
{return(VER){n1.y*n2.z-n2.y*n1.z,n1.z*n2.x-n2.z*n1.x,n1.x*n2.y-n2.x*n1.y};}
LD dot(VER n1,VER n2)
{return n1.x*n2.x+n1.y*n2.y+n1.z*n2.z;}
struct PLANE
{
    int n1,n2,n3;
    VER norm(){return cross(p[n1]-p[n2],p[n1]-p[n3]);}
    LD area(){return norm().len()/2;}
    bool above(VER n4){return dot(n4-p[n1],norm())>=0;}
}plane[4010],np[4010];
inline int read()
{
    int x=0,w=0;char ch=0;
    while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return w?-x:x;
}
int check(int sTaTe)
{
    if(!sTaTe)return 0;
    n=0;cnt=0;
    for(int i=1;i<=N;i++)
    if(sTaTe>>(i-1)&1){
        n++;
        p[n].x=XX[i];
        p[n].y=YY[i];
        p[n].z=ZZ[i];
    }
    if(n==1)
        return 1;
    for(int i=1;i<=n;i++)
        p[i].shake();
    plane[++cnt]=(PLANE){1,2,3};
    plane[++cnt]=(PLANE){3,2,1};
    for(int i=4;i<=n;i++){
        int temp=0;
        for(int j=1;j<=cnt;j++){
            bool t=plane[j].above(p[i]);
            if(!t)np[++temp]=plane[j];
            g[plane[j].n1][plane[j].n2]=t;
            g[plane[j].n2][plane[j].n3]=t;
            g[plane[j].n3][plane[j].n1]=t;
        }
        for(int j=1;j<=cnt;j++){
            int a=plane[j].n1,b=plane[j].n2;
            if(g[a][b]&&!g[b][a])
                np[++temp]=(PLANE){a,b,i};
            a=plane[j].n2,b=plane[j].n3;
            if(g[a][b]&&!g[b][a])
                np[++temp]=(PLANE){a,b,i};
            a=plane[j].n3,b=plane[j].n1;
            if(g[a][b]&&!g[b][a])
                np[++temp]=(PLANE){a,b,i};
        }
        cnt=temp;
        memcpy(plane,np,sizeof(PLANE)*(cnt+3));
        
    }
    memset(vis,0,sizeof vis);
    for(int i=1;i<=cnt;i++){
        vis[plane[i].n1]=1;
        vis[plane[i].n2]=1;
        vis[plane[i].n3]=1;
    }
    LD SUMX=0,SUMY=0,SUMZ=0;
    for(int i=1;i<=n;i++){
        SUMX+=p[i].x;
        SUMY+=p[i].y;
        SUMZ+=p[i].z;
    }
    SUMX/=n;SUMY/=n;SUMZ/=n;
    VER ZHIXIN(SUMX,SUMY,SUMZ);
    bool XIAN=1;
    for(int i=3;i<=n;i++)
    if((p[i].x-p[1].x)*(p[i].x-p[2].x)+(p[i].y-p[1].y)*(p[i].y-p[2].y)+(p[i].z-p[1].z)*(p[i].z-p[2].z))
        XIAN=0;
    if(XIAN){
        LD MAXX,MAXY,MAXZ,MINX,MINY,MINZ;
        MAXX=MINX=p[1].x;
        MAXY=MINY=p[1].y;
        MAXZ=MINZ=p[1].z;
        for(int i=1;i<=n;i++){
            MAXX=max(MAXX,p[i].x);
            MAXY=max(MAXY,p[i].y);
            MAXZ=max(MAXZ,p[i].z);
            MINY=min(MINY,p[i].y);
            MINX=min(MINX,p[i].x);
            MINY=min(MINY,p[i].y);
        }
        for(int i=1;i<=N;i++)
        if(sTaTe>>(i-1)&1){

        }else{
            if((XX[i]-p[1].x)*(XX[i]-p[2].x)+(YY[i]-p[1].y)*(YY[i]-p[2].y)+(ZZ[i]-p[1].z)*(ZZ[i]-p[2].z)){

            }else{
                if(MINX<=XX[i]&&XX[i]<=MAXX&&MINY<=YY[i]&&YY[i]<=MAXY&&MINZ<=ZZ[i]&&ZZ[i]<=MAXZ)
                    return 0;
            }
        }
        return 1;
    }
    int MIAN=1;
    for(int i=1;i<=n;i++){

    }
    for(int i=1;i<=N;i++)
    if(sTaTe>>(i-1)&1){
    }else{
        for(int j=1;j<=cnt;j++){
            VER v1=p[plane[j].n1]-p[plane[j].n3];
            VER v2=p[plane[j].n2]-p[plane[j].n3];
            VER vv1=ZHIXIN-p[plane[j].n3];
            VER pp2(XX[i],YY[i],ZZ[i]);
            VER vv2=pp2-p[plane[j].n3];
            if(sgn((v1*v2)^vv1)==sgn((v1*v2)^vv2))
                continue;
            v1=ZHIXIN-p[plane[j].n1];
            v2=pp2-p[plane[j].n1];
            vv1=p[plane[j].n2]-p[plane[j].n1];
            vv2=p[plane[j].n3]-p[plane[j].n1];
            if(sgn((v1*v2)^vv1)==sgn((v1*v2)^vv2))
                continue;
            v1=ZHIXIN-p[plane[j].n2];
            v2=pp2-p[plane[j].n2];
            vv1=p[plane[j].n1]-p[plane[j].n2];
            vv2=p[plane[j].n3]-p[plane[j].n2];
            if(sgn((v1*v2)^vv1)==sgn((v1*v2)^vv2))
                continue;
            v1=ZHIXIN-p[plane[j].n3];
            v2=pp2-p[plane[j].n3];
            vv1=p[plane[j].n2]-p[plane[j].n3];
            vv2=p[plane[j].n1]-p[plane[j].n3];
            if(sgn((v1*v2)^vv1)==sgn((v1*v2)^vv2))
                continue;
            
            return 0;
        }
    }
    return 1;
}
int main()
{
    int T=read();
    while(T --> 0){
        N=read();
        for(int i=1;i<=N;i++)
            XX[i]=read(),YY[i]=read(),ZZ[i]=read();
        int ans=0;
        for(int i=0;i<=(1<<N);i++)
            ans+=check(i);
        cout<<ans<<'\n';
    }
}