#include <bits/stdc++.h>
using namespace std;
int tot=0;
struct edge
{
    int x,y,z;
}E[410];
int a[410],d[410];
vector< pair<int,int> > V[410];
int Calc(int x)
{
    int res=0;
    for (;x>0;x>>=1) res++;
    return res;
}
void Add_Edge(int x,int y,int z)
{
    E[++tot]={x,y,z};
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int L,R;
    cin>>L>>R;
    int n=Calc(R),m=Calc(L);
    int num=20;
    // for (int i=2;i<=num;i++)
    //   Add_Edge(i,i-1,0),Add_Edge(i,i-1,1);
    //s:1 t:2
    int S=++num,T=0;
    
    // Add_Edge(1,T,0);Add_Edge(1,T,1);
    int Max=0;
    if (m+1<n) {
        for (int i=m+1;i<n;i++) 
            Add_Edge(S,i-1,1),Max=max(Max,i-1);
    }
    if (m<n) {
        int p=S;
        if (m>1) Add_Edge(p,++num,1);
          else Add_Edge(p,T,1);
        p=num;
        for (int i=m-1;i>=1;i--) {
            int c=(L>>(i-1)&1);
            if (!c) Add_Edge(p,i-1,1),Max=max(Max,i-1); 
            if (i>1) Add_Edge(p,++num,c);
              else Add_Edge(p,T,c);
            p=num;
        }
        p=S;Add_Edge(p,++num,1);p=num;
        for (int i=n-1;i>=1;i--) {
            int c=(R>>(i-1)&1);
            if (c) Add_Edge(p,i-1,0),Max=max(Max,i-1);
            if (i>1) Add_Edge(p,++num,c);
              else Add_Edge(p,T,c);
            p=num;
        }
    }
    else {
        int k=0;
        int p=S;
        for (int i=m;i>=1;i--)
          if ((L>>(i-1)&1)!=(R>>(i-1)&1)) {
              k=i;
              break;
          }
          else {
              int c=(L>>(i-1)&1);
              if (i>1) Add_Edge(p,++num,c);
              else Add_Edge(p,T,c);
              p=num;
          }
        if (k) {
            if (k>1) Add_Edge(p,++num,0);
              else Add_Edge(p,T,0);
            int q=num;
            for (int i=k-1;i>=1;i--) {
                int c=(L>>(i-1)&1);
                if (!c) Add_Edge(q,i-1,1),Max=max(Max,i-1); 
                if (i>1) Add_Edge(q,++num,c);
                  else Add_Edge(q,T,c);
                q=num;       
            }
            if (k>1) Add_Edge(p,++num,1);
              else Add_Edge(p,T,1);
            q=num;
            for (int i=k-1;i>=1;i--) {
                int c=(R>>(i-1)&1);
                if (c) Add_Edge(q,i-1,0),Max=max(Max,i-1);
                if (i>1) Add_Edge(q,++num,c);
                  else Add_Edge(q,T,c);
                q=num;
            }
        }
    }
    for (int i=1;i<=Max;i++) Add_Edge(i,i-1,0),Add_Edge(i,i-1,1);
    num=0;
    for (int i=1;i<=tot;i++) {
        if (!a[E[i].x]) a[E[i].x]=++num;
        if (!a[E[i].y]) a[E[i].y]=++num;
        d[a[E[i].x]]++;
        V[a[E[i].x]].push_back(make_pair(a[E[i].y],E[i].z));
    }
    cout<<num<<'\n';
    for (int i=1;i<=num;i++) {
        cout<<V[i].size()<<' ';
        for (int j=0;j<(int)V[i].size();j++)
          cout<<V[i][j].first<<' '<<V[i][j].second<<' ';
        cout<<'\n';
    }
    return 0;
}