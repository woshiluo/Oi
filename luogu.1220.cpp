#include <cstdio>
#include <cstring>
using namespace std;

inline int Min(int a,int b){return a<b?a:b;}

const int N=110;

struct light{
	int pow,dis;
}lgt[N];

int f[N][N][2];
// 0 left
// 1 rig
int sum[N];
int n,r,c;

int main(){
	scanf("%d%d",&n,&c);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&lgt[i].dis,&lgt[i].pow);	
		sum[i]=sum[i-1]+lgt[i].pow;
	}
	memset(f,0x3f,sizeof(f));
	f[c][c][0]=f[c][c][1]=0;
	for(int i=1;i<n;i++){
		for(int l=1;l<=n-i;l++){
			r=l+i;
			f[l][r][0]=Min(f[l+1][r][0]+(lgt[l+1].dis-lgt[l].dis)*(sum[n]-sum[r]+sum[l]),f[l+1][r][1]+(lgt[r].dis-lgt[l].dis)*(sum[n]-sum[r]+sum[l]));
			f[l][r][1]=Min(f[l][r-1][1]+(lgt[r].dis-lgt[r-1].dis)*(sum[n]-sum[r-1]+sum[l-1]),f[l][r-1][0]+(lgt[r].dis-lgt[l].dis)*(sum[n]-sum[r-1]+sum[l-1]));
		}
	}
	printf("%d",Min(f[1][n][1],f[1][n][0]));
}
