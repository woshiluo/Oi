#include<bits/stdc++.h>
#define LL long long
using namespace std;
int n,m,ttop,top,vis[100010],id[100010];
long long ans=0;
struct POINT
{
    LL x,y;
    POINT operator+(const POINT&n2){return(POINT){x+n2.x,y+n2.y};}
    POINT operator-(const POINT&n2){return(POINT){x-n2.x,y-n2.y};}
    LL operator*(const POINT&n2){return x*n2.x+y*n2.y;}
    LL operator^(const POINT&n2){return x*n2.y-y*n2.x;}
}p[100010],st[100010],pp[100010],sst[100010];
inline int read()
{
    int x=0,w=0;char ch=0;
    while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return w?-x:x;
}
bool cmp(POINT n1,POINT n2)
{
    LL temp=(n1-p[1])^(n2-p[1]);
    return temp>0;
}
bool cmp2(POINT n1,POINT n2)
{
    LL temp=(n1-pp[1])^(n2-pp[1]);
    return temp>0;
}
int main()
{
    int T=read();
    while(T --> 0){
        n=read();m=0;ans=0;
        for(int i=1;i<=n;i++){
            vis[i]=0;id[i]=0;
            p[i].x=read();
            p[i].y=read();
            if(p[i].y<p[1].y||p[i].y==p[1].y&&p[i].x>p[1].x)
                swap(p[1],p[i]);
        }
        sort(p+2,p+n+1,cmp);
        st[top=1]=p[1];
        id[1]=1;
        for(int i=2;i<=n;i++){
            while(top>1&&((st[top]-st[top-1])^(p[i]-st[top]))<0)
                vis[id[top--]]=1;
            st[++top]=p[i];
            id[top]=i;
        }
        st[++top]=p[1];
        for(int i=1;i<=top;i++)
            ans+=st[i]^st[i+1];
        for(int i=1;i<=n;i++)
        if(vis[i]){
            // cout<<p[i].x<<','<<p[i].y<<endl;
            pp[++m]=p[i];
        }
        if(!m){
            printf("-1\n");
            continue;
        }
        for(int i=1;i<=m;i++){
            if(pp[i].y<pp[1].y||pp[i].y==pp[1].y&&pp[i].x>pp[1].x)
                swap(pp[1],pp[i]);
        }
        sort(pp+2,pp+m+1,cmp2);
        sst[ttop=1]=pp[1];
        for(int i=2;i<=m;i++){
            while(ttop>1&&((sst[ttop]-sst[ttop-1])^(pp[i]-sst[ttop]))<0)
                vis[id[ttop--]]=1;
            sst[++ttop]=pp[i];
            id[ttop]=i;
        }
        sst[++ttop]=pp[1];

        // for(int i=1;i<=top;i++)
        //     cout<<st[i].x<<' '<<st[i].y<<endl;
        // cout<<endl;
        // for(int i=1;i<=ttop;i++)
        //     cout<<sst[i].x<<' '<<sst[i].y<<endl;
        long long sum=ans;
        int ptr=1,nxt=2%(ttop-1)+1;
        for(int i=1;i<=(ttop-1);i++){
            if(abs((st[1]-sst[i])^(st[2]-sst[i]))<abs((st[1]-sst[ptr])^(st[2]-sst[ptr])))
                ptr=i;
        }
        ans=-1e9;
        nxt=(ptr)%(ttop-1)+1;
        for(int i=1;i<=top;i++){
            while(abs((st[i]-sst[nxt])^(st[i+1]-sst[nxt]))<abs((st[i]-sst[ptr])^(st[i+1]-sst[ptr]))){
                ptr=nxt;
                nxt=nxt%(ttop-1)+1;
            }
            // cout<<sum<<' '<<i<<' '<<n<<' '<<m<<' '<<ptr<<endl;
            // cout<<sum<<' '<<((st[i]-sst[ptr])^(st[i+1]-sst[ptr]))<<endl;
            // if(((st[i]-sst[ptr])^(st[i+1]-sst[ptr]))>0)
            // assert(((st[i]-sst[ptr])^(st[i+1]-sst[ptr])));
            ans=max(ans,sum-abs((st[i]-sst[ptr])^(st[i+1]-sst[ptr])));
        }
        cout<<ans<<endl;
    }
}
/*
1
6
-2 0
1 -2
5 2
0 4
1 2
3 1

*/



/*
2
6
-2 0
1 -2
5 2
0 4
1 2
3 1
4
0 0
1 0
0 1
1 1

*/