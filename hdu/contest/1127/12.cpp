#include <bits/stdc++.h>
using namespace std;
int n,m,a[900010],v[900010],b[900010];
long long c[300010],f[900010],g[900010],ans[300010];
vector<int> V[300010];
struct quu
{
    int X,Y,X1,Y1,id;
}qu[300010];
void Add(int x,long long v)
{   
    x++;
    for (;x<=n+2;x+=x&(-x)) c[x]=max(c[x],v);
    return; 
}
long long Get(int x)
{
    x++;
    if (x<=0) return 0;
    long long res=0;
    for (;x;x-=x&(-x)) res=max(res,c[x]);
    return res;
}
bool cmp(quu p1,quu p2) 
{
    return p1.X<p2.X;
}
bool cmp1(quu p1,quu p2) 
{
    return p1.X1<p2.X1;
}
bool cmp2(int p1,int p2)
{
    return a[p1]<a[p2];
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin>>T;
    while (T--) {
        cin>>n>>m;
        for (int i=0;i<=n+1;i++) V[i].clear();
        int num=0;
        for (int i=1;i<=n;i++) {
            int x,y;
            cin>>x>>y;
            ++num;
            a[num]=x;b[num]=i;v[num]=y;
            V[i].push_back(num);
        }
        for (int i=1;i<=m;i++) {
            cin>>qu[i].X>>qu[i].Y>>qu[i].X1>>qu[i].Y1;
            ++num;
            b[num]=qu[i].X-1;a[num]=qu[i].Y1+1;v[num]=0;
            V[qu[i].X-1].push_back(num);
            ++num;
            b[num]=qu[i].X1+1;a[num]=qu[i].Y-1;v[num]=0;
            V[qu[i].X1+1].push_back(num);
            qu[i].id=i;
        }
        for (int i=0;i<=n+1;i++) sort(V[i].begin(),V[i].end(),cmp2);
        for (int i=1;i<=n+2;i++) c[i]=0;
        for (int i=0;i<=n+1;i++) {
            for (int j=0;j<(int)V[i].size();j++) {
                int x=V[i][j];
                long long res=Get(a[x]);
                f[x]=res+v[x];
                // cout<<x<<' '<<f[x]<<endl;
                Add(a[x],f[x]);
            }
        }
        for (int i=1;i<=n+2;i++) c[i]=0;
        for (int i=n+1;i>=0;i--) {
            for (int j=(int)V[i].size()-1;j>=0;j--) {
                int x=V[i][j];
                long long res=Get(n+1-a[x]);
                g[x]=res+v[x];
                Add(n+1-a[x],g[x]);
                // cout<<x<<' '<<i<<' '<<a[x]<<' '<<g[x]<<endl;
            }
        }
        sort(qu+1,qu+m+1,cmp);
        for (int i=1;i<=n+2;i++) c[i]=0; 
        int p=-1;
        for (int i=1;i<=m;i++) {
            while (p+1<qu[i].X) {
                p++;
                for (int j=0;j<(int)V[p].size();j++) {
                    int x=V[p][j];
                    Add(n+1-a[x],f[x]+g[x]-v[x]);
                }
            }
            long long res=Get(n+1-(qu[i].Y1+1));
            ans[qu[i].id]=res;
        }
        for (int i=1;i<=n+2;i++) c[i]=0;
        p=n+2;
        sort(qu+1,qu+m+1,cmp1);
        for (int i=m;i>=1;i--) {
            while (p-1>qu[i].X1) {
                p--;
                for (int j=0;j<(int)V[p].size();j++) {
                    int x=V[p][j];
                    Add(a[x],f[x]+g[x]-v[x]);
                }
            }
            long long res=Get(qu[i].Y-1);
            ans[qu[i].id]=max(ans[qu[i].id],res);
        }
        for (int i=1;i<=m;i++)
          cout<<ans[i]<<'\n';
    }
    return 0;
}