#include<bits/stdc++.h>
using namespace std;
int n,a[100010],id[100010],fa[100010],vis[100010];
double p[100010],suma[100010],prodp[100010],mulp=1,ans=0;
int bel[100010];
vector<int>V[100010];
struct NODE
{
    int pos;double suma,prodp;
    bool operator<(const NODE&n2)const{
        return prodp*suma*(1-n2.prodp)<n2.prodp*n2.suma*(1-prodp);
    }
};
priority_queue<NODE>q;
int getfa(int x)
{return bel[x]==x?x:bel[x]=getfa(bel[x]);}
inline int read()
{
    int x=0,w=0;char ch=0;
    while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return w?-x:x;
}
int main()
{
    vis[0]=1;
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=n;i++)cin>>p[i];
    for(int i=2;i<=n;i++)cin>>fa[i];
    iota(bel+1,bel+1+n,1);
    for(int i=1;i<=n;i++){
        q.push((NODE){i,suma[i]=a[i],prodp[i]=p[i]});
        V[i].emplace_back(i);
    }
    while(!q.empty()){
        auto tmp=q.top();
        q.pop();
        if(suma[tmp.pos]!=tmp.suma||prodp[tmp.pos]!=tmp.prodp)
            continue;
        if(vis[fa[tmp.pos]]){
            
            ans+=mulp*p[tmp.pos]*tmp.suma;
            mulp*=tmp.prodp;
            for(auto x:V[tmp.pos])
                vis[x]=1;
        }else{
            int y=getfa(fa[tmp.pos]);
            prodp[y]*=tmp.prodp;
            suma[y]+=prodp[y]/p[y]*tmp.suma;
            bel[tmp.pos]=y;
            q.push((NODE){y,suma[y],prodp[y]});
            if(V[y].size()<V[tmp.pos].size())
                swap(V[y],V[tmp.pos]);
            V[y].insert(V[y].end(),V[tmp.pos].begin(),V[tmp.pos].end());
        }
    }
    printf("%.12lf\n",ans);
}
