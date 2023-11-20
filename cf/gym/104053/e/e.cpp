#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=500005;
int n,m;
int a[N];
struct Segment_Tree
{
    #define ls i*2
    #define rs i*2+1
    struct Node
    {
        int l,r;
        long long sum;
        int cnt;
    }tree[N*4];
    void push_up(int i)
    {
        tree[i].cnt=tree[ls].cnt+tree[rs].cnt;
        tree[i].sum=tree[ls].sum+tree[rs].sum;
        return;
    }
    void build(int i,int l,int r)
    {
        tree[i].l=l,tree[i].r=r;
        if(l==r)
        {
            tree[i].sum=0;
            tree[i].cnt=0;
            return;
        }
        int mid=(l+r)/2;
        build(ls,l,mid);
        build(rs,mid+1,r);
        push_up(i);
        return;
    }
    void modify(int i,int u,long long v)
    {
        if(tree[i].l==tree[i].r)
        {
            tree[i].sum=v;
            tree[i].cnt=1;
            return;
        }
        if(u<=tree[ls].r) modify(ls,u,v);
        else modify(rs,u,v);
        push_up(i);
        return;
    }
    int query_cnt(int i,int l,int r)
    {
        if(l<=tree[i].l&&tree[i].r<=r) return tree[i].cnt;
        int res=0;
        if(l<=tree[ls].r) res+=query_cnt(ls,l,r);
        if(r>=tree[rs].l) res+=query_cnt(rs,l,r);
        return res;
    }
    long long query_sum(int i,int l,int r)
    {
        if(l<=tree[i].l&&tree[i].r<=r) return tree[i].sum;
        long long res=0;
        if(l<=tree[ls].r) res+=query_sum(ls,l,r);
        if(r>=tree[rs].l) res+=query_sum(rs,l,r);
        return res;
    }
}T;
int ans[N];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr),cout.tie(nullptr);
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    T.build(1,1,n);
    static int id[N];
    for(int i=1;i<=n;i++)
        id[i]=i;
    sort(id+1,id+n+1,[=](const int &x,const int &y){return a[x]!=a[y]?a[x]<a[y]:x<y;});
    for(int i=1;i<=n;i++)
    {
        int u=id[i];
        long long sum=(long long)T.query_cnt(1,1,n)*a[u]-T.query_sum(1,1,n)+T.query_cnt(1,1,u);
        T.modify(1,u,a[u]);
        if(sum>=m) ans[u]=-1;
        else ans[u]=sum;
    }
    for(int i=1;i<=n;i++)
        cout<<ans[i]<<"\n";
    return 0;
}