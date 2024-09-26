#include<bits/stdc++.h>
#define LL long long
using namespace std;
int n,top,ans;
map<pair<int,int>,int>mp,pos;
struct VEC
{
    LL x,y;
    VEC operator-(const VEC&n2){
        return(VEC){x-n2.x,y-n2.y};
    }
    bool operator==(const VEC&n2){
        return x==n2.x&&y==n2.y;
    }
}p[2010],st[2010],p2[2010],P;
LL cross(VEC n1,VEC n2)
{return n1.x*n2.y-n2.x*n1.y;}
LL sgn(LL x)
{
    if(x==0)return 0;
    if(x>0)return 1;
    return -1;
}
bool cmp(VEC n1,VEC n2)
{
    if(n1==P)return 1;
    if(n2==P)return 0;
    if(sgn(cross(P-p[1],n1-p[1]))!=sgn(cross(P-p[1],n2-p[1]))){
        return cross(P-p[1],n1-p[1])>0;
    }
    return cross(n1-p[1],n2-p[1])>0;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>p[i].x>>p[i].y;
        if(p[i].y<p[1].y)
            swap(p[1],p[i]);
    }
    P=p[1];
    sort(p+2,p+n+1,cmp);
    st[top=1]=p[1];
    for(int i=2;i<=n;i++){
        while(top>1&&cross(st[top]-st[top-1],p[i]-st[top])<=0)top--;
        st[++top]=p[i];
    }
    st[top+1]=p[1];
    for(int i=1;i<=top;i++){
        mp[{st[i].x,st[i].y}]=1;
        // cout<<i<<','<<st[i].x<<','<<st[i].y<<'\n';
    }
        
    memcpy(p2,p,sizeof p2);
    // cout<<top<<'\n';
    for(int i=1;i<=n;i++){
        if(mp.count({p2[i].x,p2[i].y}))continue;
        memcpy(p,p2,sizeof p);
        swap(p[1],p[i]);
        P=p[2];
        sort(p+2,p+n+1,cmp);
        for(int j=1;j<=n;j++)
            pos[{p[j].x,p[j].y}]=j;
        // cout<<p[1].x<<' '<<p[1].y<<'\n';
        // for(int j=1;j<=n;j++)
        //     cout<<p[j].x<<','<<p[j].y<<'\n';
        for(int j=1;j<=top;j++){
            // cout<<j<<','<<pos[{st[j].x,st[j].y}]<<' '<<pos[{st[j+1].x,st[j+1].y}]<<'\n';
            if(abs(pos[{st[j].x,st[j].y}]-pos[{st[j+1].x,st[j+1].y}])==1||n-2==abs(pos[{st[j].x,st[j].y}]-pos[{st[j+1].x,st[j+1].y}])){
                ans++;
                // cout<<st[j].x<<' '<<st[j].y<<' '<<st[j+1].x<<' '<<st[j+1].y<<'\n';
            }
        }
        // cout<<ans<<'\n';
    }
    cout<<ans+1<<'\n';
}
/*
5
4 0
0 0
2 1
3 3
3 1
*//*
7
1 4
4 0
2 3
3 1
3 5
0 0
2 4

9
*/