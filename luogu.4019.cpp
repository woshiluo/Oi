#include <cstdio>
#include <cstring>

const long long N=51000;
const long long mod=987654321;

inline long long Max(long long a,long long b){return a>b?a:b;}

long long n,m,c,op,x,y;
long long f[N][20],sum,ans;
bool vis[N],col[N][60];

int main(){
	scanf("%lld%lld%lld",&n,&m,&c);	
	for(long long i=1;i<=m;i++){
		scanf("%lld%lld%lld",&op,&x,&y);
		if(op==1){
			for(long long j=1;j<=c;j++){
				if(j==y) continue;
				col[x][j]=1;
			}
		}
		else if(op==2) col[x][y]=1;
		else if(op==3) vis[Max(x,y)]=1;
	}

// dp
	for(long long o=1;o<=c;o++){
		memset(f,0,sizeof(f));
		if(col[1][o]) continue;
		f[1][o]=1;	
		for(long long i=2;i<=n;i++){
			if(vis[i]){
				for(long long j=1;j<=c;j++) if(col[i][j]!=1) f[i][j]=f[i-1][j];
				continue;
			}		
			else {
				sum=0;
				for(long long j=1;j<=c;j++) sum=(sum+f[i-1][j])%mod;		
				for(long long j=1;j<=c;j++) if(col[i][j]!=1) f[i][j]=(sum-f[i-1][j]+mod)%mod;
			}
		}
		sum=0;
		for(long long j=1;j<=c;j++) sum=(sum+f[n][j])%mod;		
		ans=(ans+sum-f[n][o]+mod)%mod;	
	}
	printf("%lld",ans);
}
