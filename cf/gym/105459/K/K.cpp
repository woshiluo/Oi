#include<bits/stdc++.h>
using namespace std;
int n;
pair<int,pair<int,int>>p[100010];
long long lsuml[100010],rsuml[100010];
long long lsumlw[100010],rsumlw[100010];
long long lsumr[100010],lsumrw[100010];
long long m,ans;
int main()
{
    cin.tie(0)->sync_with_stdio(false);
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        int w,l,r;
        cin>>w>>l>>r;
        p[i]={w,{l,r}};
    }
    sort(p+1,p+1+n);
    reverse(p+1,p+1+n);
    for(int i=1;i<=n;i++){
        lsuml[i]=lsuml[i-1]+p[i].second.first;
        lsumlw[i]=lsumlw[i-1]+1ll*p[i].second.first*p[i].first;
        lsumr[i]=lsumr[i-1]+p[i].second.second-p[i].second.first;
        lsumrw[i]=lsumrw[i-1]+1ll*p[i].first*(p[i].second.second-p[i].second.first);
    }
    for(int i=n;i;i--){
        rsuml[i]=rsuml[i+1]+p[i].second.first;
        rsumlw[i]=rsumlw[i+1]+1ll*p[i].second.first*p[i].first;
    }
    for(int i=1;i<=n;i++){
        long long lst=m-(lsuml[i-1]+rsuml[i+1]);
        if(lsumr[i-1]>=lst){
            int L=1,R=i-1,M,T=0;
            while(L<=R){
                M=(L+R)>>1;
                if(lsumr[M]<=lst)
                    T=M,L=M+1;
                else R=M-1;
            }
            ans=max(ans,rsumlw[i+1]+lsumlw[i-1]+lsumrw[T]+(lst-lsumr[T])*p[T+1].first);
        }else
            ans=max(ans,lsumlw[i-1]+lsumrw[i-1]+rsumlw[i+1]+(lst-lsumr[i-1])*p[i].first);
    }
    cout<<ans<<endl;
}