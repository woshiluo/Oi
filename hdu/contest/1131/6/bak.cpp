#include<bits/stdc++.h>
#define LL long long
using namespace std;
int n,m,X[300010],Y[300010],ans[300010],fa[100010];
int E[100010];
struct SegmentTree
{int l,r,data,pos;}st[400010];
set<int>s[100010];
inline int read()
{
    int x=0,w=0;char ch=0;
    while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return w?-x:x;
}
void upd(int p)
{
    if(st[p<<1].data>st[p<<1|1].data)
        st[p].data=st[p<<1|1].data,st[p].pos=st[p<<1|1].pos;
    else st[p].data=st[p<<1].data,st[p].pos=st[p<<1].pos;
}
void build(int p,int l,int r)
{
    st[p].l=l;st[p].r=r;
    if(l==r){
        st[p].pos=l;
        if(s[l].size())
            st[p].data=*s[l].begin();
        else st[p].data=1e9;
        return;
    }
    int mid=(l+r)>>1;
    build(p<<1,l,mid);
    build(p<<1|1,mid+1,r);
    upd(p);
}
void change(int p,int pos,int val)
{
    if(st[p].l==st[p].r)
        return st[p].data=val,void();
    int mid=(st[p].l+st[p].r)>>1;
    change(p<<1|(pos>mid),pos,val);
    upd(p);
}
int getfa(int x)
{return fa[x]==x?x:fa[x]=getfa(fa[x]);}
void merge(int x,int y)
{
    x=getfa(x);y=getfa(y);
    if(x^y)fa[x]=y;
}
int main()
{
    int T=read();
    while(T --> 0){
        n=read();m=read();
        for(int i=1;i<=n;i++)s[i].clear();
        for(int i=1;i<=m;i++){
            s[X[i]=read()].insert(i);
            s[Y[i]=read()].insert(i);
        }
        memset(ans,-1,sizeof(int)*(m+5));
        for(int abc=1;;abc++){
            build(1,1,n);E[0]=0;
            if(st[1].data>m)break;
            int Node=st[1].pos;
            if(!s[Node].size())break;
            iota(fa+1,fa+1+n,1);
            int iD=*s[Node].begin();
            s[X[iD]].erase(iD);
            s[Y[iD]].erase(iD);
            merge(X[iD],Y[iD]);
            E[++E[0]]=iD;
            change(1,X[iD],1e9);
            change(1,Y[iD],1e9);
            for(int i=3;i<=n;i++){
                if(st[1].data>m)break;
                Node=st[1].pos;
                if(!s[Node].size())break;
                iD=*s[Node].begin();
                s[X[iD]].erase(iD);
                s[Y[iD]].erase(iD);
                E[++E[0]]=iD;
                merge(X[iD],Y[iD]);
                change(1,X[iD],1e9);
                change(1,Y[iD],1e9);
            }
            int cnt=0;
            for(int i=1;i<=n;i++)
            if(getfa(i)==i)cnt++;
            if(cnt!=1)break;
            if(E[0]==n-1){
                for(int i=1;i<n;i++)
                    ans[E[i]]=abc;
            }else break;
        }
        for(int i=1;i<=m;i++)
            printf("%d%c",ans[i]," \n"[i==m]);
    }
}