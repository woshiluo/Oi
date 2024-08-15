#include <bits/stdc++.h>
using namespace std;
int n,m,r0;
double K;
int main()
{
    int T=5;
    srand(time(0));
    freopen("in.txt","w",stdout);
    cout<<T<<'\n';
    while(T --> 0){
        n=rand()%1000+1;m=rand()%n+1;r0=rand()%100000+1;
        K=1.0*(rand()%9000+1001)/10000;
        cout<<n<<' '<<m<<' '<<endl;
        cout<<fixed<<setprecision(15)<<K<<'\n';
        cout<<r0<<'\n';
        for(int i=1;i<=n;i++)
            cout<<rand()%100000+1<<" \n"[i==n];
    }
}