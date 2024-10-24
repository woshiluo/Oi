#include<bits/stdc++.h>
#define Graph(x)for(int i=last[x],y=edge[i].ver;i;i=edge[i].next,y=edge[i].ver)
using namespace std;
int tot,n,A[1000010],B[1000010],C[1000010],lsh[300010],cnt,dfs_clock,st[2000010],top,idcnt;
int last[2000010],low[2000010],dfn[2000010],id[2000010],vis[2000010],num;
vector<int>NUM[300010],Lp[300010],Rp[300010];
struct EDGE
{int ver,next;}edge[4000010];
inline int read()
{
    int x=0,w=0;char ch=0;
    while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return w?-x:x;
}
void add(int X,int Y)
{
    // cout<<X<<' '<<Y<<'\n';
    edge[++num]=(EDGE){Y,last[X]};last[X]=num;
}
void tarjan(int x)
{
    dfn[st[++top]=x]=low[vis[x]=x]=++dfs_clock;
    Graph(x)if(!dfn[y]){
        tarjan(y);
        low[x]=min(low[x],low[y]);
    }else if(vis[y])
        low[x]=min(low[x],dfn[y]);
    if(low[x]==dfn[x]){
        int y;idcnt++;
        do{
            vis[y=st[top--]]=0;
            id[y]=idcnt;
        }while(x^y);
    }
}
int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        lsh[++cnt]=A[i]=read();
        lsh[++cnt]=B[i]=read();
        lsh[++cnt]=C[i]=read();
        if(B[i]==C[i])add(i+n,i);
    }
    sort(lsh+1,lsh+1+cnt);
    cnt=unique(lsh+1,lsh+1+cnt)-lsh-1;
    for(int i=1;i<=n;i++){
        A[i]=lower_bound(lsh+1,lsh+1+cnt,A[i])-lsh;
        B[i]=lower_bound(lsh+1,lsh+1+cnt,B[i])-lsh;
        C[i]=lower_bound(lsh+1,lsh+1+cnt,C[i])-lsh;
        NUM[A[i]].emplace_back(i);
        NUM[C[i]].emplace_back(i);
        NUM[B[i]].emplace_back(i);
    }
    // cout<<"ABC\n";
    tot=n*2;
    for(int i=1;i<=cnt;i++){
        sort(NUM[i].begin(),NUM[i].end());
        NUM[i].erase(unique(NUM[i].begin(),NUM[i].end()),NUM[i].end());
        for(int j=0,End=NUM[i].size();j<End;j++){
            Lp[i].push_back(++tot);
            if(j)add(tot,tot-1);
        }
        for(int j=0,End=NUM[i].size();j<End;j++)Rp[i].push_back(++tot);
        for(int j=NUM[i].size()-1;j>=0;j--){
            if(j!=NUM[i].size()-1)
                add(Rp[i][j],Rp[i][j+1]);
        }
    }
    for(int i=1;i<=n;i++){
        int pos=lower_bound(NUM[A[i]].begin(),NUM[A[i]].end(),i)-NUM[A[i]].begin();
        add(Lp[A[i]][pos],i+n);add(Rp[A[i]][pos],i+n);
        if(pos)add(i,Lp[A[i]][pos-1]);
        if(pos<Rp[A[i]].size()-1)add(i,Rp[A[i]][pos+1]);
        pos=lower_bound(NUM[B[i]].begin(),NUM[B[i]].end(),i)-NUM[B[i]].begin();
        add(Lp[B[i]][pos],i);add(Rp[B[i]][pos],i);
        if(pos)add(i+n,Lp[B[i]][pos-1]);
        if(pos<Rp[B[i]].size()-1)add(i+n,Rp[B[i]][pos+1]);
        pos=lower_bound(NUM[C[i]].begin(),NUM[C[i]].end(),i)-NUM[C[i]].begin();
        add(Lp[C[i]][pos],i);add(Rp[C[i]][pos],i);
        if(pos)add(i+n,Lp[C[i]][pos-1]);
        if(pos<Rp[C[i]].size()-1)add(i+n,Rp[C[i]][pos+1]);
    }
    // cout<<tot<<endl;
    for(int i=1;i<=tot;i++)
    if(!dfn[i])tarjan(i);
    for(int i=1;i<=n;i++)
    if(id[i]==id[i+n])
        return printf("NO\n"),0;
    printf("YES\n");
    for(int i=1;i<=n;i++)
    if(id[i]<id[i+n])
        printf("1 0 0\n");
    else printf("0 1 1\n");
}