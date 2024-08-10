#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int mod=1000000007;
int n,m,N;
struct MATRIX
{
    LL data[110][110];
    MATRIX(int flag=0){memset(data,0,sizeof data);for(int i=1;i<=N;i++)data[i][i]=flag;}
    MATRIX operator*(const MATRIX&n2)const{
        MATRIX n3;
        for(int i=1;i<=N;i++)
        for(int j=1;j<=N;j++)
        for(int k=1;k<=N;k++)
            (n3.data[i][j]+=data[i][k]*n2.data[k][j])%=mod;
        return n3;
    }
    MATRIX ksm(LL K){
        MATRIX A(1),B=*this;
        for(;K;K>>=1,B=B*B)
        if(K&1)A=A*B;
        return A;
    }
}F1,F2,F3;
inline int read()
{
    int x=0,w=0;char ch=0;
    while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return w?-x:x;
}
int main()
{
    LL T=read(),L,R,Lp,Rp,ans;
    while(T --> 0){
        N=n=read();m=read();cin>>L>>R;ans=0;
        //assert(n!=1);
        memset(F1.data,0,sizeof F1.data);
        memset(F2.data,0,sizeof F2.data);
        memset(F3.data,0,sizeof F3.data);
        for(int i=1;i<=m;i++){
            int x=read(),y=read(),z=read();
            if(y<=n)(F1.data[x][y]+=z)%=mod;
            else(F2.data[x][y-n]+=z)%=mod;
        }
        for(int i=1;i<=n;i++)F1.data[i][i]++;
        Rp=R-R%n;
        Lp=L-L%n+1;
        if(Lp<L)Lp+=n;
        // cout<<L<<' '<<R<<' '<<Lp<<' '<<Rp<<'\n';
        MATRIX TEMP;TEMP.data[1][1]=1;
        TEMP=TEMP*F1;
        if(Lp/n-1>0)
            TEMP=TEMP*((F2*F1).ksm(Lp/n-1));
        for(int i=L;i<min(Lp,R+1);i++)
            (ans+=TEMP.data[1][(i-1)%n+1])%=mod;
        // cout<<"CHECK1\n";
        // cout<<ans<<'\n';
        if(Lp>R){
            // cout<<"FUCK1\n";
            cout<<ans<<'\n';
            continue;
        }
        TEMP=TEMP*((F2*F1).ksm((Rp-Lp+1)/n+1));
        for(int i=max(Rp+1,L);i<=R;i++)
            (ans+=TEMP.data[1][(i-1)%n+1])%=mod;
        // cout<<"CHECK2\n";/
        // cout<<ans<<'\n';
        if(Lp>Rp){
            // cout<<"FUCK2\n";
            cout<<ans<<'\n';
            continue;
        }
        memset(TEMP.data,0,sizeof TEMP.data);
        TEMP.data[1][1]=1;
        TEMP=TEMP*F1;
        //TEMP=TEMP*((F2*F1).ksm(Lp/n));
        N++;
        for(int i=1;i<=N;i++)F3.data[i][i]=1;
        for(int i=1;i<N;i++)F3.data[i][N]=1;
        F1.data[N][N]=F2.data[N][N]=1;
        TEMP=TEMP*((F2*F1).ksm(Lp/n));
        for(int i=Lp;i<Lp+n;i++){
            (ans+=TEMP.data[1][(i-1)%n+1])%=mod;
            // cout << "fuck" <<i<<' '<<TEMP.data[1][(i-1)%n+1]<< endl;
        }
        // cout<<"CHECK3\n";
        // cout<<ans<<'\n';
        TEMP=TEMP*(((F2*F1)*F3)).ksm((Rp-Lp)/n);
        if((Rp-Lp)/n)
            (ans+=TEMP.data[1][N])%=mod;
        // cout<<"CHECK4\n";
        // cout<<ans<<'\n';
        // cout<<"FUCK3\n";
        cout<<ans<<'\n';
    }
}
/*
1
3 4 2 13
1 2 1
1 3 1
3 4 2
2 5 1
*//*
1
5 8 998244353 1000000007
1 2 114514
1 4 1919810
2 3 999999999
3 5 111111111
4 5 1000000000
1 10 123456789
5 6 987654321
3 9 888888888
*/