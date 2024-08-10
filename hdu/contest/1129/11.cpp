#include<bits/stdc++.h>
#define Graph(x)for(int i=last[x],y=edge[i].ver;i;i=edge[i].next,y=edge[i].ver)
#define LL long long
const int mod=998244353;
using namespace std;
int n,last[100010],num,du[100010],flag,sIze[100010];
int dfn[100010],low[100010],dfs_clock,vis[200010],vishuan[200010];
int f[100010],f2[100010],g[100010],ans[100010];
int huan[100010],firsth,dep[100010],Max[100010],md[100010];
multiset<int>ADD[200010],DEL[200010],S;
struct EDGE
{int ver,next;}edge[200010];
struct SegmentTree
{int l,r,data,pos;}st[800010];
inline int read()
{
    int x=0,w=0;char ch=0;
    while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return w?-x:x;
}
void build(int p,int l,int r)
{
    st[p].l=l;st[p].r=r;
    if(l==r)
        return st[p].data=Max[l]+l,st[p].pos=l,void();
    int mid=(l+r)>>1;
    build(p<<1,l,mid);
    build(p<<1|1,mid+1,r);
    if(st[p<<1|1].data>=st[p<<1].data)
        st[p].data=st[p<<1|1].data,st[p].pos=st[p<<1|1].pos;
    else st[p].data=st[p<<1].data,st[p].pos=st[p<<1].pos;
}
pair<int,int>ask(int p,int l,int r)
{
    if(l<=st[p].l&&st[p].r<=r)
        return {st[p].data,st[p].pos};
    int mid=(st[p].l+st[p].r)>>1;
    if(r<=mid)return ask(p<<1,l,r);
    if(mid<l)return ask(p<<1|1,l,r);
    pair<int,int>LT=ask(p<<1,l,r),RT=ask(p<<1|1,l,r),TT;
    if(RT.first>=LT.first)
        TT.first=RT.first,TT.second=RT.second;
    else TT.first=LT.first,TT.second=LT.second;
    return TT;
}
void add(int X,int Y)
{edge[++num]=(EDGE){Y,last[X]};last[X]=num;}
void tarjan(int x,int in_edge)
{
    dfn[x]=low[x]=++dfs_clock;
    Graph(x)if(i^in_edge^1){
        if(!dfn[y]){
            tarjan(y,i);
            low[x]=min(low[x],low[y]);
            if(low[y]>dfn[x])
                vis[i]=vis[i^1]=1;
        }else low[x]=min(low[x],dfn[y]);
    }
}
void dfs(int x,int F)
{
    f[x]=0;ans[x]=1;f2[x]=-1e9;
    Graph(x){
        if(y==F||vishuan[y])continue;
        dep[y]=dep[x]+1;
        dfs(y,x);
        ans[x]=max(ans[x],f[x]+f[y]+2);
        if(f[x]<f[y]+1){
            f2[x]=f[x];
            f[x]=f[y]+1;
        }else f2[x]=max(f2[x],f[y]+1);
    }
    Graph(x){
        if(y==F||vishuan[y])continue;
        dep[x]=max(dep[x],dep[y]);
    }
}
void dp(int x,int F,int Len)
{
    ans[x]=max(ans[x],f[x]+Len+1);
    Graph(x){
        if(y==F||vishuan[y])continue;
        if(f[x]!=f[y]+1){
            dp(y,x,max(f[x],Len)+1);
        }else dp(y,x,max(f2[x],Len)+1);
    }
}
void dfsh(int x,int F)
{
    huan[++huan[0]]=x;
    Graph(x){
        if(y==F||!vishuan[y]||y==firsth)continue;
        dfsh(y,x);
        break;
    }
}
void calc(int x,int F,int MD)
{
    // cout<<"<"<<x<<','<<dep[x]<<">\n";
    ans[x]=max(ans[x],dep[x]+MD);
    Graph(x){
        if(y==F||vishuan[y])continue;
        calc(y,x,MD);
    }
}
int main()
{
    int T=read();
    while(T --> 0){
        n=read();num=1;dfs_clock=0;
        memset(ans,0,sizeof(int)*(n+5));
        memset(md,0,sizeof(int)*(n+5));
        memset(dfn,0,sizeof(int)*(n+5));
        memset(last,0,sizeof(int)*(n+5));
        memset(vis,0,sizeof(int)*(n+n+5));
        memset(vishuan,0,sizeof(int)*(n+5));
        for(int i=1;i<=n;i++){
            int x=read(),y=read();
            add(x,y);add(y,x);
        }
        tarjan(1,0);//zhao huan
        for(int i=1;i<=n;i++)
        if(!vis[i<<1]){
            vishuan[edge[i<<1].ver]=1;
            vishuan[edge[i<<1|1].ver]=1;
        }
        for(int x=1;x<=n;x++)
        if(vishuan[x])//dp
            dfs(x,dep[x]=0),dp(x,0,-1e9);
        for(int i=1;i<=n;i++)ans[i]--;
        for(int x=1;x<=n;x++)// zhao huan
        if(vishuan[x]){
            firsth=x;huan[0]=0;
            dfsh(x,0);
            break;
        }
        for(int i=1;i<=huan[0];i++)//duan kai,fu zhi yi bei
            huan[huan[0]+i]=huan[i];
        huan[0]*=2;
        for(int i=1;i<=huan[0];i++)
            Max[i]=dep[huan[i]];
        // for(int i=1;i<=n;i++)
        //     printf("%d%c",ans[i]," \n"[i==n]);
        build(1,1,huan[0]);
        S.clear();
        for(int i=1;i<=huan[0];i++)ADD[i].clear(),DEL[i].clear();
        for(int i=1;i<=huan[0]/2;i++){
            pair<int,int>p=ask(1,i+1,i+huan[0]/2-1);
            int temp=p.first,pos=p.second;
            int ttemp=temp-i+dep[huan[i]];
            ADD[i].insert(-ttemp);
            DEL[pos+1].insert(-ttemp);
            md[huan[i]]=max(md[huan[i]],temp-i);
        }
        for(int i=1;i<=huan[0];i++){
            for(int x:ADD[i])S.insert(x);
            for(int x:DEL[i])S.erase(S.find(x));
            if(S.size())
                ans[huan[i]]=max(ans[huan[i]],-*S.begin());
            // cout<<i<<":\n";
            // for(int x:S)cout<<x<<' ';
            // cout<<endl;
        }
        // for(int i=1;i<=huan[0];i++){
        //     cout<<i<<":";
        //     for(int x:ADD[i])cout<<x<<' ';
        //     cout<<endl;
        //     for(int x:DEL[i])cout<<x<<' ';
        //     cout<<endl;
        // }
        // for(int i=1;i<=n;i++)
        //     printf("%d%c",ans[i]," \n"[i==n]);
        reverse(huan+1,huan+1+huan[0]);
        reverse(Max+1,Max+1+huan[0]);
        build(1,1,huan[0]);
        S.clear();
        for(int i=1;i<=huan[0];i++)ADD[i].clear(),DEL[i].clear();
        for(int i=1;i<=huan[0]/2;i++){
            pair<int,int>p=ask(1,i+1,i+huan[0]/2-1);
            int temp=p.first,pos=p.second;
            int ttemp=temp-i+dep[huan[i]];
            ADD[i].insert(-ttemp);
            DEL[pos+1].insert(-ttemp);
            md[huan[i]]=max(md[huan[i]],temp-i);
        }
        for(int i=1;i<=huan[0];i++){
            for(int x:ADD[i])S.insert(x);
            for(int x:DEL[i])S.erase(S.find(x));
            if(S.size())
                ans[huan[i]]=max(ans[huan[i]],-*S.begin());
        }
        // for(int i=1;i<=huan[0]/2;i++)
        //     cout<<huan[i]<<' '<<md[huan[i]]<<",\n"[i==huan[0]/2];
        for(int i=1;i<=huan[0]/2;i++)
            calc(huan[i],0,md[huan[i]]);
        for(int i=1;i<=n;i++)
            printf("%d%c",ans[i]," \n"[i==n]);
    }
}
/*
3
5
2 1
3 2
4 2
5 4
3 4
6
2 1
3 1
4 3
5 3
6 3
6 5
16
1 2
2 3
1 3
2 6
2 7
3 4
3 5
1 8
8 9
8 13
9 10 
10 11
11 12
13 14
14 15
15 16
*/