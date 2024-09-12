#include <bits/stdc++.h>
using namespace std;
const int Mod=998244353,N=510;
int a[20],b[20],c[500],num,id[100010],cnt[500],inv[10],nn;
int sum[500];
bool vis[20],vis1[20];
int n,K;
struct Matrix {
    int m[N][N];
    int len;
    Matrix(int cur,int _len) {
        len=_len;
        memset( m, 0, sizeof(m) );
        if( cur == 0 ) 
            return ;
        for( int i = 1; i <= len; i ++ ) 
            m[i][i] = cur;
    }
    Matrix operator* ( const Matrix &_b ) const {
        Matrix res(0,len);
        for( int i = 1; i <=len; i ++ ) {
            for( int j = 1; j <= len;j ++ ) {
                for( int k = 1; k <=len; k ++ ) {
                    res.m[i][j] += 1LL*m[i][k] * _b.m[k][j]%Mod,res.m[i][j]%=Mod;
                }
            }
        }
        return res;
    }
};
Matrix ksm_Matrix(Matrix A)
{
    Matrix res(1,A.len);
    for (;K;K>>=1) {
        if (K&1) res=res*A;
        A=A*A;
    }
    return res;
}
int ksm(int aa,int bb) 
{
    int res=1;
    for (;bb;bb>>=1) {
        if (bb&1) res=1LL*res*aa%Mod;
        aa=1LL*aa*aa%Mod;
    }
    return res;
}
int Calc(int s,int k)
{
    if (s>>k&1) return id[s-(1<<k)];
    else {
        int tmp=0;
        bool fla=false;
        int x=k/n,y=k%n;
        for (int i=0;i<nn;i++)
          if (s>>i&1) {
              if (i/n==x||i%n==y) fla=true;
              else tmp+=(1<<i);
          }
        if (!fla) tmp+=(1<<k);
        return id[tmp];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>K;nn=n*n;
    int t=0;
    for (int i=1;i<=n;i++)
      for (int j=1;j<=n;j++)
        cin>>a[(i-1)*n+j-1],t=(t+a[(i-1)*n+j-1])%Mod;
    for (int i=1;i<=n;i++)
      for (int j=1;j<=n;j++)
        cin>>b[(i-1)*n+j-1];
    for (int i=0;i<=n;i++) inv[i]=ksm(t-i,Mod-2);
    for (int i=0;i<(1<<nn);i++) {
        for (int j=0;j<n;j++) vis[j]=vis1[j]=false;
        bool fla=true;
        int s=0,ss=0;
        for (int j=0;j<nn;j++)
          if (i>>j&1) {
              s++;ss+=b[j];ss%=Mod;
              int x=j/n,y=j%n;
              if (vis[x]||vis1[y]) {fla=false;break;} 
              vis[x]=true;vis1[y]=true;
          }
        if (!fla) continue;
        c[++num]=i;cnt[num]=s;sum[num]=ss;
        id[i]=num;
    }
    // cout<<num<<'\n';
    Matrix tr(0,num+1);
    for (int i=1;i<=num;i++) {
        for (int j=0;j<nn;j++) {
            int k=Calc(c[i],j);
            if (c[i]>>j&1) tr.m[i][k]+=1LL*inv[cnt[i]]*(a[j]-1+Mod)%Mod;
              else tr.m[i][k]+=1LL*inv[cnt[i]]*a[j]%Mod;
            tr.m[i][k]%=Mod;
        }
    }
    for (int i=1;i<=num;i++)
      tr.m[i][num+1]=sum[i];
    tr.m[num+1][num+1]=1;
    Matrix res=ksm_Matrix(tr);
    int ans=res.m[1][num+1];
    for (int i=1;i<=num;i++)
      ans+=1LL*res.m[1][i]*sum[i]%Mod,ans%=Mod;
    cout<<ans;
    return 0;
}