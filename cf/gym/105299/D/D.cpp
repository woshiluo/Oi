#include<bits/stdc++.h>
using namespace std;
int n,q,root,cnt,a[100010],ans[100010],Lp[100010],Rp[100010],Pos[100010];
vector<int>G[100010];
struct Node
{int son[2],fa,val,size,flag;}tr[100010];
inline int read()
{
    int x=0,w=0;char ch=0;
    while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return w?-x:x;
}
void upd(int x)
{tr[x].size=tr[tr[x].son[0]].size+tr[tr[x].son[1]].size+1;}
void spread(int x)
{
    if(!tr[x].flag)return;
    swap(tr[x].son[0],tr[x].son[1]);
    tr[tr[x].son[0]].flag^=1;
    tr[tr[x].son[1]].flag^=1;
    tr[x].flag=0;
}
void rotate(int x)
{
    int y=tr[x].fa,z=tr[y].fa;
    int k=tr[y].son[1]==x;
    tr[z].son[tr[z].son[1]==y]=x;tr[x].fa=z;
    tr[tr[x].son[k^1]].fa=y;
    tr[y].son[k]=tr[x].son[k^1];
    tr[x].son[k^1]=y;tr[y].fa=x;
    upd(y);upd(x);
}
void splay(int x,int k)
{
    while(tr[x].fa^k){
        int y=tr[x].fa,z=tr[y].fa;
        if(z^k){
            if((tr[z].son[1]==y)^(tr[y].son[1]==x))
                rotate(x);
            else rotate(y);
        }
        rotate(x);
    }
    if(!k)root=x;
}
void insert(int val)
{
    int x=root,y=0;
    while(x)
        y=x,x=tr[x].son[val>tr[x].val];
    x=++cnt;
    if(y)tr[y].son[val>tr[y].val]=x;
    tr[x].fa=y;tr[x].val=val;tr[x].size=1;
    splay(x,0);
}
int getkth(int k)
{
    int x=root;
    while(x){
        spread(x);
        if(tr[tr[x].son[0]].size>=k)x=tr[x].son[0];
        else if(tr[tr[x].son[0]].size+1==k)return x;
        else k-=tr[tr[x].son[0]].size+1,x=tr[x].son[1];
    }
    return -1;
}
void reverse(int l,int r)
{
    int L=getkth(l),R=getkth(r+2);
    splay(L,0);splay(R,L);
    tr[tr[R].son[0]].flag^=1;
}
void dfs(int x)
{
    reverse(Lp[x],Rp[x]);
    ans[x]=getkth(Pos[x]);
    for(int y:G[x])dfs(y);
    reverse(Lp[x],Rp[x]);
}
int main()
{
    n=read();q=read();
    for(int i=1;i<=n;i++)
        a[i]=read();
    for(int i=0;i<=n+1;i++)
        insert(i);
    Lp[0]=Rp[0]=1;
    for(int i=1;i<=q;i++){
        int fa=read(),L=read()+1,R=read()+1,P=read()+2;
        G[fa].emplace_back(i);
        Lp[i]=L;Rp[i]=R;Pos[i]=P;
    }
    dfs(0);
    for(int i=1;i<=q;i++)
        printf("%d\n",a[ans[i]-1]);
}
