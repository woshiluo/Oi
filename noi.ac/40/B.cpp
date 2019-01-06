#include <cstdio>

inline int Max(int a,int b){return a>b?a:b;}

const int N=11000;
const int M=20;
const int mod=1000000007;

int n,k,m,ans;
int a[M][N];
int sum[M][N];

int main(){
	scanf("%d%d%d",&n,&k,&m);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			scanf("%d",&a[j][i]);	
		}
	}
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			sum[i][j]=sum[i][j-1]+a[i][j-1];
			a[i][j]+=sum[i-1][Max(j,0)]-sum[i-1][Max(j-k,0)];
			//printf("%2d ",a[i][j]);
			if(i==m) ans=Max(ans,a[i][j]);
		}
		printf("\n");
	}
	printf("%d",ans);
}
