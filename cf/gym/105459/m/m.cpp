#include<bits/stdc++.h>
using namespace std;
int a[100010];
long long sum;
int main()
{
    // cin.tie(0)->sync_with_stdio(false);
    int T;cin>>T;
    while(T --> 0){
        int n;cin>>n;
        a[0]=0;sum=0;
        for(int i=1;i*i<=n;i++)
        if(n%i==0){
            a[++a[0]]=i;
            if(i*i!=n)
                a[++a[0]]=n/i;
        }
        sort(a+1,a+1+a[0]);
        for(int i=2;i<=a[0];i++)
        sum=sum+1ll*(n/a[i-1])*(a[i]-a[i-1]);
        sum+=1;
        cout<<sum<<endl;
    }
}