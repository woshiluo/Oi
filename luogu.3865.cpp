#include <cstdio>
#include <math.h>

inline int Max(int a,int b){return a>b?a:b;}

const int N=110000;

int n,m,l,r;
int a[N];
int f[N][20];

int main(){
	freopen("luogu.3865.in","r",stdin);
	freopen("luogu.3865.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&f[i][0]);
//		f[i][0]=a[i];
	}
	for(int j=1;j<=21;j++){
		for(int i=1;i+(1<<j)-1<=n;i++){
			f[i][j]=Max(f[i][j-1],f[i+(1<<(j-1))][j-1]);	
		}
	}
	for(int i=1;i<=m;i++){
		scanf("%d%d",&l,&r);
		int k=(int)(log(r-l+1)/log(2));
		printf("%d\n",Max(f[l][k],f[r-(1<<k)+1][k]));
	}
	fclose(stdin);
	fclose(stdout);
}
