#include<bits/stdc++.h>
using namespace std;
int n,q,a[150010],cnt,ans[100010],c[150010];
vector<int>V[1000010];
int last[150010],num;
bool ks;
struct Li
{int x,z,next;}li[240*160010+1000000];
struct SYZ
{int x,y,z;}syz[240*160010+1000000];
bool js;
inline int read()
{
    int x=0;char ch=0,w=0;
    while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return w?-x:x;
}
void solve(int g)
{
    if(V[g].size()<3)return;
    for(int i=1,End=V[g].size();i<End;i++){
        int x=V[g][i-1],y=V[g][i],z=y*2-x;
        z=lower_bound(V[g].begin(),V[g].end(),z)-V[g].begin();
        if(z<End)
            syz[++cnt]=(SYZ){x,V[g][z],g};
    }
}
bool cmp(SYZ n1,SYZ n2)
{return n1.y<n2.y||(n2.y==n1.y&&n1.z>0);}
int ask(int x,int y=0)
{
    x=n-x+1;
    for(;x;x-=x&-x)
        y=max(y,c[x]);
    return y;
}
void change(int x,int y)
{
    x=n-x+1;
    for(;x<=n;x+=x&-x)
        c[x]=max(c[x],y);
}
void add(int Y,int X,int Z)
{
    li[++num]=(Li){X,Z,last[Y]};last[Y]=num;
}
void mysort()
{
    for(int i=1;i<=cnt;i++)
    if(syz[i].z<=0)
        add(syz[i].y,syz[i].x,syz[i].z);
    for(int i=1;i<=cnt;i++)
    if(syz[i].z>0)
        add(syz[i].y,syz[i].x,syz[i].z);
    cnt=0;
    for(int y=1;y<=n;y++)
    for(int i=last[y];i;i=li[i].next)
        syz[++cnt]=(SYZ){li[i].x,y,li[i].z};
}
int main()
{
    n=read();q=read();
    // cout<<(&js-&ks)/1024./1024<<endl;
    // n=150000;q=100000;
    bool flag=1;
    for(int i=1;i<=n;i++){
        // a[i]=rand()%1000000+1;                                Zzz
        for(int j=1;j*j<=a[i];j++)
        if(a[i]%j==0){
            V[j].emplace_back(i);
            if(j*j!=a[i])
                V[a[i]/j].emplace_back(i);
        }
    }
    // cout<<clock()<<endl;
    if(!flag)
    for(int i=1000000;i;i--)
        solve(i);
    // cout<<clock()<<endl;
    for(int i=1;i<=q;i++){
        // int l=1,r=n;
        int l=read(),r=read();
        syz[++cnt]=(SYZ){l,r,-i};
    }
    if(flag){
        for(int i=1;i<=cnt;i++){
            if(syz[i].y-syz[i].x>1)
                printf("%d\n",a[1]);
            else printf("0\n");
        }
        return 0;
    }
    mysort();
    // for(int i=1;i<=cnt;i++)
        // cout<<syz[i].x<<' '<<syz[i].y<<' '<<syz[i].z<<endl;
    // cout<<clock()<<endl;
    for(int i=1;i<=cnt;i++)
    if(syz[i].z<0){
        ans[-syz[i].z]=ask(syz[i].x);
    }else change(syz[i].x,syz[i].z);
    // cout<<clock()<<endl;
    // cout<<"ABCDE\n";
    // return 0;
    for(int i=1;i<=q;i++)
        printf("%d\n",ans[i]);
}
/*
8 8
8 24 4 6 6 7 3 3
1 5
2 6
3 7
5 8
4 8
1 3
2 5
3 8


*/
