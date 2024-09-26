#include<bits/stdc++.h>
using namespace std;
int n,id[200010],a[200010];
long long ans=0;
set<int>s;
inline int read()
{
    int x=0,w=0;char ch=0;
    while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return w?-x:x;
}
int cmp(int n1,int n2)
{return a[n1]>a[n2];}
int main()
{
    int T=read();
    while(T --> 0){
        n=read();ans=0;
        s.clear();
        s.insert(0);
        s.insert(n+1);
        for(int i=1;i<=n;i++)
            a[id[i]=i]=read();
        a[0]=a[n+1]=-1;
        sort(id+1,id+1+n,cmp);
        int Last=1;
        for(int i=2;i<=n;i++){
            if(a[id[i]]!=a[id[i-1]]){
                for(int j=Last;j<i;j++)
                s.insert(id[j]);
                for(int j=Last;j<i;j++){
                    auto it=s.lower_bound(id[j]);
                    int L=*(--it)+1,R;
                    it=s.upper_bound(id[j]);
                    if(a[*it]==a[id[j]])R=id[j];
                    else R=*it-1;
                    ans+=R-L;
                }
                Last=i;
            }
        }
        for(int j=Last;j<=n;j++)
            s.insert(id[j]);
        for(int j=Last;j<=n;j++){
            auto it=s.lower_bound(id[j]);
            int L=*(--it)+1,R;
            it=s.upper_bound(id[j]);
            if(a[*it]==a[id[j]])R=id[j];
            else R=*it-1;
            ans+=R-L;
        }
        printf("%lld\n",ans);
    }
}