#include<bits/stdc++.h>
using namespace std;
int n,K,a[1100010],pos[1100000],ans[1100000],npos[1100000],End;
int c[1100000];
struct SetmentTree
{int l,r;}st[4400010];
inline int read()
{
    int x=0;char ch=0,w=0;
    while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return w?-x:x;
}
void build(int p,int l,int r)
{
    st[p].l=l;st[p].r=r;
    if(l==r)return npos[l]=p,void();
    int mid=(l+r)>>1;
    build(p<<1,l,mid);
    build(p<<1|1,mid+1,r);
}
void change(int x,int y)
{
    for(;x<=End;x+=x&-x)
        c[x]+=y;
}
int ask(int p,int l,int r,int y=0)
{
    if(l>r)return 0;
    l--;
    for(;r;r-=r&-r)
        y+=c[r];
    for(;l;l-=l&-l)
        y-=c[l];
    return y;
}
int calc(int p)
{
    int temp=0;
    p=p>>1;
    while(p){
        int cnt=ask(1,st[p].l,st[p].r);
        // cout<<cnt<<' ';
        if(cnt>K)break;
        int tot=(st[p].l-1-1+1+End-st[p].r)-(ask(1,1,st[p].l-1)+ask(1,st[p].r+1,End));
        // cout<<tot<<' ';
        // cout<<"(,"<<(st[p].l-1-1+1+End-st[p].r)<<' '<<(ask(1,1,st[p].l-1)+ask(1,st[p].r+1,End))<<")";
        // cout<<"(,"<<st[p].l<<' '<<st[p].r<<") ";
        if(tot<cnt)break;
        temp++;
        p=p>>1;
    }
    // cout<<temp<<endl;
    return temp;
}
int main()
{
    n=read();K=read();End=1<<n;
    for(int i=1;i<=End;i++)
        pos[a[i]=read()]=i;
    build(1,1,1<<n);
    for(int i=1<<n;i;i--){
        ans[pos[i]]=calc(npos[pos[i]]);
        change(pos[i],1);
        // for(int j=1;j<=End;j++)
        //     cout<<ask(1,j,j)<<" \n"[j==End];
    }
    for(int i=1;i<=End;i++)
        printf("%d%c",ans[i]," \n"[i==End]);
}