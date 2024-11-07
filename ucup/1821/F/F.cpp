#include<bits/stdc++.h>
#define LL long long
using namespace std;
int n,m;
LL a[200010],sum[200010];
long double ans=1e9;
int main()
{
    cin.tie(0)->sync_with_stdio(false);
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    sort(a+1,a+1+n);
    for(int i=1;i<=n;i++)
        sum[i]=sum[i-1]+a[i];
    for(int i=1;i<=n;i++)
    for(int j=i+1;j<n;j++){
        LL A=sum[i],B=sum[j]-sum[i],C=sum[n]-sum[j];
        LL D=i,E=j-i,F=n-j;
        ans=min(ans,A*D+B*E+C*F+(long double)6*pow(A*A*B*B*C*C*D*D*E*E*F*F,1./6));
        cout<<i<<' '<<j<<' '<<ans<<' '<<A*D+B*E+C*F<<' '<<6*pow(A*A*B*B*C*C*D*D*E*E*F*F,1./6)<<endl;
    }
    cout<<sqrt(ans)<<endl;
}