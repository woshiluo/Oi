#include<bits/stdc++.h>
using namespace std;
int n,cnt,vis[2010],pre[2010];
long double ans=0;
vector<int>G[2010];
unordered_map<int,int>mp;
struct ABC
{
    int first,second;
    ABC operator-(ABC n2)
    {return{first-n2.first,second-n2.second};}
    int operator*(ABC n2)
    {return first*n2.second-n2.first*second;}
};
ABC p[2010],ZX;
int sgn(int x)
{
    if(x==0)return 0;
    if(x>0)return 1;
    return -1;
}

bool cmp(ABC n1,ABC n2)
{
    if(sgn(n1.second-ZX.second)!=sgn(n2.second-ZX.second))
        return sgn(n1.second-ZX.second)>sgn(n2.second-ZX.second);
    ABC x=(n1-ZX),y=n1-ZX;
    return x*y>0;
}
void dfs(int ST,int x,int last,int Sum,ABC dir,int tot)
{
    if(ST==x){
        ans+=Sum*Sum/4.0/tot;
        return;
    }
    for(int i=0,End=G[x].size();i<End;i++){
        if(G[x][i]==last){
            int j=(i+1)%End;
            if(dir*(p[G[x][j]]-p[x])<0)
                dfs(ST,G[x][j],x,Sum+p[G[x][j]]*p[x],p[G[x][j]]-p[x],tot+1);
            return;
        }
    }
}
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        int x1,x2,y1,y2,id1,id2;
        cin>>x1>>y1;
        if(!mp.count(x1*10000+y1))
            p[mp[x1*10000+y1]=++cnt]={x1,y1};
        if(!mp.count(x2*10000+y2))
            p[mp[x2*10000+y2]=++cnt]={x2,y2};
        id1=mp[x1*10000+y1];
        id2=mp[x2*10000+y2];
        G[id1].emplace_back(id2);
        G[id2].emplace_back(id1);
    }
    for(int i=1;i<=cnt;i++){
        ZX=p[i];
        sort(G[i].begin(),G[i].end(),cmp);
    }
    for(int x=1;x<=cnt;x++){
        for(int y:G[x]){
            dfs(x,y,x,p[y]*p[x],p[y]-p[x],1);
        }
    }
    printf("%.10Lf\n",ans);
}