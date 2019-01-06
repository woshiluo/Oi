#include <cstdio>

const long long N=110;
const long long mod=1000000007;

long long n,m,k,t;
long long c[N][N],ct[N][N],ct1[N][N],f[N][N*N];

long long pow(long long a,long long b){
	if (b==0) return 1;
	long long tmp=pow(a,b/2);
	tmp=(tmp*tmp)%mod;
	if (b&1) tmp=(tmp*a)%mod;
	return tmp;
}

int main(){
	scanf("%lld%lld%lld",&n,&m,&k);
	c[0][0]=1;
	t=m/n;
	for(int i=1;i<=n;i++){
		c[i][0]=ct[i][0]=ct1[i][0]=1;	
		for(int j=1;j<=i;j++){
			c[i][j]=(c[i-1][j]+c[i-1][j-1])%mod;
			ct[i][j]=pow(c[i][j],t);
			ct1[i][j]=(ct[i][j]*c[i][j])%mod;
		}
	}
	f[0][0]=1;
	for(int i=0;i<n;i++){
		for(int j=0;j<=k;j++){
			if(j<=n*i){
				for(int x=0;x<=n;x++){
					if(i<(m%n)) f[i+1][j+x]=(f[i+1][j+x]+f[i][j]*ct1[n][x])%mod;
					else f[i+1][j+x]=(f[i+1][j+x]+f[i][j]*ct[n][x])%mod;
				}
			}
		}
	}
	printf("%lld",f[n][k]);
}
